#include "LogSys.h"
#include "LogDeviceBase.h"
#include "Thread.h"
#include "PtrDefine.h"
#include <string>

BEGIN_NAMESPACE_FILEARCHIVETOOL

LogSys::LogSys()
{
	m_pLogDeviceVec = new LogDeviceVec;
	m_pAsyncLogVec = new AsyncLogVec;
	m_threadID = new boost::thread::id;
	m_asyncLogLock = new boost::mutex;
	*m_threadID = Thread::currentId();
}

LogSys::~LogSys()
{
	SAFE_DELETE(m_pLogDeviceVec);
	SAFE_DELETE(m_pAsyncLogVec);
	SAFE_DELETE(m_asyncLogLock);
	SAFE_DELETE(m_threadID);
}

void LogSys::log(const char* msg)
{
	if (*m_threadID == boost::thread::id())		// 如果是主线程中调用
	{
		LogDeviceVecIt itBegin, itEnd;
		itBegin = m_pLogDeviceVec->begin();
		itEnd = m_pLogDeviceVec->end();

		for (; itBegin != itEnd; ++itBegin)
		{
			(*itBegin)->log(msg);
		}
	}
	else
	{
		boost::lock_guard<boost::mutex> lock(*m_asyncLogLock);
		std::string str(msg);			// 测试字符串释放的时候会宕机的问题
		m_pAsyncLogVec->push_back(str);
	}
}

void LogSys::onTick()
{
	boost::lock_guard<boost::mutex> lock(*m_asyncLogLock);

	LogDeviceVecIt itBegin, itEnd;
	itBegin = m_pLogDeviceVec->begin();
	itEnd = m_pLogDeviceVec->end();

	for (; itBegin != itEnd; ++itBegin)
	{
		AsyncLogVecIt itBeginLog, itEndLog;
		itBeginLog = m_pAsyncLogVec->begin();
		itEndLog = m_pAsyncLogVec->end();

		for (; itBeginLog != itEndLog; ++itBeginLog)
		{
			(*itBegin)->log(itBeginLog->c_str());
		}
	}

	// 这个地方在释放某个 std::string 字符串析构的时候会宕机
	m_pAsyncLogVec->clear();
}

void LogSys::regLogDevice(LogDeviceBase* pDev)
{
	m_pLogDeviceVec->push_back(pDev);
}

END_NAMESPACE_FILEARCHIVETOOL