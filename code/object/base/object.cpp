//============================================
//
// �I�u�W�F�N�g[object.cpp]
// Author:Uedakou
// 
//============================================
#include "object.h"

using namespace std;

//============================================
// �R���X�g���N�^
//============================================

CObject* CObject::m_pTop[MAX_PRIORITY] = {};	// �I�u�W�F�N�g�f�[�^
CObject* CObject::m_pCur[MAX_PRIORITY] = {};	// �I�u�W�F�N�g�f�[�^
int CObject::m_nNumObject[MAX_PRIORITY] = {};	// �K�w���ƃI�u�W�F�N�g��
CObject::CObject()
{
	m_pNext = nullptr;		// ���I�u�W�F�N�g
	m_pPrev = nullptr;		// �O�I�u�W�F�N�g
	m_nNumObject[MAX_PRIORITY]++;	// �I�u�W�F�N�g�����Z
	m_nPriority = MAX_PRIORITY;		// �I�u�W�F�N�g�v���C�I���e�B

	m_type = TYPE_NULL;		// ���;

	// �g�����X�t�H�[��
	m_x = X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_fDistance = 0.0f;

	m_bAllUpdate = true;		// �S�̂ōX�V���邩
	m_bPoseUpdate = false;	// �|�[�Y���X�V���邩
	m_bAllDraw = true;			// �S�̂ŕ`�悷�邩
	m_bPoseDraw = true;		// �|�[�Y���`�悷�邩

	m_bDeath = false;		// �f�X�t���O

	// �擪���Ȃ�������擪�ݒ�
	if (m_pTop[DEFALT_PRIORITY] != nullptr)
	{
		m_pCur[DEFALT_PRIORITY]->m_pNext = this;
		m_pPrev = m_pCur[DEFALT_PRIORITY];
		m_pCur[DEFALT_PRIORITY] = this;
	}
	else
	{
		m_pTop[DEFALT_PRIORITY] = this;
		m_pCur[DEFALT_PRIORITY] = this;
	}
}
CObject::CObject(const int nPriority)
{
	m_pNext = nullptr;		// ���I�u�W�F�N�g
	m_pPrev = nullptr;		// �O�I�u�W�F�N�g
	m_nNumObject[nPriority]++;	// �I�u�W�F�N�g�����Z
	m_nPriority = nPriority;	// �I�u�W�F�N�g�v���C�I���e�B

	m_type = TYPE_NULL;		// ���

	m_bDeath = false;		// �f�X�t���O
	m_bAllUpdate = true;		// �S�̂ōX�V���邩
	m_bPoseUpdate = false;	// �|�[�Y���X�V���邩
	m_bAllDraw = true;			// �S�̂ŕ`�悷�邩
	m_bPoseDraw = true;		// �|�[�Y���`�悷�邩

	// �擪���Ȃ�������擪�ݒ�
	if (m_pTop[nPriority] != nullptr)
	{
		m_pCur[nPriority]->m_pNext = this;
		m_pPrev = m_pCur[nPriority];
		m_pCur[nPriority] = this;
	}
	else
	{
		m_pTop[nPriority] = this;
		m_pCur[nPriority] = this;
	}
}
//============================================
// �f�X�g���N�^
//============================================
CObject::~CObject()
{
	m_nNumObject[m_nPriority]--;
}
//============================================
// �`
//============================================
CObject::TYPE CObject::GetType()
{
	return m_type;
}
//============================================
// �I�u�W�F�N�g���
//============================================
void CObject::Release()
{
	m_bDeath = true;
}
//============================================
// �S�I�u�W�F�N�g���
//============================================
void CObject::ReleaseAll()
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		CObject* pObjact = m_pTop[nCntPriority];
		m_pTop[nCntPriority] = nullptr;
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->GetNext();	//	���ۊ�

			pObjact->Release();

			pObjact = pNext;
		}
		m_pCur[nCntPriority] = nullptr;
	}
}
void CObject::ReleaseDeathFlag()
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		CObject* pObjact = m_pTop[nCntPriority];
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext;	//	���ۊ�
			if (pObjact->m_bDeath == true)
			{// ���S�t���O�������Ă�����
				CObject* pNext = pObjact->m_pNext;	// ���ۊ�
				CObject* pPrev = pObjact->m_pPrev;	// �O�ۊ�
				if (pNext != nullptr)
				{// ���ɑO������
					pNext->SetPrev(pPrev);
				}
				if (pPrev != nullptr)
				{// �O�Ɏ�������
					pPrev->SetNext(pNext);
				}

				if (m_pTop[nCntPriority] == pObjact)
				{
					m_pTop[nCntPriority] = pNext;
				}
				if (m_pCur[nCntPriority] == pObjact)
				{
					m_pCur[nCntPriority] = pPrev;
				}

				pObjact->Uninit();
				delete pObjact;
			}
			pObjact = pNext;
		}
	}
}
//============================================
// �S�I�u�W�F�N�g�X�V
//============================================
void CObject::UpdateAll()
{
	const bool bPose = CManager::GetInstance()->GetSceneManager()->IsPose();
	// ���X�V�t���O�𗧂Ă�
	for (int nCntPriority = MIN_PRIORITY; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{// �v���C�I���e�B���J��Ԃ�
		// �X�V�ς݃t���O���~�낷
		CObject* pObjact = m_pTop[nCntPriority];
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext; //	���ۊ�

#if 1
			if (bPose)
			{
				if (pObjact->IsPoseUpdate())
				{
					pObjact->Update();
				}
			}
			else
			{
				if (pObjact->IsAllUpdate())
				{
					pObjact->Update();
				}
			}

#else
			std::thread th_a(&CObject::Update, pObjact);
			th_a.detach();
#endif
			pObjact = pNext;
		}
	}
	
}
//============================================
// �S�I�u�W�F�N�g�`��
//============================================
void CObject::DrawAll()
{
	const bool bPose = CManager::GetInstance()->GetSceneManager()->IsPose();
	for (int nCntPriority = MIN_PRIORITY; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		CObject* pObjact = m_pTop[nCntPriority];
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext; //	���ۊ�
			if (bPose)
			{
				if (pObjact->IsPoseDraw())
				{
					pObjact->Draw();
				}
			}
			else
			{
				if (pObjact->IsAllDraw())
				{
					pObjact->Draw();
				}
			}



			pObjact = pNext;
		}
	}
}
//============================================
// �I�u�W�F�N�g�擾
//============================================
void CObject::GetAllObject(CObject* object[MAX_PRIORITY])
{
#if 1
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		object[nCnt] = m_pTop[nCnt];
	}
#else
	object = m_pTop;
#endif // 0

}
//============================================
// �\�[�g
//============================================
void CObject::Sort()
{
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		CObject* headUnsorted;	// �O
		CObject* headSorted;	// �擪
		CObject* max;			// ���ɑ傫��
		CObject* prevMax;
		CObject* prevComp;

		//printf("���X�g�������\�[�g���܂�\n");

		headUnsorted = m_pTop[nCnt];    /* ���\�[�g���X�g */
		headSorted = NULL;      /* �\�[�g�σ��X�g */

		while (headUnsorted != NULL) {
			max = headUnsorted;         /* �ő�l�v�f�������� */
			prevMax = NULL;     /* �ő�l�v�f�̑O�̗v�f�������� */
			prevComp = headUnsorted;

			// ���\�[�g���X�g��������𖞂����ő�l��T��
			while (prevComp->m_pNext != NULL) {
				// �����𖞂����ꍇ�̂ݔ�r
				if ((prevComp->m_pNext)->m_type == TYPE::BILLBOARD) {
					// �\�[�g����
					if ((prevComp->m_pNext)->m_fDistance < max->m_fDistance) {
						max = prevComp->m_pNext;         // �ő�l���X�V
						prevMax = prevComp;         // �ő�l�̑O�̗v�f���L�^
					}
				}
				prevComp = prevComp->m_pNext;   // ���̗v�f�ɐi��
			}

			// �ő�l��������Ȃ��ꍇ�A�c��̃��X�g�̓\�[�g�ΏۊO
			if (max == NULL) {//max��NULL�ɂȂ�Ȃ�
				break;
			}

			// �ő�l�𖢃\�[�g���X�g����폜
			if (prevMax == NULL) {
				// �ő�l�����X�g�̐擪�̏ꍇ
				headUnsorted = max->m_pNext;
			}
			else {
				// �ő�l�����X�g���珜�O
				prevMax->m_pNext = max->m_pNext;
			}

			// �ő�l�v�f���\�[�g�σ��X�g�̐擪�ɒǉ�
			if (headSorted == NULL) {
				// �\�[�g�σ��X�g����̏ꍇ
				headSorted = max;
				m_pCur[nCnt] = max;
				max->m_pNext = NULL;
				max->m_pPrev = NULL;
			}
			else {
				// �\�[�g�σ��X�g�̐擪�ɒǉ�
				max->m_pNext = headSorted;
				headSorted->m_pPrev = max;
				max->m_pPrev = NULL;
				headSorted = max;

			}
		}
		m_pTop[nCnt] = headSorted;
	}
}
void CObject::CalculateDistanceToCamera()
{
	CManager* instance = CManager::GetInstance();
	CCamera* pCamera = instance->GetCamera();
	D3DXVECTOR3 pos = pCamera->GetCameraPosR();

	for (int nCntPriority = MIN_PRIORITY; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		CObject* pObjact = m_pTop[nCntPriority];
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext; //	���ۊ�

			pObjact->CalculateDistance(pos);

			pObjact = pNext;
		}
	}
}
void CObject::CalculateDistance(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 diff = m_x.pos - pos;
	m_fDistance = D3DXVec3LengthSq(&diff); // �����̓����v�Z
}
//============================================
// ��ސݒ�
//============================================
void CObject::SetType(TYPE type)
{
	m_type = type;
}