#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <QObject>

#include "opencv2/opencv.hpp"
#include "Cameradialog.h"


class ThreadWorker : public QObject
{
    Q_OBJECT
public:
    explicit ThreadWorker(QObject *parent = 0);

    VWSDK::IMAGE_INFO   imageInfo;
    VWSDK::VwCamera     *x_pCamera;
    VWSDK::RESULT       nRet;

    UINT                width;
    UINT                height;
    void                *vpBuffer;

signals:
    void    display();
    void    focusSuccess();
    void    moveMotor(int nstep);

public slots:
    void    grub();

    void    autoFocus();
};

#endif // THREADWORKER_H
