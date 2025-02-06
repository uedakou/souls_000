//===========================================
// 
// �Q�[���f�[�^�ێ�[game_data.cpp]
// Auther:UedaKou
// 
//===========================================
#include "game_data.h"
// �I�u�W�F�N�g�ۑ�
namespace Scene
{
	namespace Game
	{
		//============================================
		// �R���X�g���N�^
		//============================================
		CGameObjectSave::CGameObjectSave(CObject* object):
			CSaveObject(object)
		{
			m_type = TYPE::Null;
		};
		//============================================
		// �f�X�g���N�^
		//============================================
		CGameObjectSave::~CGameObjectSave()
		{

		}
		//============================================
		//�@����
		//============================================
		CGameObjectSave* CGameObjectSave::crate(CObject* object, TYPE type)
		{
			CGameObjectSave* p = new CGameObjectSave(object);


			p->m_type = type;

			return p;
		}
		//============================================
		// �ۑ�
		//============================================
		CGameObjectSave* CGameData::SaveObject(CGameObjectSave::TYPE type, CObject* object)
		{
			CGameObjectSave* p = CGameObjectSave::crate(object, type);

			p->SetList(m_pTop, m_pCur);

			return p;
		}
		//============================================
		// �擾
		//============================================
		CGameObjectSave* CGameData::GetTop()
		{
			return m_pTop;
		}
		//============================================
		// ���S�t���O�𗧂Ă�
		//============================================
		void CGameData::FlagDeath(CGameObjectSave* pSave)
		{
			pSave->FlagDeath();
			if (m_pTop == pSave)
			{
				m_pTop = pSave->GetNext();
			}
			if (m_pCur == pSave)
			{
				m_pCur = pSave->GetPrev();
			}

		}
		//============================================
		// �S�Ă̎��S�t���O�𗧂Ă�
		//============================================
		void CGameData::AllFlagDeath()
		{
			CGameObjectSave* pObject = m_pTop;
			CGameObjectSave* pNext = nullptr;
			while (pObject != nullptr)
			{
				pNext = pObject->GetNext();

				FlagDeath(pObject);


				pObject = pNext;
			}
			m_pTop = nullptr;
			m_pCur = nullptr;

		}
	}
}