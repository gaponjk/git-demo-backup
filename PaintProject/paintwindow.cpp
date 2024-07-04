#include "paintwindow.h"
#include "ui_paintwindow.h"
#include "paintarea.h"
PaintWindow::PaintWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PaintWindow)
{
    ui->setupUi(this);

    image = new QImage(ui->label2->size(), QImage::Format_ARGB32);
    //image_backrownd->fill(Qt::transparent);
    image_backrownd=new QImage(ui->label->size(), QImage::Format_RGB32);
    image_backrownd->fill(Qt::white);
    ui->label2->setPixmap(QPixmap::fromImage(*image));
    ui->label3->setPixmap(QPixmap::fromImage(*image));
    ui->label->setPixmap(QPixmap::fromImage(*image_backrownd));
    pen.setColor(color=Qt::black);
    pen.setWidth(width=3);
    originalStyle=pen.style();
    drawing = false;
    paintArea=new PaintArea();
    paintArea->setShape(None);
}

PaintWindow::~PaintWindow()
{
    delete ui;
    delete image;
    delete image_backrownd;
    delete paintArea;
}

void PaintWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lastPoint = event->pos();
        lastPoint -= QPoint(0,20);
    }
    paintArea->mousePressEvent(event);
    combineImages();
}

void PaintWindow::mouseMoveEvent(QMouseEvent *event) {
    if (drawing && (event->buttons() & Qt::LeftButton)) {
        QPoint currentPoint = event->pos();
        currentPoint -= QPoint(0,20);

        QPainter painter(image);
        painter.setPen(pen);
        painter.drawLine(lastPoint, currentPoint);
        lastPoint = currentPoint;

        QPixmap map(QPixmap::fromImage(*image));
        ui->label2->setPixmap(map);
    }
    paintArea->mouseMoveEvent(event);
}
void PaintWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (paintArea->getDrawing() ||paintArea->getMoveable()) {
        paintArea->setColor(color);
        paintArea->setWidth(width);

        paintArea->mouseReleaseEvent(event);
        combineImages();
    }
}
void PaintWindow::combineImages(){
    ui->label3->setPixmap(QPixmap::fromImage(paintArea->getImage()));
}

void PaintWindow::keyReleaseEvent(QKeyEvent *event){
    paintArea->keyReleaseEvent(event);
}



void PaintWindow::on_action_save_triggered()
{
    if (!image->isNull()) {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить изображение"), "", tr("(*.png);;(*.jpg)"));
        if (!fileName.isEmpty()) {
            if (image->save(fileName)) {
                ui->statusbar->showMessage("Изобржаение сохранено успешно");
            } else {
                ui->statusbar->showMessage("Не удалось сохранить изображение");
            }
        }
    } else {
        ui->statusbar->showMessage("Нет изобржения для сохранения");
    }
}


void PaintWindow::on_action_jpg_triggered()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть изображение"), "", tr("(*.png);;(*.jpg)"));
    if (!fileName.isEmpty()) {
       if (image->load(fileName)) {
            ui->label2->setPixmap(QPixmap::fromImage(*image));
            ui->label2->adjustSize();
            ui->statusbar->showMessage("Изобржаение открыто успешно");
        } else {
           ui->statusbar->showMessage("Не удалось открыть изображение");
        }
    }
}
void PaintWindow::on_painter_color_triggered()
{
    color = QColorDialog::getColor(Qt::white, this, "Выберите цвет карандаша или фигуры");
    if(color.isValid()){
        pen.setColor(color);
        paintArea->setColor(color);
    }
}


void PaintWindow::on_backrownd_color_triggered()
{
    QColor colorb = QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");
    image_backrownd->fill(colorb);
    ui->label->setPixmap(QPixmap::fromImage(*image_backrownd));
}


void PaintWindow::on_action5_triggered()
{
    width=5;
    paintArea->setWidth(5);
    pen.setWidth(5);
}


void PaintWindow::on_action10_triggered()
{
    width=10;
    paintArea->setWidth(10);
    pen.setWidth(10);
}


void PaintWindow::on_action3_triggered()
{
    width=3;
    paintArea->setWidth(3);
    pen.setWidth(3);
}


void PaintWindow::on_action_pen_triggered()
{
    paintArea->setRemove(false);
    paintArea->setMoveable(false);
    paintArea->setConnect(false);
    paintArea->setShape(None);
    settingPen();
}

void PaintWindow::on_action_triggered()
{
    settingPen();
    originalStyle=pen.style();
    paintArea->setShape(Triangle);
    pen.setStyle(Qt::NoPen);
    paintArea->setConnect(false);
    paintArea->setMoveable(false);
    paintArea->setRemove(false);
}


void PaintWindow::on_action_ellipse_triggered()
{
    settingPen();
    originalStyle=pen.style();
    paintArea->setShape(Ellipse);
    pen.setStyle(Qt::NoPen);
    paintArea->setConnect(false);
    paintArea->setMoveable(false);
    paintArea->setRemove(false);
}
void PaintWindow::on_action_rectangle_triggered(){
    settingPen();
    originalStyle=pen.style();
    paintArea->setShape(Rectangle);
    pen.setStyle(Qt::NoPen);
    paintArea->setConnect(false);
    paintArea->setMoveable(false);
    paintArea->setRemove(false);
}

void PaintWindow::on_action_bound_triggered()
{
    settingPen();
    originalStyle=pen.style();
    paintArea->setShape(None);
    pen.setStyle(Qt::NoPen);
    paintArea->setConnect(true);
    paintArea->setMoveable(false);
    paintArea->setRemove(false);
}

void PaintWindow::on_action_moveable_triggered()
{
    settingPen();
    originalStyle=pen.style();
    paintArea->setShape(None);
    pen.setStyle(Qt::NoPen);
    paintArea->setConnect(false);
    paintArea->setMoveable(true);
    paintArea->setRemove(false);
}
void PaintWindow::on_action_delete_triggered()
{
    settingPen();
    originalStyle=pen.style();
    paintArea->setShape(None);
    pen.setStyle(Qt::NoPen);
    paintArea->setConnect(false);
    paintArea->setMoveable(false);
    paintArea->setRemove(true);
}
void PaintWindow::settingPen(){
    pen.setStyle(originalStyle);
    pen.setColor(color);
    pen.setWidth(width);
}




