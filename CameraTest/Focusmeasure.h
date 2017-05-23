#ifndef FOCUSMEASURE_H
#define FOCUSMEASURE_H

#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"


using namespace cv;
using namespace std;

class FocusMeasure
{
public:
    FocusMeasure();

    double focusMain(Mat srcc);//对外调用主函数

private:
    void splitImage(Mat src_img, int m, int n);
    Mat splitImage2(Mat src);

    int findValidImage(Mat src);
    Mat findROIGrayImage(Mat gray);

    Mat findROISrcImage(Mat srcc);

    Rect findROIImage(Mat src);

    double getArea_g(Mat src, vector<int> index);

    double getArea_all(Mat src);

    double  rateFrame(Mat src);

    void blurAndThreshold(Mat gray);

    uint64  getCount(Mat src,int grayValue);

private:
    double G_MAXAREA;
    double G_THRESH;
    Mat g_validImage;
    Mat g_threshold_output;//定义二值图存放对象
    std::vector<cv::Mat> g_subImages;

    std::vector<cv::Rect> rects;//拆分的图像存储的集合

    volatile  Point_<int> tl;
    volatile  Point_<int> br;

    volatile    int     p_x1;
    volatile    int     p_x2;
    volatile    int     p_y1;
    volatile    int     p_y2;

};

#endif // FOCUSMEASURE_H
