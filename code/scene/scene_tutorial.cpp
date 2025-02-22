//===========================================
// 
// ゲームマネージャー[scene_tutorial.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_tutorial.h"

namespace Scene {
	namespace Game {
		//============================================
		// コンスト
		//============================================
		CTutorial::CTutorial(CBase* base, CGameData* gameData) :
			CBase(base , gameData)
		{
		}
		//============================================
		// デストラクタ
		//============================================
		CTutorial::~CTutorial()
		{
		}
		//============================================
		// 更新
		//============================================
		CTutorial* CTutorial::Update()
		{
			return nullptr;
		}
		//============================================
		// 描画
		//============================================
		void CTutorial::Draw() const
		{
		}
		//============================================
		// ポーズ状態取得
		//============================================
		bool CTutorial::IsPose()
		{
			return false;
		}
		//============================================
		// コンスト
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CTutorial>() {
			return new CTutorial(this, m_gameData);
		}
	}
}