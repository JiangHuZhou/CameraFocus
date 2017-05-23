#ifndef CAMERADIALOG_H
#define CAMERADIALOG_H

#include <QDialog>
#include <QThread>
#include <QReadWriteLock>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QFileDialog>
#include <QGraphicsScene>
#include <qmath.h>
#include "opencv2/opencv.hpp"

//#include "Threadworker.h"

#include "include/VwGigE.h"
#include "include/VwInterface.h"
#include "include/VwImageProcess.h"


/*
 * 错误码
相机错误码：
1.找不到网卡CAMERA_ERROR_NIC_NOTFOUND
2.读取网卡失败CAMERA_ERROR_NIC_READERROR
3.打不开相机CAMERA_ERROR_CAMERAOPEN
4.曝光时间设置错误CAMERA_ERROR_SETEXPOSURETIME
5.增益设置错误CAMERA_ERROR_SETGAIN
*/

class   ThreadWorker;

using namespace VWSDK;

namespace Ui {
class CameraDialog;
}

class CameraDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CameraDialog(QWidget *parent = 0);
    ~CameraDialog();

//子线程相关参数
public:
    QThread         *thread_grub;
    QThread         *thread_focus;

    ThreadWorker   *worker_grub;
    ThreadWorker   *worker_focus;

    volatile    bool    isQuitThreadGrub;
    volatile    bool    isQuitThreadFocus;

    //主线程相关参数
    UINT                        m_imagebuffernumber;
    VWSDK::VwGigE               *m_pvwGigE;
    VWSDK::VwCamera             *pCamera;
    VWSDK::OBJECT_INFO          *pObjectInfo;

    cv::Mat                     frame;//全局图像
    QGraphicsScene              *scense;
    QReadWriteLock              lock;  

    QTime                      times;

    //搜索相关参数
    volatile    int     gui_minStep;
    volatile    int     gui_maxStep;
    volatile    double  gui_epsylon;


private slots:
    void on_btnOpenCamera_clicked();

    void on_btnCloseCamera_clicked();

    void on_btnPlay_clicked();

    void on_btnAbort_clicked();

    void on_btnAutoFocus_clicked();

    void on_btnAbortFocus_clicked();

    void displayImage();

    void focusSuccess();

    void moveMotor(int nstep);

    void on_btnSave_clicked();

    void on_btnConnectMotor_clicked();

    void on_btnCloseMotor_clicked();

    void motorTest();

    void on_btnBigFocus_clicked();

    void on_zoomOutIcon_clicked();

    void on_zoomInIcon_clicked();

    void on_zoomSlider_valueChanged(int value);

private:
    Ui::CameraDialog *ui;

    void    connectMotorBtnSlots();
};

#endif // CAMERADIALOG_H
