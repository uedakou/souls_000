//============================================
//
// ����[input.cpp]
// Author:Uedakou
// 
//============================================
#include "input.h"

// �ÓI�����o
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//============================================
// �R���X�g�i���j
//============================================
CInput::CInput(): m_pDevice(nullptr)
{
}
//============================================
// �f�X�g���i���j
//============================================
CInput::~CInput()
{
}
//============================================
// �������i���j
//============================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		if (FAILED(DirectInput8Create(hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&m_pInput, nullptr)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}
//============================================
// �I���i���j
//============================================
void CInput::Uninit()
{
	// ���̓f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();	// �f�o�C�X�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
	// DirectInput�I�u�W�F�N�g�̕���
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}
//============================================
// �X�V�i���j
//============================================
void CInput::Update()
{

}
//============================================
// �R���X�g�i�L�[�{�[�h�j
//============================================
CInputKeyboard::CInputKeyboard() 
{
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aPless[nCnt] = 0;
		m_aTrigger[nCnt] = 0;
		m_aRepeat[nCnt] = 0;
		m_aRelease[nCnt] = 0;
	}
}
//============================================
// �f�X�g���i�L�[�{�[�h�j
//============================================
CInputKeyboard::~CInputKeyboard()
{
}
//============================================
// �������i�L�[�{�[�h�j
//============================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard,
		&m_pDevice, nullptr)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}
	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();
	return S_OK;
}
//============================================
// �I���i�L�[�{�[�h�j
//============================================
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}
//============================================
// �X�V�i�L�[�{�[�h�j
//============================================
void CInputKeyboard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏��
	int nCntKey;
	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// �L�[�{�[�h�̃����[�X����ۑ�
			m_aRelease[nCntKey] = (m_aPless[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			// �L�[�{�[�h�̃��s�[�g����ۑ�
			m_aRepeat[nCntKey] = (m_aPless[nCntKey] & aKeyState[nCntKey]);
			// �L�[�{�[�h�̃g���K�[����ۑ�
			m_aTrigger[nCntKey] = (m_aPless[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			// �L�[�{�[�h�̃v���X����ۑ�
			m_aPless[nCntKey] = aKeyState[nCntKey];
			// �v���X�͍Ō�
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}
//============================================
// �R���X�g(�}�E�X)
//============================================
CInputMouse::CInputMouse()
{
	m_lHweel = 0;
}
//============================================
// �f�X�g���N�^(�}�E�X)
//============================================
CInputMouse::~CInputMouse()
{
}
//============================================
// ������(�}�E�X)
//============================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	// ���̓f�o�C�X(�}�E�X)���쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, nullptr)))
	{
		// �f�o�C�X�̍쐬�Ɏ��s
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		// �f�[�^�t�H�[�}�b�g�Ɏ��s
		return E_FAIL;
	}
	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(m_pDevice->SetCooperativeLevel(FindWindowA(CLASS_NAME, nullptr),	DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		// ���[�h�̐ݒ�Ɏ��s
		return E_FAIL;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return E_FAIL;
	}

	// ���͐���J�n
	m_pDevice->Acquire();

	return S_OK;
}
//============================================
// �I��(�}�E�X)
//============================================
void CInputMouse::Uninit()
{
	CInput::Uninit();
}
//============================================
// �X�V(�}�E�X)
//============================================
void CInputMouse::Update()
{
	D3DXVECTOR2 PosOld = m_MousePos;	// 1�t���[���O�ʒu�ۑ��p
	POINT p;	// ���݈ʒu�ۑ��p
	GetCursorPos(&p);
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &p);

	m_MousePos.x = (float)p.x;
	m_MousePos.y = (float)p.y;


	m_MouseMove.x = m_MousePos.x - PosOld.x;
	m_MouseMove.y = m_MousePos.y - PosOld.y;

	m_PrevMouseState = m_CurrentMouseState;
	// �}�E�X�̏�Ԃ��擾���܂�
	HRESULT	hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState);
	if (FAILED(hr))
	{
		m_pDevice->Acquire();
		hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState);
		m_lHweel = m_CurrentMouseState.lZ;
	}

}
//============================================
// �v���X�擾(�}�E�X)
//============================================
bool CInputMouse::GetPress(MouseButton button_type)
{
	if (m_CurrentMouseState.rgbButtons[button_type] != 0)
	{
		return true;
	}
	return false;
}
//============================================
// �g���K�[�擾(�}�E�X)
//============================================
bool CInputMouse::GetTrigger(MouseButton button_type)
{
	if (!(m_PrevMouseState.rgbButtons[button_type] & ON_VALUE) &&
		m_CurrentMouseState.rgbButtons[button_type] & ON_VALUE)
	{
		return true;
	}
	return false;
}
//============================================
// ���s�[�g�擾(�}�E�X)
//============================================
bool CInputMouse::GetRepeat(MouseButton button_type)
{
	if (m_PrevMouseState.rgbButtons[button_type] & ON_VALUE &&
		m_CurrentMouseState.rgbButtons[button_type] & ON_VALUE)
	{
		return true;
	}

	return false;
}
//============================================
// �����[�X�擾(�}�E�X)
//============================================
bool CInputMouse::GetRelease(MouseButton button_type)
{
	if (m_PrevMouseState.rgbButtons[button_type] & ON_VALUE &&
		!(m_CurrentMouseState.rgbButtons[button_type] & ON_VALUE))
	{
		return true;
	}

	return false;
}
//============================================
// �ʒu�擾(�}�E�X)
//============================================
D3DXVECTOR2 CInputMouse::GetPos()
{
	return m_MousePos;
}
//============================================
// �����擾(�}�E�X)
//============================================
D3DXVECTOR2 CInputMouse::GetMove()
{
	return m_MouseMove;
}
//============================================
// �z�C�[���擾(�}�E�X)
//============================================
int CInputMouse::GetMouseHweel()
{
	return m_lHweel;
}
//============================================
// �R���X�g
//============================================
CInputJoypad::CInputJoypad()
{
	memset(&m_joiKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_joiKeyStateTrigger, 0, sizeof(XINPUT_STATE));
	memset(&m_joiKeyStateRepeat, 0, sizeof(XINPUT_STATE));
	memset(&m_joiKeyStateRelease, 0, sizeof(XINPUT_STATE));
}
//============================================
// �f�X�g��
//============================================
CInputJoypad::~CInputJoypad()
{
}
//============================================
// ������
//============================================
HRESULT CInputJoypad::Init()
{
	// XInput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);
	return S_OK;
}
//============================================
// �I��
//============================================
void CInputJoypad::Uninit()
{
	// XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}
//============================================
// �X�V
//============================================
void CInputJoypad::Update()
{
	XINPUT_STATE joykeyState;	// �W���C�p�b�h�̏��
	//�X�e�B�b�N��X���AY��
	float fX = 0.0f;
	float fY = 0.0f;
	// �W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		// �����[�X
		m_joiKeyStateRelease.Gamepad.wButtons = (m_joiKeyState.Gamepad.wButtons ^ joykeyState.Gamepad.wButtons) & ~joykeyState.Gamepad.wButtons;
		// ���s�[�g
		m_joiKeyStateRepeat.Gamepad.wButtons = (m_joiKeyState.Gamepad.wButtons & joykeyState.Gamepad.wButtons);
		// �g���K�[
		m_joiKeyStateTrigger.Gamepad.wButtons = (m_joiKeyState.Gamepad.wButtons ^ joykeyState.Gamepad.wButtons & joykeyState.Gamepad.wButtons);
		// �v���X
		m_joiKeyState = joykeyState;	// �W���C�p�b�h�̃v���X����ۑ�

		// �R���g���[���[�X�e�B�b�N
		for (int nCntStick = 0; nCntStick < JOYSTICK_MAX; nCntStick++)
		{
			switch (nCntStick)
			{
			case JOYSTICK_LEFT:
				fX = (float)(joykeyState.Gamepad.sThumbLX);
				fY = (float)(joykeyState.Gamepad.sThumbLY);
				break;
			case JOYSTICK_RIGHT:
				fX = (float)(joykeyState.Gamepad.sThumbRX);
				fY = (float)(joykeyState.Gamepad.sThumbRY);
				break;
			}

			float fAngle; //�p�x

			D3DXVECTOR3 pos = D3DXVECTOR3(fX, fY, 0.0f);
			D3DXVECTOR3 TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) * -1;
			fAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

			fAngle -= (D3DX_PI * 0.5f);
			fAngle *= -1.0f;

			//�p�x���擾
			m_stickState[nCntStick].afRot = fAngle;

			//�X�e�B�b�N�̓|������擾
			m_stickState[nCntStick].afSlope = fabsf(fX);

			if (m_stickState[nCntStick].afSlope < fabsf(fY))
			{
				m_stickState[nCntStick].afSlope = fabsf(fY);
			}

			m_stickState[nCntStick].afSlope /= 32768.0f; //�|���Ă����Ԃ̏����l

			bool g_bAngle[STICKANGLE_MAX];
			//�������̓t���O��������
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				g_bAngle[nCntAngle] = false;

				if (m_stickState[nCntStick].afSlope > 0.1f)
				{
					//�p�x����
					if (m_stickState[nCntStick].afRot < -D3DX_PI)
					{// ?
						m_stickState[nCntStick].afRot = D3DX_PI - (D3DX_PI + m_stickState[nCntStick].afRot) * -1.0f;
					}

					//�p�x���l�����ŏ�Ɉʒu���鎞�A��t���O��^�ɂ���
					if ((m_stickState[nCntStick].afRot < D3DX_PI * -0.625f) || (m_stickState[nCntStick].afRot > D3DX_PI * 0.625f))
					{
						g_bAngle[STICKANGLE_UP] = true;
					}
					//�p�x���l�����ŉ��Ɉʒu���鎞�A���t���O��^�ɂ���
					else if ((m_stickState[nCntStick].afRot> D3DX_PI * -0.375f) && (m_stickState[nCntStick].afRot < D3DX_PI * 0.375f))
					{
						g_bAngle[STICKANGLE_DOWN] = true;
					}
					//�p�x���l�����ŉE�Ɉʒu���鎞�A�E�t���O��^�ɂ���
					else if ((m_stickState[nCntStick].afRot > D3DX_PI * 0.125f) && (m_stickState[nCntStick].afRot < D3DX_PI * 0.875f))
					{
						g_bAngle[STICKANGLE_RIGHT] = true;
					}
					//�p�x���l�����ō��Ɉʒu���鎞�A���t���O��^�ɂ���
					else if ((m_stickState[nCntStick].afRot > D3DX_PI * -0.125f) && (m_stickState[nCntStick].afRot < D3DX_PI * -0.875f))
					{
						g_bAngle[STICKANGLE_LEFT] = true;
					}
				}

				// �X�e�B�b�N�̃g���K�[����ۑ�
				m_stickState[nCntStick].abAngleTrigger[nCntAngle] = (m_stickState[nCntStick].abAnglePress[nCntAngle] ^ g_bAngle[nCntAngle]) & g_bAngle[nCntAngle];
				// �X�e�B�b�N�̃��s�[�g����ۑ�
				m_stickState[nCntStick].abAngleRepeat[nCntAngle] =
				// �X�e�B�b�N�̃����[�X����ۑ�
					m_stickState[nCntStick].abAngleRelease[nCntAngle] = (m_stickState[nCntStick].abAnglePress[nCntAngle] & g_bAngle[nCntAngle]) & g_bAngle[nCntAngle];
				//�X�e�B�b�N�̃v���X����ۑ�
				m_stickState[nCntStick].abAnglePress[nCntAngle] = g_bAngle[nCntAngle];
			}
		}
	}
}
//============================================
// �W���C�L�[���͎擾
//============================================
// �v���X
bool CInputJoypad::GetJoykyePress(JOYKEY kye)
{
	return (m_joiKeyState.Gamepad.wButtons & (0x01 << kye)) != 0;
}
// �g���K�[
bool CInputJoypad::GetJoykyeTrigger(JOYKEY kye)
{
	return (m_joiKeyStateTrigger.Gamepad.wButtons & (0x01 << kye)) ? true : false;
}
// ���s�[�g
bool CInputJoypad::GetJoykyeRepeat(JOYKEY kye)
{
	return (m_joiKeyStateRepeat.Gamepad.wButtons & (0x01 << kye)) ? true : false;
}
// �����[�X
bool CInputJoypad::GetJoykyeRelease(JOYKEY kye)
{
	return (m_joiKeyStateRelease.Gamepad.wButtons & (0x01 << kye)) ? true : false;
}
//============================================
// �W���C�X�e�B�b�N���͎擾
//============================================
// �p�x
float CInputJoypad::GetJoystickSlope(JOYSTICK stick)
{
	return m_stickState[stick].afSlope;
}
// ����
float CInputJoypad::GetJoystickRot(JOYSTICK stick)
{
	return m_stickState[stick].afRot;
}
// �v���X
bool CInputJoypad::GetJoystickPress(JOYSTICK stick, STICKANGLE angle)
{
	return m_stickState[stick].abAnglePress[angle];
}
// �g���K�[
bool CInputJoypad::GetJoystickTrigger(JOYSTICK stick, STICKANGLE angle)
{
	return m_stickState[stick].abAngleTrigger[angle];
}
// ���s�[�g
bool CInputJoypad::GetJoystickRepeat(JOYSTICK stick, STICKANGLE angle)
{
	return m_stickState[stick].abAngleRepeat[angle];
}
// �����[�X
bool CInputJoypad::GetJoystickRelease(JOYSTICK stick, STICKANGLE angle)
{
	return m_stickState[stick].abAngleRelease[angle];
}