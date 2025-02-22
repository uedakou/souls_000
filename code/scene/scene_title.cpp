//===========================================
// 
// タイトル[scene_title.h]
// Auther:UedaKou
// 
//===========================================
#include "scene_title.h"

namespace Scene {
	//============================================
	// コンスト
	//============================================
	CTitle::CTitle(CBase* scene) :
		CBase(*scene)
	{
	}
	//============================================
	// デストラ
	//============================================
	CTitle::~CTitle()
	{
	}
	//============================================
	// 更新
	//============================================
	CTitle* CTitle::Update()
	{
		return this;
	}
	//============================================
	// 描画
	//============================================
	void CTitle::Draw() const
	{
	}
	//============================================
	// 生成
	//============================================
	template<>
	CBase* CBase::makeScene<CTitle>() {
		return new CTitle(this);
	}
}