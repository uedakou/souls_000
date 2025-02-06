//===========================================
// 
// �����_���[[renderer.cpp]
// Auther:UedaKou
// 
//===========================================
#include "renderer.h"	// �����_���[
#include "main.h"		// ���C��
#include "manager.h"	// �}�l�[�W���[

#include "../object/base/object.h"		// �I�u�W�F�N�g
#include "../object/base/text.h"


//============================================
// �R���X�g���N�^
//============================================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_pText = nullptr;
}
//============================================
// �f�X�g���N�^
//============================================
CRenderer::~CRenderer()
{
	if (m_pText != nullptr)
	{
		m_pText->Release();
	}
}
//============================================
// ����������
//============================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	// ���݂̃f�B�X�v���C���[�h�擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//	�f�o�C�X�̃f�B�X�v���C�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// �p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_W;							// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_H;							// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@��16bit�g��
	d3dpp.Windowed = bWindow;									// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��
	// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������o�[�h�E�F�A�ōs��)
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//	Direct3D�f�o�C�X�̐���
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			//	Direct3D�f�o�C�X�̐���
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	m_pText = CText::creat();

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	return S_OK;
}
//============================================
// �I������
//============================================
void CRenderer::Uninit(void)
{
	timeEndPeriod(1);	// fps���Z�b�g
	CObject::ReleaseAll();
	CObject::ReleaseDeathFlag();
}
//============================================
// �X�V����
//============================================
void CRenderer::Update(void)
{
	CObject::UpdateAll();

	timeEndPeriod(1);	// fps���Z�b�g
}
//============================================
// �`�揈��
//============================================
void CRenderer::Draw(void)
{
	CManager* instance = CManager::GetInstance();
	CCamera* pCamera = instance->GetCamera();
	Scene::CBase* Scene = instance->GetSceneManager();
	//��ʃN���A(�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A)
	m_pD3DDevice->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 255),	// �w�i�F
		1.0f,
		0);
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CObject::CalculateDistanceToCamera();
		CObject::Sort();

		if (pCamera != nullptr)
		{
			pCamera->SetCamera();
		}

		CObject::DrawAll();
		Scene->Draw();

#ifdef _DEBUG
		pCamera->DrawCamera();
		DrawFPS();

#endif // !_DEBUG
		m_pD3DDevice->EndScene();
	}
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//============================================
// FPS�\������
//============================================
void CRenderer::DrawFPS(void)
{
	int nCountFPS = GetFPS();
	string aStr;
	wsprintf(&aStr[0], "FPS:%d\n", nCountFPS);
	m_pText->Draw(aStr.c_str());
}
//============================================
// �f�o�C�X�擾����
//============================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
