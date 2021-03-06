#-*- encoding=utf-8 -*-

'''
@brief md5 checker
'''

import hashlib
import os
from FileDirDiff import Paths
from FileDirDiff.Core.AppSys import AppSysBase

mdcallback = None       # 回调计算结果
m_m_subVersion = bytes('0', encoding = "utf8")       # 子版本，所有的都会使用子版本用来升级，这个字节编码，不是字符串

#一个文件的 md5 码
def md5_for_file(filepath):
    md5hash = hashlib.md5()
    blocksize = 0x10000
    f = open(filepath, "rb")
    while True:
        data = f.read(blocksize)
        if not data:
            break
        md5hash.update(data)
        
    if hasm_subVersion():
        md5hash.update(m_m_subVersion)
    
    f.close()
    return md5hash.hexdigest()

#一个目录的 md5 码
def md5_for_onedir(directoryName, filesInDirectory):
    AppSysBase.instance().m_logSys.info(directoryName)
    for fname in filesInDirectory:
        fpath = os.path.join(directoryName, fname)
        if not os.path.isdir(fpath):
            #print(fname, "\t", _md5_for_file(fpath))
            #updateMd5(fname, _md5_for_file(fpath))
            #AppSys.AppSysBase.instance().writemd(fname, md5_for_file(fpath))
            mdcallback(directoryName, fname, md5_for_file(fpath))

#所有目录的 md5 码
def md5_for_dirs(startdir):
    for root, dirs, files in os.walk(startdir):
        AppSysBase.instance().m_logSys.info(''.join(dirs))
        md5_for_onedir(root, files)

#测试md5回调函数    
def updateMd5(filename, md):
    global gfHandle
    gfHandle.write(filename + '=' + md + '\n')
    
def hasm_subVersion():
    return m_m_subVersion != bytes('0', encoding = "utf8")       # '0' 是没有子版本号

if __name__ == '__main__':
    filepath = os.path.join(Paths.PACKAGE_DIR, 'mddest.txt')
    global gfHandle
    gfHandle = open(filepath, 'w', encoding='utf8')
    root = input("type root directory:")
    md5_for_dirs(root)
    gfHandle.close()


