#include "MImport3dMax.h"

#include "assimp/Importer.hpp"      // 导入器在该头文件中定义
#include "assimp/scene.h"           // 读取到的模型数据都放在scene中
#include "assimp/postprocess.h"     // 该头文件中包含后处理的标志位定义

bool MImport3dMax::import(const std::string& pFile)
{
	// 定义一个导入器 
	Assimp::Importer importer;

	// 使用导入器导入选定的模型文件 
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |            //后处理标志，自动计算切线和副法线
		aiProcess_Triangulate |					//后处理标志，自动将四边形面转换为三角面
		aiProcess_JoinIdenticalVertices |		//后处理标志，自动合并相同的顶点
		aiProcess_SortByPType);					//后处理标志，将不同图元放置到不同的模型中去，图片类型可能是点、直线、三角形等
	//更多后处理标志可以参考Assimp的文档  
	if (!scene)
	{
		//导入错误，获取错误信息并进行相应的处理
		//DoTheErrorLogging( importer.GetErrorString());     
		return false;
	}
	// 根据需要获取scene中的模型数据，各种数据的获取方式可以参考Assimp的文档
	//DoTheSceneProcessing( scene);   

	return true;
}