# !/usr/bin/python3
# -*- coding: utf-8 -*-
# @File      : cpu_mem_show.py

__author__ = 'JUN'
__version__ = '1.0'
__date__ = '2021/3/1'
__copyright__ = 'Copyright 2020, PI'

import random

import pyecharts.options as opts
from pyecharts.charts import Line


class CpuMemory:
    def __init__(self):
        self.x = []
        self.memory_y = []
        self.cpu_y = []
        self.begin_time = ""
        self.end_time = ""

    def read(self, filename):
        with open(filename, "rb") as f:
            for fLine in f:
                fLine = fLine.decode('ascii')
                if "Time" in fLine:
                    info = fLine[len("Message:"):]. \
                        replace('"', '').replace('\r\n', '').split("  ")
                    _time = info[0][len("Time: "):]
                    _cpu = info[1][len("CPU: "):]
                    _memory = info[2][len("Memory: "):]
                    # 时间限制
                    if _time > self.begin_time and self.end_time:
                        print(_time, _cpu, _memory)
                        self.x.append(_time)
                        self.memory_y.append(_memory)
                        self.cpu_y.append(_cpu)

    def show(self):
        line = (
            Line(init_opts=opts.InitOpts(width="2000px", height="800px"))
            .add_xaxis(xaxis_data=self.x)
            .add_yaxis(
                series_name="CPU",
                y_axis=self.cpu_y,
                is_smooth=True,
            )
            .add_yaxis(
                series_name="Memory",
                y_axis=self.memory_y,
                symbol="triangle",
            )
            .set_global_opts(
                title_opts=opts.TitleOpts(title="系统资源监控"),
                xaxis_opts=opts.AxisOpts(
                    min_interval=5,
                    offset=0,
                    name='时间'),

            )
        )
        line.render_notebook()
        line.render("line.html")  # 输出图形


if __name__ == '__main__':
    cpuMemory = CpuMemory()
    cpuMemory.begin_time = "2021-03-01 14:41:38.157"
    cpuMemory.end_time = "2021-03-02 14:55:44.657"
    cpuMemory.read("./logging.txt")
    cpuMemory.show()
