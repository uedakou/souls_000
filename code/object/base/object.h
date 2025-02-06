//============================================
//
// �I�u�W�F�N�g[object.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "../../base/manager.h"
#include "../../base/calculation.h"
#include <vector>
#include <algorithm>
#include <cmath>

// �I�u�W�F�N�g
#define DEFALT_PRIORITY (3)	// �D��x���ݒ莞�̗D��x
class CObject
{
public:
	// ���
	typedef enum {
		TYPE_NULL = 0,
		BILLBOARD,	// �r���{�[�h
		OBJECT2D,	// 2D
		FIELD,		// �t�B�[���h
		POPUP,		// �|�b�v�A�b�v
		PLAYER,	// �v���C���[
		ENEMY,		// �G
		PARTS,		// �p�[�c
		MAPOBJECT,	// �}�b�v�I�u�W�F�N�g
		POTAL,		// �|�[�^��
		BLOCK,		// �u���b�N
		MAX,
	}TYPE;			// �I�u�W�F�N�g���

	CObject();
	CObject(const int nPriority);
	virtual ~CObject();
	virtual void Init() = 0;	// ������
	virtual void Uninit() = 0;	// �I��
	virtual void Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��
	void Release();				// �������g�̉��

	// �S�̏���
	static void ReleaseAll();	// �S�I�u�W�F�N�g���
	static void ReleaseDeathFlag();	// �S�I�u�W�F�N�g���
	static void UpdateAll();	// �S�I�u�W�F�N�g�X�V
	static void DrawAll();		// �S�I�u�W�F�N�g�`��
	static void GetAllObject(CObject* object[MAX_PRIORITY]);	// �I�u�W�F�N�g�擾
	static CObject* GetMyObject(int nPriorty) { return m_pTop[nPriorty]; };	// �I�u�W�F�N�g�擾(�D��x��)
	static void Sort();

	static void CalculateDistanceToCamera();
	void CalculateDistance(D3DXVECTOR3 pos);
	//// �\�[�g�֐�
	//static bool CompareByDistance(const CObject& a, const CObject& b) {
	//	return a.m_fDistance > b.m_fDistance; // �������傫����
	//}
	//// �\�[�g����
	//static void SortObjectsByDistance(std::vector<CObject>& objects) {
	//	std::sort(objects.begin(), objects.end(), CompareByDistance);
	//}
	// ���X�g
	void SetNext(CObject* pNext) { m_pNext = pNext; }	// ���ݒ�
	void SetPrev(CObject* pPrev) { m_pPrev = pPrev; }	// �O�ݒ�
	CObject* GetNext() { return m_pNext; }//	���擾
	CObject* GetPrev() { return m_pPrev; }//	���擾

	// ���
	void SetType(TYPE type);	// ���g�̎�ސݒ�
	TYPE GetType();				// ��ގ擾

	// �g�����X�t�H�[���ݒ�
	void SetX(X x) { m_x = x; }
	void SetX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 siz) {
		m_x.pos = pos;
		m_x.rot = rot;
		m_x.siz = siz;
	}
	void SetPos(const D3DXVECTOR3 pos) { m_x.pos = pos; }	// �ʒu�ݒ�
	void SetRot(const D3DXVECTOR3 rot) { m_x.rot = rot; }	// �����ݒ�
	void SetSiz(const D3DXVECTOR3 siz) { m_x.siz = siz; }	// �傫���ݒ�
	// �g�����X�t�H�[�����Z
	void AddX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 siz) {
		m_x.pos += pos;
		m_x.rot += rot;
		m_x.siz += siz;
	}														// �g�����X�t�H�[���ݒ�
	void AddPos(const D3DXVECTOR3 pos) { m_x.pos += pos; }	// �ʒu�ݒ�
	void AddRot(const D3DXVECTOR3 rot) { m_x.rot += rot; }	// �����ݒ�
	void AddSiz(const D3DXVECTOR3 siz) { m_x.siz += siz; }	// �傫���ݒ�
	// �g�����X�t�H�[���擾
	X GetX() { return m_x; }					// �g�����X�t�H�[���ݒ�
	D3DXVECTOR3 GetPos() { return m_x.pos; }	// �ʒu�ݒ�
	D3DXVECTOR3 GetRot() { return m_x.rot; }	// �����ݒ�
	D3DXVECTOR3 GetSiz() { return m_x.siz; }	// �傫���ݒ�

	void SetDistance(float fDistance) { m_fDistance = fDistance; }	// ���ڂ炩��̋���
	float GetDistance() { return m_fDistance; }	// ���ڂ炩��̋���

	// �t���O
	void SetUpdate(bool bUpdate) { m_bAllUpdate = bUpdate; }			// �S�̂ōX�V���邩�ݒ�
	void SetPoseUpdate(bool bUpdate) { m_bPoseUpdate = bUpdate; }	// �|�[�Y���X�V���邩�ݒ�
	void SetDraw(bool bUpdate) { m_bAllDraw = bUpdate; }				// �S�̂ŕ`�悷�邩�ݒ�
	void SetPoseDraw(bool bUpdate) { m_bPoseDraw = bUpdate; }		// �|�[�Y���`�悷�邩�ݒ�

	bool IsAllUpdate() { return m_bAllUpdate; }			// �S�̂ōX�V���邩
	bool IsPoseUpdate() { return m_bPoseUpdate; }	// �|�[�Y���X�V���邩
	bool IsAllDraw() { return m_bAllDraw; }				// �S�̂ŕ`�悷�邩
	bool IsPoseDraw() { return m_bPoseDraw; }		// �|�[�Y���`�悷�邩

	void DeathFlag() { m_bDeath = true; }	// �������g�̎��S�t���O
	bool IsDeathFlag() { return m_bDeath ; }		// �������g�̎��S�t���O

protected:
private:
	// ���X�g
	static CObject* m_pTop[MAX_PRIORITY];	// �g�b�v
	static CObject* m_pCur[MAX_PRIORITY];	// �Ō��
	CObject* m_pNext;						// ��
	CObject* m_pPrev;						// �O
	static int m_nNumObject[MAX_PRIORITY];
	int m_nPriority;
	// �ϐ�
	TYPE m_type;							// ���

	X m_x;	// �g�����X�t�H�[��
	float m_fDistance;	// �J��������̋���

	bool m_bAllUpdate;						// �S�̂ōX�V���邩
	bool m_bPoseUpdate;						// �|�[�Y���X�V���邩
	bool m_bAllDraw;						// �S�̂ŕ`�悷�邩
	bool m_bPoseDraw;						// �|�[�Y���`�悷�邩
	//bool m_bAllRelease;						// 

	bool m_bDeath;							// ���S�t���O
};

#endif // !_OBJECT_H_