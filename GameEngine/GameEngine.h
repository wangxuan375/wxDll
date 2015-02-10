#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

#include <d3dx9.h>
#include <dinput.h>
#include <vector>
#include <string>
#include <io.h>
#include <MMSystem.h>
#include "Input.h"

namespace GameEngine
{
	bool GAMEENGINE_API D3DInit(
	HINSTANCE hinstance,
	int width, int height,
	bool windowed,
	D3DDEVTYPE devicetype,
	IDirect3DDevice9** device,
	MyInputClass** pInput);

	int GAMEENGINE_API EnterMsgLoop(bool (*ptr_display)(float timeDelta));

	LRESULT GAMEENGINE_API CALLBACK WndProc(
		HWND hwnd,
		UINT msg,
		WPARAM wparam,
		LPARAM lparam);

	template<class T> void GAMEENGINE_API Release(T t)
	{
		if(t){
			t->Release();
			t = 0;
		}
	}

	template<class T> void GAMEENGINE_API Delete(T t)
	{
		if(t){
			delete t;
			t = 0;
		}
	}
	//Lighters
	D3DLIGHT9 GAMEENGINE_API InitDirectionalLight(D3DXVECTOR3 *direction, D3DXCOLOR *color);
	D3DLIGHT9 GAMEENGINE_API InitPointLight(D3DXVECTOR3 *position, D3DXCOLOR *color);
	D3DLIGHT9 GAMEENGINE_API InitSpotLight(D3DXVECTOR3 *position, D3DXVECTOR3 *direction, D3DXCOLOR *color);

	//Materials
	D3DMATERIAL9 GAMEENGINE_API InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);	

	void GAMEENGINE_API GetFiles(std::string path, std::vector<std::string>& files);

	extern const int GAMEENGINE_API nWidth;
	extern const int GAMEENGINE_API nHeight;

	extern const GAMEENGINE_API D3DXCOLOR      WHITE;
	extern const GAMEENGINE_API D3DXCOLOR      BLACK;
	extern const GAMEENGINE_API D3DXCOLOR        RED;
	extern const GAMEENGINE_API D3DXCOLOR      GREEN;
	extern const GAMEENGINE_API D3DXCOLOR       BLUE;
	extern const GAMEENGINE_API D3DXCOLOR     YELLOW;
	extern const GAMEENGINE_API D3DXCOLOR       CYAN;
	extern const GAMEENGINE_API D3DXCOLOR    MAGENTA;
	extern const GAMEENGINE_API D3DXCOLOR      BROWN;

	extern const GAMEENGINE_API D3DMATERIAL9  WHITE_MTRL;
	extern const GAMEENGINE_API D3DMATERIAL9	RED_MTRL;
	extern const GAMEENGINE_API D3DMATERIAL9  GREEN_MTRL;
	extern const GAMEENGINE_API D3DMATERIAL9   BLUE_MTRL;
	extern const GAMEENGINE_API D3DMATERIAL9 YELLOW_MTRL;
};

#endif
