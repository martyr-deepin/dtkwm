/**
 * Copyright (C) 2017 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

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
