#ifndef CALIBDIALOG_H
#define CALIBDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QRect>
#include "global.h"
#include "canvas.h"

class CalibDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalibDialog(QWidget *parent = nullptr);
    ~CalibDialog();

signals:
    void passPoints(QVector<QPoint>);
    void updateImage(QImage);

private:
    Canvas* m_pCanvas;
    cv::Mat m_image;

private:

public slots:
    void display(cv::Mat);
};

#endif // CALIBDIALOG_H
