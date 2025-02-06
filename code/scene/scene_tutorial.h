//===========================================
// 
// ゲームマネージャー[scene_tutorial.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_TUTORIAL_H_
#define _SCENE_TUTORIAL_H_
#include "scene_game.h"
namespace Scene {
	namespace Game {
		class CTutorial : public CBase
		{
		public:
			CTutorial(CBase* bas, CGameData* gameData);
			~CTutorial();
			virtual CTutorial* Update() override;
			virtual void Draw() const override;
			virtual bool IsPose()override;
		private:
		};
	}
}


#endif // !_SCENE_TUTORIAL_H_