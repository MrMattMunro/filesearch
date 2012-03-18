// BitmapHelper.cpp: implementation of the CBitmapHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BitmapHelper.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBitmapHelper::CBitmapHelper()
{

}

CBitmapHelper::~CBitmapHelper()
{

}

void CBitmapHelper::SetTransBmp(HDC hDC, HBITMAP bmpImg, int cx, int cy, COLORREF old_color, COLORREF trans_color) 
{ 	
	void* p = SelectObject(hDC, bmpImg);

	for (int x = 0; x < cx; ++x) 
	{ 
		for (int y = 0; y < cy; ++y) 
		{ 
			if (GetPixel(hDC, x,y) == old_color) 
			{
				SetPixel(hDC,  x,y, trans_color); 
			}
		} 
	} 
	
	SelectObject(hDC, p);
}

void CBitmapHelper::ModifyTransBitmap(HBITMAP hMap)
{
	if ( hMap == NULL )
	{
		return;
	}

	HDC hDc = CreateCompatibleDC(NULL);
	COLORREF color = 0;

	// zhw    通过跟踪测试，发现WORD的背景透明色为RGB(236, 233, 216)
	color = RGB(236, 233, 216);

	// 修改位图的透明色，
	SetTransBmp(hDc, hMap, 0x18, 0x18,  RGB(0xff, 0, 0xff), color);
    ::DeleteDC(hDc);
}


HRESULT CBitmapHelper::Put_Invoke(IDispatch *const _pDisp, LPOLESTR _pName, int cArgs, ...)
{
	
	va_list marker;
	va_start(marker, cArgs);
	
	// Extract arguments (if any passed by caller)...
	VARIANT *const _pArgs = new VARIANT[cArgs + 1];
	for (int i = cArgs - 1; i >= 0; i--) {
		memcpy(&_pArgs[i], va_arg(marker, VARIANT*), sizeof(_pArgs[i]));
	}
	
	// End variable-argument section.
	va_end(marker);
	
	// Get DISPID (Dispatch ID) for name passed...
	DISPID dispID;
	HRESULT hr = _pDisp->GetIDsOfNames(IID_NULL, &_pName, 1,
		LOCALE_USER_DEFAULT, &dispID);
	if (FAILED(hr)) {
		return hr;
	}
	
	// Build DISPPARAMS (Dispatch params)
	DISPID dispidNamed = DISPID_PROPERTYPUT;
	DISPPARAMS dp = {_pArgs, &dispidNamed, cArgs, 1};
	
	// Make the call to Dispatch::Invoke()
	CComVariant result;
	hr = _pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT,
		DISPATCH_PROPERTYPUT, &dp, &result, NULL, NULL);
	
	// Free Args allocated with 'new' keyword
	delete [] _pArgs;
	
	return hr;
}


/************************************************************************************
create :  zhw
函数名 ： PutPicture
功能   ： 完成在插件 _CommandBarButton 对象上插入图片
参数 1 ： 为_CommandBarButton对象指针；
参数 2 ： 为位图句柄
*************************************************************************************/
BOOL CBitmapHelper::PutPicture(IDispatch  *const pDisPtch, HBITMAP bBMP)
{
	PICTDESC pdesc = { 0 };
	HRESULT  hr = 0;
	CComPtr<IPictureDisp> pd = NULL;

	if ( pDisPtch == NULL || bBMP == NULL )
	{
		return FALSE;
	}

	pdesc.cbSizeofstruct = sizeof(pdesc);
	pdesc.picType = PICTYPE_BITMAP;
	pdesc.bmp.hbitmap = bBMP;
	
	
    hr = OleCreatePictureIndirect(&pdesc, IID_IPictureDisp, TRUE, (void**)&pd);
	if ( SUCCEEDED( hr ) && (pd != NULL) )
	{
		VARIANT p1 = { 0 };
		p1.vt = VT_DISPATCH;
		p1.pdispVal = pd;

		hr = Put_Invoke(pDisPtch, L"Picture", 1, &p1 );

		if ( FAILED(hr) ) 
		{
			return FALSE;
		}
		return TRUE;
	}
	else
	{

	}
	return FALSE;
}