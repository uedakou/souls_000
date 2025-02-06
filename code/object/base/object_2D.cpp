//===========================================
// 
// �|���S��2[object_2D.cpp]
// Auther:UedaKou
// 
//===========================================
#include "object_2D.h"	// �I�u�W�F�N�g�QD
#include "../../base/manager.h"	// �}�l�[�W���[
#include "../../base/main.h"		// 


//============================================
// �R���X�g���N�^
//============================================
CObject2D::CObject2D()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetType(CObject::TYPE::OBJECT2D);
}
CObject2D::CObject2D(int nPriority):
	CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetType(CObject::TYPE::OBJECT2D);
}
//============================================
// �f�X�g���N�g
//============================================
CObject2D::~CObject2D()
{
}
//============================================
// ������
//============================================
void CObject2D::Init()
{
	

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^
	X x = GetX();

	// �f�o�C�X�̎擾
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_2D* pVtx;		// ���_���ւ̃|�C���^
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�X�V
	pVtx[0].pos = D3DXVECTOR3(x.pos.x - (x.siz.x * 0.5f), x.pos.y - (x.siz.y * 0.5f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(x.pos.x + (x.siz.x * 0.5f), x.pos.y - (x.siz.y * 0.5f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(x.pos.x - (x.siz.x * 0.5f), x.pos.y + (x.siz.y * 0.5f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(x.pos.x + (x.siz.x * 0.5f), x.pos.y + (x.siz.y * 0.5f), 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Unlock();
}
//============================================
// �I��
//============================================
void CObject2D::Uninit()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^

	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}
//============================================
// �X�V
//============================================
void CObject2D::Update()
{
}
//============================================
// �`��
//============================================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^

	// ���_�o�b�t�@�Ƀf�[�^���X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`��
	pDevice->SetTexture(0, m_pTexture);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	// �v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}
//============================================
// �e�N�X�`���Z�b�g
//============================================
void CObject2D::SetTexture(const LPDIRECT3DTEXTURE9 ptex)
{
	m_pTexture = ptex;
}
void CObject2D::SetTexture(const char aName[MAX_TXT])
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�擾
	LPDIRECT3DTEXTURE9 ptex;
	D3DXCreateTextureFromFile(
		pDevice,
		aName,
		&ptex);

	SetTexture(ptex);
}
void CObject2D::SetTexture(std::string aName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�擾
	LPDIRECT3DTEXTURE9 ptex;
	D3DXCreateTextureFromFile(
		pDevice,
		aName.c_str(),
		&ptex);

	SetTexture(ptex);
}
//============================================
// ����
//============================================
CObject2D* CObject2D::creat(D3DXVECTOR3 pos, D3DXVECTOR3 siz)
{
	CObject2D* pObject = new CObject2D;

	pObject->SetPos(pos);
	pObject->SetSiz(siz);
	pObject->Init();

	return pObject;
}
CObject2D* CObject2D::creat(int nPriority, D3DXVECTOR3 pos, D3DXVECTOR3 siz)
{
	CObject2D* pObject = new CObject2D(nPriority);

	pObject->SetPos(pos);
	pObject->SetSiz(siz);
	pObject->Init();

	return pObject;
}
//============================================
// �J���[�ݒ�
//============================================
void CObject2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_2D* pVtx;		// ���_���ւ̃|�C���^
	if (m_pVtxBuff != nullptr)
	{
		// ���_�o�b�t�@�����b�N
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�ݒ�
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;

		// ���_�o�b�t�@�����b�N
		m_pVtxBuff->Unlock();
	}
}