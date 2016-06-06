# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject
from Libs.Tools.UtilPath import UtilPath

'''
@brief 生成版本的类型
'''
class eMakeType(GObject):
    eResources = 0;
    eStreamingAssets = 1;
    ePersistent = 2;
    

'''
@brief: Config
'''

class VerConfig(GObject):
    
    def __init__(self):
        super(VerConfig, self).__init__();
        
        self.mTypeId = "Config";
        self.mProjRootPath = "";     # 工程根目录
        self.mResourcesName = "Resources";  # Resources 目录名字
        self.mAssetName = "Assets";       # Assets 目录名字
        self.mStreamingAssetsName = "StreamingAssets";  # StreamingAssets 目录名字
        
        self.mMakeVerType = eMakeType.eResources;       # 生成版本的类型


    def isMakeResources(self):
        return self.mMakeVerType == eMakeType.eResources;


    def isMakeStreamingAssets(self):
        return self.mMakeVerType == eMakeType.eStreamingAssets;
    
    
    def isMakePersistent(self):
        return self.mMakeVerType == eMakeType.ePersistent;

    
    def getResourcesPath(self):
        return UtilPath.combine(self.mProjRootPath, self.mAssetName, self.mResourcesName);
    
    
    def getAssetPath(self):
        return UtilPath.combine(self.mProjRootPath, self.mAssetName);
    

    def getStreamingAssetsPath(self):
        return UtilPath.combine(self.mProjRootPath, self.mAssetName, self.mStreamingAssetsName);
    

    