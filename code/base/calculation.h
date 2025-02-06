//============================================
//
// �v�Z�p[calculation.h]
// Author:Uedakou
// 
//============================================
#ifndef _CALCULATION_H_
#define _CALCULATION_H_
//********************************************
// �C���N���[�h
//********************************************


#include "manager.h"


#define TAU (D3DX_PI * 2)	// 

typedef struct {
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 rot;	// ����
	D3DXVECTOR3 siz;	// �傫��(�{��)
}Transform;

// �g�����X�t�H�[��
class X : public Transform
{
public:
	X() {}
	X(D3DXVECTOR3 Vec3pos, D3DXVECTOR3 Vec3rot, D3DXVECTOR3 Vec3siz) {
		pos = Vec3pos;
		rot = Vec3rot;
		siz = Vec3siz;
	}

	X& operator+= (const X& transform)
	{
		pos.x += transform.pos.x;
		pos.y += transform.pos.y;
		pos.z += transform.pos.z;

		rot.x += transform.rot.x;
		rot.y += transform.rot.y;
		rot.z += transform.rot.z;

		siz.x += transform.siz.x;
		siz.y += transform.siz.y;
		siz.z += transform.siz.z;
		return *this;
	}
	X& operator-= (const X& transform)
	{
		pos.x -= transform.pos.x;
		pos.y -= transform.pos.y;
		pos.z -= transform.pos.z;

		rot.x -= transform.rot.x;
		rot.y -= transform.rot.y;
		rot.z -= transform.rot.z;

		siz.x -= transform.siz.x;
		siz.y -= transform.siz.y;
		siz.z -= transform.siz.z;
		return *this;
	}
	X& operator*= (const X& transform)
	{
		pos.x *= transform.pos.x;
		pos.y *= transform.pos.y;
		pos.z *= transform.pos.z;

		rot.x *= transform.rot.x;
		rot.y *= transform.rot.y;
		rot.z *= transform.rot.z;

		siz.x *= transform.siz.x;
		siz.y *= transform.siz.y;
		siz.z *= transform.siz.z;
		return *this;
	}
	X& operator/= (const X& transform)
	{
		pos.x /= transform.pos.x;
		pos.y /= transform.pos.y;
		pos.z /= transform.pos.z;

		rot.x /= transform.rot.x;
		rot.y /= transform.rot.y;
		rot.z /= transform.rot.z;

		siz.x /= transform.siz.x;
		siz.y /= transform.siz.y;
		siz.z /= transform.siz.z;
		return *this;
	}
};

#endif // !_CALCULATION_H_