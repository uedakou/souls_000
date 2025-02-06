//===========================================
// 
// テキスト[text.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _TEXT_H_
#define _TEXT_H_
#include "object.h"
#include "../../base/pch.h"

class CText :public CObject
{
public:
	typedef enum {
		Terminal = 0,// ターミナル
		Max,
	}Type;	// フォントタイプ
	CText();
	CText(int nPriorithi);
	~CText()	override;
	virtual void Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;
	virtual void Draw() {};
	virtual void Draw(const char* aText) ;
	virtual void Draw(string aText) ;
	void SetData();
	void SetAll(int nH, UINT nW, UINT nBold, UINT nMip, bool bItalic, DWORD nFont, DWORD nSize, DWORD nPitch, Type type);
	void SetHyde(int nHyde) { m_nHyde = nHyde; SetData(); }		// 高さ
	void SetWide(int nWide) { m_nWide = nWide; SetData(); }		// 幅
	void SetBold(int nBold) { m_nBold = nBold; SetData(); }		// 斜体
	void SetMip(int nMip) { m_nMip = nMip; SetData(); }			// ミップマップ
	void SetItalic(bool bItalic) { m_bItalic = bItalic; SetData(); }// 斜体フォント
	void SetFont(UINT nFont) { m_nFont = nFont; SetData(); }	// フォント
	void SetSize(UINT nSize) { m_nSize = nSize; SetData(); }	// 大きさ
	void SetPitch(UINT nPitch) { m_nPitch = nPitch; SetData(); }// ピッチ
	void SetType(Type Type) { m_type = Type; SetData(); }		// 種類
	void SetCol(D3DXCOLOR pCol) { m_pCol = pCol; }				// 色
	void SetSpace(int nSpaceSW, int nSpaceSH, int nSpaceBW, int nSpaceBH) {
		m_nSpaceSW = nSpaceSW;	//領域左
		m_nSpaceSH = nSpaceSH;	//領域上
		m_nSpaceBW = nSpaceBW;	//領域右
		m_nSpaceBH = nSpaceBH;	//領域下
	}


	LPD3DXFONT GetFont();
	static CText* creat();
	static CText* creat(int nHyde, UINT nWide, UINT nBold, UINT nMip, bool bItalic, DWORD nFont, DWORD nSize, DWORD nPitch, Type type);
protected:
	static string m_aFontList[Max];	// フォント名

	int		m_nHyde;	// 文字高さ	
	UINT	m_nWide;	// 文字幅
	UINT	m_nBold;	// 文字太さ
	UINT	m_nMip;		// ミップレベル	
	bool	m_bItalic;	// 文字が斜体か
	DWORD	m_nFont;	// フォント
	DWORD	m_nSize;	// 文字サイズ(変更不可)
	DWORD	m_nPitch;	// ピッチ
	Type	m_type;		// 書体を含む文字列
	string m_aText;		// 描画文字

	int m_nSpaceSW;	//領域左
	int m_nSpaceSH;	//領域上
	int m_nSpaceBW;	//領域右
	int m_nSpaceBH;	//領域下

	D3DXCOLOR m_pCol;	// 色

	LPD3DXFONT m_pFont;// フォントのポインタ
};
#endif // !_TEXT_H_