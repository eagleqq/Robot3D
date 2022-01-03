#ifndef ROBOT3DFORDDR6FORM_H
#define ROBOT3DFORDDR6FORM_H

#include <QWidget>

namespace Ui {
class Robot3DForDDR6Form;
}
//修改ddr6的参数，可控制机械臂
//通过此调试界面，可组装多个STL模型，记录此时的参数做为完整机械臂的初始参数值
class Robot3DForDDR6Form : public QWidget {
  Q_OBJECT

public:
  explicit Robot3DForDDR6Form(QWidget *parent = 0);
  ~Robot3DForDDR6Form();

private slots:
  void slotJVarsValueChange(int index, int value);
  void slotDValueChanged(int index, double value);
  void slotAValueChanged(int index, double value);
  void slotAlphaValueChanged(int index, double value);
  void slotUpdateGlobalConfig();

private:
  Ui::Robot3DForDDR6Form *ui;
};

#endif // ROBOT3DFORDDR6FORM_H
