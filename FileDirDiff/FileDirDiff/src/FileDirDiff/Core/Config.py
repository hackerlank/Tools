#-*- encoding=utf-8 -*-

'''
'''

import os
import datetime
#import time

from FileDirDiff.Core.AppSysBase import AppSysBase

# base config info
class Config(object):
    def __init__(self): 
        # 注意全部需要初始化，否则如果配置文件不用，并且没有判断是否有这个属性，就会出问题
        self.m_srcRootPath = ""       # 资源的根目录,这个是原始资源的 目录
        self.m_tmpDir=""              # 临时目录
        self.m_destRootPath = ""      # 存放最终文件的目录,这个就是临时目录
        self.m_file2DirPath = ""      # 文件到目录清单
        self.m_file2Unity3dPath = ""  # 文件到 Unity3d 打包清单
        self.m_preVersion = ""        # 之前版本，倒数第二次保存的版本信息
        self.m_curVersion = ""        # 当前版本，最后一次保存的版本信息
        self.m_prefixMd5FileName = "Md5File"       # 校验和原始文件文件名字前缀
        self.m_prefixMd5MiniName = "Md5Mini"        # 校验和文件的校验和原始文件
        self.m_prefixVerFileName = "VerFile"       # 版本文件名字前缀
        self.m_prefixVerMiniName = "VerMini"
        self.m_subVersion = '0';        # 子版本号，主要是升级所有的文件的版本，经常有些文件传到服务器上，的那是文件有问题，需要主动升级版本号,'0' 是没有版本号
        # 工具类
        self.m_z7z= 'D:\\ProgramFiles\\7-Zip\\7z.exe'
        self.m_fileListName = ""
        
        self.m_tmpFileSubDir = "Tmp"              # 临时文件输出的子目录
        self.m_tmpOutSubDir = "Output"            # 临时文件输出目录
        
        #读取初始化数据
    def readInit(self, filename):
        try:
            fHandle = open(filename, 'r', encoding = 'utf8')
        except IOError:
            AppSysBase.instance().m_logSys.info("{0} 打开文件失败".format(filename));
            return;
        cont = fHandle.read()
        strlist = cont.split('\n')
        idx = 0
        substrList = []
        listlen = len(strlist)
        while(idx < listlen):
            substrList = strlist[idx].split('=')
            if len(substrList[0]):
                self.__dict__[substrList[0]] = substrList[1]
            idx += 1


    # 当前 md 校验和文件路径加名字
    def curMd5FilePath(self):
        curfilename = "{0}_{1}{2}".format(self.m_prefixMd5FileName, self.m_curVersion, '.bytes')
        return os.path.join(self.m_tmpDir, self.m_tmpFileSubDir, curfilename)

    
    def miniMd5FilePath(self):
        curfilename = "{0}_{1}{2}".format(self.m_prefixMd5MiniName, self.m_curVersion, '.bytes')
        return os.path.join(self.m_tmpDir, self.m_tmpFileSubDir, curfilename)
    

    # 返回  file 文件
    def verFilePath(self):
        return os.path.join(self.m_tmpDir, self.m_tmpOutSubDir, self.m_prefixVerFileName + '.bytes')
    
    # 获取最终生成 Mini 的 md5 
    def verMiniPath(self):
        return os.path.join(self.m_tmpDir, self.m_tmpOutSubDir, self.m_prefixVerMiniName + '.bytes')    
    
    
    # 返回  file 文件
    def destVerFilePath(self):
        return os.path.join(self.m_destRootPath, self.m_prefixVerFileName + '.bytes')
    
    # 获取最终生成 Mini 的 md5 
    def destVerMiniPath(self):
        return os.path.join(self.m_destRootPath, self.m_prefixVerMiniName + '.bytes')
    
    
    def verFileNameAndExt(self):
        ret = "{0}{1}".format(self.m_prefixVerFileName, ".bytes")
        return ret
    
    
    def isExistPreV(self):
        return self.m_preVersion != '0'
    
    def isExistCurV(self):
        return self.m_curVersion != '0'
    
    # 临时文件目录
    def tmpFileDir(self):
        return os.path.join(self.m_tmpDir, "tmp")
    
    def outFileDir(self):
        return os.path.join(self.m_tmpDir, "output")
    
    
    def refreshVersion(self):
        self.m_preVersion = self.m_curVersion
        #self.m_curVersion = str(datetime.date.year) + str(datetime.date.month) + str(datetime.date.day) + str(datetime.time.hour) + str(datetime.time.minute) + str(datetime.time.second)
        #nowdata = datetime.date()
        #nowtime = datetime.time()
        self.m_curVersion = str(datetime.datetime.now())
        dotidx = self.m_curVersion.find('.')
        self.m_curVersion = self.m_curVersion[0:dotidx]
        self.m_curVersion = self.m_curVersion.replace(' ', '-')
        self.m_curVersion = self.m_curVersion.replace(':', '-')

    
    def saveCFG(self):
        filename = "Config/Config.txt"
        fHandle = open(filename, 'w', encoding = 'utf8')
        fHandle.write('m_preVersion=' + self.m_preVersion + '\n')
        fHandle.write('m_curVersion=' + self.m_curVersion + '\n')
        fHandle.write('m_prefixMd5FileName=' + self.m_prefixMd5FileName + '\n')
        fHandle.write('m_prefixMd5MiniName=' + self.m_prefixMd5MiniName + '\n')
        fHandle.write('m_prefixVerFileName=' + self.m_prefixVerFileName + '\n')
        fHandle.write('m_prefixVerMiniName=' + self.m_prefixVerMiniName + '\n')

        fHandle.write('m_srcRootPath=' + self.m_srcRootPath + '\n')
        fHandle.write('m_tmpDir=' + self.m_srcRootPath + '\n')
        fHandle.write('m_destRootPath=' + self.m_destRootPath + '\n')
        fHandle.write('m_file2DirPath=' + self.m_file2DirPath + '\n')
        fHandle.write('m_file2Unity3dPath=' + self.m_file2Unity3dPath + '\n')
        fHandle.write('m_fileListName=' + self.m_fileListName + '\n')
        fHandle.write('m_z7z=' + self.m_z7z + '\n')
        fHandle.write('m_subVersion=' + self.m_subVersion)

        fHandle.close()
        
    def hasSubVersion(self):
        return self.m_subVersion != '0'       # '0' 是没有子版本号

    # 获取版本字符串的编码
    def subVersionByte(self):
        #self.m_subVersion.encode("utf-8")
        return bytes(self.m_subVersion, encoding = "utf8")
    
    
    def getFile2DirPath(self):
        return self.m_file2DirPath
    
    
    def getFile2Unity3dPath(self):
        return self.m_file2Unity3dPath
    
    
    def getFileListPath(self):
        return os.path.join(self.m_destRootPath, self.m_fileListName)
        

