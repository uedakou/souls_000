//===========================================
// 
// �Z���N�g[title_select.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SAVE_OBJECT_H_
#define _SAVE_OBJECT_H_
#include "object.h"

class CSaveObject
{
public:
	CSaveObject() = delete;
	CSaveObject(CObject* object);
	virtual ~CSaveObject();
	virtual CSaveObject* GetPrev() { return m_pPrev; }
	virtual CSaveObject* GetNext() { return m_pNext; }

	CSaveObject* SetList(CSaveObject* pTop, CSaveObject* pCor);	//�@����
	void FlagDeath();
private:
	CSaveObject* m_pPrev;	// �O
	CSaveObject* m_pNext;	// ��

	CObject* m_pObject;	// �I�u�W�F�N�g
};


#endif // !_SAVE_OBJECT_H_