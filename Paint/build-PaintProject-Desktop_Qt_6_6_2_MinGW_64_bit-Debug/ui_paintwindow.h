/********************************************************************************
** Form generated from reading UI file 'paintwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINTWINDOW_H
#define UI_PAINTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaintWindow
{
public:
    QAction *action_jpg;
    QAction *action_save;
    QAction *action3;
    QAction *action5;
    QAction *painter_color;
    QAction *backrownd_color;
    QAction *action10;
    QAction *action;
    QAction *action_rectangle;
    QAction *action_ellipse;
    QAction *action_pen;
    QAction *action_bound;
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label2;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_7;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PaintWindow)
    {
        if (PaintWindow->objectName().isEmpty())
            PaintWindow->setObjectName("PaintWindow");
        PaintWindow->resize(960, 540);
        PaintWindow->setMinimumSize(QSize(0, 0));
        PaintWindow->setMaximumSize(QSize(16777215, 16777215));
        PaintWindow->setCursor(QCursor(Qt::ArrowCursor));
        action_jpg = new QAction(PaintWindow);
        action_jpg->setObjectName("action_jpg");
        action_save = new QAction(PaintWindow);
        action_save->setObjectName("action_save");
        action3 = new QAction(PaintWindow);
        action3->setObjectName("action3");
        action5 = new QAction(PaintWindow);
        action5->setObjectName("action5");
        painter_color = new QAction(PaintWindow);
        painter_color->setObjectName("painter_color");
        backrownd_color = new QAction(PaintWindow);
        backrownd_color->setObjectName("backrownd_color");
        action10 = new QAction(PaintWindow);
        action10->setObjectName("action10");
        action = new QAction(PaintWindow);
        action->setObjectName("action");
        action_rectangle = new QAction(PaintWindow);
        action_rectangle->setObjectName("action_rectangle");
        action_ellipse = new QAction(PaintWindow);
        action_ellipse->setObjectName("action_ellipse");
        action_pen = new QAction(PaintWindow);
        action_pen->setObjectName("action_pen");
        action_bound = new QAction(PaintWindow);
        action_bound->setObjectName("action_bound");
        centralwidget = new QWidget(PaintWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 1920, 1080));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(1920, 1080));
        label->setMaximumSize(QSize(1920, 1080));
        label->setMouseTracking(false);
        label2 = new QLabel(centralwidget);
        label2->setObjectName("label2");
        label2->setGeometry(QRect(0, 0, 1920, 1080));
        sizePolicy.setHeightForWidth(label2->sizePolicy().hasHeightForWidth());
        label2->setSizePolicy(sizePolicy);
        label2->setMinimumSize(QSize(1920, 1080));
        label2->setMaximumSize(QSize(1920, 1080));
        label2->setMouseTracking(false);
        PaintWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PaintWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 960, 21));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName("menu_4");
        menu_7 = new QMenu(menubar);
        menu_7->setObjectName("menu_7");
        PaintWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PaintWindow);
        statusbar->setObjectName("statusbar");
        PaintWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_7->menuAction());
        menu->addAction(action_jpg);
        menu->addAction(action_save);
        menu_2->addAction(painter_color);
        menu_2->addAction(backrownd_color);
        menu_3->addAction(action3);
        menu_3->addAction(action5);
        menu_3->addAction(action10);
        menu_4->addAction(action);
        menu_4->addAction(action_rectangle);
        menu_4->addAction(action_ellipse);
        menu_4->addAction(action_pen);
        menu_7->addAction(action_bound);

        retranslateUi(PaintWindow);

        QMetaObject::connectSlotsByName(PaintWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PaintWindow)
    {
        PaintWindow->setWindowTitle(QCoreApplication::translate("PaintWindow", "PaintWindow", nullptr));
        action_jpg->setText(QCoreApplication::translate("PaintWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        action_save->setText(QCoreApplication::translate("PaintWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        action3->setText(QCoreApplication::translate("PaintWindow", "3 \320\277\321\202", nullptr));
        action5->setText(QCoreApplication::translate("PaintWindow", "5 \320\277\321\202", nullptr));
        painter_color->setText(QCoreApplication::translate("PaintWindow", "\320\246\320\262\320\265\321\202 \320\272\320\276\320\275\321\202\321\203\321\200\320\260", nullptr));
        backrownd_color->setText(QCoreApplication::translate("PaintWindow", "\320\246\320\262\320\265\321\202 \321\204\320\276\320\275\320\260", nullptr));
        action10->setText(QCoreApplication::translate("PaintWindow", "10 \320\277\321\202", nullptr));
        action->setText(QCoreApplication::translate("PaintWindow", "\320\242\321\200\320\265\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272", nullptr));
        action_rectangle->setText(QCoreApplication::translate("PaintWindow", "\320\237\321\200\321\217\320\274\320\276\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272", nullptr));
        action_ellipse->setText(QCoreApplication::translate("PaintWindow", "\320\255\320\273\320\273\320\270\320\277\321\201", nullptr));
        action_pen->setText(QCoreApplication::translate("PaintWindow", "\320\232\320\260\321\200\320\260\320\275\320\264\320\260\321\210", nullptr));
        action_bound->setText(QCoreApplication::translate("PaintWindow", "\320\241\320\262\321\217\320\267\320\260\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("PaintWindow", "TextLabel", nullptr));
        label2->setText(QCoreApplication::translate("PaintWindow", "TextLabel", nullptr));
        menu->setTitle(QCoreApplication::translate("PaintWindow", "\320\244\320\260\320\271\320\273", nullptr));
        menu_2->setTitle(QCoreApplication::translate("PaintWindow", "\320\246\320\262\320\265\321\202", nullptr));
        menu_3->setTitle(QCoreApplication::translate("PaintWindow", "\320\242\320\276\320\273\321\211\320\270\320\275\320\260", nullptr));
        menu_4->setTitle(QCoreApplication::translate("PaintWindow", "\320\244\320\270\320\263\321\203\321\200\321\213 \320\270 \320\272\320\260\321\200\320\260\320\275\320\264\320\260\321\210", nullptr));
        menu_7->setTitle(QCoreApplication::translate("PaintWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214, \320\277\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214 \320\270 \321\201\320\262\321\217\320\267\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PaintWindow: public Ui_PaintWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTWINDOW_H
