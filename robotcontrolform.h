#ifndef ROBOTCONTROLFORM_H
#define ROBOTCONTROLFORM_H

//#include "showcpumemory.h"
#include "showdatetime.h"
#include <QTimer>
#include <QWidget>

namespace Ui {
class RobotControlForm;
}

class RobotControlForm : public QWidget {
  Q_OBJECT

public:
  explicit RobotControlForm(QWidget *parent = 0);
  ~RobotControlForm();
  void setDValue(QVector<float> d);
  void setAValue(QVector<float> a);
  void setAlphaValue(QVector<float> alpha);
  void setJVarsValue(QVector<float> JVars);
  void createItemsARow(int row, int J1, int J2, int J3, int J4, int J5, int J6,
                       double x = 0, double y = 0);
  /**
   * @brief getIsJointChecked 是否显示关节的坐标系
   * @param jointNum 第几号关节
   * @return
   */
  bool getIsJointChecked(int jointNum);
  /**
   * @brief getIsGridChecked 网格
   * @return
   */
  bool getIsGridChecked();
  /**
   * @brief getIsWorldCoord 世界坐标系
   * @return
   */
  bool getIsWorldCoord();
  /**
   * @brief getIsShowDesk 桌子
   * @return
   */
  bool getIsShowDesk();
  /**
   * @brief getIsShowXYPlatform XY平台
   * @return
   */
  bool getIsShowXYPlatform();

public slots:
  void slotUpdateJVarsValue(int value);
  void slotDebugRobotConfig(double value);
  void slotRobotTimeOut();
  void slotCheckStateChanged(int value);
  void slotXYValueChanged(double value);

signals:
  void sigJoinValueChanged(int index, int value); // robot
  void sigDValueChanged(int index, double value);
  void sigAValueChanged(int index, double value);
  void sigAlphaValueChanged(int index, double value);
  void sigCheckStateChanged();                //所有checkbox发生改变
  void sigXYValueChanged(double x, double y); // xy

private slots:
  void on_pushButtonStart_clicked();

  void on_pushButtonStop_clicked();

  void on_pushButtonTeach_clicked();

private:
  Ui::RobotControlForm *ui;
  //自定义单元格Type的类型，在创建单元格的item时使用
  enum CellType { ctJ1, ctJ2, ctJ3, ctJ4, ctJ5, ctJ6, ctX, ctY };
  //各字段在表格中的列号
  enum FieldColNum {
    colJ1 = 0,
    colJ2,
    colJ3,
    colJ4,
    colJ5,
    colJ6,
    colJ7,
    colJ8
  };
  QTimer *robotTimer;
  int count = 0;
};

#endif // ROBOTCONTROLFORM_H
