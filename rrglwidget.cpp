#include "rrglwidget.h"
#include <GL/glu.h>
#include <QDebug>
#include <QMouseEvent>

RRGLWidget::RRGLWidget(QWidget *parent) : QGLWidget(parent) {}

RRGLWidget::~RRGLWidget() {}

void RRGLWidget::drawGrid() {
  glPushMatrix();
  GLfloat color[] = {8.0 / 255, 108.0 / 255, 162.0 / 255};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  int step = 50;
  int num = 15;
  for (int i = -num; i < num + 1; i++) {
    glBegin(GL_LINES);
    glVertex3f(i * step, -num * step, 0);
    glVertex3f(i * step, num * step, 0);
    glVertex3f(-num * step, i * step, 0);
    glVertex3f(num * step, i * step, 0);
    glEnd();
  }
  glPopMatrix();
}

void RRGLWidget::drawCoordinates() {
  glPushMatrix();
  glLineWidth(2.0f);
  // glScalef(6.0f, 6.0f, 6.0f); //模型缩放函数
  glBegin(GL_LINES);
  setupColor(255, 255, 255);
  //  qglColor(QColor::fromRgbF(1, 0, 0)); // X axis is red.
  glVertex3f(-900, 0, 0);
  glVertex3f(900, 0, 0);
  setupColor(255, 255, 255);
  //  qglColor(QColor::fromRgbF(0, 1, 0)); // Y axis is green.
  glVertex3f(0, -900, 0);
  glVertex3f(0, 900, 0);
  setupColor(255, 255, 255);
  //  qglColor(QColor::fromRgbF(0, 0, 1)); // Z axis is blue.
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 700);
  glEnd();
  // Draw labels
  qglColor(QColor::fromRgbF(1, 1, 1));
  renderText(-900, 0, 0, "-X", QFont("helvetica", 12, QFont::Bold, true));
  renderText(900, 0, 0, "+X", QFont("helvetica", 12, QFont::Bold, true));
  qglColor(QColor::fromRgbF(1, 1, 1));
  renderText(0, -900, 0, "-Y", QFont("helvetica", 12, QFont::Bold, true));
  renderText(0, 900, 0, "+Y", QFont("helvetica", 12, QFont::Bold, true));
  qglColor(QColor::fromRgbF(1, 1, 1));
  renderText(0, 0, 700, "+Z", QFont("helvetica", 12, QFont::Bold, true));
  glLineWidth(1.0f);
  glPopMatrix();
}

void RRGLWidget::drawSTLCoordinates(int r, int g, int b) {
  glPushMatrix();
  glLineWidth(1.5f);
  setupColor(r, g, b);
  glBegin(GL_LINES);
  glVertex3f(-300, 0, 0);
  glVertex3f(300, 0, 0);

  glVertex3f(0, -300, 0);
  glVertex3f(0, 300, 0);

  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 500);
  glEnd();
  // Draw labels
  qglColor(QColor::fromRgbF(1, 0, 0));
  renderText(-300, 0, 0, "-X", QFont("helvetica", 12, QFont::Bold, true));
  renderText(300, 0, 0, "+X", QFont("helvetica", 12, QFont::Bold, true));
  qglColor(QColor::fromRgbF(0, 1, 0));
  renderText(0, -300, 0, "-Y", QFont("helvetica", 12, QFont::Bold, true));
  renderText(0, 300, 0, "+Y", QFont("helvetica", 12, QFont::Bold, true));
  qglColor(QColor::fromRgbF(0, 0, 1));
  renderText(0, 0, 500, "+Z", QFont("helvetica", 12, QFont::Bold, true));
  glLineWidth(1.0f);
  glPopMatrix();
}

void RRGLWidget::drawGL() {
  //子类重写这个接口，显示各自的模型
  qDebug() << " RRGLWidget drawGL";
}

void RRGLWidget::setupColor(int r, int g, int b) {
  /*
   * 参数1的取值可以是GL_FRONT、GL_BACK或GL_FRONT_AND_BACK，指出材质属性将应用于物体的哪面
   * 参数2指出要设置的哪种材质属性,GL_AMBIENT_AND_DIFFUSE材质的环境颜色和散射颜色
   */
  GLfloat color[] = {r / 255.0, g / 255.0, b / 255.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
}

void RRGLWidget::setXRotation(int angle) {
  int tangle = angle; // normalizeAngle(angle);
  if (tangle != xRot) {
    xRot = tangle;
    emit xRotationChanged(angle);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updateGL();
  }
}

void RRGLWidget::setYRotation(int angle) {
  int tangle = angle; // normalizeAngle(angle);
  if (tangle != yRot) {
    yRot = tangle;
    emit yRotationChanged(angle);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
}

void RRGLWidget::setXYTranslate(int dx, int dy) {
  xTran += 3.0 * dx;
  yTran -= 3.0 * dy;
  updateGL();
}

int RRGLWidget::normalizeAngle(int angle) {
  int tangle = angle;
  while (tangle < 0) {
    tangle += 360 * 16;
  }
  while (tangle > 360 * 16) {
    tangle -= 360 * 16;
  }
  return tangle;
}

void RRGLWidget::setZoom(int zoom) {
  z_zoom = zoom;
  updateGL();
}

void RRGLWidget::initializeGL() {
  //用来初始化这个OpenGL窗口部件的，可以在里面设定一些有关选项
  GLfloat ambientLight[] = {0.7, 0.7, 0.7, 1.0}; //光源环境光强度数组
  GLfloat diffuseLight[] = {0.7, 0.8, 0.8, 1.0}; //光源散射光强度数组
  GLfloat specularLight[] = {0.4, 0.4, 0.4, 1.0}; //光源镜面反射光强度数组
  GLfloat positionLight[] = {20.0, 20.0, 20.0, 0.0}; //光源位置数组

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //设置0号光源的环境光属性
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); //设置0号光源的散射光属性
  glLightfv(GL_LIGHT0, GL_SPECULAR,
            specularLight); //设置0号光源的镜面反射光属性
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);
  glLightfv(GL_LIGHT0, GL_POSITION, positionLight); //设置0号光源的位置属性

  glEnable(GL_LIGHTING);   //启用光照
  glEnable(GL_LIGHT0);     //打开光源
  glEnable(GL_DEPTH_TEST); //隐藏表面消除
  glEnable(GL_NORMALIZE);

  glClearColor(0.0, 0.0, 0.0, 1.0);
}

void RRGLWidget::paintGL() {
  //用来绘制OpenGL的窗口了，只要有更新发生，这个函数就会被调用
}

void RRGLWidget::resizeGL(int w, int h) {
  //用来处理窗口大小变化这一事件的，width和height就是新的大小状态下的宽和高了，另外resizeGL()在处理完后会自动刷新屏幕
  if (w < 0 || h < 0) {
    return;
  }
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(35.0, w / float(h), 1.0, 20000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(0.0, 0.0, -40.0);
}

void RRGLWidget::mousePressEvent(QMouseEvent *event) { lastPos = event->pos(); }

void RRGLWidget::mouseMoveEvent(QMouseEvent *event) {
  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();
  //  qDebug() << dx << dy;
  // 这里必须使用buttons()
  if (event->buttons() & Qt::LeftButton) //进行的按位与
  {
    setXRotation(xRot + 4 * dy);
    setYRotation(yRot - 4 * dx);
  } else if (event->buttons() & Qt::RightButton) {
    setZoom(z_zoom + 5.0 * dy);
  } else if (event->buttons() & Qt::MidButton) {
    setXYTranslate(dx, dy);
  }
  lastPos = event->pos();
}
