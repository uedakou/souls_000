//============================================
//
// 2D�����蔻��[collision.h]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_2D_H_
#define _COLLISION_2D_H_
#include "collision.h"	// �R���W����

// ���
class CCollision2D : public CCollision
{
public:
	typedef enum {
		Line = 0,	// ��
		Surface,	// ��
		Circle,		// ��
		MAX
	}TYPE;

	CCollision2D();
	~CCollision2D();
	TYPE GetType() { return type; }	// ��ގ擾

private:
	TYPE type;
};
#endif // !_COLLISION_2D_H_
