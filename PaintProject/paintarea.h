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
    void setMoveable(bool moveable);
    void setRemove(bool remove);
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
    bool getMoveable(){
        return moveable;
    }
    bool getDrawing(){
        return drawing;
    }
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
    QVector<QPair<QPolygon, QPair<QPoint, QPoint>>> shapes;
    bool moving;
    QPair<QPolygon, QPair<QPoint, QPoint>> *movingShape;
    QVector<QPair<QPoint, QPoint>> connections;
    QPoint offset;
    bool moveable;
    bool remove;

    QPolygon drawShape(Shape shape, const QPoint &start, const QPoint &end);
    QPoint getShapeCenter(const QPair<QPoint, QPoint> &shape);

    QPolygon getShapeTriangle(const QPoint &start, const QPoint &end);
    QPolygon getShapeEllipse(const QPoint &start, const QPoint &end);

    void updateConnections();
    void updateRemovels();
};

#endif // PAINTAREA_H
