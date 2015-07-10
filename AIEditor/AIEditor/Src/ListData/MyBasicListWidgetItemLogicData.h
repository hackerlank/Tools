#ifndef __MyBasicListWidgetItemLogicData_H
#define __MyBasicListWidgetItemLogicData_H

#include <string>
#include "AIEditor.h"

BEGIN_NAMESPACE_AIEDITOR

class AIEDITOR_EXPORT MyBasicListWidgetItemLogicData
{
protected:
#include "PushWarn.h"
	std::string m_fullPathAndName;
#include "PopWarn.h"

public:
	MyBasicListWidgetItemLogicData();
	~MyBasicListWidgetItemLogicData();

	void setFullPath(std::string path);
	std::string getFullPath();
};

END_NAMESPACE_AIEDITOR

#endif