#ifndef ROBOT3DFORDDR4FORM_H
#define ROBOT3DFORDDR4FORM_H

#include <QWidget>

namespace Ui {
class Robot3DForDDR4Form;
}
//修改ddr4的参数，可控制机械臂
//通过此调试界面，可组装多个STL模型，记录此时的参数做为完整机械臂的初始参数值
class Robot3DForDDR4Form : public QWidget {
  Q_OBJECT

public:
  explicit Robot3DForDDR4Form(QWidget *parent = 0);
  ~Robot3DForDDR4Form();

private slots:
  //以下为修改机械臂参数的槽函数
  void slotJVarsValueChange(int index, int value);
  void slotDValueChanged(int index, double value);
  void slotAValueChanged(int index, double value);
  void slotAlphaValueChanged(int index, double value);
  void slotUpdateGlobalConfig();
  void slotXYValueChanged(double x, double y);

private:
  Ui::Robot3DForDDR4Form *ui;
};

#endif // ROBOT3DFORDDR4FORM_H
