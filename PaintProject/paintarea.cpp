#include "paintarea.h"
PaintArea::PaintArea(QWidget *parent)
    : QWidget(parent), currentShape(None), drawing(false) {
    setMouseTracking(true);
    image=new QImage(1920,1080, QImage::Format_ARGB32);
    painter.begin(image);
    connectionMode = false;
    isFirstPointSelected = false;
    moveable=false;
    moving=false;
    painter.setPen(pen);
}
PaintArea::~PaintArea(){
    delete image;
    delete movingShape;
    painter.end();
}

void PaintArea::setShape(Shape shape) {
    currentShape = shape;
}

void PaintArea::mousePressEvent(QMouseEvent *event) {
    startPoint = event->pos();
    startPoint -= QPoint(0, 20);
    if (event->button() == Qt::LeftButton && currentShape != None) {
        drawing = true;
    }
    if (moveable&&event->button() == Qt::LeftButton) {
        for (auto &shape : shapes) {
            if (shape.first.containsPoint(event->pos() - QPoint(0, 20), Qt::OddEvenFill)) {
                moving = true;
                movingShape = &shape;
                break;
            }
        }
    }
    if (remove) {//самый стабильный варинат работы
        for (int i = 0; i < shapes.size(); ++i) {
            if (shapes[i].first.containsPoint(event->pos() - QPoint(0, 20), Qt::OddEvenFill) && event->button() == Qt::LeftButton) {

                for (int j = 0; j < connections.size(); ) {
                    if (shapes[i].first.containsPoint(connections[j].first, Qt::OddEvenFill) ||
                        shapes[i].first.containsPoint(connections[j].second, Qt::OddEvenFill)) {
                        connections.removeAt(j);
                        connectPens.removeAt(j);
                    } else {
                        ++j;
                    }
                }
                shapes.removeAt(i);
                models.removeAt(i);
                shapePens.removeAt(i);
                --i;
            }
        }
        updateRemovels();
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
                    connections.append(qMakePair(firstConnectionPoint, center));
                    connectPens.append(pen);
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
    if (event->button() == Qt::RightButton){
        drawing = false;
        isFirstPointSelected = false;
        moving = false;
        movingShape = nullptr;
    }
}

void PaintArea::mouseMoveEvent(QMouseEvent *event) {
    if (drawing) {
        currentPoint = event->pos();
        currentPoint-= QPoint(0,20);
        update();
    }else if (moving && movingShape) {
        QPoint newCenter = event->pos() - QPoint(0, 20);
        QPoint oldCenter = getShapeCenter(movingShape->second);
        for ( auto &connection : connections) {
            if(connection.first==oldCenter)
                connection.first=newCenter;
            else if(connection.second==oldCenter)
                connection.second=newCenter;
        }

        QPoint delta = newCenter - oldCenter;

        movingShape->second.first += delta;
        movingShape->second.second += delta;

        QPolygon newPolygon;
        for (int i = 0; i < movingShape->first.size(); ++i) {
            newPolygon << (movingShape->first.point(i) + delta);
        }
        movingShape->first = newPolygon;


        update();
    }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing ) {
        drawing = false;
        shapes.append(qMakePair( drawShape(currentShape, startPoint, currentPoint), qMakePair(startPoint, currentPoint)));
        models.append(currentShape);
        shapePens.append(pen);
        update();
    } else if (event->button() == Qt::LeftButton && moveable) {
        updateConnections();
        moving = false;
        movingShape = nullptr;
        update();
    }
}

void PaintArea::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape){
        drawing =false;
        isFirstPointSelected = false;
        moving = false;
        movingShape = nullptr;
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
void PaintArea::setMoveable(bool moveable){
    this->moveable=moveable;
}
void PaintArea::setRemove(bool remove){
    this->remove=remove;
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

void PaintArea::updateConnections() {
    image->fill(Qt::transparent);
    painter.end();
    painter.begin(image);
    painter.setPen(pen);

    for (int i = 0; i < shapes.size(); ++i) {
        painter.setPen(shapePens[i]);
        painter.drawPolygon(shapes[i].first);
    }

    for (int i = 0; i < connections.size(); ++i)  {
        painter.setPen(connectPens.at(i));
        bool isLeft = false, isRight = false;
        for (const auto &shape : shapes) {
            if (shape.first.containsPoint(connections[i].first, Qt::OddEvenFill))
                isLeft = true;
            if (shape.first.containsPoint(connections[i].second, Qt::OddEvenFill))
                isRight = true;
        }
        if (isLeft && isRight)
            painter.drawLine(connections[i].first, connections[i].second);
         else if (isLeft)
            painter.drawLine(connections[i].first, getShapeCenter(movingShape->second));
         else if (isRight)
            painter.drawLine(getShapeCenter(movingShape->second), connections[i].second);
    }
    update();
}
void PaintArea::updateRemovels(){
    image->fill(Qt::transparent);
    painter.end();
    painter.begin(image);
    for (int i = 0; i < shapes.size(); ++i) {
        painter.setPen(shapePens[i]);
        painter.drawPolygon(shapes[i].first);
    }
    for (int i = 0; i < connections.size(); ++i) {
        painter.setPen(connectPens.at(i));
        painter.drawLine(connections[i].first, connections[i].second);
    }
    update();
}
bool PaintArea::saveFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Не получается открыть файл для записи";
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_15);

    out << int(shapes.size());
    for (int i = 0; i < shapes.size(); ++i) {
        out<<shapePens.at(i) << models.at(i);
        out << shapes[i].second.first << shapes[i].second.second;
    }

    out << int(connections.size());
    for (int i = 0; i < connections.size(); ++i) {
        out<<connectPens.at(i);
        out << connections[i].first << connections[i].second;
    }

    file.close();
    return true;
}

bool PaintArea::loadFile(const QString &fileName){

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Не получается открыть файл для чтения";
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_15);

    shapes.clear();
    connections.clear();
    shapePens.clear();
    int shapesSize;
    in >> shapesSize;
    for (int i = 0; i < shapesSize; ++i) {
        Shape model;
        QPen pen;
        QPoint point1, point2;
        in >>pen>> model;
        in >> point1 >> point2;
        shapePens.append(pen);
        this->pen=pen;
        painter.setPen(pen);
        shapes.append(qMakePair(drawShape(model, point1, point2), qMakePair(point1, point2)));
        models.append(model);
    }

    int connectionsSize;
    in >> connectionsSize;
    for (int i = 0; i < connectionsSize; ++i) {
        QPen pen;
        QPoint point1, point2;
        in>>pen >> point1 >> point2;
        connectPens.append(pen);
        painter.setPen(pen);
        connections.append(qMakePair(point1, point2));
        painter.drawLine(point1, point2);

    }

    file.close();
    update();
    return true;
}
