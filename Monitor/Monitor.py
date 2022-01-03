# !/usr/bin/python3
# -*- coding: utf-8 -*-
# @File      : Monitor.py

__author__ = 'JUN'
__version__ = '1.0'
__date__ = '2021/3/1'
__copyright__ = 'Copyright 2020, PI'

import logging
import psutil
import os
import time

## 设置一个日志输出文件
log_filename = "logging.txt"

# 设置日志输出格式
log_format = 'Message:"Time: %(asctime)s   %(message)s"'

# 日志文件基本设置
logging.basicConfig(
    format=log_format,
    datefmt='%Y-%m-%d %H:%M:%S',
    level=logging.DEBUG,
    filename=log_filename,
    filemode='w')

def get_memory_percent():
    return psutil.virtual_memory().percent

def get_cpu_percent():
    return psutil.cpu_percent(interval=1, percpu=False)

# Message:"Time: 2021-03-01 15:19:56.658  CPU: 35.5351  Memory: 44.0025"

while True:
    time.sleep(3)
    memory_percent = get_memory_percent()
    cpu_percent = get_cpu_percent()
    msg = 'CPU: {}  Memory: {}'.format(cpu_percent, memory_percent)
    print(msg)
    logging.debug(msg)

