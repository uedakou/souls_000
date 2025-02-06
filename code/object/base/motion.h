//===========================================
// 
// ���[�V����[motion.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "object_X.h"

#define MAX_MOTION (64)			// �ő僂�[�V����
#define MAX_KYE (32)			// �ő�L�[�t���[����
#define MAX_MOTION_MODEL (64)	// ���[�V�����Ɏg���郂�f����
#define MAX_PARTS (64)			// �ő�p�[�c��
/*
�S�̃��[�V�����Ǘ�
	���[�V����(�j���[�g����, �����Ȃ�)
		���݃L�[
		�L�[�t���[��


	�p�[�c
	���݃��[�V����
	


*/
class CPartsData
{
public:
	CPartsData();
	~CPartsData();

	void SetPosTarget(D3DXVECTOR3 pos) { m_x.pos = pos; }
	void SetRotTarget(D3DXVECTOR3 rot) { m_x.rot = rot; }
	void SetSizTarget(D3DXVECTOR3 siz) { m_x.siz = siz; }

	D3DXVECTOR3 GetPosTarget() { return m_x.pos; }
	D3DXVECTOR3 GetRotTarget() { return m_x.rot; }
	D3DXVECTOR3 GetSizTarget() { return m_x.siz; }
private:
	X m_x;	// �g�����X�t�H�[��

};

// �L�[�t���[��
class CKye
{
public:
	CKye();
	~CKye();
	void SetFrame(int nFrame) { m_nFrame = nFrame; }

	CPartsData* GetPartsData(int nParts) { return m_pParts[nParts]; }
	int GetFrame() { return m_nFrame; }
	CPartsData* creatPartsData();

private:
	CPartsData* m_pParts[MAX_PARTS];	// �p�[�c
	int m_nFrame;
};

// ���[�V����
class CMotion 
{
public:
	CMotion();
	virtual ~CMotion();
	void SetNumKye(int nNumKye) { m_nNumKye = nNumKye; }
	void SetLoop(bool bLoop) { m_bLoop = bLoop; }
	void creatKye();

	CKye* GetKye(int nKye) { return m_pKye[nKye]; }
	int GetNumKye() { return m_nNumKye; }
	bool GetLoop() { return m_bLoop; }
private:
	CKye* m_pKye[MAX_KYE];	// �L�[�t���[��
	int m_nNumKye;	// �L�[��
	bool m_bLoop;	// ���̃��[�V���������[�v���邩
};

// ���݃��[�V����
class CNowMotion
{
public:
	CNowMotion();
	~CNowMotion();
	// �ݒ�
	void SetMotion(int nMosyon) { m_nCntMotion = nMosyon; }		// ���[�V�����J�E���g
	void SetKye(int nKye) { m_nCntKye = nKye; }			// �L�[�J�E���g
	void SetFrame(int nFrame) { m_nCntFrame = nFrame; }		// �t���[��

	// �擾
	int GetMotion() { return m_nCntMotion; }	// ���[�V�����J�E���g
	int GetKye() { return m_nCntKye; }		// �L�[�J�E���g
	int GetFrame() { return m_nCntFrame; }		// �t���[��

	// �f�[�^�ǉ�
	void AddMotion(int nNum) { m_nCntMotion += nNum; }	// ���[�V�����J�E���g
	void AddKye(int nNum) { m_nCntKye += nNum; }		// �L�[�J�E���g
	void AddFrame(int nNum) { m_nCntFrame += nNum; }		// �t���[��

private:
	int m_nCntMotion;	// ���[�V�����J�E���g
	int m_nCntKye;		// �L�[�J�E���g
	int m_nCntFrame;	// �t���[��
};

// �p�[�c
class CParts : public CObjectX
{
public:
	CParts();
	CParts(int nPriority);
	~CParts()					override;
	virtual void Init()		override; // ������
	virtual void Uninit()	override; // �I��
	virtual void Update()	override; // �X�V
	virtual void Draw()		override; // �`��


	// ��{�ʒu�ݒ�
	void SetBasicX(X x) {
		m_xBasic.pos = x.pos;
		m_xBasic.rot = x.rot;
		m_xBasic.siz = x.siz;
	}
	void SetBasicX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz) {
		m_xBasic.pos = pos;
		m_xBasic.rot = rot;
		m_xBasic.siz = siz;
	}
	void SetBasicPos(D3DXVECTOR3 pos) { m_xBasic.pos = pos; }
	void SetBasicRot(D3DXVECTOR3 rot) { m_xBasic.rot = rot; }
	void SetBasicSiz(D3DXVECTOR3 siz) { m_xBasic.siz = siz; }

	// �ǉ��ʒu
	void SetAddX(X x) {
		m_xAdd.pos = x.pos;
		m_xAdd.rot = x.rot;
		m_xAdd.siz = x.siz;
	}
	void SetAddX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz) {
		m_xAdd.pos = pos;
		m_xAdd.rot = rot;
		m_xAdd.siz = siz;
	}
	void SetAddPos(D3DXVECTOR3 pos) { m_xAdd.pos = pos; }
	void SetAddRot(D3DXVECTOR3 rot) { m_xAdd.rot = rot; }
	void SetAddSiz(D3DXVECTOR3 siz) { m_xAdd.siz = siz; }

	// �����ݒ�
	void SetMoveX(X x, int nFrame) { SetMoveX(x.pos, x.rot, x.siz, nFrame); };
	void SetMoveX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz, int nFrame); 

	// �f�[�^�ݒ�
	void SetParentID(int nParent) { m_nParent = nParent; }
	void SetParentMtx(D3DXMATRIX pParent) { m_mtxParent = pParent; }
	void SetDisplay(bool bDesplay) { m_bDisplay = bDesplay; }	// �\�����邩�ǂ���

	void SetMotion(int nMotion);

	// �ʒu�擾
	X GetBasicX() {
		return m_xBasic;
	}
	D3DXVECTOR3 GetBasicPos() { return m_xBasic.pos; }
	D3DXVECTOR3 GetBasicRot() { return m_xBasic.rot; }
	D3DXVECTOR3 GetBasicSiz() { return m_xBasic.siz; }

	// �ǉ��ʒu
	X GetAddX() {
		return m_xAdd;
	}
	D3DXVECTOR3 GetAddPos() { return m_xAdd.pos; }
	D3DXVECTOR3 GetAddRot() { return m_xAdd.rot; }
	D3DXVECTOR3 GetAddSiz() { return m_xAdd.siz; }

	// �f�[�^�擾
	int GetParentID() { return m_nParent; }				// �eID�擾
	D3DXMATRIX GetParentMtx() { return m_mtxParent; }	// �e�}�g���N�X�擾
	bool GetDisplay() { return m_bDisplay; }			// �\�����邩�ǂ���
	CNowMotion* GetNowMotion() { return m_pNowMotion; }	// ���݃��[�V����

	void SetDoMotion(bool bDoMotion) { m_bDoMotion = bDoMotion; }	// ���[�V�������邩�ݒ�

private:

	X m_xBasic;			// ��{�ʒu
	X m_xAdd;			// �ǉ��ʒu
	X m_xMove;			// ����

	int m_nParent;			// �eID
	D3DXMATRIX m_mtxParent;	// �e�}�g���N�X

	bool m_bDisplay;	// �\�����邩�ǂ���

	CNowMotion* m_pNowMotion;	// ���݃��[�V����

	bool m_bDoMotion;	// ���[�V�������邩�ǂ���
};

// ���[�V�����Ǘ�
class CObjectMotion : public CObject
{
public:
	CObjectMotion();
	virtual ~CObjectMotion()		override;
	virtual void Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;
	virtual void Draw()		override;
	
	// �ʒu
	void SetPos(D3DXVECTOR3 pos) { m_x.pos = pos; }// �ʒu�ݒ�
	void SetPosX(float x) { m_x.pos.x = x; }// �ʒu�ݒ�
	void SetPosY(float y) { m_x.pos.y = y; }// �ʒu�ݒ�
	void SetPosZ(float z) { m_x.pos.z = z; }// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_x.rot = rot; }// �����ݒ�
	void SetRotX(float x) { m_x.rot.x = x; }// �ʒu�ݒ�
	void SetRotY(float y) { m_x.rot.y = y; }// �ʒu�ݒ�
	void SetRotZ(float z) { m_x.rot.z = z; }// �ʒu�ݒ�
	void SetSiz(D3DXVECTOR3 siz) { m_x.siz = siz; }// �傫���ݒ�
	void SetSizX(float x) { m_x.siz.x = x; }// �ʒu�ݒ�
	void SetSizY(float y) { m_x.siz.y = y; }// �ʒu�ݒ�
	void SetSizZ(float z) { m_x.siz.z = z; }// �ʒu�ݒ�
	void SetX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz) {
		m_x.pos = pos;
		m_x.rot = rot;
		m_x.siz = siz;
	}

	D3DXVECTOR3 GetPos() { return m_x.pos; }// �ʒu�ݒ�
	float GetPosX() { return m_x.pos.x; }// �ʒu�ݒ�
	float GetPosY() { return m_x.pos.y; }// �ʒu�ݒ�
	float GetPosZ() { return m_x.pos.z; }// �ʒu�ݒ�
	D3DXVECTOR3 GetRot() { return m_x.rot; }// �����ݒ�
	D3DXVECTOR3 GetSiz() { return m_x.siz; }// �傫���ݒ�
	X GetX() { return m_x; }

	void AddPos(D3DXVECTOR3 pos) { m_x.pos += pos; }// �ʒu�ǉ�
	void AddPosX(float x) { m_x.pos.x += x; }// �ʒu�ǉ�
	void AddPosY(float y) { m_x.pos.y += y; }// �ʒu�ǉ�
	void AddPosZ(float z) { m_x.pos.z += z; }// �ʒu�ǉ�
	void AddRot(D3DXVECTOR3 rot) { m_x.rot += rot; }// �����ǉ�
	void AddRotX(float x) { m_x.rot.x += x; }// �ʒu�ǉ�
	void AddRotY(float y) { m_x.rot.y += y; }// �ʒu�ǉ�
	void AddRotZ(float z) { m_x.rot.z += z; }// �ʒu�ǉ�
	void AddSiz(D3DXVECTOR3 siz) { m_x.siz += siz; }// �傫���ǉ�
	void AddSizX(float x) { m_x.siz.x += x; }// �ʒu�ǉ�
	void AddSizY(float y) { m_x.siz.y += y; }// �ʒu�ǉ�
	void AddSizZ(float z) { m_x.siz.z += z; }// �ʒu�ǉ�


	// 1f�O�̈ʒu�ݒ�
	void SetOldX(X x) {
		m_xold.pos = x.pos;
		m_xold.rot = x.rot;
		m_xold.siz = x.siz;
	}
	void SetOldPos(D3DXVECTOR3 pos) { m_xold.pos = pos; }// �ʒu�ݒ�
	void SetOldRot(D3DXVECTOR3 rot) { m_xold.rot = rot; }// �����ݒ�
	void SetOldSiz(D3DXVECTOR3 siz) { m_xold.siz = siz; }// �傫���ݒ�

	X GetOldX() { return m_xold; }
	D3DXVECTOR3 GetOldPos() { return m_xold.pos; }// �^���ʐݒ�
	D3DXVECTOR3 GetOldRot() { return m_xold.rot; }// ��]�ʐݒ�
	D3DXVECTOR3 GetOldSiz() { return m_xold.siz; }// �c���ʐݒ�

	void AddOldX(X x) {
		m_xold.pos += x.pos;
		m_xold.rot += x.rot;
		m_xold.siz += x.siz;
	}
	void AddOldPos(D3DXVECTOR3 pos) { m_xold.pos += pos; }// �ʒu�ݒ�
	void AddOldRot(D3DXVECTOR3 rot) { m_xold.rot += rot; }// �����ݒ�
	void AddOldSiz(D3DXVECTOR3 siz) { m_xold.siz += siz; }// �傫���ݒ�


	CMotion* GetMotion(int nNum) { return m_pMotion[nNum]; }// ���[�V�����f�[�^�擾

	int GetNumParts() { return m_nParts; }
	CParts* GetParts(int nNum) { return m_pParts[nNum]; }	// �p�[�c�擾

protected:
	bool Lode(const char* aFileName);	// ���[�V�����ǂݍ���
	void SetMotion(int nMotion);	// ���[�V�����ݒ�

	virtual int GetNextMotion() { return 0; };	// ���擾
private:
	void creatMotion();// ���[�V��������
private:

	int m_nModel;							// ���f����

	int m_nNumMotion;						// ���[�V������
	CMotion* m_pMotion[MAX_MOTION];	// ���[�V�����f�[�^

	int m_nParts;				// �p�[�c��
	CParts* m_pParts[MAX_PARTS];

	int m_nNextMotion;

	X m_x;					// �g�����X�t�H�[��
	X m_xold;		// 1f�O�ʒu
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���N�X
};




#endif // !_MOTION_H_