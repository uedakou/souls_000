//============================================
//
// �r���{�[�h[billbord.cpp]
// Author:Uedakou
// 
//============================================
#include "billboard.h"

#include <vector>
#include <algorithm>
#include <cmath>
#include <strsafe.h>

//============================================
// �R���X�g
//============================================
CBillbord::CBillbord()
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;

	CObject::SetType(CObject::TYPE::BILLBOARD);
	m_type = Null;
}
CBillbord::CBillbord(const int nPriority):
	CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;

	CObject::SetType(CObject::TYPE::BILLBOARD);
	m_type = Null;
}
//============================================
// �f�X�g���N�^
//============================================
CBillbord::~CBillbord()
{
}
//============================================
// ������
//============================================
void CBillbord::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);
	X x = GetX();

	VERTEX_3D* pVtx;	// ���_�|�C���^
	// ���_�o�b�t�@���b�N�����A���_����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-x.siz.x * 0.5f, x.siz.y,0.0f);
	pVtx[1].pos = D3DXVECTOR3(x.siz.x * 0.5f, x.siz.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-x.siz.x * 0.5f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(x.siz.x * 0.5f, 0.0f, 0.0f);

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
// �I������
//============================================
void CBillbord::Uninit()
{
}
//============================================
// �X�V
//============================================
void CBillbord::Update()
{
}
//============================================
// �`��
//============================================
void CBillbord::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxTrans;  // �v�Z�p�}�g���N�X
	D3DXMATRIX matView;

	X x = GetX();
	if (!pDevice) {
		// �f�o�C�X�������ȏꍇ�̃G���[�n���h�����O
		return;
	}

	// ���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �r���[�}�g���N�X�̎擾
	if (FAILED(pDevice->GetTransform(D3DTS_VIEW, &matView))) {
		// �r���[�}�g���N�X�擾���s���̏���
		return;
	}

	// �r���[�}�g���N�X�̋t�s����v�Z
	if (D3DXMatrixInverse(&m_mtxWorld, NULL, &matView) == NULL) {
		// �t�s��v�Z���s���̏���
		return;
	}

	// ���[���h�}�g���N�X�̈ʒu��������
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	// �I�u�W�F�N�g�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, x.pos.x, x.pos.y, x.pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@��ݒ�
	if (m_pVtxBuff) {
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	}
	else {
		// ���_�o�b�t�@�������ȏꍇ�̏���
		return;
	}

	// Z�o�b�t�@�̏������݂�L���ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// Z�o�b�t�@�̔�r��ʏ�̔�r���@�ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// �A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// Z�o�b�t�@�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
//============================================
// �e�N�X�`��UV�ݒ�
//============================================
void CBillbord::SetTexUV(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1)
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
void CBillbord::SetColor(D3DXCOLOR col)
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
// �e�N�X�`���ݒ�
//============================================
void CBillbord::SetTexture(const char aFileName[MAX_TXT])
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

void CBillbord::SetTexture(const LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}
//============================================
// UV�ǉ�
//============================================
void CBillbord::AddTexUV(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1)
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
CBillbord* CBillbord::creat(D3DXVECTOR3 pos, D3DXVECTOR3 siz)
{
	CBillbord* pBillbord = new CBillbord();


	pBillbord->SetPos(pos);
	pBillbord->SetSiz(siz);


	pBillbord->Init();

	return pBillbord;
}
CBillbord* CBillbord::creat(int nPriorith, D3DXVECTOR3 pos, D3DXVECTOR3 siz)
{
	CBillbord* pBillbord = new CBillbord(nPriorith);


	pBillbord->SetPos(pos);
	pBillbord->SetSiz(siz);


	pBillbord->Init();

	return pBillbord;
}