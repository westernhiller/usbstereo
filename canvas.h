#ifndef CANVAS_H
#define CANVAS_H

#include <QLabel>
#include <QPixmap>
#include <QImage>

class Canvas : public QLabel
{
    Q_OBJECT

public:
    explicit Canvas(QWidget* parent = nullptr);

signals:
    void setROI(QRect);
    void pickPoint(QPoint);
    void rpickPoint(QPoint);

protected:
    virtual void paintEvent(QPaintEvent *ev);
    void mouseReleaseEvent(QMouseEvent *event);

private:
private:
    QPixmap m_img;					/*!<按键图像 */

public slots:
    void updateImage(QImage);
};

#endif // IMAGEBUTTON_H
