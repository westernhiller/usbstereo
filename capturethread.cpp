#include "capturethread.h"
#include <QDebug>
#include <QDateTime>

using namespace std;
using namespace cv;

CaptureThread::CaptureThread(string cam, int width, int height, bool flip, int half, QWidget *parent) :
    m_bSaving(false),
    m_pVcap(nullptr),
    m_camdev(cam),
    m_nWidth(width),
    m_nHeight(height),
    m_bFlip(flip),
    m_half(half)
{    
    if(0 != half)
        m_half = half / abs(half);
}

CaptureThread::~CaptureThread()
{
    requestInterruption();
    quit();
    wait();
    if(m_pVcap)
    {
#ifndef USE_OPENCV_V4L2
        m_pVcap->stopCapture();
        m_pVcap->closeDevice();
#endif
        delete m_pVcap;
    }    
}

void CaptureThread::onSave()
{
    m_bSaving = true;
}

void CaptureThread::run()
{
#ifdef USE_OPENCV_V4L2
    m_pVcap = new VideoCapture(m_camdev, CAP_V4L2);
    if(!m_pVcap->isOpened())
    {
        qDebug() << "failed openning camera";
        return;
    }
    m_pVcap->set(cv::CAP_PROP_FRAME_WIDTH, m_nWidth);
    m_pVcap->set(cv::CAP_PROP_FRAME_HEIGHT, m_nHeight);
#else
    m_pVcap = new V4L2Capture((char *)m_camdev.c_str(), m_nWidth, m_nHeight);
    m_pVcap->openDevice();
    if(-1 == m_pVcap->initDevice(m_nWidth, m_nHeight))
    {
        qDebug() << "failed init camera " << m_camdev.c_str();
        return;
    }
    m_pVcap->startCapture();
    unsigned char *yuv422frame = nullptr;
    unsigned long yuvframeSize = 0;

    std::string camdev = m_camdev;
    while(true)
    {
        size_t pos = camdev.find("/");
        if(string::npos == pos)
            break;
        camdev.replace(pos, 1, "_");
    }
    while(true)
    {
        size_t pos = camdev.find("\\");
        if(string::npos == pos)
            break;
        camdev.replace(pos, 1, "_");
    }
   
#endif
    while (!isInterruptionRequested())
    {
#ifdef USE_OPENCV_V4L2
        Mat imgFrame;
        m_pVcap->read(imgFrame);
#else
        if(-1 != m_pVcap->getFrame((void **) &yuv422frame, (int *)&yuvframeSize))
        {
            Mat imgFrame = Jpeg2Mat(yuv422frame, yuvframeSize);
#endif
            if(imgFrame.data)
            {
                switch(m_half)
                {
                case 1:
                    imgFrame = imgFrame(Rect(imgFrame.cols/2, 0, imgFrame.cols/2, imgFrame.rows));
                    break;
                case -1:
                    imgFrame = imgFrame(Rect(0, 0, imgFrame.cols/2, imgFrame.rows));
                    break;
                case 0:
                default:
                    break;    
                }
                if(m_bFlip)
                {
                    cv::flip(imgFrame, imgFrame, -1);
                }
                emit getFrame(imgFrame);
                if(m_bSaving)
                {
                    QDateTime local(QDateTime::currentDateTime());
                    QString localTime = local.toString("yyyy-MM-dd-hh-mm-ss");
                    string filename = m_camdev + "_" + localTime.toStdString() + ".png";
                    imwrite(filename, imgFrame);
                    m_bSaving = false;
                }
                imgFrame.release();
            }
#ifndef USE_OPENCV_V4L2
            m_pVcap->backFrame();
        }
#endif
        usleep(20000);
    }
}