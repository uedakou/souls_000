//===========================================
// 
// ���C��[main.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _MAIN_H_	// ���̃}�N����`����ĂȂ��Ȃ�
#define _MAIN_H_	// ��d�C���N���[�h�h�~�̃}�N��
#include "pch.h"	// �v���R���p�C��

// ���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ύX�p�W���i1.0f�ŌŒ�j
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_2D;
// ���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_3D;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int GetFPS();

#endif // _MAIN_H_