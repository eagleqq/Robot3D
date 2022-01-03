#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QMutex>
#include <QTextStream>
#include <stdio.h>
#include <stdlib.h>

// 自定义消息处理程序
void myMessageOutput(QtMsgType type, const QMessageLogContext &context,
                     const QString &msg) {
  // 加锁
  static QMutex mutex;
  mutex.lock();

  QByteArray localMsg = msg.toLocal8Bit();

  QString strMsg("");
  switch (type) {
  case QtDebugMsg:
    strMsg = QString("Debug:");
    break;
  case QtWarningMsg:
    strMsg = QString("Warning:");
    break;
  case QtCriticalMsg:
    strMsg = QString("Critical:");
    break;
  case QtFatalMsg:
    strMsg = QString("Fatal:");
    break;
  }

  // 设置输出信息格式
//  QString strDateTime =
//      QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
  QString strMessage = QString("Message:%1").arg(localMsg.constData());
  // 输出信息至文件中（读写、追加形式）
  QFile file("log.txt");
  file.open(QIODevice::ReadWrite | QIODevice::Append);
  QTextStream stream(&file);
  stream << strMessage << "\r\n";
  file.flush();
  file.close();
  // 解锁
  mutex.unlock();
}

int main(int argc, char *argv[]) {
  // 安装消息处理程序
  qInstallMessageHandler(myMessageOutput);
  QApplication a(argc, argv);
  MainWindow w;
  a.setWindowIcon(QIcon(":/res/3D.png"));
  w.show();

  return a.exec();
}
