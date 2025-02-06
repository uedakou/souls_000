//===========================================
// 
// ゲーム全体処理[play.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _PLAY_H_
#define _PLAY_H_
#include "scene_game.h"
#include "../base/main.h"		// メイン
#include "../object/base/save_object.h"
#include "game_data.h"

#define MAX_FIELD (16)	// 地面最大数
#define MAX_ENEMY (64)	// 敵最大数

class CObject;
namespace Scene {
	namespace Game {
		class Play : public CBase
		{
		public:
			typedef enum {
				Null = 0,	// 遷移しない
				Result,		// リザルト
				GameOver,	// ゲームオーバー
				MAX,
			}Next;
			Play(CBase* game, CGameData* gameData);
			virtual ~Play();
			nsPrev::CBase* Update()	override;
			bool IsPose()override;
			void Draw() const override;

		private:
			void CameraController();
		private:
			const int m_nCntMax;
			int m_nCnt;
			int m_nNext;

			bool bPause;	// ポーズ
			int m_Score;
		};
	}
}





#endif // !_PLAY_H_