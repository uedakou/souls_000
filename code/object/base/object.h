//============================================
//
// オブジェクト[object.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "../../base/manager.h"
#include "../../base/calculation.h"
#include <vector>
#include <algorithm>
#include <cmath>

// オブジェクト
#define DEFALT_PRIORITY (3)	// 優先度未設定時の優先度
class CObject
{
public:
	// 種類
	typedef enum {
		TYPE_NULL = 0,
		BILLBOARD,	// ビルボード
		OBJECT2D,	// 2D
		FIELD,		// フィールド
		POPUP,		// ポップアップ
		PLAYER,	// プレイヤー
		ENEMY,		// 敵
		PARTS,		// パーツ
		MAPOBJECT,	// マップオブジェクト
		POTAL,		// ポータル
		BLOCK,		// ブロック
		MAX,
	}TYPE;			// オブジェクト種類

	CObject();
	CObject(const int nPriority);
	virtual ~CObject();
	virtual void Init() = 0;	// 初期化
	virtual void Uninit() = 0;	// 終了
	virtual void Update() = 0;	// 更新
	virtual void Draw() = 0;	// 描画
	void Release();				// 自分自身の解放

	// 全体処理
	static void ReleaseAll();	// 全オブジェクト解放
	static void ReleaseDeathFlag();	// 全オブジェクト解放
	static void UpdateAll();	// 全オブジェクト更新
	static void DrawAll();		// 全オブジェクト描画
	static void GetAllObject(CObject* object[MAX_PRIORITY]);	// オブジェクト取得
	static CObject* GetMyObject(int nPriorty) { return m_pTop[nPriorty]; };	// オブジェクト取得(優先度毎)
	static void Sort();

	static void CalculateDistanceToCamera();
	void CalculateDistance(D3DXVECTOR3 pos);
	//// ソート関数
	//static bool CompareByDistance(const CObject& a, const CObject& b) {
	//	return a.m_fDistance > b.m_fDistance; // 距離が大きい順
	//}
	//// ソート処理
	//static void SortObjectsByDistance(std::vector<CObject>& objects) {
	//	std::sort(objects.begin(), objects.end(), CompareByDistance);
	//}
	// リスト
	void SetNext(CObject* pNext) { m_pNext = pNext; }	// 次設定
	void SetPrev(CObject* pPrev) { m_pPrev = pPrev; }	// 前設定
	CObject* GetNext() { return m_pNext; }//	次取得
	CObject* GetPrev() { return m_pPrev; }//	次取得

	// 種類
	void SetType(TYPE type);	// 自身の種類設定
	TYPE GetType();				// 種類取得

	// トランスフォーム設定
	void SetX(X x) { m_x = x; }
	void SetX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 siz) {
		m_x.pos = pos;
		m_x.rot = rot;
		m_x.siz = siz;
	}
	void SetPos(const D3DXVECTOR3 pos) { m_x.pos = pos; }	// 位置設定
	void SetRot(const D3DXVECTOR3 rot) { m_x.rot = rot; }	// 向き設定
	void SetSiz(const D3DXVECTOR3 siz) { m_x.siz = siz; }	// 大きさ設定
	// トランスフォーム加算
	void AddX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 siz) {
		m_x.pos += pos;
		m_x.rot += rot;
		m_x.siz += siz;
	}														// トランスフォーム設定
	void AddPos(const D3DXVECTOR3 pos) { m_x.pos += pos; }	// 位置設定
	void AddRot(const D3DXVECTOR3 rot) { m_x.rot += rot; }	// 向き設定
	void AddSiz(const D3DXVECTOR3 siz) { m_x.siz += siz; }	// 大きさ設定
	// トランスフォーム取得
	X GetX() { return m_x; }					// トランスフォーム設定
	D3DXVECTOR3 GetPos() { return m_x.pos; }	// 位置設定
	D3DXVECTOR3 GetRot() { return m_x.rot; }	// 向き設定
	D3DXVECTOR3 GetSiz() { return m_x.siz; }	// 大きさ設定

	void SetDistance(float fDistance) { m_fDistance = fDistance; }	// 見目らからの距離
	float GetDistance() { return m_fDistance; }	// 見目らからの距離

	// フラグ
	void SetUpdate(bool bUpdate) { m_bAllUpdate = bUpdate; }			// 全体で更新するか設定
	void SetPoseUpdate(bool bUpdate) { m_bPoseUpdate = bUpdate; }	// ポーズ中更新するか設定
	void SetDraw(bool bUpdate) { m_bAllDraw = bUpdate; }				// 全体で描画するか設定
	void SetPoseDraw(bool bUpdate) { m_bPoseDraw = bUpdate; }		// ポーズ中描画するか設定

	bool IsAllUpdate() { return m_bAllUpdate; }			// 全体で更新するか
	bool IsPoseUpdate() { return m_bPoseUpdate; }	// ポーズ中更新するか
	bool IsAllDraw() { return m_bAllDraw; }				// 全体で描画するか
	bool IsPoseDraw() { return m_bPoseDraw; }		// ポーズ中描画するか

	bool IsDeathFlag() { return m_bDeath ; }		// 自分自身の死亡フラグ

protected:
private:
	// リスト
	static CObject* m_pTop[MAX_PRIORITY];	// トップ
	static CObject* m_pCur[MAX_PRIORITY];	// 最後尾
	CObject* m_pNext;						// 次
	CObject* m_pPrev;						// 前
	static int m_nNumObject[MAX_PRIORITY];
	int m_nPriority;
	// 変数
	TYPE m_type;							// 種類

	X m_x;	// トランスフォーム
	float m_fDistance;	// カメラからの距離

	bool m_bAllUpdate;						// 全体で更新するか
	bool m_bPoseUpdate;						// ポーズ中更新するか
	bool m_bAllDraw;						// 全体で描画するか
	bool m_bPoseDraw;						// ポーズ中描画するか
	//bool m_bAllRelease;						// 

	bool m_bDeath;							// 死亡フラグ
};

#endif // !_OBJECT_H_