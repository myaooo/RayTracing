/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *open_action;
    QAction *save_action;
    QAction *quit_action;
    QWidget *centralWidget;
    QGraphicsView *pic;
    QPushButton *trace;
    QPushButton *simplify;
    QFrame *line;
    QFrame *line_3;
    QPushButton *open;
    QPushButton *save;
    QPushButton *quit;
    QFrame *line_5;
    QPushButton *shift_up;
    QPushButton *shift_left;
    QPushButton *shift_right;
    QPushButton *shift_down;
    QPushButton *rotate_left;
    QPushButton *rotate_right;
    QPushButton *orbit_left;
    QPushButton *orbit_right;
    QPushButton *twist_left;
    QPushButton *twist_right;
    QPushButton *zoom_in;
    QPushButton *zoom_out;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 526);
        open_action = new QAction(MainWindow);
        open_action->setObjectName(QStringLiteral("open_action"));
        save_action = new QAction(MainWindow);
        save_action->setObjectName(QStringLiteral("save_action"));
        quit_action = new QAction(MainWindow);
        quit_action->setObjectName(QStringLiteral("quit_action"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pic = new QGraphicsView(centralWidget);
        pic->setObjectName(QStringLiteral("pic"));
        pic->setGeometry(QRect(29, 39, 500, 400));
        pic->setAutoFillBackground(false);
        trace = new QPushButton(centralWidget);
        trace->setObjectName(QStringLiteral("trace"));
        trace->setGeometry(QRect(550, 80, 91, 32));
        simplify = new QPushButton(centralWidget);
        simplify->setObjectName(QStringLiteral("simplify"));
        simplify->setGeometry(QRect(650, 80, 91, 32));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(550, 110, 191, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(550, 240, 191, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        open = new QPushButton(centralWidget);
        open->setObjectName(QStringLiteral("open"));
        open->setGeometry(QRect(550, 40, 91, 32));
        save = new QPushButton(centralWidget);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(650, 40, 91, 32));
        quit = new QPushButton(centralWidget);
        quit->setObjectName(QStringLiteral("quit"));
        quit->setGeometry(QRect(930, 670, 91, 32));
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(830, 560, 191, 20));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        shift_up = new QPushButton(centralWidget);
        shift_up->setObjectName(QStringLiteral("shift_up"));
        shift_up->setGeometry(QRect(600, 130, 88, 27));
        shift_left = new QPushButton(centralWidget);
        shift_left->setObjectName(QStringLiteral("shift_left"));
        shift_left->setGeometry(QRect(550, 170, 88, 27));
        shift_right = new QPushButton(centralWidget);
        shift_right->setObjectName(QStringLiteral("shift_right"));
        shift_right->setGeometry(QRect(650, 170, 88, 27));
        shift_down = new QPushButton(centralWidget);
        shift_down->setObjectName(QStringLiteral("shift_down"));
        shift_down->setGeometry(QRect(600, 210, 88, 27));
        rotate_left = new QPushButton(centralWidget);
        rotate_left->setObjectName(QStringLiteral("rotate_left"));
        rotate_left->setGeometry(QRect(550, 270, 88, 27));
        rotate_right = new QPushButton(centralWidget);
        rotate_right->setObjectName(QStringLiteral("rotate_right"));
        rotate_right->setGeometry(QRect(660, 270, 88, 27));
        orbit_left = new QPushButton(centralWidget);
        orbit_left->setObjectName(QStringLiteral("orbit_left"));
        orbit_left->setGeometry(QRect(550, 330, 88, 27));
        orbit_right = new QPushButton(centralWidget);
        orbit_right->setObjectName(QStringLiteral("orbit_right"));
        orbit_right->setGeometry(QRect(660, 330, 88, 27));
        twist_left = new QPushButton(centralWidget);
        twist_left->setObjectName(QStringLiteral("twist_left"));
        twist_left->setGeometry(QRect(550, 370, 88, 27));
        twist_right = new QPushButton(centralWidget);
        twist_right->setObjectName(QStringLiteral("twist_right"));
        twist_right->setGeometry(QRect(650, 370, 131, 27));
        zoom_in = new QPushButton(centralWidget);
        zoom_in->setObjectName(QStringLiteral("zoom_in"));
        zoom_in->setGeometry(QRect(550, 410, 88, 27));
        zoom_out = new QPushButton(centralWidget);
        zoom_out->setObjectName(QStringLiteral("zoom_out"));
        zoom_out->setGeometry(QRect(660, 410, 88, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ObjViewer", 0));
        open_action->setText(QApplication::translate("MainWindow", "Open", 0));
        save_action->setText(QApplication::translate("MainWindow", "Save", 0));
        quit_action->setText(QApplication::translate("MainWindow", "Quit", 0));
        trace->setText(QApplication::translate("MainWindow", "tracing", 0));
        simplify->setText(QApplication::translate("MainWindow", "simplifying", 0));
        open->setText(QApplication::translate("MainWindow", "open", 0));
        save->setText(QApplication::translate("MainWindow", "save", 0));
        quit->setText(QApplication::translate("MainWindow", "quit", 0));
        shift_up->setText(QApplication::translate("MainWindow", "shift up", 0));
        shift_left->setText(QApplication::translate("MainWindow", "shift left", 0));
        shift_right->setText(QApplication::translate("MainWindow", "shift right", 0));
        shift_down->setText(QApplication::translate("MainWindow", "shift down", 0));
        rotate_left->setText(QApplication::translate("MainWindow", "rotate left", 0));
        rotate_right->setText(QApplication::translate("MainWindow", "rotate right", 0));
        orbit_left->setText(QApplication::translate("MainWindow", "orbit left", 0));
        orbit_right->setText(QApplication::translate("MainWindow", "orbit right", 0));
        twist_left->setText(QApplication::translate("MainWindow", "twist clkwise", 0));
        twist_right->setText(QApplication::translate("MainWindow", "twist counterclkwise", 0));
        zoom_in->setText(QApplication::translate("MainWindow", "zoom in", 0));
        zoom_out->setText(QApplication::translate("MainWindow", "zoom out", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
