#ifndef HR
#define HR(x)    { hr = x; if( FAILED(hr) ) { return hr; } }         
//�Զ���һ��HR�꣬����ִ�д���ķ���
#endif

#ifdef GAMEENGINE_EXPORTS
#define GAMEENGINE_API __declspec(dllexport)
#else
#define GAMEENGINE_API __declspec(dllimport)
#endif

#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

#include <d3dx9.h>
#include <dinput.h>
#include <vector>
#include <string>
#include <io.h>
#include <MMSystem.h>

namespace GameEngine
{
	class MyInputClass;

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

	class GAMEENGINE_API MyInputClass
	{
	private:
		IDirectInput8			*m_pDirectInput;	//IDirectInput8�ӿڶ���
		IDirectInputDevice8		*m_KeyboardDevice;  //�����豸�ӿڶ���
		char					 m_keyBuffer[256];  //���ڼ��̼�ֵ�洢������

		IDirectInputDevice8		*m_MouseDevice;     //����豸�ӿڶ���
		DIMOUSESTATE			 m_MouseState;		//��������ֵ�洢��һ���ṹ��

	public:
		HRESULT		Init(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags); //��ʼ��DirectInput���̼���������豸
		void				GetInput();   //���ڻ�ȡ������Ϣ�ĺ���
		bool				IsKeyDown(int iKey);   //�жϼ�����ĳ���Ƿ���

		bool				IsMouseButtonDown(int button);  //�ж���갴���Ƿ񱻰���
		float				MouseDX();   //��������X������ֵ
		float				MouseDY();	//��������Y������ֵ
		float				MouseDZ();	//��������Z������ֵ


	public:
		MyInputClass();	//���캯��
		~MyInputClass();	//��������
	};
};

#endif
