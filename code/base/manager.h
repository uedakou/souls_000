//===========================================
// 
// �S�̃}�l�[�W���[[managerer.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include "renderer.h"			// �����_���[
#include "light.h"				// ���C�g
#include "camera.h"				// �J����
#include "fog.h"				// �t�H�O
#include "input.h"				// ����

#include "sound.h"	// �T�E���h

#include "../scene/scene_maneger.h"		// �V�[���}�l�[�W���[

#include "../collision/collision_manager.h"	// �R���W�����}�l�[�W���[


#define MAX_TXT	(0x400)


class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND nWnd, BOOL bWindow);	// ������
	void Uninit();		// �I��
	void Update();		// �X�V
	void Draw();		// �`��

	static CManager* GetInstance()
	{
		static CManager instance;	// �ÓI�C���X�^���X
		return &instance;
	}

	CRenderer* GetRenderer(){ return m_pRenderer; };	// �����_���[�擾
	CLight* GetLight() { return m_pLight; }				// ���C�g�擾
	CCamera* GetCamera() { return m_pCamera; }			// �J�����擾
	CFog* GetFog() { return m_pFog; }					// �t�H�O
	CSound* GetSound() { return m_pSound; }				// �T�E���h
	
	CInputKeyboard* GetInKey() { return m_pInkey; }	// �L�[�{�[�h�擾
	CInputMouse* GetMouse() { return m_pInMouse; }	// �}�E�X�擾
	CInputJoypad* GetJoyKey() { return m_pJoiKey; }	// �}�E�X�擾

	Scene::CBase* GetSceneManager() { return m_pSceneManager; }					// �V�[���}�l�[�W���[
	CCollisionManager* GetCollisionManager() { return m_pCollisionManager; }	// �R���W�����}�l�[�W���[

	static void SetEnd(bool bEnd) { m_bEnd = bEnd; }
	static bool GetEnd() { return m_bEnd; }
private:
	CRenderer* m_pRenderer;	// �����_���[
	CLight* m_pLight;		// ���C�g
	CCamera* m_pCamera;		// �J����
	CFog* m_pFog;			// �t�H�O
	CSound* m_pSound;		// �T�E���h

	CInputKeyboard* m_pInkey;				// �L�[�{�[�h
	CInputMouse* m_pInMouse;				// �}�E�X
	CInputJoypad* m_pJoiKey;				// �W���C�p�b�h

	Scene::CBase* m_pSceneManager;			// �V�[���}�l�[�W���[
	CCollisionManager* m_pCollisionManager;	// �R���W�����}�l�[�W���[

	static bool m_bEnd;	// �I��
};



#endif // !_MANAGER_H_