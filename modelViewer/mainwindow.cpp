#include "mainwindow.h"
#include "ui_mainwindow.h"

#define VIEWER_ANGLE 15
#define ZOOMING 1.2
#define SHIFT_DISTANCE 20

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
#define DEF(a, b) a = findChild<b*>( #a )
#define BUTTON_CONNECT(a) connect(a, SIGNAL(clicked()), this, SLOT(do_ ## a()))
#define DEFF(a, b) DEF(a, b); BUTTON_CONNECT(a)

	DEFF(open, QPushButton);
	DEFF(save, QPushButton);
	DEFF(quit, QPushButton);
	DEFF(trace, QPushButton);


	DEF(simplify, QPushButton);
    connect(simplify, SIGNAL(clicked()), this, SLOT(update_mesh()));

	DEF(smooth, QCheckBox);
	connect(smooth, SIGNAL(toggled(bool)), this, SLOT(update_mesh()));

	DEF(pic, QGraphicsView);
	DEF(target_rate, QLineEdit);

    scene = new QGraphicsScene();
    pixmap = new QPixmap(pic->width() - 10, pic->height() - 10);
    image = new QImage(pic->width() - 10, pic->height() - 10, QImage::Format_RGB32);
    scene->addPixmap(*pixmap);
    pic->setScene(scene);

	DEFF(shift_up, QPushButton);
	DEFF(shift_down, QPushButton);
	DEFF(shift_right, QPushButton);
	DEFF(shift_left, QPushButton);

	DEFF(rotate_left, QPushButton);
	DEFF(rotate_right, QPushButton);
	DEFF(twist_left, QPushButton);
	DEFF(twist_right, QPushButton);
	DEFF(orbit_left, QPushButton);
	DEFF(orbit_right, QPushButton);

	DEFF(zoom_in, QPushButton);
	DEFF(zoom_out, QPushButton);


	done_load = true;
	done_load = false;
}

void MainWindow::do_trace() {
    if(done_load == false) {
        QMessageBox::critical(this, tr("Error"), tr("Please open a obj file"));
        return;
    }
}

void MainWindow::do_open() {
	QString fname = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Obj Files (*.obj);;"));
	if(fname != "") {
		QFile file(fname);
		if(!file.open(QIODevice::ReadOnly)) {
			QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
			return;
		}

		now_fname = fname.toStdString();
	}
	done_load = true;
}

void MainWindow::do_save() {
	QString fname = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Png Files (*.png);;"));
    //if(fname != "") viewer->r.save(fname.toStdString().c_str());
}

void MainWindow::update_mesh() {
	if(done_load == false) {
		QMessageBox::critical(this, tr("Error"), tr("Please open a obj file."));
		return;
	}

}

void MainWindow::update_scene() {
	QPixmap pixmap = QPixmap::fromImage(*image);
	scene->clear();
	scene->addPixmap(pixmap);
	scene->update();

	pic->setScene(scene);
	pic->viewport()->update();
	QApplication::processEvents();
}

void MainWindow::do_shift_up() {
    //view->shift(SHIFT_DISTANCE, false);
}
void MainWindow::do_shift_down() {
    //view->shift(-SHIFT_DISTANCE, false);
}
void MainWindow::do_shift_left() {
    //view->shift(SHIFT_DISTANCE, true);
}
void MainWindow::do_shift_right() {
    //view->shift(-SHIFT_DISTANCE, true);
}
void MainWindow::do_rotate_left() {
    //view->rotate(VIEWER_ANGLE);
}
void MainWindow::do_rotate_right() {
    //view->rotate(-VIEWER_ANGLE);
}
void MainWindow::do_orbit_left() {
    //view->orbit(-VIEWER_ANGLE);
}
void MainWindow::do_orbit_right() {
    //view->orbit(VIEWER_ANGLE);
}
void MainWindow::do_twist_left() {
    //view->twist(VIEWER_ANGLE);
}
void MainWindow::do_twist_right() {
    //view->twist(-VIEWER_ANGLE);
}
void MainWindow::do_zoom_in() {
    //view->zoom(ZOOMING);
};
void MainWindow::do_zoom_out() {
    //view->zoom(1.0 / ZOOMING);
};

MainWindow::~MainWindow() {
    delete ui;
    //delete view;
    //delete viewer;
    delete scene;
    delete pixmap;
    delete image;
}
void MainWindow::do_quit() { qApp->quit(); }
