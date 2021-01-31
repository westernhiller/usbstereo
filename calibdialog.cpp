#include "calibdialog.h"
#include <QBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QSlider>
#include <QFileDialog>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace std;
using namespace cv;

CalibDialog::CalibDialog(QWidget *parent) :
    QDialog(parent)
{    
    QVBoxLayout* layout = new QVBoxLayout(); 
    m_pCanvas = new Canvas(this);
    m_pCanvas->setScaledContents(true);
    layout->addWidget(m_pCanvas);

    setLayout(layout);
    connect(this, SIGNAL(updateImage(QImage)), m_pCanvas, SLOT(updateImage(QImage)));
    resize(640, 480);
}

CalibDialog::~CalibDialog()
{
}

void CalibDialog::display(cv::Mat image)
{
    emit updateImage(mat2qimage(image));
}