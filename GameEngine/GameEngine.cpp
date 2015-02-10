#include "stdafx.h"
const int GameEngine::nWidth = 1024;
const int GameEngine::nHeight = 720;

const D3DXCOLOR      GameEngine::WHITE( D3DCOLOR_XRGB(255, 255, 255) );
const D3DXCOLOR      GameEngine::BLACK( D3DCOLOR_XRGB(  0,   0,   0) );
const D3DXCOLOR        GameEngine::RED( D3DCOLOR_XRGB(255,   0,   0) );
const D3DXCOLOR      GameEngine::GREEN( D3DCOLOR_XRGB(  0, 255,   0) );
const D3DXCOLOR       GameEngine::BLUE( D3DCOLOR_XRGB(  0,   0, 255) );
const D3DXCOLOR     GameEngine::YELLOW( D3DCOLOR_XRGB(255, 255,   0) );
const D3DXCOLOR       GameEngine::CYAN( D3DCOLOR_XRGB(  0, 255, 255) );
const D3DXCOLOR    GameEngine::MAGENTA( D3DCOLOR_XRGB(255,   0, 255) );
const D3DXCOLOR      GameEngine::BROWN( D3DCOLOR_XRGB( 75,  60,  52) );

const D3DMATERIAL9  WHITE_MTRL = GameEngine::InitMtrl(GameEngine::WHITE, GameEngine::WHITE, GameEngine::WHITE, GameEngine::BLACK, 2.0f);
const D3DMATERIAL9	  RED_MTRL = GameEngine::InitMtrl(GameEngine::RED, GameEngine::RED, GameEngine::RED, GameEngine::BLACK, 2.0f);
const D3DMATERIAL9  GREEN_MTRL = GameEngine::InitMtrl(GameEngine::GREEN, GameEngine::GREEN, GameEngine::GREEN, GameEngine::BLACK, 2.0f);
const D3DMATERIAL9   BLUE_MTRL = GameEngine::InitMtrl(GameEngine::BLUE, GameEngine::BLUE, GameEngine::BLUE, GameEngine::BLACK, 2.0f);
const D3DMATERIAL9 YELLOW_MTRL = GameEngine::InitMtrl(GameEngine::YELLOW, GameEngine::YELLOW, GameEngine::YELLOW, GameEngine::BLACK, 2.0f);

bool GameEngine::D3DInit(
	HINSTANCE hinstance, 
	int width, int height, 
	bool windowed, D3DDEVTYPE devicetype,
	IDirect3DDevice9** device,
	MyInputClass** pInput) 
{
	WNDCLASSEX Class1 = {
		sizeof(WNDCLASSEX),
		CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW,
		GameEngine::WndProc,
		0, 0,
		hinstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		NULL,
		L"MYGAMECLASS",
		LoadIcon(NULL, IDI_APPLICATION)
	};
	if( !RegisterClassEx(&Class1) ){
		MessageBox(0, L"RegisterClass() - FAILED", 0, 0);
		return false;
	}
	HWND hwnd;
	if( !(hwnd = CreateWindowEx( NULL, 
		L"MYGAMECLASS", L"Window Title",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100,50,
		width,height,
		NULL,NULL,
		hinstance,NULL ) ) ){
			MessageBox(0, L"CreateWindow() - FAILED", 0, 0);
			return false;
	}

	HRESULT hr = 0;
	IDirect3D9 *d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if( !d3d9 ){
		MessageBox(0, L"Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}
	D3DCAPS9 caps;
	int vp;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth			 = width;
	d3dpp.BackBufferHeight			 = height;
	d3dpp.BackBufferFormat			 = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount			 = 2;
	d3dpp.MultiSampleType			 = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality		 = 0;
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow				 = hwnd;
	d3dpp.Windowed					 = windowed;
	d3dpp.EnableAutoDepthStencil	 = true;
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D24S8;
	d3dpp.Flags                      = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT,
		devicetype,
		hwnd,
		vp,
		&d3dpp,
		device);
	if( FAILED(hr) ){
		// try again using a 16-bit depth buffer
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			devicetype,
			hwnd,
			vp,
			&d3dpp,
			device);
		if( FAILED(hr) ){
			d3d9->Release();
			MessageBox(0, L"CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}
	*pInput = new MyInputClass();
	(*pInput)->Init(hwnd, hinstance, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	d3d9->Release();

	return true;
}

int GameEngine::EnterMsgLoop( bool (*ptr_display)(float timeDelta))
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	static float lastTime = (float)timeGetTime();

	while(msg.message != WM_QUIT) {
		if( PeekMessage(&msg, 0, 0, 0, PM_REMOVE) ){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			float curTime  = (float)timeGetTime();
			float timeDelta = (curTime - lastTime)*0.001f;
			ptr_display(timeDelta);
			lastTime = curTime;
		}
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK GameEngine::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg){
	case WM_KEYDOWN:
		{
			if( wparam == VK_ESCAPE )
				DestroyWindow(hwnd);
		}break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;
	default:
		break;
	}
	return ( DefWindowProc(hwnd, msg, wparam, lparam) );
}

D3DLIGHT9 GameEngine::InitDirectionalLight(D3DXVECTOR3 *direction, D3DXCOLOR *color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));
	light.Type      = D3DLIGHT_DIRECTIONAL;
	light.Ambient   = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	light.Diffuse   = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular  = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	light.Direction = *direction;
	return light;
}

D3DLIGHT9 GameEngine::InitPointLight(D3DXVECTOR3 *position, D3DXCOLOR *color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));
	light.Type      = D3DLIGHT_POINT;
	light.Ambient   = *color * 0.6f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	return light;
}

D3DLIGHT9 GameEngine::InitSpotLight(D3DXVECTOR3 *position, D3DXVECTOR3 *direction, D3DXCOLOR *color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));
	light.Type      = D3DLIGHT_SPOT;
	light.Ambient   = *color * 0.0f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Direction = *direction;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta        = 0.4f;
	light.Phi          = 0.9f;
	return light;
}

D3DMATERIAL9 GameEngine::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient  = a;
	mtrl.Diffuse  = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power    = p;
	return mtrl;
}

void GameEngine::GetFiles( std::string path, std::vector<std::string>& files )
{
	//文件句柄
	intptr_t   hFile   =   0;
	//文件信息
	struct _finddata_t fileinfo;
	std::string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if((fileinfo.attrib &  _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					GetFiles( p.assign(path).append("\\").append(fileinfo.name), files );
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}