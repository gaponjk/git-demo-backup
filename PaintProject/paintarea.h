#ifndef PAINTAREA_H
#define PAINTAREA_H
// этот класс я создал, чтобы
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QFile>
#include<QMessageBox>
enum Shape { None, Rectangle, Triangle, Ellipse };//чтобы определять фигуру
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
    bool saveFile(const QString &fileName);
    bool loadFile(const QString &fileName);
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
    int width;//толщина для обработаваемой фигуры
    QPen pen;//карандаш для рисовки
    Shape currentShape=None;//для обработаваемой фигуры
    QPainter painter;//исую этой штукой
    QImage *image;//куда рисую
    QColor color;//цвет для обработаваемой фигуры
    QPoint startPoint;//точка слева ввеврху
    QPoint currentPoint;//точка справа внизу эти две точки нужны, чтобы понять каких размеров фигура
    bool drawing;//отрисовываю ли я фигуру
    bool connectionMode;//ставить ли мне конекторы
    QPoint firstConnectionPoint;
    bool isFirstPointSelected;//опрееделяю стадию соеденения
    QVector<QPair<QPolygon, QPair<QPoint, QPoint>>> shapes;//массив фигур с их координатами и их полигонами
    QVector <Shape> models;//массив фигур
    QVector <QPen> shapePens,connectPens;//массив из рисовашек для фигур и коннекторов,последний три массива
    //по факту работают одновременно с основными  массивами этих фигур
    bool moving;//перемещаю ли я фигуру
    QPair<QPolygon, QPair<QPoint, QPoint>> *movingShape;//фигура кооторую я перемещаю
    QVector<QPair<QPoint, QPoint>> connections;//массив коннекторов
    bool moveable;//можно ли перемещать фигуру
    bool remove;//надо ли удалять фигуру

    QPolygon drawShape(Shape shape, const QPoint &start, const QPoint &end);
    QPoint getShapeCenter(const QPair<QPoint, QPoint> &shape);

    QPolygon getShapeTriangle(const QPoint &start, const QPoint &end);
    QPolygon getShapeEllipse(const QPoint &start, const QPoint &end);

    void updateConnections();
    void updateRemovels();
};

#endif // PAINTAREA_H
