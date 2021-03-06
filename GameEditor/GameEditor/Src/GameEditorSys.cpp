#include "GameEditorSys.h"
#include <assert.h>
#include "SkillActionNodeConfig.h"
#include "LuaCScriptMgr.h"
#include "LuaCTestWrap.h"
#include "OgreSys.h"

BEGIN_NAMESPACE_GAMEEDITOR

template <> GameEditorSys* Singleton<GameEditorSys>::ms_Singleton = 0;

GameEditorSys::GameEditorSys()
{
	m_pLuaCScriptMgr = new LuaCScriptMgr;
	m_pSkillActionNodeConfig = new SkillActionNodeConfig;
	m_pOgreSys = new OgreSys;
	LuaCTestWrap_Bind();
	//const char* testfunc = "cHelloWorld(\"ninhoa\")";
	//const char* testfunc = "LuaCTest.cHelloWorld(\"ninhoa\")";
	//const char* testfunc = "TestStaticHandle.cHelloWorld(\"ninhoa\")";
	//const char* testfunc = "asdf.cppHelloWorld(\"ninhoa\")";
	//const char* testfunc = "cppHelloWorld(asdf, \"ninhoa\")";
	//m_pLuaCScriptMgr->doString(testfunc);

	//const char* testCPPFunc = "aaa.bbb.ccc:cppHelloWorld(\"ninhoa\")";
	//const char* testCPPFunc = "cppHelloWorld(aaa, \"ninhoa\")";
	//const char* testCPPFunc = 
	//	"obj = asdf.nihao" \
	//	"func = asdf.cppHelloWorld" \
	//	"asdf.func(\"asasas\")";
	//m_pLuaCScriptMgr->doString(testCPPFunc);
}

void GameEditorSys::instanceT()
{
	assert(0);
	g_pGameEditorSys;
}

SkillActionNodeConfig* GameEditorSys::getSkillActionNodeConfigPtr()
{
	return m_pSkillActionNodeConfig;
}

LuaCScriptMgr* GameEditorSys::getLuaCScriptMgrPtr()
{
	return m_pLuaCScriptMgr;
}

OgreSys* GameEditorSys::getOgreSysPtr()
{
	return m_pOgreSys;
}

void GameEditorSys::init()
{
	m_pSkillActionNodeConfig->loadXml();
}

END_NAMESPACE_GAMEEDITOR