//===========================================
// 
// ゲーム全体処理[play.h]
// Auther:UedaKou
// 
//===========================================
#include "play.h"// プレイシーン
namespace Scene {
	class CTitle;
	namespace Game {
		//============================================
		// コンストラクタ
		//============================================
		Play::Play(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData),
			m_nCntMax(30)
		{

			CManager* pManager = CManager::GetInstance();
			CSound* pSound = pManager->GetSound();
			pSound->PlaySoundA(CSound::SOUND_LABEL::SOUND_STAGE000);
			bPause = false;
			m_nCnt = 0;

			m_nNext = Null;
		}
		Play::~Play()
		{
			CManager* pManager = CManager::GetInstance();
			CSound* pSound = pManager->GetSound();
			pSound->StopSound(CSound::SOUND_LABEL::SOUND_STAGE000);


		}

		//============================================
		// 更新
		//============================================
		nsPrev::CBase* Play::Update()
		{
			CInputKeyboard* Kye = CManager::GetInstance()->GetInKey();
			if (Kye->GetTrigger(DIK_P))
			{// ポーズ
				bPause = bPause ? false : true;
			}
			// ポーズ中
			if (bPause)
			{
				if (Kye->GetTrigger(DIK_RETURN))
				{
					return nsPrev::CBase::makeScene<CTitle>();
				}
			}
			else
			{
				CameraController();	// カメラコントロール
				CObject* pObjectTop[MAX_PRIORITY];
				CObject:: GetAllObject(pObjectTop);
				for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
				{
					CObject* pObject = pObjectTop[nCnt];
					while (pObject != nullptr)
					{
						CObject* pNext = pObject->GetNext();
						
						pObject = pNext;
					}

				}
			}
			return this;
		}
		//============================================
		// 描画
		//============================================
		void Play::Draw() const
		{

		}
		
		//============================================
		// ポーズ中取得
		//============================================
		bool Play::IsPose()
		{
			if (bPause == true)
			{
				return true;
			}
			return false;
		}
		//============================================
		// カメラ制御
		//============================================
		void Play::CameraController()
		{
			CCamera* pCamera = CManager::GetInstance()->GetCamera();
			if (pCamera->GetCameraControllreFpllow() == false)
			{
				//CSaveObject* object = m_gameData->GetTop();
				//CSaveObject* Next = nullptr;
				CObject* object[MAX_PRIORITY];
				CObject::GetAllObject(object);
				CObject* Next = nullptr;
				for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
				{
					while (object[nCnt] != nullptr)
					{
						Next = object[nCnt]->GetNext();


						object[nCnt] = Next;
					}			

				}
			}
		}

		//============================================
		// 生成
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<Play>() {
			
			return new Play(this, m_gameData);
		}
	}
}