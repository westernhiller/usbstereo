#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QThread>
#include "global.h"
//#define USE_OPENCV_V4L2

#ifndef USE_OPENCV_V4L2
#include "v4l2capture.h"
#include "turbojpeg.h"
#include "jpegdecode.h"
#endif


class CaptureThread : public QThread
{
    Q_OBJECT

public:
    explicit CaptureThread(std::string cam = "/dev/video0", int width = 640, int height = 480, bool flip = false, int half = 1, QWidget *parent = nullptr);
    ~CaptureThread();

signals:    
    void getFrame(cv::Mat image);
    void saveImage(std::string, cv::Mat);
    
private:
    bool m_bSaving;
    std::string m_camdev;
    int m_nWidth;
    int m_nHeight;
    bool m_bFlip;
    int m_half;

#ifdef USE_OPENCV_V4L2
    cv::VideoCapture *m_pVcap;
#else
    V4L2Capture *m_pVcap;
#endif

protected:
    void run() override;

public slots:
    void onSave();
};

#endif // CALIBDIALOG_H
