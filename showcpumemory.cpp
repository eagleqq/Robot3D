#include "showcpumemory.h"
#include <QDateTime>
#include <QDebug>
#include <QLabel>
#include <QProcess>
#include <QTimer>

#define MB (1024 * 1024)
#define KB (1024)

ShowCPUMemory::ShowCPUMemory(QObject *parent) : QObject(parent) {
  totalNew = idleNew = totalOld = idleOld = 0;
  cpuPercent = 0;

  memoryPercent = 0;
  memoryAll = 0;
  memoryUse = 0;
  labCPUMemory = 0;

  timerCPU = new QTimer(this);
  connect(timerCPU, SIGNAL(timeout()), this, SLOT(GetCPU()));

  timerMemory = new QTimer(this);
  connect(timerMemory, SIGNAL(timeout()), this, SLOT(GetMemory()));

  process = new QProcess(this);
  connect(process, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

void ShowCPUMemory::SetLab(QLabel *labCPUMemory) {
  this->labCPUMemory = labCPUMemory;
  GetCPU();
  GetMemory();
}

void ShowCPUMemory::Start(int interval) {
  timerCPU->start(interval);
  timerMemory->start(interval + 200);
}

void ShowCPUMemory::Stop() {
  timerCPU->stop();
  timerMemory->stop();
}

void ShowCPUMemory::GetCPU() {
  if (process->state() == QProcess::NotRunning) {
    totalNew = idleNew = 0;
    process->start("cat /proc/stat");
  }
  qDebug() << tr("Time: %1  CPU: %2  Memory: %3")
                  .arg(QDateTime::currentDateTime().toString(
                      "yyyy-MM-dd HH:mm:ss.zzz"))
                  .arg(cpuPercent)
                  .arg(memoryPercent);
}

void ShowCPUMemory::GetMemory() {
  if (process->state() == QProcess::NotRunning) {
    process->start("cat /proc/meminfo");
  }
}

void ShowCPUMemory::ReadData() {
  /* CPU计算公式：
   * 例：cpu  27463416(user) 13228(system) 3164572(nice) 93748703(idle)
   * 201145(iowait) 0(irq) 383097(softirq) 0 0 0
   * cpu_total=user+system+nice+idle+iowait+irq+softirq
   * CPU使用率 = (idle2-idle1)/(cpu2-cpu1)*100
   * 内存使用率 = (MemTotal - MemAvailable) / MemTotal * 100%
   */
  while (!process->atEnd()) {
    QString s = QLatin1String(process->readLine());
    if (s.startsWith("cpu")) {
      QStringList list = s.split(" ");
      idleNew = list.at(5).toInt();
      foreach (QString value, list) { totalNew += value.toInt(); }
      int total = totalNew - totalOld;
      int idle = idleNew - idleOld;
      cpuPercent = 100.0 * (total - idle) / total;
      totalOld = totalNew;
      idleOld = idleNew;
      break;
    } else if (s.startsWith("MemTotal")) {
      s = s.replace(" ", "");
      s = s.split(":").at(1);
      memoryAll = s.left(s.length() - 3).toInt() / KB;
    } else if (s.startsWith("MemAvailable")) {
      s = s.replace(" ", "");
      s = s.split(":").at(1);
      memoryFree = s.left(s.length() - 3).toInt() / KB;
      memoryUse = memoryAll - memoryFree;
      memoryPercent = 100.0 * memoryUse / memoryAll;
      break;
    }
  }
  QString msg = QString("CPU : %1%  内存 : %2% ( 已用 %3 MB / 共 %4 MB )")
                    .arg(cpuPercent)
                    .arg(memoryPercent)
                    .arg(memoryUse)
                    .arg(memoryAll);
  labCPUMemory->setText(msg);
}
