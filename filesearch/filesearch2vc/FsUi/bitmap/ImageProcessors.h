#if !defined(AFX_IMAGEPROCESSORS_H__1FDE0A4E_8AB4_11D6_95AD_EFA89432A428__INCLUDED_)
#define AFX_IMAGEPROCESSORS_H__1FDE0A4E_8AB4_11D6_95AD_EFA89432A428__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "enbitmap.h"

//////////////////////////////////////////////////////////////////////////////////////
// derived image processors

class CImageRotator : public C32BitImageProcessor
{
public:
	CImageRotator(int nDegrees, BOOL bEnableWeighting = TRUE);
	CImageRotator(double dRadians);
	virtual ~CImageRotator();

	virtual CSize CalcDestSize(CSize sizeSrc);
	virtual BOOL ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest);

protected:
	double m_dRadians;
};

class CImageShearer : public C32BitImageProcessor
{
public:
	CImageShearer(int nHorz, int nVert, BOOL bEnableWeighting = TRUE);
	virtual ~CImageShearer();

	virtual CSize CalcDestSize(CSize sizeSrc);
	virtual BOOL ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest);

protected:
	int m_nHorz, m_nVert;
};

class CImageGrayer : public C32BitImageProcessor
{
public:
	CImageGrayer();
	virtual ~CImageGrayer();

	virtual BOOL ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest);
};

class CImageBlurrer : public C32BitImageProcessor
{
public:
	CImageBlurrer(int nAmount = 5); // 1 - 10 (10 is very blurred)
	virtual ~CImageBlurrer();

	virtual BOOL ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest);

protected:
	int m_nAmount;
};

class CImageSharpener : public C32BitImageProcessor
{
public:
	CImageSharpener(int nAmount = 5); // 1 - 10 (10 is very sharp)
	virtual ~CImageSharpener();

	virtual BOOL ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest);

protected:
	int m_nAmount;
};

class CImageResizer : public C32BitImageProcessor
{
public:
	CImageResizer(double dFactor);
	virtual ~CImageResizer();

	virtual CSize CalcDestSize(CSize sizeSrc);
	virtual BOOL ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest);

protected:
	double m_dFactor;

protected:
	BOOL Enlarge(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest);
	BOOL Shrink(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest);
};

class CImageNegator : public C32BitImageProcessor
{
public:
	CImageNegator();
	virtual ~CImageNegator();

	virtual BOOL ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest);
};

class CImageFlipper : public C32BitImageProcessor
{
public:
	CImageFlipper(BOOL bHorz, BOOL bVert = 0); 
	virtual ~CImageFlipper();

	virtual BOOL ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest);

protected:
	BOOL m_bHorz, m_bVert;
};

class CColorReplacer : public C32BitImageProcessor
{
public:
	CColorReplacer(COLORREF crFrom, COLORREF crTo);
	virtual ~CColorReplacer();

	virtual BOOL ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest);

protected:
	COLORREF m_crFrom, m_crTo;
};


#endif