#-*- encoding=utf-8 -*-

'''
'''

from threading import Lock

class LogSys(object):
    def __init__(self):
        self.m_effLock = Lock()
        self.m_effLog = []

    # 输出一行信息
    def info(self, desc):
        if not desc is None:
            self.m_effLock.acquire()
            if isinstance(desc, bytes):
                try:
                    desc = desc.decode("utf-8")
                except:
                    desc = desc.decode("gbk")
            if len(desc):
                self.m_effLog.append(desc)
            self.m_effLock.release()

    def getlogger(self, loglist):
        self.m_effLock.acquire()
        for log in self.m_effLog:
            loglist.append(log)
        del self.m_effLog[:]
        self.m_effLock.release()
