//===========================================
// 
// �Q�[���}�l�[�W���[[scene_game_manager.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_GAME_MANAGER_H_
#define _SCENE_GAME_MANAGER_H_
#include "scene_game.h"
namespace Scene {
	namespace Game {
		class CGameManager : public CBase
		{
		public:
			CGameManager(nsPrev::CBase* pScene);
			~CGameManager();
		private:
			nsPrev::CBase* m_pScene;		// �V�[��
			nsPrev::CBase* m_pNextScene;	// ���V�[��
			nsPrev::CBase* m_pStageController;	// �X�e�[�W����

		public :
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;
			bool IsPose()override;
		};
	}
}





#endif // !_