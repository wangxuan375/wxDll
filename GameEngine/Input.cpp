#include "stdafx.h"


//-----------------------------------------------------------------------------
// Desc: ���캯��
//-----------------------------------------------------------------------------
MyInputClass::MyInputClass()
{
	m_pDirectInput = NULL;
	m_KeyboardDevice = NULL;
	ZeroMemory(m_keyBuffer,sizeof(char)*256);
	m_MouseDevice= NULL;
	ZeroMemory(&m_MouseState, sizeof(m_MouseState));
}


//-----------------------------------------------------------------------------
// Name��MyInputClass::Init(��
// Desc: ��ʼ��DirectInput���̼���������豸
//-----------------------------------------------------------------------------
HRESULT MyInputClass::Init( HWND hWnd,HINSTANCE hInstance,DWORD keyboardCoopFlags, DWORD mouseCoopFlags )
{
	HRESULT hr;
	//��ʼ��һ��IDirectInput8�ӿڶ���
	HR(DirectInput8Create( hInstance, DIRECTINPUT_VERSION, 
		IID_IDirectInput8,(void**)&m_pDirectInput,NULL ));

	//���м����豸�ĳ�ʼ��
	HR( m_pDirectInput->CreateDevice( GUID_SysKeyboard, &m_KeyboardDevice, NULL ));
	HR( m_KeyboardDevice->SetCooperativeLevel( hWnd, keyboardCoopFlags));
	HR( m_KeyboardDevice->SetDataFormat( &c_dfDIKeyboard ));
	HR( m_KeyboardDevice->Acquire( ));
	HR( m_KeyboardDevice->Poll( ));

	//��������豸�ĳ�ʼ��
	HR( m_pDirectInput->CreateDevice( GUID_SysMouse, &m_MouseDevice, NULL ));
	HR( m_MouseDevice->SetCooperativeLevel( hWnd,mouseCoopFlags));
	HR( m_MouseDevice->SetDataFormat( &c_dfDIMouse ));
	HR( m_MouseDevice->Acquire( ));
	HR( m_KeyboardDevice->Poll( ));

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name��MyInputClass::GetInput()
// Desc: ���ڻ�ȡ������Ϣ�ĺ���
//-----------------------------------------------------------------------------
void MyInputClass::GetInput()
{
	HRESULT hr = m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer); 
	//��ȡ����������Ϣ
	if(hr)
	{
		m_KeyboardDevice->Acquire();  
		m_KeyboardDevice->GetDeviceState( sizeof(m_keyBuffer),(LPVOID)m_keyBuffer );
	}

	hr = m_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**)&m_MouseState); 
	//��ȡ���������Ϣ
	if(hr)
	{
		m_MouseDevice->Acquire();
		m_MouseDevice->GetDeviceState( sizeof(DIMOUSESTATE), (void**)&m_MouseState);
	}
}

//-----------------------------------------------------------------------------
// Name��MyInputClass::IsKeyDown()
// Desc: �жϼ�����ĳ�����Ƿ���
//-----------------------------------------------------------------------------
bool MyInputClass::IsKeyDown(int iKey)
{
	if(m_keyBuffer[iKey] & 0x80)
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------
// Name��MyInputClass::IsMouseButtonDown()
// Desc: �ж������ĳ���Ƿ���
//-----------------------------------------------------------------------------
bool MyInputClass::IsMouseButtonDown(int button)
{
	return (m_MouseState.rgbButtons[button] & 0x80) != 0;
}

//-----------------------------------------------------------------------------
// Name��MyInputClass::MouseDX
// Desc: �������ָ���X������ֵ
//-----------------------------------------------------------------------------
float MyInputClass::MouseDX()
{
	return (float)m_MouseState.lX;
}

//-----------------------------------------------------------------------------
// Name��MyInputClass::MouseDY
// Desc: �������ָ���Y������ֵ
//-----------------------------------------------------------------------------
float MyInputClass::MouseDY()
{
	return (float)m_MouseState.lY;
}

//-----------------------------------------------------------------------------
// Name��MyInputClass::MouseDZ
// Desc: �������ָ���Z������ֵ�����֣�
//-----------------------------------------------------------------------------
float MyInputClass::MouseDZ()
{
	return (float)m_MouseState.lZ;
}




//-----------------------------------------------------------------------------
// Desc: ��������
//-----------------------------------------------------------------------------
MyInputClass::~MyInputClass(void)
{
	if(m_KeyboardDevice != NULL)
		m_KeyboardDevice->Unacquire();
	if(m_MouseDevice != NULL)
		m_MouseDevice->Unacquire();
	GameEngine::Release<IDirectInputDevice8*>(m_KeyboardDevice);
	GameEngine::Release<IDirectInputDevice8*>(m_MouseDevice);
	GameEngine::Release<IDirectInput8*>(m_pDirectInput);
}
