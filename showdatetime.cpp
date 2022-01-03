#include "showdatetime.h"
#include <QDateTime>
#include <QLCDNumber>
#include <QLabel>
#include <QTimer>

#define DATETIME                                                               \
  qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))

ShowDateTime::ShowDateTime(QObject *parent) : QObject(parent) {
  labDateTime = 0;
  labLive = 0;
  lcdNumber = 0;

  day = 0;
  hour = 0;
  minute = 0;
  seconds = 0;

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(ShowTime()));
}

ShowDateTime::~ShowDateTime() {}

void ShowDateTime::SetLab(QLabel *labDateTime, QLabel *labLive) {
  this->labDateTime = labDateTime;
  this->labLive = labLive;
  this->SetTimeInfo();
}

void ShowDateTime::SetLcdNumber(QLCDNumber *lcdNumber) {
  this->lcdNumber = lcdNumber;
  this->SetTimeInfo();
}

void ShowDateTime::Start(int interval) {
  begin_time = QDateTime::currentDateTime(); //获取或设置时间
  timer->start(interval);
}

void ShowDateTime::Stop() { timer->stop(); }

void ShowDateTime::ShowTime() {
  seconds++;
  if (seconds >= 60) {
    seconds = 0;
    minute++;
  }
  if (minute >= 60) {
    minute = 0;
    hour++;
  }
  if (hour >= 24) {
    hour = 0;
    day++;
  }
  SetTimeInfo();
}

void ShowDateTime::SetTimeInfo() {
  QDateTime end_time = QDateTime::currentDateTime(); //获取或设置时间
  QTime m_time;
  m_time.setHMS(0, 0, 0, 0); //初始化数据，时 分 秒 毫秒
  this->labDateTime->setText(m_time.addSecs(begin_time.secsTo(end_time)).toString("hh:mm:ss"));

  this->labLive->setText(QString("已运行 : %1天%2时%3分%4秒  |  ")
                             .arg(day)
                             .arg(hour)
                             .arg(minute)
                             .arg(seconds));
//  this->labDateTime->setText(QDateTime::currentDateTime().toString(
//      "当前时间 : yyyy年MM月dd日 HH:mm:ss  "));
  //  if (lcdNumber != 0) {
  //    lcdNumber->display(DATETIME);
  //  }
}
