//=============================================================================//
//  ___  ___   _   _   _    __   _   ___ ___ __ __
// |_ _|| __| / \ | \_/ |  / _| / \ | o \ o \\ V /
//  | | | _| | o || \_/ | ( |_n| o ||   /   / \ / 
//  |_| |___||_n_||_| |_|  \__/|_n_||_|\\_|\\ |_|  2008
//										 
//=============================================================================//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "ILuaInterface.h"
#include "ILuaObject.h"

#include "ILuaModuleManager.h"

#ifdef WIN32
#define  DLL_EXPORT   extern "C" __declspec( dllexport )
#define  DLL_IMPORT   extern "C" __declspec( dllimport )
#else
#define DLL_EXPORT extern "C" __attribute__((visibility("default")))
#define DLL_IMPORT 
#endif

// You should place this at the top of your module
#define GMOD_MODULE( _startfunction_, _closefunction_ ) \
	ILuaModuleManager* modulemanager = NULL;\
	int _startfunction_( lua_State* L );\
	int _closefunction_( lua_State* L );\
	DLL_EXPORT int gmod_open( ILuaInterface* i ) \
	{ \
		modulemanager = i->GetModuleManager();\
		return _startfunction_( (lua_State*)(i->GetLuaState()) );\
	}\
	DLL_EXPORT int gmod_close( lua_State* L ) \
	{\
		_closefunction_( L );\
		return 0;\
	}\

#define LUA_FUNCTION( _function_ ) static int _function_( lua_State* L )
