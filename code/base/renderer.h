//===========================================
// 
// �����_���[[renderer.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _RCNDRERE_H_
#define _RCNDRERE_H_
#include "main.h"

#define B_SORT true

class CText;
// �����_���[
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND nWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	void DrawFPS(void);
	LPDIRECT3DDEVICE9 GetDevice();
private:
	LPDIRECT3D9 m_pD3D;				// Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Direct3D�f�o�C�X

	CText* m_pText;
};

#endif // !_RCNDRERE_H_
