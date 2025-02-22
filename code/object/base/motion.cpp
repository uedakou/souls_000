//===========================================
// 
// モーション[motion.cpp]
// Auther:UedaKou
// 
//===========================================
#include "motion.h"
#include <fstream>
#include <iostream>
#include "../../base/pch.h"

//============================================
// コンストラクタ(パーツデータ)
//============================================
CPartsData::CPartsData()
{
	m_x = X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
//============================================
// デストラ(パーツデータ)
//============================================
CPartsData::~CPartsData()
{
}

//============================================
// コンストラクタ(キーフレーム)
//============================================
CKye::CKye()
{
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (m_pParts[nCntParts] != nullptr)
		{
			m_pParts[nCntParts] = nullptr;
		}
	}
	m_nFrame = 0;
}
//============================================
// デストラ(キーフレーム)
//============================================
CKye::~CKye()
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		delete m_pParts[nCnt];
	}
}
//============================================
// 生成
//============================================
CPartsData* CKye::creatPartsData()
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (m_pParts[nCnt] == nullptr)
		{
			m_pParts[nCnt] = new CPartsData;
			return m_pParts[nCnt];
		}
	}
	return 0;
}

//============================================
// コンストラクタ
//============================================
CMotion::CMotion()
{
	for (int nCntkye = 0; nCntkye < MAX_KYE; nCntkye++)
	{
		m_pKye[nCntkye] = nullptr;
	}
	m_nNumKye = 0;
	m_bLoop = 0;
}
//============================================
// デストラ
//============================================
CMotion::~CMotion()
{
	for (int nCnt = 0; nCnt < MAX_KYE; nCnt++)
	{
		if (m_pKye[nCnt] != nullptr)
		{
			delete m_pKye[nCnt];
		}
	}
}
//============================================
// キーフレーム生成
//============================================
void CMotion::creatKye()
{
	for (int nCntKye = 0; nCntKye < m_nNumKye; nCntKye++)
	{
		if (m_pKye[nCntKye] == nullptr)
		{
			m_pKye[nCntKye] = new CKye;
			return;
		}
	}
}


//============================================
// コンスト(現在モーション)
//============================================
CNowMotion::CNowMotion()
{
	m_nCntMotion = 0;
	m_nCntKye = 0;
	m_nCntFrame = 0;
}
//============================================
// デストラ(現在モーション)
//============================================
CNowMotion::~CNowMotion()
{
}



//============================================
// コンストラクタ(パーツ)
//============================================
CParts::CParts()
{
	// 基本位置
	m_xBasic.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xBasic.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xBasic.siz = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	// 追加位置
	m_xAdd.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xAdd.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xAdd.siz = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 動き
	m_xMove.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xMove.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xMove.siz = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nParent = -1;

	m_bDisplay = 0;		// 表示するかどうか

	m_pNowMotion = new CNowMotion;

	SetUpdate(false);
}
CParts::CParts(int nPriority) : CObjectX(nPriority)
{
	// 基本位置
	m_xBasic.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xBasic.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xBasic.siz = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	// 追加位置
	m_xAdd.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xAdd.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xAdd.siz = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 動き
	m_xMove.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xMove.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xMove.siz = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nParent = -1;	// 親

	//m_nIndex = 0;		// パーツ種類// 
	m_bDisplay = 0;		// 表示するかどうか

	m_pNowMotion = new CNowMotion;
}
//============================================
// デストラ(パーツ)
//============================================
CParts::~CParts()
{
	delete m_pNowMotion;
}
//============================================
// 初期化(パーツ)
//============================================
void CParts::Init()
{
	SetUpdate(false);
	CObjectX::Init();
}
//============================================
// 終了(パーツ)
//============================================
void CParts::Uninit()
{
	CObjectX::Uninit();
}
//============================================
// 更新(パーツ)
//============================================
void CParts::Update()
{
	// 動きを加算
	//m_nID;
	m_xAdd.pos += m_xMove.pos;
	m_xAdd.rot += m_xMove.rot;
	m_xAdd.siz += m_xMove.siz;
	// 加算分を計算
	D3DXVECTOR3 pos, rot, siz;
	pos = m_xAdd.pos + m_xBasic.pos;
	rot = m_xAdd.rot + m_xBasic.rot;
	siz = m_xAdd.siz + m_xBasic.siz;
	// 計算分を反映
	CObjectX::SetX(pos, rot, siz);
	CObjectX::Update();
}
//============================================
// 描画(パーツ)
//============================================
void CParts::Draw()
{
#if 0
	CObjectX::Draw();
#else
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// デバイス取得
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld, mtxParent;	// 計算用マトリクス	
	D3DMATERIAL9 matDef;					// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;						// マテリアルデータへのポインタ
	CModelX* pModel = CModelX::GetModel(GetID());

	X x = GetX();

	mtxWorld = GetMtx();
	// ワールドマトリクスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 向き
	D3DXMatrixRotationYawPitchRoll(&mtxRot, x.rot.y, x.rot.x, x.rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, x.pos.x, x.pos.y, x.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	mtxRot = m_mtxParent;

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	SetMtx(mtxWorld);

	// ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pModel->GetBuffMtx()->GetBufferPointer();

	// マテリアルサイズ分繰り返す
	for (int nCntMat = 0; nCntMat < (int)pModel->GetNumMat(); nCntMat++)
	{
		// 色
		//pMat[nCntMat].MatD3D.Diffuse.g = 0.0f;
		//pMat[nCntMat].MatD3D.Diffuse.a = 0.1f;

		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, pModel->GetTexture(nCntMat));

		//モデル(パーツ)の描画
		pModel->GetMesh()->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
#endif // 0
}
void CParts::SetMotion(int nMotion)
{
	m_pNowMotion->SetMotion(nMotion);
	m_pNowMotion->SetKye(0);
	m_pNowMotion->SetFrame(0);
}

void CParts::SetMoveX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz, int nFrame)
{
	X x;
	x.pos.x = pos.x - m_xAdd.pos.x;
	x.pos.y = pos.y - m_xAdd.pos.y;
	x.pos.z = pos.z - m_xAdd.pos.z;
	x.rot.x = rot.x - m_xAdd.rot.x;
	x.rot.y = rot.y - m_xAdd.rot.y;
	x.rot.z = rot.z - m_xAdd.rot.z;
	x.siz.x = siz.x - m_xAdd.siz.x;
	x.siz.y = siz.y - m_xAdd.siz.y;
	x.siz.z = siz.z - m_xAdd.siz.z;


	if (x.rot.x > D3DX_PI)
	{
		x.rot.x -= TAU;
	}
	else if (x.rot.x < -D3DX_PI)
	{
		x.rot.x += TAU;
	}

	if (x.rot.y > D3DX_PI)
	{
		x.rot.y -= TAU;
	}
	else if (x.rot.y < -D3DX_PI)
	{
		x.rot.y += TAU;
	}

	if (x.rot.z > D3DX_PI)
	{
		x.rot.z -= TAU;
	}
	else if (x.rot.z < -D3DX_PI)
	{
		x.rot.z += TAU;
	}

	m_xMove.pos.x = x.pos.x / (float)nFrame;
	m_xMove.pos.y = x.pos.y / (float)nFrame;
	m_xMove.pos.z = x.pos.z / (float)nFrame;
	m_xMove.rot.x = x.rot.x / (float)nFrame;
	m_xMove.rot.y = x.rot.y / (float)nFrame;
	m_xMove.rot.z = x.rot.z / (float)nFrame;
	m_xMove.siz.x = x.siz.x / (float)nFrame;
	m_xMove.siz.y = x.siz.y / (float)nFrame;
	m_xMove.siz.z = x.siz.z / (float)nFrame;
	m_pNowMotion->SetFrame(nFrame);
}
//============================================
// コンストラクタ
//============================================
CObjectMotion::CObjectMotion()
{
	// モデル
	m_nModel = 0;

	// モーションデータ
	m_nNumMotion = 0;
	for (int i = 0; i < MAX_MOTION; i++)
	{
		m_pMotion[i] = nullptr;
	}

	// パーツ
	m_nParts = 0;
	for (int i = 0; i < MAX_PARTS; i++)
	{
		m_pParts[i] = nullptr;
	}

	//	現在モーション
	m_nNextMotion = 0;

	// トランスフォーム
	m_x.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_x.rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_x.siz = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_xold = {};
}

//============================================
// デストラ
//============================================
CObjectMotion::~CObjectMotion()
{
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		if (m_pMotion[nCnt])
		{
			delete m_pMotion[nCnt];
		}
	}
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{

		if (m_pParts[nCnt] != nullptr)
		{
			m_pParts[nCnt]->Release();
			m_pParts[nCnt] = nullptr;
		}
	}

}
//============================================
// 初期化
//============================================
void CObjectMotion::Init()
{
	for (int nCnt = 0; nCnt < m_nNumMotion; nCnt++)
	{
		CPartsData* TargetMotion = m_pMotion[GetNextMotion()]->GetKye(0)->GetPartsData(nCnt);	// 目標モーション取得
		// 動きを設定
		m_pParts[nCnt]->SetAddX(
			TargetMotion->GetPosTarget(),	// 位置
			TargetMotion->GetRotTarget(),	// 向き
			TargetMotion->GetSizTarget());	// 大きさ
		m_pParts[nCnt]->GetNowMotion()->SetFrame(1);
		m_pParts[nCnt]->SetMoveX(
			TargetMotion->GetPosTarget(),	// 位置
			TargetMotion->GetRotTarget(),	// 向き
			TargetMotion->GetSizTarget(),
			m_pMotion[GetNextMotion()]->GetKye(0)->GetFrame());	// 大きさ
	}
}
//============================================
// 終了処理
//============================================
void CObjectMotion::Uninit()
{
	for (int nCntParts = 0; nCntParts < m_nParts; nCntParts++)
	{
		m_pParts[nCntParts]->Uninit();
	}
	CObject::Release();
}
//============================================
// 更新処理
//============================================
void CObjectMotion::Update()
{


	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// デバイス取得
	D3DXMATRIX mtxRot0, mtxRot1, mtxTrans;	// 計算用マトリクス
	// ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot1, m_x.rot.y, m_x.rot.x, m_x.rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot1);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_x.pos.x, m_x.pos.y, m_x.pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// モーション
	for (int nCntParts = 0; nCntParts < m_nParts; nCntParts++)
	{
		CNowMotion* pNowMotion = m_pParts[nCntParts]->GetNowMotion();
		CMotion* pTargetMotion0 = m_pMotion[pNowMotion->GetMotion()];

		pNowMotion->AddFrame(-1);	// フレームを１進める
		int nNowFrame = pNowMotion->GetFrame();
		if (nNowFrame <= 0)
		{// キーのフレームが経過したら
			pNowMotion->AddKye(1);	// kyeを１進める
			int nNowKye = pNowMotion->GetKye(),
				nTarget = pTargetMotion0->GetNumKye();
			if (nNowKye >= nTarget)
			{// モーションのキーが経過したら
				pNowMotion->SetKye(0);
				bool bLoop = pTargetMotion0->GetLoop();
				if (bLoop == false)
				{// ループしないなら
					pNowMotion->SetMotion(GetNextMotion());
				}
			}
			CPartsData* pTargetMotion1;	// モーション格納用
			pTargetMotion1 = m_pMotion[pNowMotion->GetMotion()]->GetKye(pNowMotion->GetKye())->GetPartsData(nCntParts);	// 目標モーション取得
			// 動きを設定
			m_pParts[nCntParts]->SetMoveX(
				pTargetMotion1->GetPosTarget(),	// 位置
				pTargetMotion1->GetRotTarget(),	// 向き
				pTargetMotion1->GetSizTarget(),	// 大きさ
				m_pMotion[pNowMotion->GetMotion()]->GetKye(0)->GetFrame());
		}
		m_pParts[nCntParts]->Update();
	}
}
//============================================
// 描画処理
//============================================
void CObjectMotion::Draw()
{
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (m_pParts[nCntParts] != nullptr)
		{
			int ParentID = m_pParts[nCntParts]->GetParentID();	// 親ID格納用
			// 親がいなかったら
			if (ParentID == -1)
			{
				m_pParts[nCntParts]->SetParentMtx(m_mtxWorld);
			}
			// 親がいたら
			else
			{
				m_pParts[nCntParts]->SetParentMtx(m_pParts[ParentID]->GetMtx());
			}

			m_pParts[nCntParts]->Draw();
		}
	}
}

//============================================
// 読み込み処理
//============================================
bool CObjectMotion::Lode(const char* aFileName)
{
	ifstream file(aFileName);  // 読み込むファイルのパスを指定
	if (file.fail()) {
		cerr << "ファイルを開けませんでした\n";
		return false;
	}
	string str0, str1, str2 , str3;	// 文字列格納用
	string skip;			// スキップ用格納
	string aModelFile[MAX_MOTION_MODEL];	// モデルファイル

	int nCntModel = 0;		// 読み込んだモデル数
	int nCntPartsset0 = 0;	// 読み込んだパーツ数(ベース)
	int nCntPartsset1 = 0;	// 読み込んだパーツ数
	int nCntMotion = 0;		// 読み込んだモーション数
	int nCntKye = 0;		// 読み込んだキー数


	// 抽出演算子>>を使ってデリミタで区切られた単語，値を読み込む
	while (file >> str0)
	{
		// コメントアウト
		if (str0[0] == '#')
		{
			getline(file, skip);	// 一行スキップ
		}
		// モデル数
		else if (str0.compare("NUM_MODEL") == 0)
		{
			file >> skip;	// 一文スキップ
			file >> str1;	// モデル数を取得
			m_nModel = atoi(str1.c_str());
			getline(file, skip);	// 一行スキップ
		}
		// モデルファイル名前
		else if (str0.compare("MODEL_FILENAME") == 0 &&
			nCntModel < m_nModel &&
			m_nModel > 0)
		{
			file >> skip;	// 一文スキップ
			file >> str1;	// モデル名を取得
			aModelFile[nCntModel] = str1;

			nCntModel++;
			getline(file, skip);	// 一行スキップ
		}
		// キャラクター情報
		else if (str0.compare("CHARACTERSET") == 0)
		{
			while (file >> str1 &&
				str1.compare("END_CHARACTERSET") != 0)
			{
				// パーツ数
						// コメントアウト
				if (str1[0] == '#')
				{
					getline(file, skip);	// 一行スキップ
				}
				else if (str1.compare("NUM_PARTS") == 0)
				{
					file >> skip;	// 一文スキップ
					file >> str2;	// モデル名を取得
					m_nParts = atoi(str2.c_str());
					getline(file, skip);	// 一行スキップ
				}
				else if (str1.compare("MOVE") == 0)
				{// 未使用のためスキップ
					getline(file, skip);	// 一行スキップ
				}
				else if (str1.compare("JUMP") == 0)
				{// 未使用のためスキップ
					getline(file, skip);	// 一行スキップ
				}
				else if (str1.compare("RADIUS") == 0)
				{// 未使用のためスキップ
					getline(file, skip);	// 一行スキップ
				}
				else if (str1.compare("HEIGHT") == 0)
				{// 未使用のためスキップ
					getline(file, skip);	// 一行スキップ
				}
				// パーツデータ
				else if (str1.compare("PARTSSET") == 0)
				{
					if (nCntPartsset0 < MAX_PARTS)
					{
						m_pParts[nCntPartsset0] = new CParts(4);
						m_pParts[nCntPartsset0]->Init();
						m_pParts[nCntPartsset0]->SetID(nCntPartsset0);
						while (file >> str2 &&
							str2.compare("END_PARTSSET") != 0)
						{
							// コメントアウト
							if (str2[0] == '#')
							{
								getline(file, skip);	// 一行スキップ
							}
							// モデル名を取得
							else if (str2.compare("INDEX") == 0)
							{
								file >> skip;	// 一文スキップ
								file >> str3;	// モデル名を取得
								int nID = CModelX::Lode(aModelFile[atoi(str3.c_str())].c_str());
								m_pParts[nCntPartsset0]->CObjectX::SetID(nID);

								getline(file, skip);	// 一行スキップ
							}
							else if (str2.compare("PARENT") == 0)
							{
								file >> skip;	// 一文スキップ
								file >> str3;	// モデル名を取得
								int nParentID = atoi(str3.c_str());
								m_pParts[nCntPartsset0]->SetParentID(nParentID);

								getline(file, skip);	// 一行スキップ
							}
							else if (str2.compare("POS") == 0)
							{
								D3DXVECTOR3 pos;// pos 格納用
								file >> skip;	// 一文スキップ
								file >> str3;	// モデル名を取得
								pos.x = stof(str3.c_str());
								file >> str3;	// モデル名を取得
								pos.y = stof(str3.c_str());
								file >> str3;	// モデル名を取得
								pos.z = stof(str3.c_str());
								m_pParts[nCntPartsset0]->SetBasicPos(pos);
								getline(file, skip);	// 一行スキップ
							}
							else if (str2.compare("ROT") == 0)
							{
								D3DXVECTOR3 rot;// rot 格納用
								file >> skip;	// 一文スキップ
								file >> str3;	// モデル名を取得
								rot.x = stof(str3.c_str());
								file >> str3;	// モデル名を取得
								rot.y = stof(str3.c_str());
								file >> str3;	// モデル名を取得
								rot.z = stof(str3.c_str());
								m_pParts[nCntPartsset0]->SetBasicRot(rot);
								getline(file, skip);	// 一行スキップ
							}
							else if (str2.compare("SIZ") == 0)
							{
								D3DXVECTOR3 siz;// siz 格納用
								file >> skip;	// 一文スキップ
								file >> str3;	// モデル名を取得
								siz.x = stof(str3.c_str());
								file >> str3;	// モデル名を取得
								siz.y = stof(str3.c_str());
								file >> str3;	// モデル名を取得
								siz.z = stof(str3.c_str());
								m_pParts[nCntPartsset0]->SetBasicSiz(siz);
								getline(file, skip);	// 一行スキップ
							}
						}
						nCntPartsset0++;
					}
				}
			}
		}
		else if (str0.compare("MOTIONSET") == 0)
		{
			if (nCntMotion < MAX_MOTION)
			{
				creatMotion();
				while (file >> str1 &&
					str1.compare("END_MOTIONSET") != 0)
				{
					// コメントアウト
					if (str1[0] == '#')
					{
						getline(file, skip);	// 一行スキップ
					}
					else if (str1.compare("LOOP") == 0)
					{
						file >> skip;	// 一文スキップ
						file >> str2;	// モデル名を取得
						if (str2.compare("0") == 0)
						{ m_pMotion[nCntMotion]->SetLoop(false); }
						else
						{ m_pMotion[nCntMotion]->SetLoop(true); }
						getline(file, skip);	// 一行スキップ
					}
					else if (str1.compare("NUM_KEY") == 0)
					{
						file >> skip;	// 一文スキップ
						file >> str2;	// モデル名を取得
						m_pMotion[nCntMotion]->SetNumKye(atoi(str2.c_str()));
						getline(file, skip);	// 一行スキップ
					}
					else if (str1.compare("KEYSET") == 0)
					{
						m_pMotion[nCntMotion]->creatKye();
						while (file >> str2 &&
							str2.compare("END_KEYSET") != 0)
						{
							// コメントアウト
							if (str2[0] == '#')
							{
								getline(file, skip);	// 一行スキップ
							}
							else if (str2.compare("FRAME") == 0)
							{
								file >> skip;	// 一文スキップ
								file >> str3;	// フレーム数を取得
								m_pMotion[nCntMotion]->GetKye(nCntKye)->SetFrame(atoi(str3.c_str()));
								getline(file, skip);	// 一行スキップ
							}
							else if (str2.compare("KEY") == 0)
							{
								m_pMotion[nCntMotion]->GetKye(nCntKye)->creatPartsData();
								while (file >> str3 &&
									str3.compare("END_KEY") != 0)
								{
									if (str3[0] == '#')
									{
										getline(file, skip);	// 一行スキップ
									}
									else if (str3.compare("POS") == 0)
									{
										D3DXVECTOR3 pos;// pos 格納用
										file >> skip;	// 一文スキップ
										file >> str3;	// モデル名を取得
										pos.x = stof(str3.c_str());
										file >> str3;	// モデル名を取得
										pos.y = stof(str3.c_str());
										file >> str3;	// モデル名を取得
										pos.z = stof(str3.c_str());
										m_pMotion[nCntMotion]->GetKye(nCntKye)->GetPartsData(nCntPartsset1)->SetPosTarget(pos);
									}
									else if (str3.compare("ROT") == 0)
									{
										D3DXVECTOR3 rot;// pos 格納用
										file >> skip;	// 一文スキップ
										file >> str3;	// モデル名を取得
										rot.x = stof(str3.c_str());
										file >> str3;	// モデル名を取得
										rot.y = stof(str3.c_str());
										file >> str3;	// モデル名を取得
										rot.z = stof(str3.c_str());
										m_pMotion[nCntMotion]->GetKye(nCntKye)->GetPartsData(nCntPartsset1)->SetRotTarget(rot);
									}
									else if (str3.compare("SIZ") == 0)
									{
										D3DXVECTOR3 siz;// pos 格納用
										file >> skip;	// 一文スキップ
										file >> str3;	// モデル名を取得
										siz.x = stof(str3.c_str());
										file >> str3;	// モデル名を取得
										siz.y = stof(str3.c_str());
										file >> str3;	// モデル名を取得
										siz.z = stof(str3.c_str());
										m_pMotion[nCntMotion]->GetKye(nCntKye)->GetPartsData(nCntPartsset1)->SetSizTarget(siz);
									}
								}
								nCntPartsset1++;
							}
						}
						nCntKye++;
						nCntPartsset1 = 0;
					}
				}
				nCntMotion++;
				nCntKye = 0;
			}
		}
	}
	// ファイルを閉じる
	file.close();
	return true;
}
void CObjectMotion::SetMotion(int nMotion)
{
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		CParts* pParts = GetParts(nCnt);

		if (pParts->GetNowMotion()->GetMotion() != nMotion)
		{
			pParts->SetMotion(nMotion);

			CPartsData* pTarget = GetMotion(nMotion)->GetKye(0)->GetPartsData(nCnt);
			pParts->SetMoveX(
				pTarget->GetPosTarget(),	// 位置
				pTarget->GetRotTarget(),	// 向き
				pTarget->GetSizTarget(),
				10);	// 大きさ
		}
	}
}
//============================================
// モーション生成
//============================================
void CObjectMotion::creatMotion()
{
	for (int nCntMotion = 0; nCntMotion < MAX_KYE; nCntMotion++)
	{
		if (m_pMotion[nCntMotion] == nullptr)
		{
			m_pMotion[nCntMotion] = new CMotion;
			return;
		}
	}
}