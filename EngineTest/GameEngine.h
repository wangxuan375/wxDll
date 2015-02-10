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
	bool D3DInit(
	HINSTANCE hinstance,
	int width, int height,
	bool windowed,
	D3DDEVTYPE devicetype,
	IDirect3DDevice9** device,
	MyInputClass** pInput);

	int EnterMsgLoop(bool (*ptr_display)(float timeDelta));

	LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT msg,
		WPARAM wparam,
		LPARAM lparam);

	template<class T> void Release(T t)
	{
		if(t){
			t->Release();
			t = 0;
		}
	}

	template<class T> void Delete(T t)
	{
		if(t){
			delete t;
			t = 0;
		}
	}
	//Lighters
	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3 *direction, D3DXCOLOR *color);
	D3DLIGHT9 InitPointLight(D3DXVECTOR3 *position, D3DXCOLOR *color);
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3 *position, D3DXVECTOR3 *direction, D3DXCOLOR *color);

	//Materials
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);	

	void GetFiles(std::string path, std::vector<std::string>& files);

	extern const int nWidth;
	extern const int nHeight;

	extern const D3DXCOLOR      WHITE;
	extern const D3DXCOLOR      BLACK;
	extern const D3DXCOLOR        RED;
	extern const D3DXCOLOR      GREEN;
	extern const D3DXCOLOR       BLUE;
	extern const D3DXCOLOR     YELLOW;
	extern const D3DXCOLOR       CYAN;
	extern const D3DXCOLOR    MAGENTA;
	extern const D3DXCOLOR      BROWN;

	extern const D3DMATERIAL9  WHITE_MTRL;
	extern const D3DMATERIAL9	RED_MTRL;
	extern const D3DMATERIAL9  GREEN_MTRL;
	extern const D3DMATERIAL9   BLUE_MTRL;
	extern const D3DMATERIAL9 YELLOW_MTRL;
};

#endif
