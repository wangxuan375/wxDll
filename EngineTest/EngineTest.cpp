// EngineTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GameEngine.h"

#ifdef _DEBUG
#pragma comment(lib,"GameEngine.lib") 
//#else
//#pragma comment(lib,"..//Release//GameEngine.lib") 
#endif

//INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE g_hEngine = NULL;
#ifdef _DEBUG
	g_hEngine = LoadLibraryA("..//Debug//GameEngine.dll");
#else
	g_hEngine = LoadLibraryA("..//Release//GameEngine.dll");
#endif
	if (!g_hEngine)
	{
		printf("Load Engine.dll failed!");
		getchar();
		return 1;
	}
	//pD3DInitFun g_pfnD3DInit = (pD3DInitFun)GetProcAddress(g_hEngine, "D3DInit");
	//if (!g_pfnD3DInit)
	//{
	//	printf("Cannot Get Function GameEngine::D3DInit");
	//	getchar();
	//	return 1;
	//}
	HINSTANCE hInst = NULL;
	IDirect3DDevice9 *g_pDevice = NULL;
	GameEngine::MyInputClass* pInput = NULL;
	GameEngine::D3DInit(hInst, 800, 600, 1, D3DDEVTYPE_HAL, &g_pDevice, &pInput);
	//g_pfnD3DInit(hInst, 800, 600, 1, D3DDEVTYPE_HAL, &g_pDevice, NULL);
	getchar();
	return 0;
}