#include "robot3dforddr4form.h"
#include "ui_robot3dforddr4form.h"

#include <QDebug>
#include <QDoubleSpinBox>

Robot3DForDDR4Form::Robot3DForDDR4Form(QWidget *parent)
    : QWidget(parent), ui(new Ui::Robot3DForDDR4Form) {
  ui->setupUi(this);

  //关节
  connect(ui->robotControl, SIGNAL(sigJoinValueChanged(int, int)), this,
          SLOT(slotJVarsValueChange(int, int)), Qt::UniqueConnection);
  //参数调试
  connect(ui->robotControl, SIGNAL(sigDValueChanged(int, double)), this,
          SLOT(slotDValueChanged(int, double)), Qt::UniqueConnection);
  connect(ui->robotControl, SIGNAL(sigAValueChanged(int, double)), this,
          SLOT(slotAValueChanged(int, double)), Qt::UniqueConnection);
  connect(ui->robotControl, SIGNAL(sigAlphaValueChanged(int, double)), this,
          SLOT(slotAlphaValueChanged(int, double)), Qt::UniqueConnection);
  // checkbox
  connect(ui->robotControl, SIGNAL(sigCheckStateChanged()), this,
          SLOT(slotUpdateGlobalConfig()), Qt::UniqueConnection);

  //XY
  connect(ui->robotControl, SIGNAL(sigXYValueChanged(double, double)), this,
          SLOT(slotXYValueChanged(double, double)), Qt::UniqueConnection);

  ui->robotControl->setDValue(ui->robot3D->mRobotConfig.d);
  ui->robotControl->setAValue(ui->robot3D->mRobotConfig.a);
  ui->robotControl->setAlphaValue(ui->robot3D->mRobotConfig.alpha);
  ui->robotControl->setJVarsValue(ui->robot3D->mRobotConfig.JVars);
}

Robot3DForDDR4Form::~Robot3DForDDR4Form() { delete ui; }

void Robot3DForDDR4Form::slotJVarsValueChange(int index, int value) {
  ui->robot3D->mRobotConfig.JVars[index] = value;
  ui->robot3D->updateGL();
}

void Robot3DForDDR4Form::slotDValueChanged(int index, double value) {
  ui->robot3D->mRobotConfig.d[index] = value;
  ui->robot3D->updateGL();
}

void Robot3DForDDR4Form::slotAValueChanged(int index, double value) {
  ui->robot3D->mRobotConfig.a[index] = value;
  ui->robot3D->updateGL();
}

void Robot3DForDDR4Form::slotAlphaValueChanged(int index, double value) {
  ui->robot3D->mRobotConfig.alpha[index] = value;
  ui->robot3D->updateGL();
}

void Robot3DForDDR4Form::slotUpdateGlobalConfig() {
  ui->robot3D->mGlobalConfig.isDrawGrid = ui->robotControl->getIsGridChecked();
  ui->robot3D->mGlobalConfig.isDrawWorldCoord =
      ui->robotControl->getIsWorldCoord();
  ui->robot3D->mGlobalConfig.isDrawJoint1Coord =
      ui->robotControl->getIsJointChecked(1);
  ui->robot3D->mGlobalConfig.isDrawJoint2Coord =
      ui->robotControl->getIsJointChecked(2);
  ui->robot3D->mGlobalConfig.isDrawJoint3Coord =
      ui->robotControl->getIsJointChecked(3);
  ui->robot3D->mGlobalConfig.isDrawJoint4Coord =
      ui->robotControl->getIsJointChecked(4);
  ui->robot3D->mGlobalConfig.isDrawJoint5Coord =
      ui->robotControl->getIsJointChecked(5);
  ui->robot3D->mGlobalConfig.isDrawJoint6Coord =
      ui->robotControl->getIsJointChecked(6);
  ui->robot3D->mGlobalConfig.isDrawDesk = ui->robotControl->getIsShowDesk();
  ui->robot3D->mGlobalConfig.isDrawXYPlatform =
      ui->robotControl->getIsShowXYPlatform();
  ui->robot3D->updateGL();
}

void Robot3DForDDR4Form::slotXYValueChanged(double x, double y)
{
    //XY平台需要世界坐标系
    ui->robot3D->mXYPlatformConfig.x = x;
    ui->robot3D->mXYPlatformConfig.y = y;
    ui->robot3D->updateGL();
}