//============================================
//
// 3D�����蔻��[collision.h]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_3D_H_
#define _COLLISION_3D_H_
#include "collision.h"	// �R���W����

// ���
class CCollision3D : public CCollision
{
public:
	typedef enum {
		Line = 0,	// ��
		Surface,	// ��
		Box,		// ��
		Sphere,		// ��
		Capsule,	// �J�v�Z��
		MAX
	}TYPE;

	CCollision3D();
	CCollision3D(TYPE type);
	~CCollision3D();
	TYPE GetType() { return m_type; }	// ��ގ擾

private:
	TYPE m_type;
};

#endif // !_COLLISION_H_
