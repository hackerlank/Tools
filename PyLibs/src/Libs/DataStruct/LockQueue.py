﻿# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;
from Libs.DataStruct.LockList import LockList;

class LockQueue(GObject):
    
    def __init__(self, name = ""):
        super(LockQueue, self).__init__();
        
        self.m_list = LockList();
        
        self.mName = name;
        

    def push(self, item):
        self.m_list.Add(item);


    def pop(self):
        return self.m_list.RemoveAt(0);


