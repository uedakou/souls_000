//============================================
//
// �����蔻��[collision.h]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "../base/pch.h"	// �v���R���p�C��

// ���
class CCollision
{
public:
	typedef enum {
		TYPE_2D = 0,
		TYPE_3D,
		MAX,
	}TYPE;
	CCollision();
	CCollision(TYPE type);
	~CCollision();
	TYPE GetType() { return m_type; }	// ��ގ擾
	// ��������
	static bool Hit(D3DXVECTOR3 pos0, D3DXVECTOR3 collision0, D3DXVECTOR3 pos1, D3DXVECTOR3 collision1);
	// Collision
	bool OnCollisionEnter(CCollision * collision);	// ��������
	bool OnCollisionStay(CCollision * collision);	// �������Ă���
	bool OnCollisionExit(CCollision * collision);	// ���ꂽ
	// Trigger
	bool OnTriggerEnter(CCollision * collision);	// ���蔲����
	bool OnTriggerStay(CCollision * collision);	// ���蔲���Ă���
	bool OnTriggerExit(CCollision * collision);	// �ʂ蔲����

private:
	TYPE m_type;
};

#endif // !_COLLISION_H_