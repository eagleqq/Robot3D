#include "mainwindow.h"
#include "showdatetime.h"

#include "stlfileloader.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QStyleFactory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("机械臂实时显示");
  moveWindowToCenter();

  mRobot3DForDDR4Form = new Robot3DForDDR4Form(this);
  mRobot3DForDDR6Form = new Robot3DForDDR6Form(this);

  ui->stackedWidget->addWidget(mRobot3DForDDR4Form);
  ui->stackedWidget->addWidget(mRobot3DForDDR6Form);
  initSystemMonitor();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::moveWindowToCenter() {
  //屏幕居中
  this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                        this->size(),
                                        qApp->desktop()->availableGeometry()));
}

void MainWindow::initSystemMonitor()
{
    showDateTime = new ShowDateTime(this);
    showDateTime->SetLab(ui->labDateTime, ui->labLive);
    showDateTime->Start(1000);

    showCPUMemory = new ShowCPUMemory(this);
    showCPUMemory->SetLab(ui->labCPUMemory);
  #ifdef __arm__
    showCPUMemory->Start(3000);
  #else
    showCPUMemory->Start(3000);
  #endif
}

void MainWindow::on_radioButtonDDR4_toggled(bool checked) {
  if (checked) {
//    qDebug() << " 切换模型 DDR4";
    ui->stackedWidget->setCurrentWidget(mRobot3DForDDR4Form);
  }
}

void MainWindow::on_radioButtonDDR6_toggled(bool checked) {
  if (checked) {
//    qDebug() << " 切换模型 DDR6";
    ui->stackedWidget->setCurrentWidget(mRobot3DForDDR6Form);
  }
}
