#include "maindialog.h"
#include <QLayout>
#include <QCheckBox>
#include <QPushButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace std;
using namespace cv;

MainDialog::MainDialog(string stereocam, string ircam, QWidget *parent) :
    QDialog(parent),
    m_pVisible(nullptr),
    m_pIr(nullptr),
	m_stereocam(stereocam),
	m_ircam(ircam)
{
    QVBoxLayout* layout = new QVBoxLayout();
    QCheckBox* pVisible = new QCheckBox("Left Image");
    layout->addWidget(pVisible);
    QCheckBox* pIr = new QCheckBox("Right Image");
    layout->addWidget(pIr);
    QPushButton* btnSave = new QPushButton("Save");
    layout->addWidget(btnSave);
    QPushButton* btnExit = new QPushButton("Exit");
    layout->addWidget(btnExit);

    setLayout(layout);

    connect(pVisible, SIGNAL(stateChanged(int)), this, SLOT(onVisibleChecked(int)));
    connect(pIr, SIGNAL(stateChanged(int)), this, SLOT(onIrChecked(int)));
    connect(btnSave, SIGNAL(clicked()), this, SLOT(onSave()));
    connect(btnExit, SIGNAL(clicked()), this, SLOT(onExit()));

    m_pVisibleCapturer = new CaptureThread(stereocam, 2560, 960, false, 1, this);
    m_pIrCapturer = new CaptureThread(ircam, 720, 480, true, 0, this);
    
    connect(this, SIGNAL(save()), m_pVisibleCapturer, SLOT(onSave()));
    connect(this, SIGNAL(save()), m_pIrCapturer, SLOT(onSave()));
}

MainDialog::~MainDialog()
{
	if(m_pVisible)
		delete m_pVisible;
	if(m_pIr)
		delete m_pIr;
	if(m_pVisibleCapturer)
		delete m_pVisibleCapturer;
	if(m_pIrCapturer)
		delete m_pIrCapturer;
}

void MainDialog::onVisibleChecked(int state)
{
    if (state == Qt::Checked) // "选中"
    {
        if(!m_pVisible)
        {
            m_pVisible = new CalibDialog(this);
            connect(m_pVisibleCapturer, SIGNAL(getFrame(cv::Mat)), m_pVisible, SLOT(display(cv::Mat)));
            connect(this, SIGNAL(save()), m_pVisibleCapturer, SLOT(onSave()));
            m_pVisible->setWindowTitle(QString::fromStdString(m_stereocam));
            m_pVisibleCapturer->start();
        }
        m_pVisible->show();
    }
    else {
        if(m_pVisible)
            m_pVisible->hide();
    }
}

void MainDialog::onIrChecked(int state)
{
    if (state == Qt::Checked) // "选中"
    {
        if(!m_pIr)
        {
            m_pIr = new CalibDialog(this);
            connect(m_pIrCapturer, SIGNAL(getFrame(cv::Mat)), m_pIr, SLOT(display(cv::Mat)));
            connect(this, SIGNAL(save()), m_pIrCapturer, SLOT(onSave()));
            m_pIr->setWindowTitle(QString::fromStdString(m_ircam));
            m_pIrCapturer->start();
        }
        m_pIr->show();
    }
    else {
        if(m_pIr)
            m_pIr->hide();
    }
}

void MainDialog::onSave()
{
    emit save();
}


void MainDialog::onExit()
{
    close();
}

