/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/ros_qt_sub/main_window.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ros_qt_sub
{
using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget* parent) : QMainWindow(parent), qnode(argc, argv)
{
  ui.setupUi(this);  // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

  setWindowIcon(QIcon(":/images/icon.png"));

  qnode.init();

  QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

  qRegisterMetaType<std::string>("std::string");
  QObject::connect(&qnode, SIGNAL(msgSubSignal(std::string)), this, SLOT(msgSubCallback(std::string)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::msgSubCallback(std::string msg)
{
  ui.subMsg->clear();
  QString msgQ = QString::fromStdString(msg);
  ui.subMsg->setText(msgQ);
  qnode.isRecived = false;
}

/*****************************************************************************
** Functions
*****************************************************************************/

}  // namespace ros_qt_sub
