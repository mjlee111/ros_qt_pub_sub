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
#include "../include/ros_qt_pub/main_window.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ros_qt_pub
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
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_pubBtn_clicked()
{
  if (ui.pubMsg->text().isEmpty())
  {
    QMessageBox::warning(nullptr, "Warning", "There is no message to publish.");
    qnode.isPublished = true;
    return;
  }
  else
  {
    qnode.isPublished = false;
    qnode.msgData = ui.pubMsg->text().toStdString();
    qnode.publishMsg();
    ui.pubMsg->clear();
  }
}

/*****************************************************************************
** Functions
*****************************************************************************/

}  // namespace ros_qt_pub
