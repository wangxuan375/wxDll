#ifndef HR
#define HR(x)    { hr = x; if( FAILED(hr) ) { return hr; } }         
//�Զ���һ��HR�꣬����ִ�д���ķ���
#endif

#ifdef GAMEENGINE_EXPORTS
#define GAMEENGINE_API __declspec(dllexport)
#else
#define GAMEENGINE_API __declspec(dllimport)
#endif

#ifndef _MYINPUT_H_
#define _MYINPUT_H_
#include <dinput.h>

//DInputClass�ඨ�忪ʼ
class GAMEENGINE_API MyInputClass
{
private:
	IDirectInput8			*m_pDirectInput;	//IDirectInput8�ӿڶ���
	IDirectInputDevice8		*m_KeyboardDevice;  //�����豸�ӿڶ���
	char					 m_keyBuffer[256];  //���ڼ��̼�ֵ�洢������

	IDirectInputDevice8		*m_MouseDevice;     //����豸�ӿڶ���
	DIMOUSESTATE			 m_MouseState;		//��������ֵ�洢��һ���ṹ��

public:
	HRESULT		Init( HWND hWnd,HINSTANCE hInstance,DWORD keyboardCoopFlags, DWORD mouseCoopFlags ); //��ʼ��DirectInput���̼���������豸
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
#endif