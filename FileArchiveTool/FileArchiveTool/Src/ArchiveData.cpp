#include "ArchiveData.h"
#include "FileArchiveToolSys.h"
#include "Util.h"
#include <io.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

ArchiveData::ArchiveData()
{

}

ArchiveData::~ArchiveData()
{

}

void ArchiveData::ArchiveDir(const char* pDir)
{
	FileArchiveToolSysDef->getUtilPtr()->bindWalkDirDelegate(fastdelegate::MakeDelegate(this, &ArchiveData::fileHandle));
}

bool ArchiveData::fileHandle(struct _finddata_t* FileInfo)
{


	return true;
}

END_NAMESPACE_FILEARCHIVETOOL