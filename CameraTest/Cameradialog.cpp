#include "Cameradialog.h"
#include "ui_Cameradialog.h"

#include "Threadworker.h"
#include "include/DTStageDriver.h"

CameraDialog::CameraDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraDialog)
{
    ui->setupUi(this);
    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    //QSize iconSize(size, size);
    //QToolButton *zoomInIcon = new QToolButton;
//    this->ui->zoomInIcon->setAutoRepeat(true);
//    this->ui->zoomInIcon->setAutoRepeatInterval(33);
//    this->ui->zoomInIcon->setAutoRepeatDelay(0);
//    this->ui->zoomInIcon->setIcon(QPixmap(":/zoomin.png"));
//    this->ui->zoomInIcon->setIconSize(iconSize);

    //QToolButton *zoomOutIcon = new QToolButton;
//    this->ui->zoomOutIcon->setAutoRepeat(true);
//    this->ui->zoomOutIcon->setAutoRepeatInterval(33);
//    this->ui->zoomOutIcon->setAutoRepeatDelay(0);
//    this->ui->zoomOutIcon->setIcon(QPixmap(":/zoomout.png"));
//    this->ui->zoomOutIcon->setIconSize(iconSize);

    //下面3行是增加dialog的最大、最小化按钮
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    //this->ui->scrollArea->setWidget(this->ui->labelImg);
    scense = new QGraphicsScene;

    this->ui->graphicsView->setScene(scense);
    ui->graphicsView->show();

    //相机参数
    m_imagebuffernumber = 2;//图片buffer数量


    //按钮初始化
    this->ui->btnOpenCamera->setEnabled(true);
    this->ui->btnAbort->setEnabled(false);
    this->ui->btnAbortFocus->setEnabled(false);
    this->ui->btnCloseCamera->setEnabled(false);
    this->ui->btnPlay->setEnabled(false);

    connectMotorBtnSlots();
}

CameraDialog::~CameraDialog()
{
    delete ui;
}

void CameraDialog::on_btnOpenCamera_clicked()
{
    this->m_pvwGigE = new VwGigE;

    VWSDK::RESULT ret;

    //第一步:打开网卡
    ret = m_pvwGigE->Open();//open NIC

    if(VWSDK::RESULT_SUCCESS != ret)
    {
        QMessageBox::information(this,"error......",QStringLiteral("网卡打开失败，找不到相机连接的网卡"));
        qDebug("The NIC open failed , can not find the camera who is connected to the NIC ");
        delete m_pvwGigE;
        return ;
    }
    //第二步:获取网卡数量
    UINT  NICNum = 0;//用来表示网卡数量
    ret = m_pvwGigE->GetNumInterfaces( &NICNum );
    if ( VWSDK::RESULT_SUCCESS != ret )
    {
        QMessageBox::information(this,"error......",QStringLiteral("读取网卡失败"));
        qDebug("Get the network interface card failed ");
        delete m_pvwGigE;
        return ;
    }
    //第三步:遍历网卡,找到对应的相机
    for(int i=0;i<(int)NICNum;i++)
    {
        VWSDK::VwInterface *pInterface = NULL;//定义interface的指针变量

        m_pvwGigE->OpenInterface(i,&pInterface);//打开网卡接口

        UINT DeviceNum = 0;
        pInterface->GetNumCameras( &DeviceNum );//通过接口获取网卡上的相机数量

        //当前PC上有3个网卡，DeviceNum分别等于1,0,0 当前PC只有网卡0上有相机
        /***********获取相机的基本信息***********/
        if(DeviceNum == 1) //网卡上有一个相机
        {
            VWSDK::VWINTERFACE_INFO interfaceinfo;
            m_pvwGigE->GetInterfaceInfo(i,&interfaceinfo);

            qDebug()<<"NIC interface name:"<< interfaceinfo.name;

            char chDevName[1024] = {0,};
            size_t sizeDevName = sizeof( chDevName );
            pInterface->GetCameraName( 0, chDevName, &sizeDevName );

            qDebug() << "device name: " << chDevName;

        }
    }

    //第四步:打开相机
    this->pObjectInfo = new OBJECT_INFO;

    if( VWSDK::RESULT_SUCCESS !=  m_pvwGigE->OpenCamera( (UINT)0, &pCamera, m_imagebuffernumber, (UINT)0, (UINT)0, (UINT)0, pObjectInfo,NULL) )
    {
        QMessageBox::information(this,"information......",QStringLiteral("无法打开相机"));
        qDebug() << "Can not open a Camera ";
        m_pvwGigE->Close();
        delete m_pvwGigE,pObjectInfo;
        return ;
    }

    //第五步:保存相机基本信息
    pObjectInfo->pVwCamera    = pCamera;//保存相机对象,pCamera中有相机的基本信息,VendorName,ModelName,Version,Width,Height,PixelFormat,MACAddress等
    pObjectInfo->pUserPointer = this;


    QString exposetime = this->ui->ExpuseTime->text();
    pCamera->SetCustomCommand((char *)"ExposureTime",exposetime.toLocal8Bit().data());

    //设置增益
    pCamera->SetGain(GAIN_ANALOG_ALL,this->ui->Gain->text().toFloat());

    //设置像素格式
    ret = pCamera->SetPixelFormat( PIXEL_FORMAT_BAYGR8 );
    if(VWSDK::RESULT_SUCCESS != ret)
    {
        QMessageBox::information(this,"information for set pixelformat","Invalid pixelformat.");
        qDebug("set pixelformat,Invalid pixelformat.");
        m_pvwGigE->Close();
        delete m_pvwGigE,pObjectInfo;
        return ;
    }

    //更新buffer
    UINT nWidth = 0;
    UINT nHeight = 0;
    VWSDK::PIXEL_FORMAT pixelFormat = VWSDK::PIXEL_FORMAT_MONO8;
    pCamera->GetWidth( &nWidth );
    pCamera->GetHeight( &nHeight );
    pCamera->GetPixelFormat( &pixelFormat );
    if( VWSDK::RESULT_SUCCESS != pCamera->ChangeBufferFormat( m_imagebuffernumber, nWidth, nHeight, pixelFormat ) )
    {
        QMessageBox::information(this,"information for change the camera buffer","Can't change the camera buffer.");
        qDebug("Can't change the camera buffer.");
        m_pvwGigE->Close();
        delete m_pvwGigE,pObjectInfo;
        return;
    }


    QMessageBox::information(this,"information......",QStringLiteral("相机打开成功"));
    qDebug() << "Camera open success! ";

    //禁止打开相机按钮,使能其他按钮

    this->ui->btnOpenCamera->setEnabled(false);
    this->ui->btnPlay->setEnabled(true);
    this->ui->btnCloseCamera->setEnabled(true);
    this->ui->btnAutoFocus->setEnabled(false);

}

void CameraDialog::on_btnCloseCamera_clicked()
{
    //退出线程
    //1.退出grub线程
    if(thread_grub->isRunning())
    {
        isQuitThreadGrub = true;

        thread_grub->quit();
        thread_grub->wait();
    }
    //2.退出focus线程
    //

    if ( NULL == pCamera )
    {
        return;
    }

    RESULT ret;
    ret = pCamera->CloseCamera();
    if(ret != RESULT_SUCCESS)
    {
        QMessageBox::information(this,"error for close Camera....",QStringLiteral("相机关闭失败"));
        qCritical("Close the Camera failed! ");
        return;
    }
    m_pvwGigE->Close();
    delete m_pvwGigE,pObjectInfo;

    //this->ui->labelImg->clear();

    this->ui->btnCloseCamera->setEnabled(false);

    this->ui->btnOpenCamera->setEnabled(true);

    this->ui->btnPlay->setEnabled(false);

    this->ui->btnAbort->setEnabled(false);

    this->ui->btnAutoFocus->setEnabled(false);

    this->ui->btnAbortFocus->setEnabled(false);
}

void CameraDialog::on_btnPlay_clicked()
{
    this->isQuitThreadGrub = false;

    worker_grub = new ThreadWorker;
    thread_grub = new QThread(this);

    worker_grub->moveToThread(thread_grub);

    connect(thread_grub,SIGNAL(started()),worker_grub,SLOT(grub()));

    connect(thread_grub,SIGNAL(finished()),worker_grub,SLOT(deleteLater()));

    connect(worker_grub,SIGNAL(display()),this,SLOT(displayImage()));

    thread_grub->start();

    this->ui->btnAbort->setEnabled(true);

    this->ui->btnPlay->setEnabled(false);

    this->ui->btnAutoFocus->setEnabled(false);

}

void CameraDialog::on_btnAbort_clicked()
{
    this->isQuitThreadGrub = true;

    while(thread_grub->isRunning())
    {
        if( pCamera->Abort() == VWSDK::RESULT_SUCCESS )//等待相机终止成功
        {
            thread_grub->quit();
            thread_grub->wait();

            qDebug()<<"abort success";
            QMessageBox::information(this,"information for Abort","abort success.");
            this->ui->btnAutoFocus->setEnabled(true);
            this->ui->btnPlay->setEnabled(true);
            this->ui->btnAbort->setEnabled(false);

            return ;
         }
        QThread::currentThread()->msleep(100);
        //thread_grub->terminate();
    }
}

void CameraDialog::on_btnAutoFocus_clicked()
{
    this->isQuitThreadFocus = false;

    //获取聚焦时的默认参数值
    this->gui_minStep = this->ui->MinStep->text().toInt();
    this->gui_maxStep = this->ui->MaxStep->text().toInt();
    this->gui_epsylon = this->ui->Epsylon->text().toDouble();

    worker_focus = new ThreadWorker;
    thread_focus = new QThread(this);

    worker_focus->moveToThread(thread_focus);

    connect(thread_focus,SIGNAL(started()),worker_focus,SLOT(autoFocus()));

    connect(thread_focus,SIGNAL(finished()),worker_focus,SLOT(deleteLater()));

    connect(worker_focus,SIGNAL(display()),this,SLOT(displayImage()));

    connect(worker_focus,SIGNAL(focusSuccess()),this,SLOT(focusSuccess()));

    connect(worker_focus,SIGNAL(moveMotor(int)),this,SLOT(moveMotor(int)));

    thread_focus->start();

    times.start();//启动定时器

    this->ui->btnAbortFocus->setEnabled(true);

    this->ui->btnAutoFocus->setEnabled(false);

    this->ui->MinStep->setEnabled(false);

    this->ui->MaxStep->setEnabled(false);

    this->ui->Epsylon->setEnabled(false);
}

void CameraDialog::on_btnAbortFocus_clicked()
{
    this->isQuitThreadFocus = true;

    if(thread_focus->isRunning())
    {
        thread_focus->quit();
        thread_focus->wait();

        qDebug()<<"abort success";
        QMessageBox::information(this,"information for Abort focus","abort success.");
        this->ui->btnAutoFocus->setEnabled(true);
        this->ui->btnAbortFocus->setEnabled(false);

        this->ui->MinStep->setEnabled(false);

        this->ui->MaxStep->setEnabled(false);

        this->ui->Epsylon->setEnabled(false);

        return;
    }
    thread_focus->terminate();
}

void CameraDialog::displayImage()
{
    if(thread_grub->isRunning() || thread_focus->isRunning())
    {
        lock.lockForRead();
        cv::Mat src;
        this->frame.copyTo(src);
        lock.unlock();

        cv::cvtColor(src,src,CV_BGR2RGB);
        QImage img = QImage((const unsigned char *)src.data,src.cols,src.rows,src.cols * src.channels(),QImage::Format_RGB888);

        //QPixmap img = QPixmap();
        //img.bits();
        //this->ui->labelImg->setPixmap(QPixmap::fromImage(img));
        scense->clear();

        scense->addPixmap(QPixmap::fromImage(img));

        //ui->graphicsView->resize(img.width(), img.height());

        ui->graphicsView->update();

        //QThread::currentThread()->msleep(50);

        //lock.unlock();

        double temper;

        this->pCamera->GigEGetTemperature(&temper);

        QString s = QStringLiteral("℃");

        this->ui->labelTemper->setText(QString::number(temper).append(s));
    }
}

void CameraDialog::focusSuccess()
{
    float focustime = (float)times.elapsed()/1000;

    this->ui->label_focusTime->setText(QString::number(focustime));

    this->ui->btnAbortFocus->setEnabled(false);

    this->ui->btnAutoFocus->setEnabled(true);

    this->isQuitThreadFocus = true;
    //终止聚焦线程
    thread_focus->terminate();

}

void CameraDialog::moveMotor(int nstep)
{
    //DTMoveSteps('Z',step);//电机转动
}

void CameraDialog::on_btnSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Open Image"), "D:/testImage/", tr("Image Files (*.png *.jpg *.bmp)"));
       if(fileName.isEmpty())
       {
           return;
       }
       else
       {
           //imwrite(fileName,this->frame);
           if(!(imwrite(fileName.toStdString(),this->frame)))
           //if(!(this->ui->labelImg->pixmap()->save(fileName)))
           {
               QMessageBox::warning(this,"error for save image",QStringLiteral("图片 ") + fileName + QStringLiteral(" 保存失败！"));
               return;
           }
       }
}

void CameraDialog::on_btnConnectMotor_clicked()
{
    int comm = this->ui->MotorCom->text().toInt();

    int ret = DTInitStage(comm);
    //DTInitStage函数使用之前,需连接好线路并启动电源
    if(ret < 0)
    {
        //连接失败,通常表示可能未启动电源或者线路不正常,此时调用另外一个函数DTSetComm
        //手动设置端口号,待启动电源后,即可连接成功
        //DTSetComm(commNum);
        QMessageBox::warning(this,QStringLiteral("错误"),QStringLiteral("端口设置错误，请查看PC上的端口号，或检查电源是否打开，线缆是否连接正确"));
        //this->isMotorActive = false;
        return;
    }
    //5.回到原点
    //DTHomeLimit('L','T');//表示左上角,RT:右上角,LB:左下角,RB:右下角

    //6.初始化成功,蜂鸣器叫一声
    DTBuzzing(1);
    //QMessageBox::information(this,QStringLiteral("成功"),QStringLiteral("电机设置成功！"));
    qDebug("Motor setup success");
    //this->isMotorActive = true;

    this->ui->MotorCom->setEnabled(false);
    this->ui->MaxStep->setEnabled(false);
    this->ui->MinStep->setEnabled(false);
}

void CameraDialog::on_btnCloseMotor_clicked()
{
    DTStop('X','Y','Z');

    this->ui->MaxStep->setEnabled(true);
    this->ui->MinStep->setEnabled(true);
    this->ui->MotorCom->setEnabled(true);
}

void CameraDialog::motorTest()
{
    //QPushButton *btn = (QPushButton *)sender();
    //QString  name = btn->text();
    int pulses = this->ui->pulses->text().toInt();

    qDebug()<<"pulses = " << pulses;

    QObject* sender = QObject::sender();
    if(sender == ui->btnX)
    {
        MoveStage('X',1,pulses);return;
    }
    else if(sender == ui->btnNX)
    {
        MoveStage('X',-1,pulses);return;
    }
    else if(sender == ui->btnY)
    {
        MoveStage('Y',1,pulses);return;
    }
    else if(sender == ui->btnNY)
    {
        MoveStage('Y',-1,pulses);return;
    }
    else if(sender == ui->btnZ)
    {
        MoveStage('Z',1,pulses);return;
    }
    else if(sender == ui->btnNZ)
    {
        MoveStage('Z',-1,pulses);return;
    }
}

void CameraDialog::connectMotorBtnSlots()
{
    connect(this->ui->btnX,SIGNAL(clicked()),this,SLOT(motorTest()));
    connect(this->ui->btnNX,SIGNAL(clicked()),this,SLOT(motorTest()));
    connect(this->ui->btnY,SIGNAL(clicked()),this,SLOT(motorTest()));
    connect(this->ui->btnNY,SIGNAL(clicked()),this,SLOT(motorTest()));
    connect(this->ui->btnZ,SIGNAL(clicked()),this,SLOT(motorTest()));
    connect(this->ui->btnNZ,SIGNAL(clicked()),this,SLOT(motorTest()));
}

void CameraDialog::on_btnBigFocus_clicked()
{

    /*

///////////////////////////现有电动平台操作方法/////////////////////////////////
    //粗调步骤:
    //1.先让Z轴回到限位点
    DTMoveSteps('Z',-99999990);
    //2.等待电机到位
    int nPosition, nGetPosition;

    do{
        nGetPosition = DTReadStatus();
        if( nGetPosition & 0x80000000)//值有效
        {
            nPosition = nGetPosition & 0xF00;// Z 轴
            if( nPosition != 0x0) //为0表示正在运行
            {
                break;
            }
        }
    }while(1);

    //3.清除Z轴移动的脉冲数
    DTClearPulses('Z');

    //4.转动到起始位置
    DTMoveSteps('Z',5000);//转动的脉冲数手工测试后写入软件
    //5.等待电机到位
    do{
        nGetPosition = DTReadStatus();
        if( nGetPosition & 0x80000000)//值有效
        {
            nPosition = nGetPosition & 0xF00;// Z 轴
            if( nPosition != 0x0) //为0表示正在运行
            {
                break;
            }
        }
    }while(1);

    //6.读取Z轴移动的脉冲数
    int pulses = DTGetPulses('Z');
//////////////////////////////////////////////////////////////////////////
    //7.与硬件产生的脉冲数进行比对,修正,确保电机必须移动相应的脉冲数

///////////////////////////自设计电动平台操作方法///////////////////////////
    //1.发脉冲让电机回到最低限位点
    //2.等待电机到位
    //3.脉冲数清零
    //4.通知相机采集图像
    //5.图像分析(图像由全黑到出现模糊图像)
    //6.发固定脉冲让电机向同一个方向移动
    //7.返回第5步,直到出现在聚焦范围内

    */
}

void CameraDialog::on_zoomOutIcon_clicked()
{
    this->ui->zoomSlider->setValue(this->ui->zoomSlider->value() - 1);
}

void CameraDialog::on_zoomInIcon_clicked()
{
    this->ui->zoomSlider->setValue(this->ui->zoomSlider->value() + 1);
}

void CameraDialog::on_zoomSlider_valueChanged(int value)
{
    qreal scale = qPow(qreal(2), (value - 250) / qreal(50));
    //qDebug()<<"scale = "<<scale;

    QMatrix matrix;
    matrix.scale(scale,scale);
    this->ui->graphicsView->setMatrix(matrix);
}
