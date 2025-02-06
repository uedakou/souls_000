//===========================================
// 
// �L�����N�^�[[charactor.cpp]
// Auther:UedaKou
// 
//===========================================
#include "character.h"

CCharacter::CCharacter()
{
	m_nLife = 0;
	m_nCntInvincible = 0;
	m_nAttcak = 0;
	m_nDefense = 0;
	m_fSpeed = 0;
	m_Xcollision = X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_xmove = X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	bJump = false;
}

CCharacter::~CCharacter()
{
}

void CCharacter::Init()
{

	CObjectMotion::Init();
}
void CCharacter::Uninit()
{
	CObjectMotion::Uninit();
}
void CCharacter::Update()
{
	CObjectMotion::SetOldPos(CObjectMotion::GetPos());
	CObjectMotion::AddPos(m_xmove.pos);
	CObjectMotion::AddRot(m_xmove.rot);
	MoveAttenuation();
	CObjectMotion::Update();
	if (m_nCntInvincible > 0)
	{
		m_nCntInvincible--;
	}
}
void CCharacter::Draw()
{
	CObjectMotion::Draw();
}
int CCharacter::GetNextMotion()
{
	return 0;
}
//============================================
// �q�b�g����
//============================================
void CCharacter::Hit(int nDamage)
{
	if (m_nCntInvincible <= 0)
	{
		m_nCntInvincible = 0;
		m_nLife -= nDamage;
	}
}
void CCharacter::Hit(int nCntInvincible, int nDamage)
{
	if (m_nCntInvincible <= 0)
	{
		Hit(nDamage);
	}
}
void CCharacter::Hit(D3DXVECTOR3 ShockRot, int nCntInvincible, int nDamage)
{
	if (m_nCntInvincible <= 0)
	{
		Hit(nCntInvincible, nDamage);
		m_xmove.pos += ShockRot;
	}
}
//============================================
// �ړ�����
//============================================
void CCharacter::MoveAttenuation()
{
	m_xmove.pos.x += (0 - m_xmove.pos.x) * BASE_RESISTANCE;
	m_xmove.pos.z += (0 - m_xmove.pos.z) * BASE_RESISTANCE;

	m_xmove.rot.y += (0 - m_xmove.rot.y) * 0.05f;

}
//============================================
// �s��
//============================================
void CCharacter::ActivityUpdate()
{
	if (m_pActivity != nullptr)
	{// NULL����Ȃ�������X�V
		auto* p = m_pActivity->update();
		if (p != m_pActivity)
		{// �X�V�ŋA���Ă����|�C���^���ς���Ă������������
			delete m_pActivity;
			m_pActivity = p;
		}
	}
}