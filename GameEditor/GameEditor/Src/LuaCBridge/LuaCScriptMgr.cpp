#include "LuaCScriptMgr.h"
#include <sstream>
#include "LuaCVM.h"
#include "LuaCObjectTranslator.h"
#include <string>
#include "LuaCFunction.h"
#include "LuaCTable.h"
#include "LuaCObject.h"

BEGIN_NAMESPACE_GAMEEDITOR

LuaCObjectTranslator* LuaCScriptMgr::_translator = nullptr;
#if MULTI_STATE
List<LuaScriptMgr*> LuaCScriptMgr::mgrList;
int LuaCScriptMgr::mgrPos = 0;
#else
LuaCFunction* LuaCScriptMgr::traceback;
#endif

LuaCScriptMgr::LuaCScriptMgr()
{
	m_pLuaCVM = new LuaCVM;
	setLuaFilePath("D:/file/opensource/unity-game-git/unitygame/Tools/GameEditor/LuaScript");
	luaL_dofile(m_pLuaCVM->L, "TestLua.lua");
}

LuaCScriptMgr::~LuaCScriptMgr()
{
	m_pLuaCVM->closeLua();
}

LuaCVM* LuaCScriptMgr::getLuaCVM()
{
	return m_pLuaCVM;
}

void LuaCScriptMgr::setLuaFilePath(std::string path)
{
	std::stringstream strStream;
	strStream << "local m_package_path = package.path" << "\r\n" << "package.path = string.format(\"%s;%s/?.lua\", m_package_path, " << path << ")";
	luaL_dostring(m_pLuaCVM->L, strStream.str().c_str());
}

void LuaCScriptMgr::setCFilePath(std::string path)
{

}

void LuaCScriptMgr::doString(std::string value)
{
	m_pLuaCVM->doString(value);
}

void LuaCScriptMgr::doFile(std::string path)
{
	m_pLuaCVM->doFile(path);
}

void LuaCScriptMgr::CheckArgsCount(lua_State* L, int count)
{
	int c = lua_gettop(L);

	if (c != count)
	{
		std::string str = "no overload for method '{0}' takes '{1}' arguments";
		luaL_error(L, str.c_str());
	}
}

//��ȡobject���ͣ�objectΪ��������, �ܶ�ȡ���д�lua���ݵĲ���
LuaCObject* LuaCScriptMgr::GetVarObject(lua_State* L, int stackPos)
{
	LuaCObject* ret = nullptr;
	int type = lua_type(L, stackPos);

	switch (type)
	{
	case LUA_TNUMBER:
		ret->m_float = lua_tonumber(L, stackPos);
	case LUA_TSTRING:
		ret->m_pChar = lua_tostring(L, stackPos);
	case LUA_TUSERDATA:
	{
		ret->m_pUserData = lua_touserdata(L, stackPos);

		//if (udata != -1)
		//{
		//	object obj = null;
		//	GetTranslator(L).objects.TryGetValue(udata, out obj);
		//	return obj;
		//}
		//else
		//{
		//	return null;
		//}
	}
	case LUA_TBOOLEAN:
		ret->m_bool = lua_toboolean(L, stackPos);
	case LUA_TTABLE:
		ret = GetVarTable(L, stackPos);
	case LUA_TFUNCTION:
		lua_pushvalue(L, stackPos);
		ret->m_pLuaCFunction = new LuaCFunction(luaL_ref(L, LUA_REGISTRYINDEX), GetTranslator(L)->interpreter);
	default:
		return nullptr;
	}

	return ret;
}

LuaCObject* LuaCScriptMgr::GetVarTable(lua_State* L, int stackPos)
{
	LuaCObject* o = nullptr;
	int oldTop = lua_gettop(L);
	lua_pushvalue(L, stackPos);
	lua_pushstring(L, "class");
	lua_gettable(L, -2);

	if (lua_isnil(L, -1))
	{
		lua_settop(L, oldTop);
		lua_pushvalue(L, stackPos);
		o->m_pLuaCTable = new LuaCTable(luaL_ref(L, LUA_REGISTRYINDEX), GetTranslator(L)->interpreter);
	}
	else
	{
		std::string cls = lua_tostring(L, -1);
		lua_settop(L, oldTop);

		stackPos = stackPos > 0 ? stackPos : stackPos + oldTop + 1;

		/*if (cls == "Vector3")
		{
			o = GetVector3(L, stackPos);
		}
		else if (cls == "Vector2")
		{
			o = GetVector2(L, stackPos);
		}
		else if (cls == "Quaternion")
		{
			o = GetQuaternion(L, stackPos);
		}
		else if (cls == "Color")
		{
			o = GetColor(L, stackPos);
		}
		else if (cls == "Vector4")
		{
			o = GetVector4(L, stackPos);
		}
		else if (cls == "Ray")
		{
			o = GetRay(L, stackPos);
		}
		else if (cls == "Bounds")
		{
			o = GetBounds(L, stackPos);
		}
		else
		{
			lua_pushvalue(L, stackPos);
			o = new LuaTable(LuaDLL.luaL_ref(L, LuaIndexes.LUA_REGISTRYINDEX), GetTranslator(L).interpreter);
		}*/
	}

	//LuaDLL.lua_settop(L, oldTop);
	return o;
}

LuaCObjectTranslator* LuaCScriptMgr::GetTranslator(lua_State* L)
{
#if MULTI_STATE
	return LuaCObjectTranslator.FromState(L);
#else            
	if (_translator == nullptr)
	{
		return LuaCObjectTranslator::FromState(L);
	}

	return _translator;
#endif        
}

//ѹ��һ��object����
void LuaCScriptMgr::PushVarObject(lua_State* L, LuaCObject* o)
{
	if (o == nullptr)
	{
		lua_pushnil(L);
		return;
	}

	int t = o->GetType();

	if (LUAC_TBOOLEAN == t)
	{
		lua_pushnil(L);
	}
	else if (LUAC_TBOOLEAN == t)
	{
		lua_pushboolean(L, o->m_bool);
	}
	else if (LUAC_TLIGHTUSERDATA == t)
	{
		lua_pushlightuserdata(L, o->m_pLightUserData);
	}
	else if (LUAC_TNUMBER == t)
	{
		lua_pushnumber(L, o->m_float);
	}
	else if (LUAC_TSTRING == t)
	{
		lua_pushstring(L, o->m_pChar);
	}
	else if (LUAC_TTABLE == t)
	{
		lua_rawseti(L, LUA_REGISTRYINDEX, o->m_pLuaCTable->getRef());
	}
	else if (LUAC_TFUNCTION == t)
	{
		lua_rawseti(L, LUA_REGISTRYINDEX, o->m_pLuaCFunction->getRef());
	}
	else if (LUAC_TUSERDATA == t)
	{
		//lua_rawseti(L, o->m_pUserData);
	}
	else if (LUAC_TTHREAD == t)
	{

	}
	else
	{
		lua_pushinteger(L, o->m_int);
	}
	//if (t.IsValueType)
	//{
	//	if (t == typeof(bool))
	//	{
	//		bool b = (bool)o;
	//		lua_pushboolean(L, b);
	//	}
	//	else if (t.IsEnum)
	//	{
	//		Push(L, (System.Enum)o);
	//	}
	//	else if (t.IsPrimitive)
	//	{
	//		double d = Convert.ToDouble(o);
	//		lua_pushnumber(L, d);
	//	}
	//	else if (t == typeof(Vector3))
	//	{
	//		Push(L, (Vector3)o);
	//	}
	//	else if (t == typeof(Vector2))
	//	{
	//		Push(L, (Vector2)o);
	//	}
	//	else if (t == typeof(Vector4))
	//	{
	//		Push(L, (Vector4)o);
	//	}
	//	else if (t == typeof(Quaternion))
	//	{
	//		Push(L, (Quaternion)o);
	//	}
	//	else if (t == typeof(Color))
	//	{
	//		Push(L, (Color)o);
	//	}
	//	else if (t == typeof(RaycastHit))
	//	{
	//		Push(L, (RaycastHit)o);
	//	}
	//	else if (t == typeof(Touch))
	//	{
	//		Push(L, (Touch)o);
	//	}
	//	else if (t == typeof(Ray))
	//	{
	//		Push(L, (Ray)o);
	//	}
	//	else
	//	{
	//		PushValue(L, o);
	//	}
	//}
	//else
	//{
	//	if (t.IsArray)
	//	{
	//		PushArray(L, (System.Array)o);
	//	}
	//	else if (t == typeof(LuaCSFunction))
	//	{
	//		GetTranslator(L).pushFunction(L, (LuaCSFunction)o);
	//	}
	//	else if (t.IsSubclassOf(typeof(Delegate)))
	//	{
	//		Push(L, (Delegate)o);
	//	}
	//	else if (IsClassOf(t, typeof(IEnumerator)))
	//	{
	//		Push(L, (IEnumerator)o);
	//	}
	//	else if (t == typeof(string))
	//	{
	//		string str = (string)o;
	//		LuaDLL.lua_pushstring(L, str);
	//	}
	//	else if (t == typeof(LuaStringBuffer))
	//	{
	//		LuaStringBuffer lsb = (LuaStringBuffer)o;
	//		LuaDLL.lua_pushlstring(L, lsb.buffer, lsb.buffer.Length);
	//	}
	//	else if (t.IsSubclassOf(typeof(UnityEngine.Object)))
	//	{
	//		UnityEngine.Object obj = (UnityEngine.Object)o;

	//		if (obj == null)
	//		{
	//			LuaDLL.lua_pushnil(L);
	//		}
	//		else
	//		{
	//			PushObject(L, o);
	//		}
	//	}
	//	else if (t == typeof(LuaTable))
	//	{
	//		((LuaTable)o).push(L);
	//	}
	//	else if (t == typeof(LuaFunction))
	//	{
	//		((LuaFunction)o).push(L);
	//	}
	//	else if (t == monoType)
	//	{
	//		Push(L, (Type)o);
	//	}
	//	else if (t.IsSubclassOf(typeof(TrackedReference)))
	//	{
	//		UnityEngine.TrackedReference obj = (UnityEngine.TrackedReference)o;

	//		if (obj == null)
	//		{
	//			LuaDLL.lua_pushnil(L);
	//		}
	//		else
	//		{
	//			PushObject(L, o);
	//		}
	//	}
	//	else
	//	{
	//		PushObject(L, o);
	//	}
	//}
}

//������LuaFunction
std::vector<LuaCObject*> LuaCScriptMgr::CallLuaFunction(std::string name, std::vector<LuaCObject*>& args)
{
	std::vector<LuaCObject*> objs;
	LuaCBase* lb = nullptr;

	if (dict.find(name) != dict.end())
	{
		LuaCFunction* func = (LuaCFunction*)lb;
		return func->Call(args);
	}
	else
	{
		lua_State* L = m_pLuaCVM->L;
		LuaCFunction* func = nullptr;
		int oldTop = lua_gettop(L);

		if (PushLuaFunction(L, name))
		{
			int reference = luaL_ref(L, LUA_REGISTRYINDEX);
			func = new LuaCFunction(reference, m_pLuaCVM);
			lua_settop(L, oldTop);
			//std::vector<LuaCObject*> objs = func->Call(args);
			objs = func->Call(args);
			//func.Dispose();
			return objs;
		}

		//return nullptr;
		return objs;
	}
}

bool LuaCScriptMgr::PushLuaFunction(lua_State* L, std::string fullPath)
{
	int oldTop = lua_gettop(L);
	int pos = (int)fullPath.find_last_of('.');

	if (pos > 0)
	{
		std::string tableName = fullPath.substr(0, pos);

		if (PushLuaTable(L, tableName))
		{
			std::string funcName = fullPath.substr(pos + 1);
			lua_pushstring(L, funcName.c_str());
			lua_rawget(L, -2);
		}

		int type = lua_type(L, -1);

		if (type != LUA_TFUNCTION)
		{
			lua_settop(L, oldTop);
			return false;
		}

		lua_insert(L, oldTop + 1);
		lua_settop(L, oldTop + 1);
	}
	else
	{
		lua_getglobal(L, fullPath.c_str());
		int type = lua_type(L, -1);

		if (type != LUA_TFUNCTION)
		{
			lua_settop(L, oldTop);
			return false;
		}
	}

	return true;
}

void LuaCScriptMgr::PushTraceBack(lua_State* L)
{
#if !MULTI_STATE
	if (traceback == nullptr)
	{
		lua_getglobal(L, "traceback");
		return;
	}

	traceback->push();
#else
	lua_getglobal(L, "traceback");
#endif
}

bool LuaCScriptMgr::PushLuaTable(lua_State* L, std::string fullPath)
{
	//string[] path = fullPath.Split(new char[] { '.' });
	std::vector<std::string> path;
	std::string delim = ".";
	LuaCScriptMgr::split(fullPath, delim, &path);

	int oldTop = lua_gettop(L);
	lua_getglobal(L, path[0].c_str());
	//lua_pushstring(L, path[0].c_str());
	//lua_rawget(L, LUA_GLOBALSINDEX);

	int type = lua_type(L, -1);

	if (type != LUA_TTABLE)
	{
		lua_settop(L, oldTop);
		lua_pushnil(L);
		//Debugger.LogError("Push lua table {0} failed", path[0]);
		return false;
	}

	for (int i = 1; i < path.size(); i++)
	{
		lua_pushstring(L, path[i].c_str());
		lua_rawget(L, -2);
		type = lua_type(L, -1);

		if (type != LUA_TTABLE)
		{
			lua_settop(L, oldTop);
			//Debugger.LogError("Push lua table {0} failed", fullPath);
			return false;
		}
	}

	if (path.size() > 1)
	{
		lua_insert(L, oldTop + 1);
		lua_settop(L, oldTop + 1);
	}

	return true;
}

////ѹ��һ����object�����ı���
//void LuaCScriptMgr::PushObject(lua_State* L, object o)
//{
//	GetTranslator(L).pushObject(L, o, "luaNet_metatable");
//}
//
//void LuaCScriptMgr::Push(lua_State* L, UnityEngine.Object obj)
//{
//	PushObject(L, obj == null ? null : obj);
//}

void LuaCScriptMgr::split(std::string& s, std::string& delim, std::vector<std::string>* ret)
{
	size_t last = 0;
	size_t index = s.find_first_of(delim, last);
	while (index != std::string::npos)
	{
		ret->push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(delim, last);
	}
	if (index - last>0)
	{
		ret->push_back(s.substr(last, index - last));
	}
}

END_NAMESPACE_GAMEEDITOR