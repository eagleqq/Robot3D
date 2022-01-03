#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "robot3dforddr4form.h"
#include "robot3dforddr6form.h"
#include "showcpumemory.h"
#include "showdatetime.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    /**
   * @brief moveWindowToCenter 屏幕居中
   */
  void moveWindowToCenter();
  /**
   * @brief initSystemMonitor 资源监控
   */
  void initSystemMonitor();

private slots:
  void on_radioButtonDDR4_toggled(bool checked);

  void on_radioButtonDDR6_toggled(bool checked);

private:
  Ui::MainWindow *ui;
  Robot3DForDDR4Form *mRobot3DForDDR4Form; // ddr4
  Robot3DForDDR6Form *mRobot3DForDDR6Form; // ddr6
  ShowDateTime *showDateTime;
  ShowCPUMemory *showCPUMemory;
};

#endif // MAINWINDOW_H
