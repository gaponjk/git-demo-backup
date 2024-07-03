#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
enum Shape { None, Rectangle, Triangle, Ellipse };
class PaintArea : public QWidget {
    Q_OBJECT

public:


    PaintArea(QWidget *parent = nullptr);
    ~PaintArea();
    void setShape(Shape shape);
    void setColor(QColor color);
    void setWidth(int width);
    void setConnect(bool connect);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    QImage getImage(){
        return *image;
    }
    Shape getCurrentShape(){
        return currentShape;
    }
    void enableConnectionMode();
protected:

private:
    int width;
    QPen pen;
    Shape currentShape=None;
    QPainter painter;
    QImage *image;
    QColor color;
    QPoint startPoint;
    QPoint currentPoint;
    bool drawing;
    bool connectionMode;
    QPoint firstConnectionPoint;
    bool isFirstPointSelected;
    QList<QPair<Shape, QPair<QPoint, QPoint>>> shapes;

    void drawShape(Shape shape, const QPoint &start, const QPoint &end);
    QPoint getShapeCenter(const QPair<QPoint, QPoint> &shape);

    QPolygon getShapeTriangle(const QPoint &start, const QPoint &end);
    QPolygon getShapeEllipse(const QPoint &start, const QPoint &end);
};

#endif // PAINTAREA_H
