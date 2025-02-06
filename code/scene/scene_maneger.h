//===========================================
// 
// �V�[��[scene.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SECENE_MANEGER_H_
#define _SECENE_MANEGER_H_

#include "scene_base.h"
#include "../scene/common_data.h"	// �V�[���ԃf�[�^�ێ�

namespace Scene {
	class CCommonData;
	class CSceneManager: public CBase
	{
	public:
		CSceneManager();
		CSceneManager(const CSceneManager&) = delete;
		CSceneManager& operator = (const CSceneManager &) = delete;
		~CSceneManager();

		CBase* Update() override;
		void Draw() const override;
		bool IsPose()override;
	private:
		CBase* m_pScene;	// �V�[��
	};

}




#endif // !_SECENE_MANEGER_H_