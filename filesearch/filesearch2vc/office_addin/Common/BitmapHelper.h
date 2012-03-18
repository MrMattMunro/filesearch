// BitmapHelper.h: interface for the CBitmapHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPHELPER_H__B7E45F0A_699F_457E_808F_076EC181B74A__INCLUDED_)
#define AFX_BITMAPHELPER_H__B7E45F0A_699F_457E_808F_076EC181B74A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBitmapHelper  
{
public:
	CBitmapHelper();
	virtual ~CBitmapHelper();

	void ModifyTransBitmap(HBITMAP hMap);
	
	// add zhw	参数：1、为_CommandBarButton对象指针；2、为位图句柄
	BOOL PutPicture( IDispatch  *const pDisPtch, HBITMAP bBMP);
private:
	//trans color
	void SetTransBmp(HDC hDC, HBITMAP bmpImg, int cx, int cy, COLORREF old_color, COLORREF trans_color);
	HRESULT Put_Invoke(IDispatch *const _pDisp, LPOLESTR _pName, int cArgs, ...);
};

#endif // !defined(AFX_BITMAPHELPER_H__B7E45F0A_699F_457E_808F_076EC181B74A__INCLUDED_)
