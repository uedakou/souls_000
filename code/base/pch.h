//============================================
//
// �v���R���p�C��[pch.h]
// Author:Uedakou
// 
//============================================

// �C���N���[�h
#include <Windows.h>
#include "d3dx9.h"	 // �`��ɕK�v

#include "dinput.h"
#include "Xinput.h"


// ���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")		// �`��ɕK�v
#pragma comment(lib,"d3dx9.lib")	// [d3d9,lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	// DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	// �V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")	// D�C���v�b�g
#pragma comment(lib,"Xinput.lib")	// X�C���v�b�g
//#pragma comment(lib,"x86")		// 
//#pragma comment(lib,"Redist")	// X�C���v�b�g

// C++ �e�L�X�g
#include <iostream>	// �C���A�E�g�X�g���[��
#include <string>
using namespace std;

// �}�N����`
#define SCREEN_W (1280)			// �E�B���h�E�̕�
#define SCREEN_H (720)			// �E�B���h�E�̍���

#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#define FPS (60)	// FPS

#define ANIM_SLEEP (5)	// �A�j���[�V�������x����

#define CLASS_NAME "CatasrtopheMobile"		// �E�B���h�E�N���X���O
#define WINDOW_NAME "CatasrtopheMobile"		// �E�B���h�E�̖��O

