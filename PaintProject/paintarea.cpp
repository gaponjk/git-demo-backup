#include "paintarea.h"
PaintArea::PaintArea(QWidget *parent)
    : QWidget(parent), currentShape(None), drawing(false) {
    setMouseTracking(true);
    image=new QImage(1920,1080, QImage::Format_ARGB32);
    painter.begin(image);
    connectionMode = false;
    isFirstPointSelected = false;
}
PaintArea::~PaintArea(){
    delete image;
}

void PaintArea::setShape(Shape shape) {
    currentShape = shape;
}

void PaintArea::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && currentShape != None) {
        startPoint = event->pos();
        startPoint -= QPoint(0,20);
        drawing = true;
    }
    if (connectionMode) {
        bool clickedOnShape = false;
        for (const auto &shape : shapes) {
            QPoint center = getShapeCenter(shape.second);
            if (shape.first.containsPoint(event->pos()-QPoint(0,20), Qt::OddEvenFill)&&event->button() == Qt::LeftButton) {
                clickedOnShape = true;
                if(firstConnectionPoint==center)
                    break;
                if (!isFirstPointSelected) {
                    firstConnectionPoint = center;
                    isFirstPointSelected = true;
                } else {
                    painter.setPen(pen);
                    painter.drawLine(firstConnectionPoint, center);
                    isFirstPointSelected = false;
                    update();
                }
                break;
            }
        }
        if (!clickedOnShape)
            isFirstPointSelected = false;
    }else
        isFirstPointSelected = false;
    if (event->button() == Qt::RightButton)
    isFirstPointSelected = false;
}

void PaintArea::mouseMoveEvent(QMouseEvent *event) {
    if (drawing) {
        currentPoint = event->pos();
        currentPoint-= QPoint(0,20);
        update();
    }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event) {
    if (currentShape==None)
        return;
    if (event->button() == Qt::LeftButton && drawing ) {
        drawing = false;
        shapes.append(qMakePair( drawShape(currentShape, startPoint, currentPoint), qMakePair(startPoint, currentPoint)));
        update();
    } else if (event->button() == Qt::RightButton) {
        drawing = false;
        update();
    }
}

void PaintArea::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape){
        drawing =false;
        isFirstPointSelected = false;
        update();
    }
}

QPolygon PaintArea::drawShape(Shape shape, const QPoint &start, const QPoint &end) {

    painter.setPen(pen);
    QPolygon temp;

    switch (shape) {
    case Rectangle:
        temp=QPolygon(QRect(start, end));
        break;
    case Triangle: {
        temp=getShapeTriangle(start,end);
        break;
    }
    case Ellipse:
        temp=getShapeEllipse(start,end);
        break;
    default:
        break;
    }
    painter.drawPolygon(temp);
    return temp;
}

QPolygon PaintArea::getShapeTriangle(const QPoint &start, const QPoint &end){
    QPoint top((start.x() + end.x()) / 2, start.y());
    QPoint left(start.x(), end.y());
    QPoint right(end.x(), end.y());
    QPolygon triangle;
    triangle << top << left << right;
    return triangle;
}
QPolygon PaintArea::getShapeEllipse(const QPoint &start, const QPoint &end)  {
    QPolygon ellipse;
    QRect rect(start, end);
    int steps = 200;
    for (int i = 0; i < steps; ++i) {
        double theta = 2.0 * M_PI * double(i) / double(steps);//угол
        double x = rect.center().x() + rect.width() / 2.0 * cos(theta);
        double y = rect.center().y() + rect.height() / 2.0 * sin(theta);
        ellipse << QPoint(x, y);
    }
    return ellipse;
}
QPoint PaintArea::getShapeCenter(const QPair<QPoint, QPoint> &shape) {
    return (shape.first + shape.second) / 2;
}

void PaintArea::setConnect(bool connect){
    this->connectionMode=connect;
}
void PaintArea::setColor(QColor color){
     this->color=color;
    pen.setWidth(width);
    pen.setColor(color);
   painter.setPen(pen);
}
void PaintArea::setWidth(int width){
    this->width=width;
    pen.setWidth(width);
    pen.setColor(color);
    painter.setPen(pen);
}
