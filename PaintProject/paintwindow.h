#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include <QMainWindow>
#include<QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include<QColorDialog>
#include<QFileDialog>
#include"paintarea.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class PaintWindow;
}
QT_END_NAMESPACE

class PaintWindow : public QMainWindow
{
    Q_OBJECT

public:
    PaintWindow(QWidget *parent = nullptr);
    ~PaintWindow();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private slots:

    void on_painter_color_triggered();

    void on_backrownd_color_triggered();

    void on_action5_triggered();

    void on_action10_triggered();

    void on_action3_triggered();

    void on_action_triggered();

    void on_action_pen_triggered();

    void on_action_ellipse_triggered();

    void on_action_rectangle_triggered();

    void on_action_save_triggered();

    void on_action_jpg_triggered();

    void on_action_bound_triggered();

    void on_action_moveable_triggered();

    void on_action_delete_triggered();

private:
    int width;
    Ui::PaintWindow *ui;
    QColor color;
    Qt::PenStyle originalStyle;//для сохранения стиля перед тем как я его удаляю у карандаша
    QPoint lastPoint;//для непрерывности карандаша
    bool drawing;//когда рисую карандашом
    QPen pen;//сам карандаш, так же я его использую чтобы задавать цвет и толщину фигурам и связям
    QImage* image;//где я рисую карандашом
    QImage* image_backrownd;//фон
    PaintArea *paintArea;
    void combineImages();//для того чтобы вывести слой с фигурами и связями
    void settingPen();//для того чтобы было удобно задавать карандаш

};
#endif // PAINTWINDOW_H
