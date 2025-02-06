//============================================
//
// ����[input.cpp]
// Author:Uedakou
// 
//============================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

class CInput	// ����
{
public:
	CInput();
	~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;;
protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
private:
};

// �L�[�{�[�h����
#define NUM_KEY_MAX (256)
#define ON_VALUE (0x80)		// �I����Ԃ̒l
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit()override;
	void Update()override;

	bool GetPless() {
		for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
		{
			if ((m_aPless[nCnt] & 0x80) != 0)
			{
				return true;
			}
		}
		return false;
	}		// �v���X
	bool GetPless(int Key) { return (m_aPless[Key] & 0x80) != 0; }		// �v���X
	bool GetTrigger(int Key) { return (m_aTrigger[Key] & 0x80) != 0; }	// �g���K�[
	bool GetRepeat(int Key) { return (m_aRepeat[Key] & 0x80) != 0; }	// ���s�[�g
	bool GetRelease(int Key) { return (m_aRelease[Key] & 0x80) != 0; }	// �����[�X
private:
	BYTE m_aPless[NUM_KEY_MAX];		// �v���X
	BYTE m_aTrigger[NUM_KEY_MAX];	// �g���K�[
	BYTE m_aRepeat[NUM_KEY_MAX];	// ���s�[�g
	BYTE m_aRelease[NUM_KEY_MAX];	// �����[�X
};

// �}�E�X����
class CInputMouse : public CInput
{
public:
	typedef enum
	{
		MOUSEBUTTON_LEFT = 0,	// ���N���b�N
		MOUSEBUTTON_RIGHT,		// �E�N���b�N
		MOUSEBUTTON_CENTER,		// ���N���b�N
		MOUSEBUTTON_BACK,		// �߂�
		MOUSEBUTTON_MAX
	}MouseButton;	// �}�E�X�L�[���
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit()override;
	void Update()override;

	bool GetPress(MouseButton button_type);   	// �v���X����
	bool GetTrigger(MouseButton button_type);	// �g���K�[����
	bool GetRepeat(MouseButton button_type);	// ���s�[�g����
	bool GetRelease(MouseButton button_type);	// �����[�X����

	D3DXVECTOR2 GetPos();
	D3DXVECTOR2 GetMove();
	int GetMouseHweel();
private:
	DIMOUSESTATE m_PrevMouseState;			//!< �}�E�X�̂P�t���[���O�̓��͏��
	DIMOUSESTATE m_CurrentMouseState;		//!< �}�E�X�̌��݂̓��͏��
	D3DXVECTOR2 m_MousePos;					// �}�E�X�ʒu
	D3DXVECTOR2 m_MouseMove;				// �}�E�X����
	long m_lHweel;
};
#define MAX_CONTROLLERS 4 // XInput���F���ł���R���g���[���[�̍ő吔

class CInputJoypad
{
public:
	// �W���C�L�[�̎��
	typedef enum
	{
		JOYKEY_UP = 0,	// �\���L�[�i��j
		JOYKEY_DOWN,	// �\���L�[�i���j
		JOYKEY_LEFT,	// �\���L�[�i���j
		JOYKEY_RIGHT,	// �\���L�[�i�E�j
		JOYKEY_START,	// �X�^�[�g
		JOYKEY_BACK,	// �o�b�N
		JOYKEY_L3,		// L3
		JOYKEY_R3,		// R3
		JOYKEY_LB,		// L1
		JOYKEY_RB,		// R1
		JOYKEY_LT,		// L2	// �����Ȃ�
		JOYKEY_RT,		// R2	// �����Ȃ�
		JOYKEY_A,		// A
		JOYKEY_B,		// B
		JOYKEY_X,		// X
		JOYKEY_Y,		// Y
		JOYKEY_MAX
	}JOYKEY;	// �W���C�p�b�h�L�[���͎��
	typedef enum
	{
		JOYSTICK_LEFT = 0, // ���X�e�B�b�N
		JOYSTICK_RIGHT,	// �E�X�e�B�b�N
		JOYSTICK_MAX
	}JOYSTICK;	// �W���C�p�b�h�X�e�B�b�N���͎��

	typedef enum
	{
		STICKANGLE_UP = 0, // ��
		STICKANGLE_DOWN,   // ��
		STICKANGLE_LEFT,   // ��
		STICKANGLE_RIGHT,  // �E
		STICKANGLE_MAX,
	}STICKANGLE;

	typedef struct
	{
		float afSlope;							// �X�e�B�b�N�̊p�x
		float afRot;							// �X�e�B�b�N�̌���
		bool abAnglePress[STICKANGLE_MAX];		// �X�e�B�b�N�̕����v���X���
		bool abAngleTrigger[STICKANGLE_MAX];	// �X�e�B�b�N�̕����g���K�[���
		bool abAngleRepeat[STICKANGLE_MAX];		// �X�e�B�b�N�̕������s�[�g���
		bool abAngleRelease[STICKANGLE_MAX];	// �X�e�B�b�N�̕��������[�X���

	}STICK_STATE;
	CInputJoypad();
	~CInputJoypad();
	// �W���C�L�[
	HRESULT Init();						// �W���C�p�b�h������
	void Uninit();						// �W���C�p�b�h�I��
	void Update();						// �W���C�p�b�h�X�V
	// �W���C�L�[
	bool GetJoykyePress() {
		for (int nCnt = 0; nCnt < JOYKEY_MAX; nCnt++)
		{
			if ((m_joiKeyState.Gamepad.wButtons & (0x01 << nCnt)) != 0)
			{
				return true;
			}
		}
		return false;
	}
	bool GetJoykyePress(JOYKEY kye);	// �W���C�p�b�h(�v���X)
	bool GetJoykyeTrigger(JOYKEY kye);	// �W���C�p�b�h(�g���K�[)
	bool GetJoykyeRepeat(JOYKEY kye);	// �W���C�p�b�h(���s�[�g)
	bool GetJoykyeRelease(JOYKEY kye);	// �W���C�p�b�h(�����[�X)

	// �W���C�X�e�B�b�N
	float GetJoystickSlope(JOYSTICK stick);	// �p�x�擾
	float GetJoystickRot(JOYSTICK stick);	// �����擾

	bool GetJoystickPress(JOYSTICK stick , STICKANGLE angle);	// �W���C�p�b�h(�v���X)
	bool GetJoystickTrigger(JOYSTICK stick, STICKANGLE angle);	// �W���C�p�b�h(�g���K�[)
	bool GetJoystickRepeat(JOYSTICK stick, STICKANGLE angle);	// �W���C�p�b�h(���s�[�g)
	bool GetJoystickRelease(JOYSTICK stick, STICKANGLE angle);	// �W���C�p�b�h(�����[�X)

private:
	XINPUT_STATE m_joiKeyState;			// �W���C�p�b�h�v���X���
	XINPUT_STATE m_joiKeyStateTrigger;	// �W���C�p�b�h�v���X���
	XINPUT_STATE m_joiKeyStateRepeat;	// �W���C�p�b�h�v���X���
	XINPUT_STATE m_joiKeyStateRelease;	// �W���C�p�b�h�v���X���

	STICK_STATE m_stickState[JOYSTICK_MAX];											//�X�e�B�b�N�̓��͏��
};





#endif // !_INPUT_H_