#ifndef DDR6ROBOTWIDGET_H
#define DDR6ROBOTWIDGET_H

#include "rrglwidget.h"

/**
 * @brief The DDR6RobotWidget class
 * DDR4轴机械臂3d显示
 */
class DDR6RobotWidget : public RRGLWidget {
public:
  DDR6RobotWidget(QWidget *parent = 0);
  ~DDR6RobotWidget();
  /**
   * @brief drawGL 画ddr6 STL模型
   */
  void drawGL() override;

protected:
  void paintGL() override;

public:
  typedef struct DD6RobotModel {
    // 7个小部件组成
    STLFileLoader *link0;
    STLFileLoader *link1;
    STLFileLoader *link2;
    STLFileLoader *link3;
    STLFileLoader *link4;
    STLFileLoader *link5;
    STLFileLoader *link6;
  } DDR6RobotSTLModel;

  DDR6RobotSTLModel mRobotModel;
};

#endif // DDR6ROBOTWIDGET_H
