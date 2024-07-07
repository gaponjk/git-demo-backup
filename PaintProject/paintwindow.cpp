#include "paintwindow.h"
#include "ui_paintwindow.h"
#include "paintarea.h"
PaintWindow::PaintWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PaintWindow)
{
    ui->setupUi(this);

    image = new QImage(ui->label2->size(), QImage::Format_ARGB32);//ARGB, потому что тогда изображение изначально прозрачное
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

void PaintWindow::mousePressEvent(QMouseEvent *event) {//движение мыши
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lastPoint = event->pos();
        lastPoint -= QPoint(0,20);
    }
    if(paintArea->getMoveable())
        setCursor(Qt::ClosedHandCursor);//ставлю курсор если двигаю фигуру
    paintArea->mousePressEvent(event);//для обратботки фигур связей и удаления

    combineImages();
}

void PaintWindow::mouseMoveEvent(QMouseEvent *event) {//движение мыши
    if (drawing && (event->buttons() & Qt::LeftButton)) {//рисую карандашом, соеденяя точки
        QPoint currentPoint = event->pos();
        currentPoint -= QPoint(0,20);

        QPainter painter(image);
        painter.setPen(pen);
        painter.drawLine(lastPoint, currentPoint);
        lastPoint = currentPoint;

        QPixmap map(QPixmap::fromImage(*image));
        ui->label2->setPixmap(map);
    }
    paintArea->mouseMoveEvent(event);//для обратботки фигур связей и удаления
}
void PaintWindow::mouseReleaseEvent(QMouseEvent *event) {//отпускание мыши
    if (paintArea->getDrawing() ||paintArea->getMoveable()) {
        paintArea->setColor(color);
        paintArea->setWidth(width);

        paintArea->mouseReleaseEvent(event);//для обратботки фигур связей и удаления
        combineImages();
    }
    if(paintArea->getMoveable())
       setCursor(Qt::OpenHandCursor);//ставлю курсор если перестаю двигать фигуру
}
void PaintWindow::combineImages(){//для того чтобы вывести слой с фигурами и связями
    ui->label3->setPixmap(QPixmap::fromImage(paintArea->getImage()));
}

void PaintWindow::keyReleaseEvent(QKeyEvent *event){//отпускание кнопки
    paintArea->keyReleaseEvent(event);//для реализаци отмены деяствия с фигурами удалением и связями
}



void PaintWindow::on_action_save_triggered() {//копка Сохранить
    QMessageBox::warning(this,"Сохранение файла","При сохранении Ваша работа будет сохранена в два файла:"
                                                   "\n-Бинарный файл с фигурами и их связими\n-JPG Файл с фоном и тем, что вы писали карандашом.\n");
    paintArea->setRemove(false);
    paintArea->setMoveable(false);
    paintArea->setConnect(false);
    paintArea->setShape(None);
    setCursor(Qt::ArrowCursor);//на всякий случай
    settingPen();
    QPainter painter(image_backrownd);
    painter.drawImage(0, 0, *image);

    if (!image->isNull()) {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить изображение"), "", tr("Binary Files (*.bin)"));

        if (!fileName.isEmpty()) {
            bool binSaved = paintArea->saveFile(fileName);

            QString jpegFileName = fileName;
            jpegFileName.replace(jpegFileName.length() - 4, 4, ".jpg");// я сохраняю два файла, бинарный файл с фигурами и .jpg файл с фоном и карандашом
            bool jpgSaved = image_backrownd->save(jpegFileName);

            if (binSaved && jpgSaved) {
                ui->statusbar->showMessage("Изображение сохранено успешно");//на всякий
            } else {
                ui->statusbar->showMessage("Не удалось сохранить изображение");
            }
        }
    } else {
        ui->statusbar->showMessage("Нет изображения для сохранения");//на всякий
    }
}

void PaintWindow::on_action_jpg_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть изображение"), "", tr("Binary Files (*.bin)"));
    paintArea->setRemove(false);
    paintArea->setMoveable(false);
    paintArea->setConnect(false);
    paintArea->setShape(None);
    setCursor(Qt::ArrowCursor);//на всякий
    settingPen();
    if (!fileName.isEmpty()) {
        if (paintArea->loadFile(fileName)) {
            QString jpegFileName = fileName;
            jpegFileName.replace(jpegFileName.length() - 4, 4, ".jpg");//сразу открывается и бинарный и jpg файл, это все сделано для того,
            //чтобы можно было работать с фигурамми

            if (image_backrownd->load(jpegFileName)) {
                combineImages();
                ui->label->setPixmap(QPixmap::fromImage(*image_backrownd));
                ui->statusbar->showMessage("Изображение открыто успешно");
            } else {
                QMessageBox::warning(this,"Причина возможной ошибки","Вы могли удалить или переименовать JPG файл");
                ui->statusbar->showMessage("Не удалось открыть изображение в формате JPG");
            }
        } else {
            ui->statusbar->showMessage("Не удалось открыть изображение в формате BIN");//на всякий
        }
    }
}
void PaintWindow::on_painter_color_triggered()//меняю цвет карандаша фигуры связи
{
    color = QColorDialog::getColor(Qt::white, this, "Выберите цвет карандаша или фигуры");
    if(color.isValid()){
        pen.setColor(color);
        paintArea->setColor(color);
    }
}


void PaintWindow::on_backrownd_color_triggered()//меняю цвет фона
{
    QColor colorb = QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");
    image_backrownd->fill(colorb);
    ui->label->setPixmap(QPixmap::fromImage(*image_backrownd));
}


void PaintWindow::on_action5_triggered()//следующие три метода для изменения ширины у фигуры карандаша и связи
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


void PaintWindow::on_action_pen_triggered()//для активации каранадаша, несмотря на то что карандаш работает по дефолту
{
    paintArea->setRemove(false);
    paintArea->setMoveable(false);
    paintArea->setConnect(false);
    paintArea->setShape(None);
    setCursor(Qt::ArrowCursor);
    settingPen();
}

void PaintWindow::on_action_triggered()//для отрисовки треугольника
{
    settingPen();
    originalStyle=pen.style();
    paintArea->setShape(Triangle);
    pen.setStyle(Qt::NoPen);
    setCursor(Qt::ArrowCursor);
    paintArea->setConnect(false);
    paintArea->setMoveable(false);
    paintArea->setRemove(false);
}


void PaintWindow::on_action_ellipse_triggered()//для отрисовки эллипса
{
    settingPen();
    originalStyle=pen.style();
    paintArea->setShape(Ellipse);
    pen.setStyle(Qt::NoPen);
    setCursor(Qt::ArrowCursor);
    paintArea->setConnect(false);
    paintArea->setMoveable(false);
    paintArea->setRemove(false);
}
void PaintWindow::on_action_rectangle_triggered(){//для отрисовки прямоугольника
    settingPen();
    originalStyle=pen.style();
    paintArea->setShape(Rectangle);
    pen.setStyle(Qt::NoPen);
    setCursor(Qt::ArrowCursor);
    paintArea->setConnect(false);
    paintArea->setMoveable(false);
    paintArea->setRemove(false);
}

void PaintWindow::on_action_bound_triggered()//для отрисовки связи между фигурами
{
    settingPen();
    originalStyle=pen.style();
    paintArea->setShape(None);
    pen.setStyle(Qt::NoPen);
    setCursor(Qt::ArrowCursor);
    paintArea->setConnect(true);
    paintArea->setMoveable(false);
    paintArea->setRemove(false);
}

void PaintWindow::on_action_moveable_triggered()//для передвижения фигуры
{
    settingPen();
    originalStyle=pen.style();
    paintArea->setShape(None);
    pen.setStyle(Qt::NoPen);
    setCursor(Qt::OpenHandCursor);
    paintArea->setConnect(false);
    paintArea->setMoveable(true);
    paintArea->setRemove(false);
}
void PaintWindow::on_action_delete_triggered()//для удаления фигур с ее связми
{
    settingPen();
    originalStyle=pen.style();
    paintArea->setShape(None);
    pen.setStyle(Qt::NoPen);
    setCursor(Qt::ArrowCursor);
    paintArea->setConnect(false);
    paintArea->setMoveable(false);
    paintArea->setRemove(true);
}
void PaintWindow::settingPen(){//для удобства
    pen.setStyle(originalStyle);
    pen.setColor(color);
    pen.setWidth(width);
}




