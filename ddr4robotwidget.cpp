#include "ddr4robotwidget.h"
#include <QDebug>

DDR4RobotWidget::DDR4RobotWidget(QWidget *parent) : RRGLWidget(parent) {

  mRobotModel.link0 =
      new STLFileLoader("./STLFile/ASCII/ddr4_v2_1/ddr4v2_link0.STL", 1000);
  mRobotModel.link1 =
      new STLFileLoader("./STLFile/ASCII/ddr4_v2_1/ddr4v2_link1.STL", 1000);
  mRobotModel.link2 =
      new STLFileLoader("./STLFile/ASCII/ddr4_v2_1/ddr4v2_link2.STL", 1000);
  mRobotModel.link3 =
      new STLFileLoader("./STLFile/ASCII/ddr4_v2_1/ddr4v2_link3.STL", 1000);
  mRobotModel.link4 =
      new STLFileLoader("./STLFile/ASCII/ddr4_v2_1/ddr4v2_link4.STL", 1000);

  mXYModel.link0 =
      new STLFileLoader("./STLFile/ASCII/xy_table/XY_link0.STL", 1000);
  mXYModel.link1 =
      new STLFileLoader("./STLFile/ASCII/xy_table/XY_link1.STL", 1000);
  mXYModel.link2 =
      new STLFileLoader("./STLFile/ASCII/xy_table/XY_link2.STL", 1000);

  mDeskModel.link0 =
      new STLFileLoader("./STLFile/ASCII/desk/desk_link0.STL", 1);

  //注意：经过旋转\平移后坐标系会改变！！！
  mRobotConfig.d = {0, 70.00, -153.00, -143.00, 202.00, 0, 0}; //沿z轴平移
  mRobotConfig.JVars = {0, 0, 0, 178, 0, 0, 0}; //绕z轴旋转角度
  mRobotConfig.a = {0, 0, -229.00, 0, 0, 0, 0}; //沿x轴平移
  mRobotConfig.alpha = {0, 0, 0, 0, 0, 0, 0};   //绕X轴旋转角度

  mGlobalConfig = {false, false, false, false, false,
                   false, false, false, false, false};
}

DDR4RobotWidget::~DDR4RobotWidget() {}

void DDR4RobotWidget::drawGL() {
  if (mGlobalConfig.isDrawGrid) {
    drawGrid();
  }
  if (mGlobalConfig.isDrawWorldCoord) {
    drawCoordinates();
  }
  if (mGlobalConfig.isDrawXYPlatform) {
    drawGLForXYRobot();
  }
  if (mGlobalConfig.isDrawDesk) {
    drawGLForDesk();
  }
  drawGLForDDR4Robot();
}

void DDR4RobotWidget::drawGLForDDR4Robot() {
  glPushMatrix();
  // Link0
  setupColor(255, 69, 0);
  mRobotModel.link0->draw();

  // Link1
  if (mGlobalConfig.isDrawJoint1Coord) {
    drawSTLCoordinates(255, 0, 0);
  }
  setupColor(169, 169, 169);
  glTranslatef(0.0, 0.0, mRobotConfig.d[1]);       // z轴方向平移
  glRotatef(mRobotConfig.JVars[1], 0.0, 0.0, 1.0); //绕z轴旋转
  glTranslatef(mRobotConfig.a[1], 0.0, 0.0);       // x轴方向平移
  glRotatef(mRobotConfig.alpha[1], 1.0, 0.0, 0.0); //绕x轴旋转
  mRobotModel.link1->draw();

  // 调整坐标系！！！
  glTranslatef(272, 0, 0);
  glTranslatef(0, 0, 145);
  glRotatef(180, 0.0, 0.0, 1.0);

  // Link2
  if (mGlobalConfig.isDrawJoint2Coord) {
    drawSTLCoordinates(0, 255, 0);
  }
  setupColor(255, 69, 0);
  glTranslatef(0.0, 0.0, mRobotConfig.d[2]);
  glRotatef(mRobotConfig.JVars[2], 0.0, 0.0, 1.0);
  glTranslatef(mRobotConfig.a[2], 0.0, 0.0);
  glRotatef(mRobotConfig.alpha[2], 1.0, 0.0, 0.0);
  mRobotModel.link2->draw(); // 调整坐标系！！！

  // Link3
  if (mGlobalConfig.isDrawJoint3Coord) {
    drawSTLCoordinates(0, 0, 255);
  }
  setupColor(255, 0, 0);
  glTranslatef(0.0, 0.0, mRobotConfig.d[3]);
  glRotatef(mRobotConfig.JVars[3], 0.0, 0.0, 1.0);
  glTranslatef(mRobotConfig.a[3], 0.0, 0.0);
  glRotatef(mRobotConfig.alpha[3], 1.0, 0.0, 0.0);
  mRobotModel.link3->draw();

  // Link4
  if (mGlobalConfig.isDrawJoint4Coord) {
    drawSTLCoordinates(255, 255, 0);
  }
  setupColor(148, 0, 211);
  glTranslatef(0.0, 0.0, mRobotConfig.d[4]);
  glRotatef(mRobotConfig.JVars[4], 0.0, 0.0, 1.0);
  glTranslatef(mRobotConfig.a[4], 0.0, 0.0);
  glRotatef(mRobotConfig.alpha[4], 1.0, 0.0, 0.0);
  mRobotModel.link4->draw();
  glPopMatrix();
}

void DDR4RobotWidget::drawGLForXYRobot() {
  glPushMatrix();
  glTranslatef(900.0, 0.0, 0); //偏移中央显示
  // link0
  setupColor(255, 69, 0);
  mXYModel.link0->draw();

  // link1
  setupColor(255, 0, 0);
  glTranslatef(0.0, 0.0, 126);
  glTranslatef(-52, 0.0, 0.0);
  glTranslatef(0, mXYPlatformConfig.y, 0.0);
  mXYModel.link1->draw();

  // link2
  setupColor(0, 255, 0);
  glTranslatef(0.0, 0.0, -55);
  glTranslatef(mXYPlatformConfig.x, 0.0, 0.0);
  mXYModel.link2->draw();

  glPopMatrix();
}

void DDR4RobotWidget::drawGLForDesk() {
  glPushMatrix();
  setupColor(169, 169, 169);
  glTranslatef(0.0, 0.0, 490); //桌子高度
  mDeskModel.link0->draw();
  glPopMatrix();
  glTranslatef(0.0, 0.0, 490); // glPushMatrix\glPopMatrix
                               // 会回到原始坐标系，此处抬高机械手坐标系，处于桌子上方
}

void DDR4RobotWidget::paintGL() {
  //用来绘制OpenGL的窗口了，只要有更新发生，这个函数就会被调用
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存
  glPushMatrix();
  glTranslated(0, 0, z_zoom);
  glTranslated(xTran, yTran, 0);
  glRotated(xRot / 16.0, 1.0, 0.0, 0.0); //绕x轴旋转
  glRotated(yRot / 16.0, 0.0, 1.0, 0.0); //绕y轴旋转
  glRotated(zRot / 16.0, 0.0, 0.0, 1.0); //绕z轴旋转
  glRotated(+90.0, 1.0, 0.0, 0.0);
  drawGL();
  glPopMatrix();
}
