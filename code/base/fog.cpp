//===========================================
// 
// �t�H�O[fog.h]
// Auther:UedaKou
// 
//===========================================
#include "fog.h"
#include "manager.h"
CFog::CFog()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �t�H�O�L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	// �t�H�O�J���[
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	// �t�H�O�p�����[�^
	m_type = EXP;
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);

	// �����w��

	m_fFogStartPos = 100.0f;
	m_fFogEndPos = 10000.0f;
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&m_fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&m_fFogEndPos));

	// ���x�w��
	m_m_fFogDensity = 0.0002f;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_m_fFogDensity));
}

CFog::~CFog()
{

}

void CFog::SetFogType(FogType type)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �t�H�O�p�����[�^
	m_type = type;
	switch (type)
	{
	case EXP:
		pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);
		break;
	case LINEAR:
		pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
		break;
	default:
		break;
	}
}
void CFog::SetFogLinear(float fStart, float fEnd)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �����w��
	m_fFogStartPos = fStart;
	m_fFogEndPos = fEnd;
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&m_fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&m_fFogEndPos));

}
void CFog::SetFogDensity(float fDensity)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���x�w��
	m_m_fFogDensity = fDensity;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_m_fFogDensity));
}

CFog* CFog::creat()
{
	return new CFog;
}