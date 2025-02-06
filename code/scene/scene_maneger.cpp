//===========================================
// 
// �V�[���}�l�[�W���[[scene_maneger.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_maneger.h"	// �V�[���}�l�[�W���[
#include "../base/manager.h"		// �}�l�[�W���[

namespace Scene {

	class CTitle;
	//============================================
	// �R���X�g
	//============================================
	CSceneManager::CSceneManager() :
		CBase(new CCommonData()),
		m_pScene(makeScene<CTitle>())
	{
		
	}
	//============================================
	// �f�X�g���N�^
	//============================================
	CSceneManager::~CSceneManager()
	{
		if (m_pScene != nullptr)
		{
			delete m_pScene;
		}
		delete m_pCommonData;
	}
	//============================================
	// �X�V
	//============================================
	CBase* CSceneManager::Update()
	{
		CBase* p = m_pScene->Update();

		if (p != m_pScene)
		{// �A��l���ς���Ă�����V�[���ύX
			delete m_pScene;
			if (p == nullptr)
			{
				CManager::GetInstance()->SetEnd(true);
			}
			m_pScene = p;
		}
		return m_pScene;
	}
	//============================================
	// �`��
	//============================================
	void CSceneManager::Draw() const
	{
		if (m_pScene != nullptr)
		{
			m_pScene->Draw();
		}
	}

	//============================================
	// �|�[�Y���擾
	//============================================
	bool CSceneManager::IsPose()
	{
		if (m_pScene != nullptr)
		{
			return m_pScene->IsPose();
		}
		return false;
	}
}
