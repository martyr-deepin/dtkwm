#include "mainwindow.h"

#include <dscreenwindowsutil.h>
#include <QDebug>

DWM_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Double-screens");

    QPoint pos = this->cursor().pos();
    DScreenWindowsUtil* screenWin = DScreenWindowsUtil::instance(pos);

    qDebug() << "This is in the primaryScreen:" << screenWin->isPrimayScreen();
    QRect bgRect = screenWin->backgroundRect();
    this->move(bgRect.x(), bgRect.y());

}

MainWindow::~MainWindow()
{

}
