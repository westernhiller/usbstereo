#ifndef GLOBAL_H
#define GLOBAL_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QImage>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/videoio/videoio.hpp"

//#define USE_OPENCV_V4L2 1

QImage mat2qimage(const cv::Mat &mat);
cv::Mat qimage2mat(const QImage &qimage);

#endif // GLOBAL_H
