//===========================================
// 
// モーション[motion.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "object_X.h"

#define MAX_MOTION (64)			// 最大モーション
#define MAX_KYE (32)			// 最大キーフレーム数
#define MAX_MOTION_MODEL (64)	// モーションに使えるモデル数
#define MAX_PARTS (64)			// 最大パーツ数
/*
全体モーション管理
	モーション(ニュートラル, 歩きなど)
		現在キー
		キーフレーム


	パーツ
	現在モーション
	


*/
class CPartsData
{
public:
	CPartsData();
	~CPartsData();

	void SetPosTarget(D3DXVECTOR3 pos) { m_x.pos = pos; }
	void SetRotTarget(D3DXVECTOR3 rot) { m_x.rot = rot; }
	void SetSizTarget(D3DXVECTOR3 siz) { m_x.siz = siz; }

	D3DXVECTOR3 GetPosTarget() { return m_x.pos; }
	D3DXVECTOR3 GetRotTarget() { return m_x.rot; }
	D3DXVECTOR3 GetSizTarget() { return m_x.siz; }
private:
	X m_x;	// トランスフォーム

};

// キーフレーム
class CKye
{
public:
	CKye();
	~CKye();
	void SetFrame(int nFrame) { m_nFrame = nFrame; }

	CPartsData* GetPartsData(int nParts) { return m_pParts[nParts]; }
	int GetFrame() { return m_nFrame; }
	CPartsData* creatPartsData();

private:
	CPartsData* m_pParts[MAX_PARTS];	// パーツ
	int m_nFrame;
};

// モーション
class CMotion 
{
public:
	CMotion();
	virtual ~CMotion();
	void SetNumKye(int nNumKye) { m_nNumKye = nNumKye; }
	void SetLoop(bool bLoop) { m_bLoop = bLoop; }
	void creatKye();

	CKye* GetKye(int nKye) { return m_pKye[nKye]; }
	int GetNumKye() { return m_nNumKye; }
	bool GetLoop() { return m_bLoop; }
private:
	CKye* m_pKye[MAX_KYE];	// キーフレーム
	int m_nNumKye;	// キー数
	bool m_bLoop;	// このモーションをループするか
};

// 現在モーション
class CNowMotion
{
public:
	CNowMotion();
	~CNowMotion();
	// 設定
	void SetMotion(int nMosyon) { m_nCntMotion = nMosyon; }		// モーションカウント
	void SetKye(int nKye) { m_nCntKye = nKye; }			// キーカウント
	void SetFrame(int nFrame) { m_nCntFrame = nFrame; }		// フレーム

	// 取得
	int GetMotion() { return m_nCntMotion; }	// モーションカウント
	int GetKye() { return m_nCntKye; }		// キーカウント
	int GetFrame() { return m_nCntFrame; }		// フレーム

	// データ追加
	void AddMotion(int nNum) { m_nCntMotion += nNum; }	// モーションカウント
	void AddKye(int nNum) { m_nCntKye += nNum; }		// キーカウント
	void AddFrame(int nNum) { m_nCntFrame += nNum; }		// フレーム

private:
	int m_nCntMotion;	// モーションカウント
	int m_nCntKye;		// キーカウント
	int m_nCntFrame;	// フレーム
};

// パーツ
class CParts : public CObjectX
{
public:
	CParts();
	CParts(int nPriority);
	~CParts()					override;
	virtual void Init()		override; // 初期化
	virtual void Uninit()	override; // 終了
	virtual void Update()	override; // 更新
	virtual void Draw()		override; // 描画


	// 基本位置設定
	void SetBasicX(X x) {
		m_xBasic.pos = x.pos;
		m_xBasic.rot = x.rot;
		m_xBasic.siz = x.siz;
	}
	void SetBasicX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz) {
		m_xBasic.pos = pos;
		m_xBasic.rot = rot;
		m_xBasic.siz = siz;
	}
	void SetBasicPos(D3DXVECTOR3 pos) { m_xBasic.pos = pos; }
	void SetBasicRot(D3DXVECTOR3 rot) { m_xBasic.rot = rot; }
	void SetBasicSiz(D3DXVECTOR3 siz) { m_xBasic.siz = siz; }

	// 追加位置
	void SetAddX(X x) {
		m_xAdd.pos = x.pos;
		m_xAdd.rot = x.rot;
		m_xAdd.siz = x.siz;
	}
	void SetAddX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz) {
		m_xAdd.pos = pos;
		m_xAdd.rot = rot;
		m_xAdd.siz = siz;
	}
	void SetAddPos(D3DXVECTOR3 pos) { m_xAdd.pos = pos; }
	void SetAddRot(D3DXVECTOR3 rot) { m_xAdd.rot = rot; }
	void SetAddSiz(D3DXVECTOR3 siz) { m_xAdd.siz = siz; }

	// 動き設定
	void SetMoveX(X x, int nFrame) { SetMoveX(x.pos, x.rot, x.siz, nFrame); };
	void SetMoveX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz, int nFrame); 

	// データ設定
	void SetParentID(int nParent) { m_nParent = nParent; }
	void SetParentMtx(D3DXMATRIX pParent) { m_mtxParent = pParent; }
	void SetDisplay(bool bDesplay) { m_bDisplay = bDesplay; }	// 表示するかどうか

	void SetMotion(int nMotion);

	// 位置取得
	X GetBasicX() {
		return m_xBasic;
	}
	D3DXVECTOR3 GetBasicPos() { return m_xBasic.pos; }
	D3DXVECTOR3 GetBasicRot() { return m_xBasic.rot; }
	D3DXVECTOR3 GetBasicSiz() { return m_xBasic.siz; }

	// 追加位置
	X GetAddX() {
		return m_xAdd;
	}
	D3DXVECTOR3 GetAddPos() { return m_xAdd.pos; }
	D3DXVECTOR3 GetAddRot() { return m_xAdd.rot; }
	D3DXVECTOR3 GetAddSiz() { return m_xAdd.siz; }

	// データ取得
	int GetParentID() { return m_nParent; }				// 親ID取得
	D3DXMATRIX GetParentMtx() { return m_mtxParent; }	// 親マトリクス取得
	bool GetDisplay() { return m_bDisplay; }			// 表示するかどうか
	CNowMotion* GetNowMotion() { return m_pNowMotion; }	// 現在モーション

	void SetDoMotion(bool bDoMotion) { m_bDoMotion = bDoMotion; }	// モーションするか設定

private:

	X m_xBasic;			// 基本位置
	X m_xAdd;			// 追加位置
	X m_xMove;			// 動き

	int m_nParent;			// 親ID
	D3DXMATRIX m_mtxParent;	// 親マトリクス

	bool m_bDisplay;	// 表示するかどうか

	CNowMotion* m_pNowMotion;	// 現在モーション

	bool m_bDoMotion;	// モーションするかどうか
};

// モーション管理
class CObjectMotion : public CObject
{
public:
	CObjectMotion();
	virtual ~CObjectMotion()		override;
	virtual void Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;
	virtual void Draw()		override;
	
	// 位置
	void SetPos(D3DXVECTOR3 pos) { m_x.pos = pos; }// 位置設定
	void SetPosX(float x) { m_x.pos.x = x; }// 位置設定
	void SetPosY(float y) { m_x.pos.y = y; }// 位置設定
	void SetPosZ(float z) { m_x.pos.z = z; }// 位置設定
	void SetRot(D3DXVECTOR3 rot) { m_x.rot = rot; }// 向き設定
	void SetRotX(float x) { m_x.rot.x = x; }// 位置設定
	void SetRotY(float y) { m_x.rot.y = y; }// 位置設定
	void SetRotZ(float z) { m_x.rot.z = z; }// 位置設定
	void SetSiz(D3DXVECTOR3 siz) { m_x.siz = siz; }// 大きさ設定
	void SetSizX(float x) { m_x.siz.x = x; }// 位置設定
	void SetSizY(float y) { m_x.siz.y = y; }// 位置設定
	void SetSizZ(float z) { m_x.siz.z = z; }// 位置設定
	void SetX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz) {
		m_x.pos = pos;
		m_x.rot = rot;
		m_x.siz = siz;
	}

	D3DXVECTOR3 GetPos() { return m_x.pos; }// 位置設定
	float GetPosX() { return m_x.pos.x; }// 位置設定
	float GetPosY() { return m_x.pos.y; }// 位置設定
	float GetPosZ() { return m_x.pos.z; }// 位置設定
	D3DXVECTOR3 GetRot() { return m_x.rot; }// 向き設定
	D3DXVECTOR3 GetSiz() { return m_x.siz; }// 大きさ設定
	X GetX() { return m_x; }

	void AddPos(D3DXVECTOR3 pos) { m_x.pos += pos; }// 位置追加
	void AddPosX(float x) { m_x.pos.x += x; }// 位置追加
	void AddPosY(float y) { m_x.pos.y += y; }// 位置追加
	void AddPosZ(float z) { m_x.pos.z += z; }// 位置追加
	void AddRot(D3DXVECTOR3 rot) { m_x.rot += rot; }// 向き追加
	void AddRotX(float x) { m_x.rot.x += x; }// 位置追加
	void AddRotY(float y) { m_x.rot.y += y; }// 位置追加
	void AddRotZ(float z) { m_x.rot.z += z; }// 位置追加
	void AddSiz(D3DXVECTOR3 siz) { m_x.siz += siz; }// 大きさ追加
	void AddSizX(float x) { m_x.siz.x += x; }// 位置追加
	void AddSizY(float y) { m_x.siz.y += y; }// 位置追加
	void AddSizZ(float z) { m_x.siz.z += z; }// 位置追加


	// 1f前の位置設定
	void SetOldX(X x) {
		m_xold.pos = x.pos;
		m_xold.rot = x.rot;
		m_xold.siz = x.siz;
	}
	void SetOldPos(D3DXVECTOR3 pos) { m_xold.pos = pos; }// 位置設定
	void SetOldRot(D3DXVECTOR3 rot) { m_xold.rot = rot; }// 向き設定
	void SetOldSiz(D3DXVECTOR3 siz) { m_xold.siz = siz; }// 大きさ設定

	X GetOldX() { return m_xold; }
	D3DXVECTOR3 GetOldPos() { return m_xold.pos; }// 運動量設定
	D3DXVECTOR3 GetOldRot() { return m_xold.rot; }// 回転量設定
	D3DXVECTOR3 GetOldSiz() { return m_xold.siz; }// 膨張量設定

	void AddOldX(X x) {
		m_xold.pos += x.pos;
		m_xold.rot += x.rot;
		m_xold.siz += x.siz;
	}
	void AddOldPos(D3DXVECTOR3 pos) { m_xold.pos += pos; }// 位置設定
	void AddOldRot(D3DXVECTOR3 rot) { m_xold.rot += rot; }// 向き設定
	void AddOldSiz(D3DXVECTOR3 siz) { m_xold.siz += siz; }// 大きさ設定


	CMotion* GetMotion(int nNum) { return m_pMotion[nNum]; }// モーションデータ取得

	int GetNumParts() { return m_nParts; }
	CParts* GetParts(int nNum) { return m_pParts[nNum]; }	// パーツ取得

protected:
	bool Lode(const char* aFileName);	// モーション読み込み
	void SetMotion(int nMotion);	// モーション設定

	virtual int GetNextMotion() { return 0; };	// 次取得
private:
	void creatMotion();// モーション生成
private:

	int m_nModel;							// モデル数

	int m_nNumMotion;						// モーション数
	CMotion* m_pMotion[MAX_MOTION];	// モーションデータ

	int m_nParts;				// パーツ数
	CParts* m_pParts[MAX_PARTS];

	int m_nNextMotion;

	X m_x;					// トランスフォーム
	X m_xold;		// 1f前位置
	D3DXMATRIX m_mtxWorld;	// ワールドマトリクス
};




#endif // !_MOTION_H_