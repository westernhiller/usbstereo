#include "maindialog.h"
#include <QApplication>
#include <QDebug>
#include "global.h"

int main(int argc, char *argv[])
{
    std::string stereo_cam = "/dev/video2";
    std::string ir_cam = "/dev/video4";
    if(argc != 3)
        qDebug() << "Usage: ircalib + stereo_camera + ir_camera";
    else
    {
        stereo_cam = argv[1];
        ir_cam = argv[2];
    }

    qRegisterMetaType<cv::Mat>("cv::Mat"); 
    qRegisterMetaType<std::string>("std::string"); 

    QApplication a(argc, argv);
    MainDialog w(stereo_cam, ir_cam);
    w.show();

    return a.exec();
}
