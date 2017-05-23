#include "Cameradialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CameraDialog w;
    w.show();

    return a.exec();
}
