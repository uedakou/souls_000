//============================================
//
// �|���S���RD[object3D.cpp]
// Author:Uedakou
// 
//============================================
#include "object_3D.h"	// �I�u�W�F�N�g3D
#include "../../base/manager.h"	// �}�l�[�W���[
#include "../../base/main.h"		// ���C��
//============================================
// �R���X�g
//============================================
CObject3D::CObject3D()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_col = D3DXCOLOR(0.0f, 0.0f ,0.0f ,0.0f);

}
CObject3D::CObject3D(const int nPriority):
	CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
}
//============================================
// �f�X�g��
//============================================
CObject3D::~CObject3D()
{
}
//============================================
// ������
//============================================
void CObject3D::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^
	X x = GetX();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);


	VERTEX_3D* pVtx;	// ���_�|�C���^
	// ���_�o�b�t�@���b�N�����A���_����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3( - x.siz.x * 0.5f, x.siz.y	,   x.siz.z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(   x.siz.x * 0.5f, x.siz.y	,   x.siz.z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3( - x.siz.x * 0.5f, 0			, - x.siz.z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(   x.siz.x * 0.5f, 0			, - x.siz.z * 0.5f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���b�N���A�����b�N
	m_pVtxBuff->Unlock();
}
//============================================
// �I��
//============================================
void CObject3D::Uninit()
{
	this;
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}
//============================================
// �X�V
//============================================
void CObject3D::Update()
{
}
//============================================
// �`��
//============================================
void CObject3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���N�X
	
	X x = GetX();

	// ���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	// ����
	D3DXMatrixRotationYawPitchRoll(&mtxRot, x.rot.y, x.rot.x, x.rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, x.pos.x, x.pos.y, x.pos.z);
	//D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// ���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	// ���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`��
	pDevice->SetTexture(0, m_pTexture);
	//	�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}
//============================================
// �e�N�X�`��UV�ݒ�
//============================================
void CObject3D::SetTexUV(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1)
{
	VERTEX_3D* pVtx;	// ���_�|�C���^
	// ���_�o�b�t�@���b�N�����A���_����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(tex0.x, tex0.y);
	pVtx[1].tex = D3DXVECTOR2(tex1.x, tex0.y);
	pVtx[2].tex = D3DXVECTOR2(tex0.x, tex1.y);
	pVtx[3].tex = D3DXVECTOR2(tex1.x, tex1.y);

	// ���_���b�N���A�����b�N
	m_pVtxBuff->Unlock();
}
//============================================
// �F�ݒ�
//============================================
void CObject3D::SetColor(D3DXCOLOR col)
{

	VERTEX_3D* pVtx;	// ���_�|�C���^
	// ���_�o�b�t�@���b�N�����A���_����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	// ���_���b�N���A�����b�N
	m_pVtxBuff->Unlock();
}
//============================================
// �����ݒ�ݒ�
//============================================
void CObject3D::SetBlock(int nX, int nY)
{
	X x = GetX();
	VERTEX_3D* pVtx;	// ���_�|�C���^
	// ���_�o�b�t�@���b�N�����A���_����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(-x.siz.x * 0.5f * (float)nX, x.siz.y * (float)nY, x.siz.z * 0.5f * (float)nY);
	pVtx[1].pos = D3DXVECTOR3(x.siz.x * 0.5f * (float)nX, x.siz.y * (float)nY, x.siz.z * 0.5f * (float)nY);
	pVtx[2].pos = D3DXVECTOR3(-x.siz.x * 0.5f * (float)nX, 0 * (float)nY, -x.siz.z * 0.5f * (float)nY);
	pVtx[3].pos = D3DXVECTOR3(x.siz.x * 0.5f * (float)nX, 0 * (float)nY, -x.siz.z * 0.5f * (float)nY);

	pVtx[0].tex = D3DXVECTOR2(0.0f * (float)nX, 0.0f * (float)nY);
	pVtx[1].tex = D3DXVECTOR2(1.0f * (float)nX, 0.0f * (float)nY);
	pVtx[2].tex = D3DXVECTOR2(0.0f * (float)nX, 1.0f * (float)nY);
	pVtx[3].tex = D3DXVECTOR2(1.0f * (float)nX, 1.0f * (float)nY);


	// ���_���b�N���A�����b�N
	m_pVtxBuff->Unlock();
}
//============================================
// �e�N�X�`���ݒ�
//============================================
void CObject3D::SetTexture(const char aFileName[MAX_TXT])
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	LPDIRECT3DTEXTURE9 pTex = nullptr;

	// �e�N�X�`��
	D3DXCreateTextureFromFile(
		pDevice,
		aFileName,
		&pTex);
	if (pTex != nullptr)
	{
		SetTexture(pTex);
	}
}

void CObject3D::SetTexture(const LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}
//============================================
// UV�ǉ�
//============================================
void CObject3D::AddTexUV(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1)
{
	VERTEX_3D* pVtx;	// ���_�|�C���^
	// ���_�o�b�t�@���b�N�����A���_����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex += D3DXVECTOR2(tex0.x, tex0.y);
	pVtx[1].tex += D3DXVECTOR2(tex1.x, tex0.y);
	pVtx[2].tex += D3DXVECTOR2(tex0.x, tex1.y);
	pVtx[3].tex += D3DXVECTOR2(tex1.x, tex1.y);

	// ���_���b�N���A�����b�N
	m_pVtxBuff->Unlock();
}
//============================================
// ����
//============================================
CObject3D* CObject3D::creat(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz)
{
	CObject3D* pObject3D = new CObject3D;

	pObject3D->SetX(pos, rot, siz);
	pObject3D->Init();

	return pObject3D;
}