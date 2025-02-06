//===========================================
// 
// ƒ^ƒCƒgƒ‹[scene_title.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_
#include "scene_base.h"

namespace Scene {
	class CTitle : public CBase
	{
	public:
		CTitle(CBase* scene);
		virtual ~CTitle();
		virtual CTitle* Update()	override;
		virtual void Draw() const	override;
		bool IsPose()override { return false; }
	private:

	};


}
#endif // !_SCENE_TITLE_H_