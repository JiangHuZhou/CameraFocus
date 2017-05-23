#include "Threadworker.h"
#include "Focusmeasure.h"
#include "hillclimbsearch.h"

ThreadWorker::ThreadWorker(QObject *parent) : QObject(parent)
{

}

void ThreadWorker::grub()
{
    CameraDialog *dialog = (CameraDialog *)QThread::currentThread()->parent();

    x_pCamera = dialog->pCamera;

    //开始捕获图像
    x_pCamera->Grab();
    //获取图像的width和height
    x_pCamera->GetWidth(&width);
    x_pCamera->GetHeight(&height);

    //qDebug()<<"width = "<<width<<"height = "<<height;


    BYTE *temp= new BYTE[width*height*3];


    while(!dialog->isQuitThreadGrub)
    {
        nRet = x_pCamera->GetGrabData( &imageInfo );

        if( nRet == VWSDK::RESULT_ERROR_VWCAMERA_GRAB_TIMEOUT ||
                nRet == VWSDK::RESULT_ERROR_INVALID_PARAMETER )
        {
            break;
        }

        vpBuffer = imageInfo.pImage;

        if(vpBuffer == NULL)
        {
            delete [] temp;
            return;
        }

        VWSDK::VwImageProcess::ConvertBAYGR8ToBGR8( PBYTE(vpBuffer),temp,width,height );

        cv::Mat srcImage = cv::Mat(height,width,CV_8UC3,temp);

        if(!srcImage.empty())
        {
            dialog->lock.lockForWrite();

            srcImage.copyTo(dialog->frame);

            dialog->lock.unlock();

            emit    display();
        }

        QThread::currentThread()->msleep(100);
        //memset(temp,0,width*height*3);
    }

    delete [] temp;
}

void ThreadWorker::autoFocus()
{
    int count = 0;
    vector<double> rateFrame(3,0);
    CameraDialog *dialog = (CameraDialog *)QThread::currentThread()->parent();

    x_pCamera = dialog->pCamera;

    x_pCamera->GetWidth(&width);
    x_pCamera->GetHeight(&height);

    //qDebug()<<"width = "<<width<<"height = "<<height;


    BYTE *temp= new BYTE[width*height*3];

    FocusMeasure fm;

    HillClimbSearch hillsearch;
    hillsearch.def_MinStep = dialog->gui_minStep;
    hillsearch.def_MaxStep = dialog->gui_maxStep;
    hillsearch.epsylon = dialog->gui_epsylon;

    double value = 0;//清晰度值
//    int step = 0;    //搜索算法返回值,即电机要移动的步长

    while(!dialog->isQuitThreadFocus)
    {
        if ( x_pCamera->Snap(1) != VWSDK::RESULT_SUCCESS )
        {
            //QMessageBox::information(imgc,"information for AutoFocus","snap error.");
            //this->ui->btnAutoFocus->setEnabled(true);
            qDebug()<<"information for AutoFocus snap error.";
            return;
        }

        nRet = x_pCamera->GetGrabData( &imageInfo );

        if( nRet == VWSDK::RESULT_ERROR_VWCAMERA_GRAB_TIMEOUT ||
                nRet == VWSDK::RESULT_ERROR_INVALID_PARAMETER )
        {
            qDebug()<<"time out";
            QThread::currentThread()->msleep(50);//图像捕获超时,等待50ms，采集下一帧图像
            break;
        }

        vpBuffer = imageInfo.pImage;

        if(vpBuffer == NULL)
        {
            delete [] temp;
            return;
        }

        VWSDK::VwImageProcess::ConvertBAYGR8ToBGR8( PBYTE(vpBuffer),temp,width,height );

        cv::Mat srcImage = cv::Mat(height,width,CV_8UC3,temp);

        if(!srcImage.empty())
        {
            dialog->lock.lockForWrite();

            srcImage.copyTo(dialog->frame);

            dialog->lock.unlock();

            //qDebug()<<"emit display";

            emit    display();
        }

        //图像分析
        value = fm.focusMain(srcImage);
        qDebug()<<"value = "<<value;
        rateFrame[count++] = value;

        if(count == 3)
        {
            count = 0;
            value = (rateFrame[0] + rateFrame[1] + rateFrame[2])/3;
            qDebug()<<"avr value = "<<value;

#if 0
            //调用搜索函数进行搜索
            bool isSuccess = hillsearch.search((int)(value + 0.5));

            if(isSuccess)
            {
                //聚焦成功
                qDebug()<<"autoFocus successed!";
                //发射聚焦完成的信号

                emit    focusSuccess();

                delete []temp;//图片分析完成之后,释放资源
                return;
            }
#endif

        }

        QThread::currentThread()->msleep(100);//采集下一帧图像
    }

    //emit    focusSuccess();

    delete [] temp;
}

