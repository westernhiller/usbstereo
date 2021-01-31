#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>

Canvas::Canvas(QWidget *parent)
    : QLabel(parent)
{
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), m_img);
}

void Canvas::updateImage(QImage image)
{
    m_img = QPixmap::fromImage(image);
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint endPoint = event->pos();

    if (event->button() == Qt::LeftButton)
        emit pickPoint(endPoint);
    else if(event->button() == Qt::RightButton)
        emit rpickPoint(endPoint);
    
   return QWidget::mouseReleaseEvent(event);
}

