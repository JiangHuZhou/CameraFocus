#include "Focusmeasure.h"

FocusMeasure::FocusMeasure()
{
    G_MAXAREA = 500000;
    G_THRESH = 20;


    tl.x = 0;
    tl.y = 0;
    br.x = 0;
    br.y = 0;

    p_x1 = 0;
    p_x2 = 0;
    p_y1 = 0;
    p_y2 = 0;
}

double FocusMeasure::focusMain(Mat srcc)
{
    Mat src,ROI_temp;
    srcc.copyTo(src);

    if(p_x2 > p_x1 || p_y2 > p_y1)
    {
        ROI_temp = src(Rect(p_x1,p_y1,p_x2-p_x1,p_y2-p_y1));
    }
    else
    {
        ROI_temp = findROISrcImage(src);
    }
    Mat ROI = splitImage2(ROI_temp);

  //求面积
    //使用面积计算时要先滤波
    Mat gray;
    //转成灰度图
    cvtColor(ROI,gray,CV_BGR2GRAY);

    //进行高斯滤波
    GaussianBlur(gray, gray, Size(7, 7), 0.8, 0.8);

    double area = getArea_all(gray);

    return area;

/* 统计灰度值大于30的像素个数
        uint64 count = getCount(ROI,15);

        return count;
*/

/*  求灰度值
    return rateFrame(ROI);
*/
/*
    //转成灰度图
    cvtColor(src,gray,CV_BGR2GRAY);
    //imwrite("D:\\testImage\\20170511\\gray2.bmp",gray);
    //进行高斯滤波
    GaussianBlur(gray, gray, Size(7, 7), 0.8, 0.8);

    Mat ROI,vaildImage;

    if((tl.x != 0)&&(br.x !=0))
    {
        cout << "tl = [" << tl.x << ","<<tl.y << "], br = [" <<br.x<<","<<br.y<<"]"<<endl;

       Rect rect(tl.x,tl.y,br.x-tl.x,br.y-tl.y);
       ROI = gray(rect);
       vaildImage = src(rect);
       imwrite("D:\\testImage\\20170512\\ROI2.bmp",vaildImage);
       //blurAndThreshold(ROI);
    }
    else
    {
        //先找有效区域
        ROI = findROIGrayImage(gray);

        vaildImage = findROISrcImage(src);

        imwrite("D:\\testImage\\20170512\\ROI1.bmp",vaildImage);
    }
    */
/*
///////////////////////////////////////////////////////////////////////

    //测试找坐标点
    splitImage2(ROI,5,5);
    //Mat temp = src(findROIImage(gray));

    rectangle(vaildImage,rects[6].tl(),rects[6].br(),CV_RGB(255,0,5),6,8,0);
    rectangle(vaildImage,rects[8].tl(),rects[8].br(),CV_RGB(255,0,5),6,8,0);
    rectangle(vaildImage,rects[12].tl(),rects[12].br(),CV_RGB(255,0,5),6,8,0);
    rectangle(vaildImage,rects[16].tl(),rects[16].br(),CV_RGB(255,0,5),6,8,0);
    rectangle(vaildImage,rects[18].tl(),rects[18].br(),CV_RGB(255,0,5),6,8,0);

    imwrite("D:\\testImage\\20170512\\rects.bmp",vaildImage);
//////////////////////////////////////////////////////////////////////////
*/
/*
    splitImage2(ROI,5,5);

    std::vector<int>      index;//待提取的图像在rects中的索引
    index.push_back(6);
    index.push_back(8);
    index.push_back(12);
    index.push_back(16);
    index.push_back(18);
*/
/*
    vector<vector<cv::Point> > contours;//定义点集存放集合
    vector<cv::Vec4i> hierarchy;
    //找到轮廓
    Mat threshold_out;
    threshold(ROI,threshold_out,G_THRESH,255,THRESH_BINARY);
    imwrite("D:\\testImage\\20170512\\threshold2.bmp",threshold_out);

    findContours( threshold_out, contours, hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    int length = (int)contours.size();

    cout << "after findContours() contours.size() = "<<length<<endl;

    double area = 0;//包围每个点集的矩形的面积
    double areaAvr = 0;//每个区域点集的矩形面积

    for(int i = 0; i < length; i++ )
    {
        //boundRect[i] = boundingRect(Mat(contours[i]));//计算点集最小包围矩形
        area += fabs(contourArea(contours[i]));//求每个矩形的面积
    }
    cout << "area = "<< area <<endl;
    areaAvr = area/length;
    cout << "areaAvr = " <<areaAvr<<endl;
////////////////////////////////////////////////////////////////////////
*/
}

void FocusMeasure::splitImage(Mat src_img, int m, int n)
{
    int height = src_img.rows;
    int width  = src_img.cols;
    int sub_w = width/m;
    int sub_h = height/n;
    std::vector<cv::Rect> rects;//拆分的图像存储的集合
    std::vector<int> index; //8幅图像的索引
    int count=0;
    for(int i = 0; i < m; i++ )
    {
        for(int j = 0; j < n; j++ )
        {
            //拆分图像,提取特定的八幅图像,并保存其在rects集合中的索引
            rects.push_back(Rect(i*sub_w,j*sub_h,sub_w,sub_h));
            //第1幅图
            if(i == 1 && j == 1)
            {
                index.push_back(count);
                //rects.push_back(Rect(i*sub_w,j*sub_h,sub_w,sub_h));
            }
            //第2幅图
            if((i == m -2) && (j == 1))
            {
                index.push_back(count);
                //rects.push_back(Rect(i*sub_w,j*sub_h,sub_w,sub_h));
            }
            //第3幅图
            if((i == 1) && (j == n-2))
            {
                index.push_back(count);
                //rects.push_back(Rect(i*sub_w,j*sub_h,sub_w,sub_h));
            }
            //第4幅图
            if((i == m - 2) && (j == n - 2))
            {
                index.push_back(count);
                //rects.push_back(Rect(i*sub_w,j*sub_h,sub_w,sub_h));
            }
            //第5幅图
            if((i == m/2-1) && (j == n/2-1))
            {
                index.push_back(count);
                //rects.push_back(Rect(i*sub_w,j*sub_h,sub_w,sub_h));
            }
            //第6幅图
            if((i == m/2) && (j == n/2-1))
            {
                index.push_back(count);
                //rects.push_back(Rect(i*sub_w,j*sub_h,sub_w,sub_h));
            }
            //第7幅图
            if((i == m/2-1) && (j == n/2))
            {
                index.push_back(count);
                //rects.push_back(Rect(i*sub_w,j*sub_h,sub_w,sub_h));
            }
            //第8幅图
            if((i == m/2) && (j == n/2))
            {
                index.push_back(count);
                //rects.push_back(Rect(i*sub_w,j*sub_h,sub_w,sub_h));
            }
            count++;
        }
    }

    g_subImages.clear();
    for(int i = 0; i < 8;i++ )
    {
        //将8幅图像保存到传入的集合subImages中
        int num = index[i];
        Mat temp;
        src_img(rects[num]).copyTo(temp);
        g_subImages.push_back(temp);
    }
}

Mat FocusMeasure::splitImage2(Mat src)
{
    //std::vector<cv::Mat> subImages;
    //g_subImages.clear();

    Rect rect(src.cols/7*3,src.rows/3,src.cols/7,src.rows/3);
    return src(rect);

}


int FocusMeasure::findValidImage(Mat src)
{
    Mat gray,temp;

    src.copyTo(temp);

    //(1) 转成灰度图进行平滑
    cvtColor(temp,gray,CV_BGR2GRAY);

    //blur(gray,gray,Size(7,7));
    GaussianBlur(gray, gray, Size(7, 7), 0.8, 0.8);
    Mat threshold_output;//定义二值图存放对象
    vector<vector<Point> > contours;//定义点集存放集合

    //(2) 使用Threshold检测边缘
    threshold(gray,threshold_output,0,255,THRESH_BINARY);
    imwrite("D:\\testImage\\20170512\\threshod.bmp",threshold_output);
    //(3) 找到轮廓
    findContours( threshold_output, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    cout <<"findContours() "<<endl;
    vector<Rect> boundRect( contours.size() );
    //Mat boundRect_Mat;

    double area = 0;//包围每个点集的矩形的面积
    double areaMax = 0;//包围点集的最大矩形面积
    int idx = 0;//包围点集的最大矩形在点集集合中的下标


    for(int i = 0; i < (int)contours.size(); i++ )
    {
        boundRect[i] = boundingRect(Mat(contours[i]));//计算点集最小包围矩形

        rectangle(temp,boundRect[i].tl(),boundRect[i].br(),CV_RGB(255,0,5),2,8,0);//在temp上画矩形,tl为矩形左上角,br为右上角

        area = fabs(contourArea(contours[i]));//求每个矩形的面积

        if(area > areaMax)
        {
            areaMax = area;
            idx = i;
        }
    }

    imwrite("D:\\testImage\\20170510\\temp2.bmp",temp);
    cout << "for out areaMax = "<< areaMax<<endl;

    if(areaMax > G_MAXAREA)
    {
        Rect rect = boundingRect(contours[idx]);
        Mat ROIImage = src(rect);//在原图上提取有效区域
        //rect.tl();
        //Point_<int> tl = rect.tl(); //左上角
        //Point_<int> br = rect.br(); //右上角

        //tl = rect.tl();
        //br = rect.br();

        //创建和ROIImage类型大小一样的对象并拷贝
        g_validImage.create(ROIImage.size(),ROIImage.type());
        ROIImage.copyTo(g_validImage);

        //cout << "areaMax = "<< areaMax<<endl;

        imwrite("D:\\testImage\\20170510\\ROI2.bmp",g_validImage);
        return 0;
    }


    return -1;
}

Mat FocusMeasure::findROIGrayImage(Mat gray)
{
    //遍历像素点
    int cols = gray.cols;
    int rows = gray.rows;

    int grayValue = 30;

    int idx1 = 0;
    int idx2 = 0;

    int idy1 = 0;
    int idy2 = 0;

    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            int value = (int)gray.at<uchar>(j,i);
            if(value >= grayValue)
            {
                idx1 = i;
                goto next2;
            }
        }
    }
next2:
    for(int i = cols-1; i > idx1; i--)
    {
        for(int j = 0; j < rows; j++)
        {
            if(gray.at<uchar>(j,i) >= grayValue)
            {
                idx2 = i;
                goto next3;

            }
        }
    }
next3:
    for(int i = 0; i < rows; i++)
    {
        for(int j = idx1; j < idx2; j++)
        {
            if(gray.at<uchar>(i,j) >= grayValue)
            {
                idy1 = i;
                goto next4;
            }
        }
    }
next4:
    for(int i = rows - 1;i > idy1; i-- )
    {
        for(int j = idx1; j < idx2; j++)
        {
            if(gray.at<uchar>(i,j) >= grayValue)
            {
                idy2 = i;
                goto last;
            }
        }
    }
last:
    cout<<"x1,x2 = "<< idx1 << ","<<idx2<<endl;
    cout<<"y1,y2 = "<< idy1 << ","<<idy2<<endl;

//    Point_<int> tl;
//    Point_<int> br;
    tl.x = idx1;
    tl.y = idy1;
    br.x = idx2;
    br.y = idy2;

//    if((idx2 <= idx1)||(idy2 <= idy1))
//    {
//        return ;
//    }

    Rect rect(idx1,idy1,idx2-idx1,idy2-idy1);
    Mat ROI = gray(rect);

    imwrite("D:\\testImage\\20170512\\ROI3.bmp",ROI);
    return ROI;
}

Mat FocusMeasure::findROISrcImage(Mat srcc)
{
    //遍历像素点
    int cols = srcc.cols;
    int rows = srcc.rows;

    Mat src;
    cvtColor(srcc,src,CV_BGR2GRAY);

    GaussianBlur(src, src, Size(7, 7), 0.8, 0.8);

    int grayValue = 30;
    //cout<<"clos = "<<cols<<",rows = "<<rows<<endl;

    int idx1 = 0;
    int idx2 = 0;

    int idy1 = 0;
    int idy2 = 0;

    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            int value = (int)src.at<uchar>(j,i);
            if(value >= grayValue)
            {
                idx1 = i;
                //cout << "idx1 = "<<i<<endl;
                goto next2;
            }
        }
    }
next2:
    //cout<< "next2"<<endl;
    for(int i = cols-1; i > idx1; i--)
    {
        for(int j = 0; j < rows; j++)
        {
            if(src.at<uchar>(j,i) >= grayValue)
            {
                idx2 = i;
                //cout << "idx2 = "<<i<<endl;
                goto next3;

            }
        }
    }
next3:
    //cout<< "next3"<<endl;
    for(int i = 0; i < rows; i++)
    {
        for(int j = idx1; j < idx2; j++)
        {
            if(src.at<uchar>(i,j) >= grayValue)
            {
                idy1 = i;
                goto next4;
            }
        }
    }
next4:
    //cout<< "next4"<<endl;
    for(int i = rows - 1;i > idy1; i-- )
    {
        for(int j = idx1; j < idx2; j++)
        {
            if(src.at<uchar>(i,j) >= grayValue)
            {
                idy2 = i;
                goto last;
            }
        }
    }
last:
    //cout<<"x1,x2 = "<< idx1 << ","<<idx2<<endl;
    //cout<<"y1,y2 = "<< idy1 << ","<<idy2<<endl;

//    Point_<int> tl;
//    Point_<int> br;
//    tl.x = idx1;
//    tl.y = idy1;
//    br.x = idx2;
//    br.y = idy2;

    p_x1 = idx1;
    p_x2 = idx2;
    p_y1 = idy1;
    p_y2 = idy2;


//    if((idx2 <= idx1)||(idy2 <= idy1))
//    {
//        return ;
//    }

    Rect rect(idx1,idy1,idx2-idx1,idy2-idy1);
    Mat ROI = srcc(rect);

    //g_validImage.create(ROI.size(),ROI.type());
    //ROI.copyTo(g_validImage);

    //imwrite("D:\\testImage\\20170512\\ROI1.bmp",ROI);
    return ROI;
}

cv::Rect FocusMeasure::findROIImage(Mat gray)
{
    //遍历像素点
    int cols = gray.cols;
    int rows = gray.rows;

    int grayValue = 30;

    int idx1 = 0;
    int idx2 = 0;

    int idy1 = 0;
    int idy2 = 0;

    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            int value = (int)gray.at<uchar>(j,i);
            if(value >= grayValue)
            {
                idx1 = i;
                goto next2;
            }
        }
    }
next2:
    for(int i = cols-1; i > idx1; i--)
    {
        for(int j = 0; j < rows; j++)
        {
            if(gray.at<uchar>(j,i) >= grayValue)
            {
                idx2 = i;
                goto next3;

            }
        }
    }
next3:
    for(int i = 0; i < rows; i++)
    {
        for(int j = idx1; j < idx2; j++)
        {
            if(gray.at<uchar>(i,j) >= grayValue)
            {
                idy1 = i;
                goto next4;
            }
        }
    }
next4:
    for(int i = rows - 1;i > idy1; i-- )
    {
        for(int j = idx1; j < idx2; j++)
        {
            if(gray.at<uchar>(i,j) >= grayValue)
            {
                idy2 = i;
                goto last;
            }
        }
    }
last:
    tl.x = idx1;
    tl.y = idy1;
    br.x = idx2;
    br.y = idy2;

    Rect rect(idx1,idy1,idx2-idx1,idy2-idy1);

    return rect;

}

double FocusMeasure::getArea_g(Mat src,vector<int> index)
{
    //imwrite("D:\\testImage\\20170512\\xx.bmp",src);
    vector<vector<cv::Point> > contours;//定义点集存放集合
    vector<cv::Vec4i> hierarchy;
    //找到轮廓
    Mat threshold_out;
    threshold(src,threshold_out,G_THRESH,255,THRESH_BINARY);
    imwrite("D:\\testImage\\20170512\\threshold.bmp",threshold_out);

    Mat temp;
    //Rect rct;
    //vector<Rect> boundRect;
    double area = 0;//包围每个点集的矩形的面积
    double areaPerImg = 0;//每个区域点集的矩形面积

    size_t len = index.size();
    //cout << "len = "<<len<<endl;

    for(size_t i = 0; i< len; i++)
    {
        //rct = rects(index[i]);
        Rect rct;
        cout << "index[i] = "<<index[i]<<endl;
        //cout << "Rect tl = " << rects[index[i]].tl()<<endl;
        //cout << "Rect br = " << rects[index[i]].br()<<endl;
        int x = index[i];
        rct = rects[x];

        threshold_out(rct).copyTo(temp);

        //imwrite("D:\\testImage\\20170512\\threshold_out_index.bmp",temp);

        findContours( temp, contours, hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

        cout << "after findContours() contours.size() = "<<(int)contours.size()<<endl;

        //计算点集最小包围矩形面积
        //vector<Rect> boundRect( contours.size() );

        for(int i = 0; i < (int)contours.size(); i++ )
        {
            //boundRect.push_back(boundingRect(Mat(contours[i])));
            //boundRect[i] = boundingRect(Mat(contours[i]));//计算点集最小包围矩形
            area += fabs(contourArea(contours[i]));//求每个矩形的面积
            //area += fabs(contourArea(temp(boundingRect(Mat(contours[i])))));
            //areaSum += area;
        }
        areaPerImg += area / contours.size();

        cout << "areaPerImg = "<< area / contours.size() <<endl;
    }
    cout << "areaSum = "<<areaPerImg<<endl;
    //返回每个点集的平均面积
    return areaPerImg / 5;
}

double FocusMeasure::getArea_all(Mat src)
{
    //转为二值图
    Mat threshold_out;
    threshold(src,threshold_out,10,255,THRESH_BINARY);
    //imwrite("D:\\testImage\\20170515\\threshold2.bmp",threshold_out);

    //遍历像素点,统计像素值为255的数量
    int cols = threshold_out.cols;
    int rows = threshold_out.rows;

    unsigned int count = 0;

    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            int value = (int)threshold_out.at<uchar>(j,i);
            if(value == 255)
            {
                count++;
            }
        }
    }
    return count;


/*  找到轮廓求点集的面积
    vector<vector<cv::Point> > contours;//定义点集存放集合
    vector<cv::Vec4i> hierarchy;

    findContours( threshold_out, contours, hierarchy,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    int length = (int)contours.size();

    double area = 0;//包围每个点集的矩形的面积
    //double areaAvr = 0;//每个区域点集的矩形面积

    for(int i = 0; i < length; i++ )
    {
        //boundRect[i] = boundingRect(Mat(contours[i]));//计算点集最小包围矩形
        area += fabs(contourArea(contours[i]));//求每个点集的面积
    }
    return area/length;
*/
}

double FocusMeasure::rateFrame(Mat src)
{
    Mat gray;
    //转成灰度图
    cvtColor(src,gray,CV_BGR2GRAY);

    //进行高斯滤波
    GaussianBlur(gray, gray, Size(7, 7), 0.8, 0.8);

    Mat dst;

    Laplacian(gray,dst,CV_16U);

    //Sobel(gray,dst,CV_16U,1,1);

    //图像的平均灰度
    double meanValue = 0.0;
    meanValue = mean(dst)[0];

    return meanValue;


//    Mat laplacian_output;

//    Laplacian(src,laplacian_output,CV_16U);

//    imwrite("D:\\testImage\\20170512\\laplacian_output.bmp",laplacian_output);

//    double meanValue = 0.0;
//    meanValue = mean(laplacian_output)[0];

//    return meanValue;
}

void FocusMeasure::blurAndThreshold(Mat gray)
{
    //传入的是灰度图
    g_threshold_output.create(gray.size(),gray.type());

    threshold(gray,g_threshold_output,G_THRESH,255,THRESH_BINARY);

    imwrite("D:\\testImage\\20170512\\threshold1.bmp",g_threshold_output);
}

uint64 FocusMeasure::getCount(Mat src,int grayValue)
{
    Mat gray;
    //转成灰度图
    cvtColor(src,gray,CV_BGR2GRAY);

    //进行高斯滤波
    GaussianBlur(gray, gray, Size(7, 7), 0.8, 0.8);

    //遍历像素点
    int cols = gray.cols;
    int rows = gray.rows;

    //int grayValue = 30;

    uint64 count = 0;

    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            int value = (int)gray.at<uchar>(j,i);
            if(value >= grayValue)
            {
                count++;
            }
        }
    }

    return count;

}
