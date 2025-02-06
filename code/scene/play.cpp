//===========================================
// 
// �Q�[���S�̏���[play.h]
// Auther:UedaKou
// 
//===========================================
#include "play.h"// �v���C�V�[��
namespace Scene {
	class CTitle;
	namespace Game {
		//============================================
		// �R���X�g���N�^
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
		// �X�V
		//============================================
		nsPrev::CBase* Play::Update()
		{
			CInputKeyboard* Kye = CManager::GetInstance()->GetInKey();
			if (Kye->GetTrigger(DIK_P))
			{// �|�[�Y
				bPause = bPause ? false : true;
			}
			// �|�[�Y��
			if (bPause)
			{
				if (Kye->GetTrigger(DIK_RETURN))
				{
					return nsPrev::CBase::makeScene<CTitle>();
				}
			}
			else
			{
				CameraController();	// �J�����R���g���[��
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
		// �`��
		//============================================
		void Play::Draw() const
		{

		}
		
		//============================================
		// �|�[�Y���擾
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
		// �J��������
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
		// ����
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<Play>() {
			
			return new Play(this, m_gameData);
		}
	}
}