#include "ddr6robotwidget.h"
#include <QDebug>

DDR6RobotWidget::DDR6RobotWidget(QWidget *parent) : RRGLWidget(parent) {
  // DDR6 模型由7个小部件组成
  mRobotModel.link0 =
      new STLFileLoader("./STLFile/ASCII/ddr6_v2_1/ddr6v2_link0.STL", 1000);
  mRobotModel.link1 =
      new STLFileLoader("./STLFile/ASCII/ddr6_v2_1/ddr6v2_link1.STL", 1000);
  mRobotModel.link2 =
      new STLFileLoader("./STLFile/ASCII/ddr6_v2_1/ddr6v2_link2.STL", 1000);
  mRobotModel.link3 =
      new STLFileLoader("./STLFile/ASCII/ddr6_v2_1/ddr6v2_link3.STL", 1000);
  mRobotModel.link4 =
      new STLFileLoader("./STLFile/ASCII/ddr6_v2_1/ddr6v2_link4.STL", 1000);
  mRobotModel.link5 =
      new STLFileLoader("./STLFile/ASCII/ddr6_v2_1/ddr6v2_link5.STL", 1000);
  mRobotModel.link6 =
      new STLFileLoader("./STLFile/ASCII/ddr6_v2_1/ddr6v2_link6.STL", 1000);

  //注意：经过旋转\平移后坐标系会改变！！！
  mRobotConfig.d = {0, 181.00, -111.00, 1.00, -1.00, 132.00, 96.00}; //沿z轴平移
  mRobotConfig.JVars = {0, 0, 0, 0, 0, 0, 0}; //绕z轴旋转角度
  mRobotConfig.a = {0, 0, 0, 0, 0, 0, 0}; //沿x轴平移
  mRobotConfig.alpha = {0, 0, 180.00, 0, 0, 0, 0}; //绕X轴旋转角度

  mGlobalConfig = {false, false, false, false, false, false, false, false, false, false};
}

DDR6RobotWidget::~DDR6RobotWidget() {
  //    delete objRobot;
  //    objRobot = nullptr;
}

void DDR6RobotWidget::drawGL() {
  //方法：不断调整每个link的坐标系（glTranslatef、glRotatef），依次组合起所有link
  //TODO: 此处待优化，调整坐标系不通用，这里写死了

  glPushMatrix();
  if (mGlobalConfig.isDrawGrid) {
    drawGrid();
  }
  if (mGlobalConfig.isDrawWorldCoord) {
    drawCoordinates();
  }
  // Link0
  setupColor(255, 69, 0);
  mRobotModel.link0->draw();

  // Link1
  if (mGlobalConfig.isDrawJoint1Coord) {
    drawSTLCoordinates(255, 0, 0);
  }
  setupColor(169, 169, 169);
  glTranslatef(0.0, 0.0, mRobotConfig.d[1]);                 // z轴方向平移
  glRotatef(mRobotConfig.JVars[1], 0.0, 0.0, 1.0); //绕z轴旋转
  glTranslatef(mRobotConfig.a[1], 0.0, 0.0);                 // x轴方向平移
  glRotatef(mRobotConfig.alpha[1], 1.0, 0.0, 0.0); //绕x轴旋转
  mRobotModel.link1->draw();

  // 调整坐标系！！！
  glRotatef(90, 1.0, 0.0, 0.0);

  // Link2
  if (mGlobalConfig.isDrawJoint2Coord) {
    drawSTLCoordinates(0, 255, 0);
  }
  setupColor(255, 69, 0);
  glTranslatef(0.0, 0.0, mRobotConfig.d[2]);                 // z轴方向平移
  glRotatef(mRobotConfig.JVars[2], 0.0, 0.0, 1.0); //绕z轴旋转
  glTranslatef(mRobotConfig.a[2], 0.0, 0.0);                 // x轴方向平移
  glRotatef(mRobotConfig.alpha[2], 1.0, 0.0, 0.0); //绕x轴旋转
  mRobotModel.link2->draw();

  // 调整坐标系！！！
  glTranslatef(245, 0.0, 0.0);

  // Link3
  if (mGlobalConfig.isDrawJoint3Coord) {
    drawSTLCoordinates(0, 0, 255);
  }
  setupColor(169, 169, 169);
  glTranslatef(0.0, 0.0, mRobotConfig.d[3]);                 // z轴方向平移
  glRotatef(mRobotConfig.JVars[3], 0.0, 0.0, 1.0); //绕z轴旋转
  glTranslatef(mRobotConfig.a[3], 0.0, 0.0);                 // x轴方向平移
  glRotatef(mRobotConfig.alpha[3], 1.0, 0.0, 0.0); //绕x轴旋转
  mRobotModel.link3->draw();

  // 调整坐标系！！！
  glTranslatef(213, 0.0, 0.0);
  glRotatef(-90, 0.0, 0.0, 1.0); //绕x轴旋转

  // Link4
  if (mGlobalConfig.isDrawJoint4Coord) {
    drawSTLCoordinates(255, 255, 0);
  }
  setupColor(255, 69, 0);
  glTranslatef(0.0, 0.0, mRobotConfig.d[4]);                 // z轴方向平移
  glRotatef(mRobotConfig.JVars[4], 0.0, 0.0, 1.0); //绕z轴旋转
  glTranslatef(mRobotConfig.a[4], 0.0, 0.0);                 // x轴方向平移
  glRotatef(mRobotConfig.alpha[4], 1.0, 0.0, 0.0); //绕x轴旋转
  mRobotModel.link4->draw();

  // 调整坐标系！！！
  glRotatef(-90, 1.0, 0.0, 0.0); //绕x轴旋转

  // Link5
  if (mGlobalConfig.isDrawJoint5Coord) {
    drawSTLCoordinates(0, 255, 255);
  }
  setupColor(169, 169, 169);
  glTranslatef(0.0, 0.0, mRobotConfig.d[5]);                 // z轴方向平移
  glRotatef(mRobotConfig.JVars[5], 0.0, 0.0, 1.0); //绕z轴旋转
  glTranslatef(mRobotConfig.a[5], 0.0, 0.0);                 // x轴方向平移
  glRotatef(mRobotConfig.alpha[5], 1.0, 0.0, 0.0); //绕x轴旋转
  mRobotModel.link5->draw();

  // 调整坐标系！！！
  glRotatef(90, 1.0, 0.0, 0.0); //绕x轴旋转

  // Link6
  if (mGlobalConfig.isDrawJoint6Coord) {
    drawSTLCoordinates(255, 0, 255);
  }
  setupColor(255, 69, 0);
  glTranslatef(0.0, 0.0, mRobotConfig.d[6]);                 // z轴方向平移
  glRotatef(mRobotConfig.JVars[6], 0.0, 0.0, 1.0); //绕z轴旋转
  glTranslatef(mRobotConfig.a[6], 0.0, 0.0);                 // x轴方向平移
  glRotatef(mRobotConfig.alpha[6], 1.0, 0.0, 0.0); //绕x轴旋转
  mRobotModel.link6->draw();

  glPopMatrix();
}

void DDR6RobotWidget::paintGL() {
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
