#ifndef DDR4ROBOTWIDGET_H
#define DDR4ROBOTWIDGET_H

#include "rrglwidget.h"

/**
 * @brief The DDR4RobotWidget class
 * DDR4轴机械臂3d显示
 */
class DDR4RobotWidget : public RRGLWidget {
public:
  DDR4RobotWidget(QWidget *parent = 0);
  ~DDR4RobotWidget();

  /**
   * @brief drawGL 画STL模型
   */
  void drawGL() override;
  /**
   * @brief drawGLForDDR4Robot 机械手
   */
  void drawGLForDDR4Robot();
  /**
   * @brief drawGLForXYRobot XY平台
   */
  void drawGLForXYRobot();
  /**
   * @brief drawGLForDesk 桌面
   */
  void drawGLForDesk();

protected:
  void paintGL() override;

public:
  //ddr4模型结构体
  typedef struct DD4RobotModel {
    // 5个小部件组成
    STLFileLoader *link0;
    STLFileLoader *link1;
    STLFileLoader *link2;
    STLFileLoader *link3;
    STLFileLoader *link4;
  } DD4RobotModel;

  //xy平台模型结构体
  typedef struct XYModel {
    // 3个小部件组成
    STLFileLoader *link0;
    STLFileLoader *link1;
    STLFileLoader *link2;
  } XYModel;
  //桌子模型结构体
  typedef struct DeskModel {
    // 桌子
    STLFileLoader *link0;
  } DeskModel;

  XYModel mXYModel;
  DeskModel mDeskModel;
  DD4RobotModel mRobotModel;
};

#endif // DDR4ROBOTWIDGET_H
