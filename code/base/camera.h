//============================================
//
// �J����[camera.h]
// Author:Uedakou
// 
//============================================
#ifndef _CUMERA_H_
#define _CUMERA_H_
#include "main.h"

#define POS_CAMERA (600.0f)	// ���_�Əœ_�̋���
// �����ݒ�
#define CAMERA_TYPE (true)	// ���ߓ��e
#define CAMERA_CONTROLLER (false)	// �J�����R���g���[���[���g����
#define CAMERA_V D3DXVECTOR3(0.0f, 300.0f, -POS_CAMERA)
#define CAMERA_R D3DXVECTOR3(0.0f, 10.0f, 0.0f)
#define CAMERA_U D3DXVECTOR3(0.0f, 1.0f, 0.0f)

class CText;

class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init(void);		//������
	void Uninit(void);		// �I��
	void Update(void);		// �X�V
	void SetCamera(void);	// �`��
	typedef enum {
		V = 0,
		R,
	}CENTER;
	void SetCameraPosV(D3DXVECTOR3 pos) { m_posV = pos;}	// �J�����ʒu�擾
	void SetCameraPosR(D3DXVECTOR3 pos) { m_posR = pos;}	// �J�����œ_�ʒu�擾
	void SetCameraRot(CENTER centor, D3DXVECTOR3 rot);
	void SetCameraPosNomal() { 
		m_posR = CAMERA_R;
		m_posV = CAMERA_V;
	}	// �J�����œ_�ʒu�擾

	D3DXVECTOR3 GetCameraPosV() { return m_posV; }	// �J�����ʒu�擾
	D3DXVECTOR3 GetCameraPosR() { return m_posR; }	// �J�����œ_�ʒu�擾
	D3DXVECTOR3 GetCameraRot() { return m_rot; }

	void AddCameraPosV(D3DXVECTOR3 pos) { m_posV += pos;}	// �J�����ʒu�擾
	void AddCameraPosR(D3DXVECTOR3 pos) { m_posR += pos;}	// �J�����œ_�ʒu�擾
	void AddCameraRot(CENTER centor, D3DXVECTOR3 rot);

	bool GetCameraControllreFpllow()// ���݃J�������R���g���[�����邩
	{return m_bCumeraController;}
	
	void DrawCamera();		// �J�������`��
private:
	// �֐�
	void Controller();	// ����
	// �ϐ�
	D3DXVECTOR3 m_posV;			// �J����
	D3DXVECTOR3 m_posR;			// �œ_
	D3DXVECTOR3 m_vecU;			// �㑤
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����s��
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_rotTarget;	// ����
	bool m_bRotTarget;			// �^�[�Q�b�g�Ɍ����邩

	bool m_bCameraTipe;			// �J���������ߓ��e�������e��
	bool m_bCumeraController;	// �J�����̃R���g���[�����ł��邩
	const float m_fMoveSpeed;
	const float m_fMoveFastSpeed;

	CText* m_pTex;
};



#endif // !_CUMERA_H_