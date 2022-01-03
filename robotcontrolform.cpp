#include "robotcontrolform.h"
#include "ui_robotcontrolform.h"
#include <QDebug>

RobotControlForm::RobotControlForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::RobotControlForm) {
  ui->setupUi(this);

  ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
  ui->tableWidget->verticalHeader()->setVisible(true);
  ui->tableWidget->setStyleSheet(
      "QTableWidget::item:selected { background-color: rgb(255, 0, 0) }");

  //机械手关节
  ui->valueQ1->setText("0");
  ui->valueQ2->setText("0");
  ui->valueQ3->setText("0");
  ui->valueQ4->setText("0");
  ui->valueQ5->setText("0");
  ui->valueQ6->setText("0");
  QList<QSlider *> SliderList = ui->groupBoxRobot->findChildren<QSlider *>();
  for (int i = 0; i < SliderList.size(); i++) {
    QSlider *slider = SliderList.at(i);
    slider->setMinimum(-360);
    slider->setMaximum(360);
    slider->setTickInterval(1);
    connect(slider, SIGNAL(valueChanged(int)), this,
            SLOT(slotUpdateJVarsValue(int)), Qt::UniqueConnection);
    slider->setValue(0);
  }
  //参数调试
  QList<QDoubleSpinBox *> doubleSpinList =
      ui->debugTab->findChildren<QDoubleSpinBox *>();
  for (int i = 0; i < doubleSpinList.size(); i++) {
    QDoubleSpinBox *doubleSpin = doubleSpinList.at(i);
    doubleSpin->setValue(0);
    doubleSpin->setMinimum(-999.999);
    doubleSpin->setMaximum(999.999);
    connect(doubleSpin, SIGNAL(valueChanged(double)), this,
            SLOT(slotDebugRobotConfig(double)), Qt::UniqueConnection);
  }
  // checkBox 触发刷新OpenGL
  QList<QCheckBox *> checkBoxList = this->findChildren<QCheckBox *>();
  for (int i = 0; i < checkBoxList.size(); i++) {
    QCheckBox *checkBox = checkBoxList.at(i);
    connect(checkBox, SIGNAL(stateChanged(int)), this,
            SLOT(slotCheckStateChanged(int)), Qt::UniqueConnection);
  }
  // XY
  QList<QDoubleSpinBox *> XYSpinList =
      ui->groupBoxXY->findChildren<QDoubleSpinBox *>();
  for (int i = 0; i < XYSpinList.size(); i++) {
    QDoubleSpinBox *XYSpin = XYSpinList.at(i);
    XYSpin->setValue(0);
    XYSpin->setMinimum(-999.999);
    XYSpin->setMaximum(999.999);
    connect(XYSpin, SIGNAL(valueChanged(double)), this,
            SLOT(slotXYValueChanged(double)), Qt::UniqueConnection);
  }
  robotTimer = new QTimer(this);
  connect(robotTimer, SIGNAL(timeout()), this, SLOT(slotRobotTimeOut()));

}

RobotControlForm::~RobotControlForm() { delete ui; }

void RobotControlForm::slotUpdateJVarsValue(int value) {
  QSlider *slider = (QSlider *)sender();
  QString objectName = slider->objectName();
  QString index = objectName.at(objectName.size() - 1);
  ui->valueQ1->setText(QString::number(ui->sliderQ1->value()));
  ui->valueQ2->setText(QString::number(ui->sliderQ2->value()));
  ui->valueQ3->setText(QString::number(ui->sliderQ3->value()));
  ui->valueQ4->setText(QString::number(ui->sliderQ4->value()));
  ui->valueQ5->setText(QString::number(ui->sliderQ5->value()));
  ui->valueQ6->setText(QString::number(ui->sliderQ6->value()));
  emit sigJoinValueChanged(index.toInt(), value);
}

void RobotControlForm::slotDebugRobotConfig(double value) {
  QDoubleSpinBox *sb = (QDoubleSpinBox *)sender();
  QString objectName = sb->objectName();
  QString index = objectName.at(objectName.size() - 1);
  if (objectName.contains("doubleSpinBox_d")) {
    emit sigDValueChanged(index.toInt(), value);
  } else if (objectName.contains("doubleSpinBox_JVars")) {
    // todo
  } else if (objectName.contains("doubleSpinBox_alpha")) {
    emit sigAlphaValueChanged(index.toInt(), value);
  } else if (objectName.contains("doubleSpinBox_a")) {
    emit sigAValueChanged(index.toInt(), value);
  }
}

void RobotControlForm::setDValue(QVector<float> d) {
  ui->doubleSpinBox_d0->setValue(d[0]);
  ui->doubleSpinBox_d1->setValue(d[1]);
  ui->doubleSpinBox_d2->setValue(d[2]);
  ui->doubleSpinBox_d3->setValue(d[3]);
  ui->doubleSpinBox_d4->setValue(d[4]);
  ui->doubleSpinBox_d5->setValue(d[5]);
  ui->doubleSpinBox_d6->setValue(d[6]);
}

void RobotControlForm::setAValue(QVector<float> a) {
  ui->doubleSpinBox_a0->setValue(a[0]);
  ui->doubleSpinBox_a1->setValue(a[1]);
  ui->doubleSpinBox_a2->setValue(a[2]);
  ui->doubleSpinBox_a3->setValue(a[3]);
  ui->doubleSpinBox_a4->setValue(a[4]);
  ui->doubleSpinBox_a5->setValue(a[5]);
  ui->doubleSpinBox_a6->setValue(a[6]);
}

void RobotControlForm::setAlphaValue(QVector<float> alpha) {
  ui->doubleSpinBox_alpha0->setValue(alpha[0]);
  ui->doubleSpinBox_alpha1->setValue(alpha[1]);
  ui->doubleSpinBox_alpha2->setValue(alpha[2]);
  ui->doubleSpinBox_alpha3->setValue(alpha[3]);
  ui->doubleSpinBox_alpha4->setValue(alpha[4]);
  ui->doubleSpinBox_alpha5->setValue(alpha[5]);
  ui->doubleSpinBox_alpha6->setValue(alpha[6]);
}

void RobotControlForm::setJVarsValue(QVector<float> JVars) {
  // 0号表示底座
  ui->sliderQ1->setValue(JVars[1]);
  ui->sliderQ2->setValue(JVars[2]);
  ui->sliderQ3->setValue(JVars[3]);
  ui->sliderQ4->setValue(JVars[4]);
  ui->sliderQ5->setValue(JVars[5]);
  ui->sliderQ6->setValue(JVars[6]);
}

void RobotControlForm::createItemsARow(int row, int J1, int J2, int J3, int J4,
                                       int J5, int J6, double x, double y) {
  QTableWidgetItem *item;
  item = new QTableWidgetItem(QString::number(J1), RobotControlForm::ctJ1);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //文本对齐格式
  ui->tableWidget->setItem(row, RobotControlForm::colJ1,
                           item); //为单元格设置Item

  item = new QTableWidgetItem(QString::number(J2), RobotControlForm::ctJ2);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //文本对齐格式
  ui->tableWidget->setItem(row, RobotControlForm::colJ2,
                           item); //为单元格设置Item

  item = new QTableWidgetItem(QString::number(J3), RobotControlForm::ctJ3);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //文本对齐格式
  ui->tableWidget->setItem(row, RobotControlForm::colJ3,
                           item); //为单元格设置Item

  item = new QTableWidgetItem(QString::number(J4), RobotControlForm::ctJ4);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //文本对齐格式
  ui->tableWidget->setItem(row, RobotControlForm::colJ4,
                           item); //为单元格设置Item

  item = new QTableWidgetItem(QString::number(J5), RobotControlForm::ctJ5);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //文本对齐格式
  ui->tableWidget->setItem(row, RobotControlForm::colJ5,
                           item); //为单元格设置Item

  item = new QTableWidgetItem(QString::number(J6), RobotControlForm::ctJ6);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //文本对齐格式
  ui->tableWidget->setItem(row, RobotControlForm::colJ6,
                           item); //为单元格设置Item

  item = new QTableWidgetItem(QString::number(x), RobotControlForm::ctX);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //文本对齐格式
  ui->tableWidget->setItem(row, RobotControlForm::colJ7,
                           item); //为单元格设置Item

  item = new QTableWidgetItem(QString::number(y), RobotControlForm::ctY);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //文本对齐格式
  ui->tableWidget->setItem(row, RobotControlForm::colJ8,
                           item); //为单元格设置Item
}

bool RobotControlForm::getIsJointChecked(int jointNum) {
  //"checkBoxJ1"
  QString tObjectName = "checkBoxJ" + QString::number(jointNum);
  QList<QCheckBox *> checkBoxList = ui->jointTab->findChildren<QCheckBox *>();
  for (int i = 0; i < checkBoxList.size(); i++) {
    QCheckBox *checkBox = checkBoxList.at(i);
    if (checkBox->objectName() == tObjectName) {
      return checkBox->isChecked();
    }
  }
  return false;
}

bool RobotControlForm::getIsGridChecked() {
  return ui->checkBoxGrid->isChecked();
}

bool RobotControlForm::getIsWorldCoord() {
  return ui->checkBoxWorldCoordinate->isChecked();
}

bool RobotControlForm::getIsShowDesk() { return ui->checkBoxDesk->isChecked(); }

bool RobotControlForm::getIsShowXYPlatform() {
  return ui->checkBoxXY->isChecked();
}

void RobotControlForm::slotCheckStateChanged(int value) {
//  qDebug() << value;
  emit sigCheckStateChanged();
}

void RobotControlForm::slotXYValueChanged(double value) {
//  qDebug() << value;
  sigXYValueChanged(ui->doubleSpinBoXYP_X->value(),
                    ui->doubleSpinBoXYP_Y->value());
}

void RobotControlForm::slotRobotTimeOut() {
  if (count < ui->tableWidget->rowCount()) {
    ui->tableWidget->selectRow(count);
    QVector<float> JVars = {0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i <= 5; i++) {
      JVars[i + 1] = ui->tableWidget->item(count, i)->text().toInt();
    }
    setJVarsValue(JVars);
    ui->doubleSpinBoXYP_X->setValue(
        ui->tableWidget->item(count, 6)->text().toDouble());
    ui->doubleSpinBoXYP_Y->setValue(
        ui->tableWidget->item(count, 7)->text().toDouble());
  } else {
    count = -1;
  }
  count++;
}

void RobotControlForm::on_pushButtonStart_clicked() {
  int rowCount = ui->tableWidget->rowCount();
  if (rowCount > 0) {
    count = 0;
    robotTimer->start(ui->spinBoxInterval->value());
  }
}

void RobotControlForm::on_pushButtonStop_clicked() { robotTimer->stop(); }

void RobotControlForm::on_pushButtonTeach_clicked() {
  int curRow = ui->tableWidget->rowCount();
//  qDebug() << curRow;
  ui->tableWidget->insertRow(curRow); //插入一行，但不会自动为单元格创建item
  createItemsARow(curRow, ui->sliderQ1->value(), ui->sliderQ2->value(),
                  ui->sliderQ3->value(), ui->sliderQ4->value(),
                  ui->sliderQ5->value(), ui->sliderQ6->value(),
                  ui->doubleSpinBoXYP_X->value(),
                  ui->doubleSpinBoXYP_Y->value());
}
