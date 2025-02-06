//===========================================
// 
// �Q�[���S�̏���[play.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _PLAY_H_
#define _PLAY_H_
#include "scene_game.h"
#include "../base/main.h"		// ���C��
#include "../object/base/save_object.h"
#include "game_data.h"

#define MAX_FIELD (16)	// �n�ʍő吔
#define MAX_ENEMY (64)	// �G�ő吔

class CObject;
namespace Scene {
	namespace Game {
		class Play : public CBase
		{
		public:
			typedef enum {
				Null = 0,	// �J�ڂ��Ȃ�
				Result,		// ���U���g
				GameOver,	// �Q�[���I�[�o�[
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

			bool bPause;	// �|�[�Y
			int m_Score;
		};
	}
}





#endif // !_PLAY_H_