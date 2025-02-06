//============================================
//
// �|���S���RD[object_3D.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBJECT_3D_H_
#define _OBJECT_3D_H_

#include "object.h"	// �I�u�W�F�N�g���N���X
#include <stdio.h>

class CObject3D : public CObject
{
public:
	CObject3D();
	CObject3D(const int nPriority);
	~CObject3D()			override;
	virtual void Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;
	virtual void Draw()		override;

	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 pVtxBuff) { m_pVtxBuff = pVtxBuff; }

	void SetTexture(const char aFileName[MAX_TXT]);
	void SetTexture(const LPDIRECT3DTEXTURE9 pTex);

	void SetTexUV(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1);// �e�N�X�`��UV�ݒ�(����E��)
	void SetColor(D3DXCOLOR col);
	void SetBlock(int X, int Y);

	LPDIRECT3DVERTEXBUFFER9* GetVtxBuff() { return &m_pVtxBuff; }

	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }

	D3DXCOLOR GetColor() { return m_col; }

	void AddTexUV(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1);// �e�N�X�`��UV�ݒ�(����E��)

	static CObject3D* creat(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// �o�[�e�b�N�X�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`��
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���N�X
	D3DXCOLOR m_col;
	int BlockX;
	int BlockY;

};
#endif // _OBJECT_3D_H_