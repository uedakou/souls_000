//============================================
//
// �J����[camera.cpp]
// Author:Uedakou
// 
//============================================
#include "camera.h"	// �J����
#include "manager.h"	// �}�l�[�W���[
#include <strsafe.h>	// StringCbPrintf���g�p����ɂ̂ɕK�v
#include "../object/Base/object.h"	// �I�u�W�F�N�g
#include "../object/base/text.h"


//============================================
// �R���X�g
//============================================
CCamera::CCamera():
	m_fMoveSpeed(10.0f),
	m_fMoveFastSpeed(50.0f)
{
	m_posV = CAMERA_V;	// ���_
	m_posR = CAMERA_R;	// �œ_
	m_vecU = CAMERA_U;	// �����

	m_rot = D3DXVECTOR3(
		atan2f((m_posV.z - m_posR.z), (m_posV.y - m_posR.y)),
		atan2f((m_posV.x - m_posR.x), (m_posV.z - m_posR.z)),
		0.0f);		// ����

	m_rotTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����(�ڕW)
	m_bRotTarget = false;						// �␳��]������
	m_bCameraTipe = CAMERA_TYPE;				// �J�������ߓ��e
	m_bCumeraController = CAMERA_CONTROLLER;			// �v���C���[�Ǐ]

	m_pTex = CText::creat();
}
//============================================
// �f�X�g��
//============================================
CCamera::~CCamera()
{
}
//============================================
// ����������
//============================================
HRESULT CCamera::Init(void)
{

	return S_OK;
}
//============================================
// �I������
//============================================
void CCamera::Uninit(void)
{}
//============================================
// �X�V����
//============================================
void CCamera::Update(void)
{
	CInputKeyboard* pKey = CManager::GetInstance()->GetInKey();	// �L�[�{�[�h����
	if (pKey->GetTrigger(DIK_F2))
	{
		m_bCumeraController = m_bCumeraController ? false : true;
	}
	if (m_bCumeraController)
	{
		Controller();
		// �l���␳��]
		if (m_bRotTarget == true)
		{
			// �l���␳��]�K��
			float fRotY = (m_rotTarget.y - m_rot.y);
			if (fRotY >= D3DX_PI)
			{
				fRotY -= TAU;
			}
			else if (fRotY <= -D3DX_PI)
			{
				fRotY += TAU;
			}

			m_rot.y += fRotY * 0.1f;

			if (m_rot.y >= D3DX_PI)
			{
				m_rot.y -= TAU;
			}
			else if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y += TAU;
			}
			// ��]������������
			if (m_rot.y - m_rotTarget.y <= 0.005f &&
				m_rot.y - m_rotTarget.y >= 0.005f)
			{
				m_bRotTarget = false;
			}
		}
		m_posR.x = m_posV.x + cosf(m_rot.x - (D3DX_PI * 0.5f)) * sinf(m_rot.y) * POS_CAMERA;
		m_posR.y = m_posV.y + sinf(m_rot.x - (D3DX_PI * 0.5f)) * POS_CAMERA;
		m_posR.z = m_posV.z + cosf(m_rot.x - (D3DX_PI * 0.5f)) * cosf(m_rot.y) *	POS_CAMERA;
	}
	if (pKey->GetTrigger(DIK_F1))
	{
		m_bCameraTipe = m_bCameraTipe ? false : true;
	}

}
//============================================
// �`�揈��
//============================================
void CCamera::SetCamera(void)
{

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^
	// �v���W�F�N�V�����}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
	if (m_bCameraTipe)
	{// ���ߓ��e
		// �v���W�F�N�V�����}�g���N�X���쐬
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_W / (float)SCREEN_H,
			50.0f, 10000.0f);

	}
	else
	{// �����e
		D3DXMatrixOrthoLH(
			&m_mtxProjection,
			(float)SCREEN_W,
			(float)SCREEN_H,
			10.0f,
			10000.0f);

	}
#if _DEBUG
	// DrawCamera();

#endif // _DEBUG


	// �v���W�F�N�V�����}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);


	// �r���[�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
	// �r���[�}�g���N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);
	// �r���[�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//============================================
// �J���������ݒ�
//============================================
void CCamera::SetCameraRot(CENTER centor, D3DXVECTOR3 rot)
{
	switch (centor)
	{
	case CENTER::V:

		break;
	case CENTER::R:

		break;
	default:
		break;
	}
	m_rot = rot;
}
void CCamera::AddCameraRot(CENTER centor, D3DXVECTOR3 rot)
{
	switch (centor)
	{
	case CENTER::V:
		m_rot += rot;
		if (m_rot.y <= 0.0f)
		{
			m_rot.y += TAU;
		}
		else if (m_rot.y >= TAU)
		{
			m_rot.y -= TAU;
		}
		break;
	case CENTER::R:

		m_rot += rot;
		if (m_rot.y <= 0.0f)
		{
			m_rot.y += TAU;
		}
		else if (m_rot.y >= TAU)
		{
			m_rot.y -= TAU;
		}
		break;
	default:
		break;
	}
}
//============================================
// �J�������`��
//============================================
void CCamera::DrawCamera()
{
}
//============================================
// ����
//============================================
void CCamera::Controller()
{
	CInputKeyboard* pKey = CManager::GetInstance()->GetInKey();
	// ��]
	if (pKey->GetTrigger(DIK_Q))
	{
		if (pKey->GetRepeat(DIK_LSHIFT))
		{
			m_bRotTarget = true;
			if (m_rot.y <= 0.0f + 0.005f &&
				m_rot.y > -(D3DX_PI * 0.5f )+ 0.005f)
			{
				m_rotTarget.y = -(D3DX_PI * 0.5f);
			}
			else if (m_rot.y <= -(D3DX_PI * 0.5f) + 0.005f &&
				m_rot.y > -D3DX_PI + 0.005f)
			{
				m_rotTarget.y = -D3DX_PI;
			}
			else if (m_rot.y <= -D3DX_PI + 0.005f ||
				m_rot.y > (D3DX_PI * 0.5f) + 0.005f)
			{
				m_rotTarget.y = D3DX_PI * 0.5f;
			}
			else if (m_rot.y <= (D3DX_PI * 0.5f) + 0.005f &&
				m_rot.y > 0.0f + 0.005f)
			{
				m_rotTarget.y = 0.0f;
			}
		}
		else
		{
			m_bRotTarget = false;
			m_rot.y -= 0.05f;
			if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y += TAU;
			}
		}
	}
	else if (pKey->GetRepeat(DIK_Q) &&
		m_bRotTarget == false)
	{
		m_rot.y -= 0.05f;
		if (m_rot.y <= -D3DX_PI)
		{
			m_rot.y += TAU;
		}
	}
	else if (pKey->GetTrigger(DIK_E))
	{
		if (pKey->GetRepeat(DIK_LSHIFT))
		{
			m_bRotTarget = true;
			if (m_rot.y >= 0.0f - 0.005f &&
				m_rot.y < (D3DX_PI * 0.5f) - 0.005f)
			{
				m_rotTarget.y = D3DX_PI * 0.5f;
			}
			else if (m_rot.y >= D3DX_PI * 0.5f - 0.005f &&
				m_rot.y < D3DX_PI - 0.005f)
			{
				m_rotTarget.y = D3DX_PI;
			}
			else if (m_rot.y >= D3DX_PI - 0.005f ||
				m_rot.y < -( D3DX_PI * 0.5f) - 0.005f)
			{
				m_rotTarget.y = -D3DX_PI * 0.5f;
			}
			else if (m_rot.y >= -(D3DX_PI * 0.5f) - 0.005f &&
				m_rot.y < 0.0f - 0.005f)
			{
				m_rotTarget.y = 0.0f;
			}
		}
		else
		{
			m_bRotTarget = false;
			m_rot.y -= 0.05f;
			if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y += TAU;
			}
		}
	}
	else if (pKey->GetRepeat(DIK_E) &&
		m_bRotTarget == false)
	{
		m_rot.y += 0.05f;
		if (m_rot.y >= D3DX_PI)
		{
			m_rot.y -= TAU;
		}
	}
	if (pKey->GetRepeat(DIK_R))
	{
		if (m_rot.x > -D3DX_PI)
		{
			m_rot.x -= 0.05f;
		}
		else
		{
			int a = 0;
		}
	}
	else if (pKey->GetRepeat(DIK_F))
	{
		if (m_rot.x < 0)
		{
			m_rot.x += 0.05f;
		}
				else
		{
			int a = 0;
		}
	}
	// �ړ�
	if(pKey->GetRepeat(DIK_LSHIFT))
	{
		if (pKey->GetRepeat(DIK_W))
		{// �O���ړ�
			if (pKey->GetRepeat(DIK_A))
			{// ���O�ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveFastSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// �E�O�ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveFastSpeed);
			}
			else
			{// �O�ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveFastSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_S))
		{// ����ړ�
			if (pKey->GetRepeat(DIK_A))
			{// ����ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveFastSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// �E��ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveFastSpeed);
			}
			else
			{// ��ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveFastSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_A))
		{// ���ړ�
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveFastSpeed, 0.0f,
				cosf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveFastSpeed);
		}
		else if (pKey->GetRepeat(DIK_D))
		{// �E�ړ�
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveFastSpeed, 0.0f,
				cosf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveFastSpeed);
		}
		// �㉺
		if (pKey->GetRepeat(DIK_SPACE))
		{// �㏸
			m_posV.y += m_fMoveFastSpeed;
		}
		else if (pKey->GetRepeat(DIK_LCONTROL))
		{// ���~
			m_posV.y -= m_fMoveFastSpeed;
		}
	}
	else
	{
		if (pKey->GetRepeat(DIK_W))
		{// �O���ړ�
			if (pKey->GetRepeat(DIK_A))
			{// ���O�ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// �E�O�ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveSpeed);
			}
			else
			{// �O�ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_S))
		{// ����ړ�
			if (pKey->GetRepeat(DIK_A))
			{// ����ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// �E��ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveSpeed);
			}
			else
			{// ��ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_A))
		{// ���ړ�
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveSpeed, 0.0f,
				cosf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveSpeed);
		}
		else if (pKey->GetRepeat(DIK_D))
		{// �E�ړ�
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveSpeed, 0.0f,
				cosf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveSpeed);
		}
	}

	// �㉺
	if (pKey->GetRepeat(DIK_SPACE))
	{// �㏸
		m_posV.y += 10.0f;
	}
	else if (pKey->GetRepeat(DIK_LCONTROL))
	{// ���~
		m_posV.y -= 10.0f;
	}
}