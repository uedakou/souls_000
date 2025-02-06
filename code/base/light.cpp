//============================================
//
// ����[light.cpp]
// Author:Uedakou
// 
//============================================
#include "light.h"
#include "manager.h"
#include "manager.h"
#include <strsafe.h>


// �O���[�o���ϐ��錾

CLight::CLight()
{
}

CLight::~CLight()
{
}
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^
	D3DXVECTOR3 vecDir[3];	//�ݒ�p�����x�N�g��
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{

		// ���C�g�̏����N���A����
		ZeroMemory(&m_light, sizeof(D3DLIGHT9));
		//	���C�g�̎��
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U�g�U�ݒ�
		m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		switch (nCntLight)
		{
		case 0:
			// ���C�g�̕����ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(0.2f, -0.8f, -1.0f);
			break;
		case 1:
			// ���C�g�̕����ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(-0.2f, 0.8f, 0.4f);
			break;
		case 2:
			// ���C�g�̕����ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(0.8f, -0.8f, -0.4f);
			break;
		}
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		m_light[nCntLight].Direction = vecDir[nCntLight];
		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);
		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
	// 
	return S_OK;
}
void CLight::Uninit(void)
{}
void CLight::Update(void)
{}