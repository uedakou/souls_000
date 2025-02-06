//===========================================
// 
// �t�H�O[fog.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _FOG_H_
#define _FOG_H_

class CFog
{
public:
	typedef enum {
		EXP = 0,	// ���x
		LINEAR,		// �͈�
	}FogType;
	CFog();
	~CFog();

	void SetFogType(FogType type);
	void SetFogLinear(float fStart, float fEnd);
	void SetFogDensity(float fDensity);

	static CFog* creat();

private:
	FogType m_type;

	float m_fFogStartPos;	// �t�H�O�J�n�ʒu
	float m_fFogEndPos;		// �t�H�O�I���ʒu

	float m_m_fFogDensity;	// �t�H�O���x
};

#endif // !_FOG_H_