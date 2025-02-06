//===========================================
// 
// ���C��[main.cpp]
// Auther:UedaKou
// 
//===========================================
#include "main.h"		// [main.h]�ǂݍ���]
#include "manager.h"	// �}�l�[�W���[

// �O���[�o���錾
int g_nCountFPS = 0;

//============================================
// ���C���֐�
//============================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hindtscePrev, _In_ LPSTR LpCmdline, _In_ int nCmdShow)
{
	CManager* instance = CManager::GetInstance();// �}�l�[�W���[�C���X�^���X

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							// �E�B���h�E�̃X�^�C��
		WindowProc,							// �E�B���h�E�v���V���[�V
		0,									// �O�ɂ���i�ʏ�͎g�p���Ȃ��j
		0,									// �O�ɂ���i�ʏ�͎g�p���Ȃ��j
		hInstance,							// �C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),		// �^�X�N�o�[�A�C�R��
		LoadCursor(NULL, IDC_ARROW),		// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			// �N���C�A���g�̈�̔w�i�F
		NULL,								// ���j���[�o�[
		CLASS_NAME,							// �E�B���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)		// �t�@�C���̃A�C�R��
	};
	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_W,SCREEN_H };

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//	�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,	// �g���E�B���h�E�X�^�C��
		CLASS_NAME,				// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,			// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	// �E�B���h�E�X�^�C��
		0,//CW_USEDEFAULT,		// �E�B���h�E�̍����x���W
		0,//CW_USEDEFAULT,		// �E�B���h�E�̍����y���W
		(rect.right - rect.left),	// �E�B���h�E�̕�
		(rect.bottom - rect.top),	// �E�B���h�E�̍���
		NULL,
		NULL,
		hInstance,
		NULL);

	// �E�B���h�E�\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwCuppentTime;	// ���ݎ���
	DWORD dwExecLastTime;	// �Ō�ɏ�����������
	DWORD dwFrameCount;		// �t���[���J�E���g
	DWORD dwFPSLostTime;	// �Ō��FPS���v����������

	if (FAILED(instance->Init(hInstance, hWnd, TRUE)))
	{// ����������
		return -1;
	}

	timeBeginPeriod(1);	// ����\��ݒ� 
	dwCuppentTime = 0;	// ����������
	dwExecLastTime = timeGetTime();	// ���ݎ������擾
	dwFrameCount = 0;
	dwFPSLostTime = timeGetTime();

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectX�̏���
			dwCuppentTime = timeGetTime();	// ���ݎ������擾

			if ((dwCuppentTime - dwFPSLostTime) >= 500)
			{// 0.5�b
				// FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCuppentTime - dwFPSLostTime);
				dwFPSLostTime = dwCuppentTime;
				dwFrameCount = 0;

			}

			if ((dwCuppentTime - dwExecLastTime) >= (1000 / FPS))
			{// 60����1�b�o��

				// �X�V����
				instance->Update();

				// �`�揈��
				instance->Draw();
				dwFrameCount++;
			}

		}
		// ���b�Z�[�W�̐ݒ�
		if (CManager::GetEnd() == true)
		{
			break;
		}
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}
//============================================
//�@�E�B���h�E�v���V���[�V
//============================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	CManager* instance = CManager::GetInstance();// �}�l�[�W���[�C���X�^���X


	switch (uMsg)
	{
	case WM_CREATE: // �E�B���h�E�n���h��
		break;

	case WM_DESTROY:
		// WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				instance->Uninit();
				// �E�B���h�E��j������
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_COMMAND: // �{�^���������ꂽ

		break;
	case WM_CLOSE:
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			instance->Uninit();
			// �E�B���h�E��j������
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;

	case WM_LBUTTONDOWN:	// �}�E�X���N���b�N�̃��b�Z�[�W
		// �E�B���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
int GetFPS()
{
	return g_nCountFPS;
}