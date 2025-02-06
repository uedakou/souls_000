//===========================================
// 
// �Q�[���}�l�[�W���[[scene_game_manager.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_game_manager.h"	// �Q�[���}�l�[�W���[	
#include "game_data.h"			// �Q�[���f�[�^

namespace nsThis = Scene::Game;
namespace Scene {
	namespace Game {
		class Play;
		class CSceneDebug;
		class CStage_000;
		class CSceneDebug;
		class CTutorial;
		//============================================
		// �R���X�g���N�^
		//============================================
		CGameManager::CGameManager(nsPrev::CBase* scene) :
			CBase(scene, new CGameData()),
			m_pScene(makeScene<Play>()),
			m_pStageController(makeScene<CTutorial>())
		{
			//CObject::ReleaseAll();
			m_pNextScene = nullptr;
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CGameManager::~CGameManager()
		{
			if (m_pScene != nullptr)
			{
				delete m_pScene;
			}
			if (m_pStageController)
			{
				delete m_pStageController;
			}
		}
		//============================================
		// �X�V
		//============================================
		nsPrev::CBase* CGameManager::Update()
		{
			{
				auto p = m_pScene->Update();
				if (p != m_pScene)
				{
					m_pNextScene = p;
					delete m_pScene;
					auto p2 = dynamic_cast<CBase*>(p);
					if (p2 != nullptr)
					{
						m_pScene = p2;
						return this;
					}
					else
					{
						m_pScene = nullptr;
						return p;
					}
				}
			}
			{
				auto p = m_pStageController->Update();
				if (p != m_pStageController)
				{
					delete m_pStageController;

					if (true)
					{

					}
					m_pStageController = p;
					return this;
				}
			}
			return this;
		}
		//============================================
		// �`��
		//============================================
		void CGameManager::Draw() const
		{
		}
		//============================================
		// �R���X�g���N�^
		//============================================

		//============================================
		// �|�[�Y���擾
		//============================================
		bool CGameManager::IsPose()
		{
			if (m_pScene != nullptr)
			{
				return m_pScene->IsPose();
			}
			return false;
		}
	}
	template<>
	Scene::CBase* nsThis::nsPrev::CBase::makeScene<nsThis::CGameManager>() {
		return new nsThis::CGameManager(this);
	}
}