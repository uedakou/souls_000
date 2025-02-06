//============================================
//
// �V�[���ێ��I�u�W�F�N�g[scene_save.cpp]
// Author:Uedakou
// 
//============================================
#include "save_object.h"
//============================================
// �R���X�g
//============================================
CSaveObject::CSaveObject(CObject* object) :
	m_pObject(object)
{
	m_pNext = nullptr;
	m_pPrev = nullptr;
}
//============================================
// �f�X�g��
//============================================
CSaveObject::~CSaveObject()
{
}
//============================================
// ����
//============================================
CSaveObject* CSaveObject::SetList(CSaveObject* pTop, CSaveObject* pCor)
{
	if (pTop == nullptr)
	{
		pTop = this;
	}
	if (pCor == nullptr)
	{
		pCor = this;
	}
	else
	{
		this->m_pPrev = pCor;
		pCor->m_pNext = this;
		pCor = this;
	}
	return this;
}
//============================================
// �폜
//============================================
void CSaveObject::FlagDeath()
{
	CSaveObject* p = m_pNext;
	m_pNext->m_pPrev = m_pPrev;
	m_pPrev->m_pNext = p;
}
