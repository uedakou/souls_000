//===========================================
// 
// �t�F�[�h[object_fade.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _FADE_H_
#define _FADE_H_
#include "object_2D.h"	// �I�u�W�F�N�g2D
#include "../../base/manager.h"	// �}�l�[�W���[

class CFade: public CObject2D
{
public:
	typedef enum {
		WHITE_OUT = 0,	// ���h��
		WHITE_IN,
		BLACK_OUT,
		BLACK_IN,
		MAX
	}FADE_TYPE;
	CFade();
	~CFade()		override;
	void Init()	override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
	static CFade* creat(FADE_TYPE type, int nCnt);
private:
	int m_nCnt;
	int m_nCntMax;
	FADE_TYPE m_type;
};




#endif // !_FADE_H_