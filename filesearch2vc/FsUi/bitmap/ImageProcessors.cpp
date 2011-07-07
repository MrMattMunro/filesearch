// ImageProcessors.cpp: C32BitImageProcessor derivations (c) daniel godson 2002.
//
// credits: Karl Lager's 'A Fast Algorithm for Rotating Bitmaps' 
// 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "imageprocessors.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////
// C32BitImageProcessor derivations

const double PI = 3.14159265358979323846;

CImageRotator::CImageRotator(int nDegrees, BOOL bEnableWeighting)
	: C32BitImageProcessor(bEnableWeighting)
{
	// normalize the angle
	while (nDegrees >= 360)
		nDegrees -= 360;

	while (nDegrees < 0)
		nDegrees += 360;

	ASSERT (nDegrees >= 0 && nDegrees < 360);

	m_dRadians = nDegrees * PI / 180;
}

CImageRotator::CImageRotator(double dRadians)
{
	// normalize the angle
	while (dRadians >= 2 * PI)
		dRadians -= 2 * PI;

	while (dRadians <= 0)
		dRadians += 2 * PI;

	ASSERT (dRadians >= 0 && dRadians < 2 * PI);

	m_dRadians = dRadians;
}

CImageRotator::~CImageRotator()
{
}

CSize CImageRotator::CalcDestSize(CSize sizeSrc)
{
	if (!m_dRadians || !sizeSrc.cx || !sizeSrc.cy)
		return sizeSrc;

	// calculate the four rotated corners
	double dCosA = cos(m_dRadians);
	double dSinA = sin(m_dRadians);

	CPoint ptTopLeft, ptTopRight, ptBottomLeft, ptBottomRight;

	ptTopLeft.x = (int)(-sizeSrc.cx * dCosA / 2 + sizeSrc.cy * dSinA / 2);
	ptTopLeft.y = (int)(sizeSrc.cy * dCosA / 2 - (-sizeSrc.cx) * dSinA / 2);

	ptTopRight.x = (int)(sizeSrc.cx * dCosA / 2 + sizeSrc.cy * dSinA / 2);
	ptTopRight.y = (int)(sizeSrc.cy * dCosA / 2 - sizeSrc.cx * dSinA / 2);

	ptBottomLeft.x = (int)(-sizeSrc.cx * dCosA / 2 + (-sizeSrc.cy) * dSinA / 2);
	ptBottomLeft.y = (int)(-sizeSrc.cy * dCosA / 2 - (-sizeSrc.cx) * dSinA / 2);

	ptBottomRight.x = (int)(sizeSrc.cx * dCosA / 2 + (-sizeSrc.cy) * dSinA / 2);
	ptBottomRight.y = (int)(-sizeSrc.cy * dCosA / 2 - sizeSrc.cx * dSinA / 2);

	// find the max absolute values in each direction
	int nMaxY = max(abs(ptTopLeft.y), max(abs(ptTopRight.y), max(abs(ptBottomLeft.y), abs(ptBottomRight.y))));
	int nMaxX = max(abs(ptTopLeft.x), max(abs(ptTopRight.x), max(abs(ptBottomLeft.x), abs(ptBottomRight.x))));
	
	return CSize((nMaxX + 1) * 2, (nMaxY + 1) * 2);
}

BOOL CImageRotator::ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest)
{
	DWORD dwTick = GetTickCount();
	BOOL bRes = TRUE;

	if (!m_dRadians)
		bRes = C32BitImageProcessor::ProcessPixels(pSrcPixels, sizeSrc, pDestPixels, sizeDest);
	else
	{
		// note: we also need to translate the coords after rotating
		CSize sizeDestOffset(sizeDest.cx / 2 + sizeDest.cx % 2, sizeDest.cy / 2 + sizeDest.cy % 2);
		CSize sizeSrcOffset(sizeSrc.cx / 2 + sizeSrc.cx % 2, sizeSrc.cy / 2 + sizeSrc.cy % 2);

		CRect rSrc(0, 0, sizeSrc.cx - 1, sizeSrc.cy - 1);
		rSrc.OffsetRect(-sizeSrcOffset);

		// note: traversing the src bitmap leads to artifacts in the destination image
		// what we do is to traverse the destination bitmaps and compute the equivalent 
		// source color - credit for this observation goes to Yves Maurer (GDIRotate) 2002
		double dCosA = cos(m_dRadians);
		double dSinA = sin(m_dRadians);

		for (int nY = 0; nY < sizeDest.cy; nY++)
		{
			// calc y components of rotation
			double dCosYComponent = (nY - sizeDestOffset.cy) * dCosA;
			double dSinYComponent = (nY - sizeDestOffset.cy) * dSinA;

			double dSrcX = -sizeDestOffset.cx * dCosA + dSinYComponent;
			double dSrcY = dCosYComponent - (-sizeDestOffset.cx * dSinA);

			for (int nX = 0; nX < sizeDest.cx; nX++)
			{
				dSrcX += dCosA;
				dSrcY -= dSinA;

				CPoint ptSrc((int)dSrcX, (int)dSrcY);
				int nPixel = (nY * sizeDest.cx + nX);

				if (rSrc.PtInRect(ptSrc))
				{
					if (!m_bWeightingEnabled)
					{
						ptSrc.Offset(sizeSrcOffset);
						RGBX* pRGBSrc = &pSrcPixels[ptSrc.y * sizeSrc.cx + ptSrc.x];
						
						pDestPixels[nPixel] = *pRGBSrc;
					}
					else
						pDestPixels[nPixel] = CalcWeightedColor(pSrcPixels, sizeSrc, 
															dSrcX + sizeSrcOffset.cx, dSrcY + sizeSrcOffset.cy);
				}
			}
		}
	}

	TRACE ("CImageRotator::ProcessPixels(radians = %0.03f) took %0.03f seconds\n", 
				m_dRadians, (GetTickCount() - dwTick) / 1000.0f);

	return bRes;
}

///////

CImageShearer::CImageShearer(int nHorz, int nVert, BOOL bEnableWeighting)
	: C32BitImageProcessor(bEnableWeighting), m_nHorz(nHorz), m_nVert(nVert)
{
}

CImageShearer::~CImageShearer()
{
}

CSize CImageShearer::CalcDestSize(CSize sizeSrc)
{
	return CSize(sizeSrc.cx + abs(m_nHorz), sizeSrc.cy + abs(m_nVert));
}

BOOL CImageShearer::ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest)
{
	DWORD dwTick = GetTickCount();
	BOOL bRes = TRUE;

	if (!m_nHorz && !m_nVert)
		bRes = C32BitImageProcessor::ProcessPixels(pSrcPixels, sizeSrc, pDestPixels, sizeDest);
	else
	{
		// shears +ve (down) or -ve (up)
		for (int nX = 0; nX < sizeDest.cx; nX++)
		{
			double dYOffset = 0;

			// calc the offset to src Y coord
			if (m_nVert > 0)
				dYOffset = (double)m_nVert * nX / sizeDest.cx;
				
			else if (m_nVert < 0)
				dYOffset = (double)-m_nVert * (sizeDest.cx - nX) / sizeDest.cx;

			// shears +ve (right) or -ve (left)
			for (int nY = 0; nY < sizeDest.cy; nY++)
			{
				double dXOffset = 0;

				// calc the offset to src X coord
				if (m_nHorz < 0)
					dXOffset = (double)-m_nHorz * nY / sizeDest.cy;
				
				else if (m_nHorz > 0)
					dXOffset = (double)m_nHorz * (sizeDest.cy - nY) / sizeDest.cy;

				double dSrcX = nX - dXOffset;
				double dSrcY = nY - dYOffset;

				if ((int)dSrcX >= 0 && (int)dSrcX < sizeSrc.cx && (int)dSrcY >= 0 && (int)dSrcY < sizeSrc.cy)
				{
					if (!m_bWeightingEnabled)
					{
						RGBX* pRGBSrc = &pSrcPixels[(int)dSrcY * sizeSrc.cx + (int)dSrcX];
						pDestPixels[nY * sizeDest.cx + nX] = *pRGBSrc;
					}
					else
						pDestPixels[nY * sizeDest.cx + nX] = CalcWeightedColor(pSrcPixels, sizeSrc, dSrcX, dSrcY);
				}
			}
		}
	}

	TRACE ("CImageShearer::ProcessPixels(horz = %d, vert = %d) took %0.03f seconds\n", 
				m_nHorz, m_nVert, (GetTickCount() - dwTick) / 1000.0f);

	return bRes;
}

///////

CImageGrayer::CImageGrayer()
{
}

CImageGrayer::~CImageGrayer()
{
}

BOOL CImageGrayer::ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest)
{
	ASSERT (sizeSrc == sizeDest);

	DWORD dwTick = GetTickCount();

	for (int nX = 0; nX < sizeSrc.cx; nX++)
	{
		for (int nY = 0; nY < sizeSrc.cy; nY++)
		{
			RGBX* pRGBSrc = &pSrcPixels[nY * sizeSrc.cx + nX];
			RGBX* pRGBDest = &pDestPixels[nY * sizeSrc.cx + nX];

			*pRGBDest = pRGBSrc->Gray();
		}
	}

	TRACE ("CImageGrayer::ProcessPixels() took %0.03f seconds\n", (GetTickCount() - dwTick) / 1000.0f);

	return TRUE;
}

///////

CImageBlurrer::CImageBlurrer(int nAmount)
{
	m_nAmount = max(0, nAmount);
	m_nAmount = min(m_nAmount, 10);
}

CImageBlurrer::~CImageBlurrer()
{
}

BOOL CImageBlurrer::ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest)
{
	DWORD dwTick = GetTickCount();
	BOOL bRes = TRUE;

	if (m_nAmount == 0)
		bRes = C32BitImageProcessor::ProcessPixels(pSrcPixels, sizeSrc, pDestPixels, sizeDest);
	else
	{
		ASSERT (sizeSrc == sizeDest);

		char cMask[9] = { 1, 1, 1, 
						  1, 5 * (11 - m_nAmount), 1, 
						  1, 1, 1 };

		for (int nX = 0; nX < sizeSrc.cx; nX++)
		{
			for (int nY = 0; nY < sizeSrc.cy; nY++)
			{
				int nRed = 0, nGreen = 0, nBlue = 0, nSubCount = 0, nDivisor = 0;

				for (int nSubX = nX - 1; nSubX <= nX + 1; nSubX++)
				{
					for (int nSubY = nY - 1; nSubY <= nY + 1; nSubY++)
					{
						if (nSubX >= 0 && nSubX < sizeSrc.cx && nSubY >= 0 && nSubY < sizeSrc.cy)
						{
							RGBX* pRGBSub = &pSrcPixels[nSubY * sizeSrc.cx + nSubX];

							nRed += pRGBSub->btRed * cMask[nSubCount];
							nGreen += pRGBSub->btGreen * cMask[nSubCount];
							nBlue += pRGBSub->btBlue * cMask[nSubCount];

							nDivisor += cMask[nSubCount];
						}

						nSubCount++;
					}
				}

				RGBX* pRGBDest = &pDestPixels[nY * sizeDest.cx + nX];

				pRGBDest->btRed = min(255, nRed / nDivisor);
				pRGBDest->btGreen = min(255, nGreen / nDivisor);
				pRGBDest->btBlue = min(255, nBlue / nDivisor);
			}
		}
	}

	TRACE ("CImageBlurrer::ProcessPixels(amount = %d) took %0.03f seconds\n", 
			m_nAmount, (GetTickCount() - dwTick) / 1000.0f);

	return TRUE;
}

///////

CImageSharpener::CImageSharpener(int nAmount)
{
	m_nAmount = max(0, nAmount);
	m_nAmount = min(m_nAmount, 10);
}

CImageSharpener::~CImageSharpener()
{
}

BOOL CImageSharpener::ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest)
{
	DWORD dwTick = GetTickCount();
	BOOL bRes = TRUE;

	if (m_nAmount == 0)
		bRes = C32BitImageProcessor::ProcessPixels(pSrcPixels, sizeSrc, pDestPixels, sizeDest);
	else
	{
		ASSERT (sizeSrc == sizeDest);

		double dMinMaxRatio = (double)1 / (1 + (10 - m_nAmount) * 5);

		double dMaxFactor = 1 / (4 * (1 + dMinMaxRatio));
		double dMinFactor = dMaxFactor * dMinMaxRatio;

		double dMask[9] = { -dMinFactor, -dMaxFactor, -dMinFactor, -dMaxFactor,  2, -dMaxFactor, -dMinFactor, -dMaxFactor, -dMinFactor };

		for (int nX = 0; nX < sizeSrc.cx; nX++)
		{
			for (int nY = 0; nY < sizeSrc.cy; nY++)
			{
				if (nX > 0 && nX < sizeSrc.cx - 1 && nY > 0 && nY < sizeSrc.cy - 1)
				{
					double dRed = 0, dGreen = 0, dBlue = 0, dDivisor = 0;
					int nSubCount = 0;
					
					for (int nSubX = nX - 1; nSubX <= nX + 1; nSubX++)
					{
						for (int nSubY = nY - 1; nSubY <= nY + 1; nSubY++)
						{
							RGBX* pRGBSub = &pSrcPixels[nSubY * sizeSrc.cx + nSubX];
							
							dRed += pRGBSub->btRed * dMask[nSubCount];
							dGreen += pRGBSub->btGreen * dMask[nSubCount];
							dBlue += pRGBSub->btBlue * dMask[nSubCount];
							
							nSubCount++;
						}
					}

					RGBX* pRGBDest = &pDestPixels[nY * sizeDest.cx + nX];
					
					dRed = min(255, dRed);
					dGreen = min(255, dGreen);
					dBlue = min(255, dBlue);
					dRed = max(0, dRed);
					dGreen = max(0, dGreen);
					dBlue = max(0, dBlue);

					pRGBDest->btRed = (int)dRed;
					pRGBDest->btGreen = (int)dGreen;
					pRGBDest->btBlue = (int)dBlue;
				}
				else
				{
					pDestPixels[nY * sizeDest.cx + nX] = pSrcPixels[nY * sizeSrc.cx + nX];
				}
			}
		}
	}

	TRACE ("CImageSharpener::ProcessPixels(amount = %d) took %0.03f seconds\n", 
			m_nAmount, (GetTickCount() - dwTick) / 1000.0f);

	return TRUE;
}

////////

CImageResizer::CImageResizer(double dFactor) : m_dFactor(dFactor)
{
	ASSERT (m_dFactor > 0);

	if (m_dFactor > 1)
		m_bWeightingEnabled = TRUE;
}

CImageResizer::~CImageResizer()
{
}

CSize CImageResizer::CalcDestSize(CSize sizeSrc)
{
	return CSize((int)(sizeSrc.cx * m_dFactor), (int)(sizeSrc.cy * m_dFactor));
}

BOOL CImageResizer::ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest)
{
	DWORD dwTick = GetTickCount();
	BOOL bRes = TRUE;

	if (m_dFactor <= 0)
		return FALSE;

	if (m_dFactor == 1)
		bRes = C32BitImageProcessor::ProcessPixels(pSrcPixels, sizeSrc, pDestPixels, sizeDest);

	else if (m_dFactor > 1)
		bRes = Enlarge(pSrcPixels, sizeSrc, pDestPixels, sizeDest);

	else
		bRes = Shrink(pSrcPixels, sizeSrc, pDestPixels, sizeDest);

	TRACE ("CImageResizer::ProcessPixels(factor = %0.03f) took %0.03f seconds\n", 
			m_dFactor, (GetTickCount() - dwTick) / 1000.0f);

	return TRUE;
}

BOOL CImageResizer::Enlarge(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest)
{
	ASSERT (m_dFactor > 1);

	if (m_dFactor <= 1)
		return FALSE;

	double dFactor = 1 / m_dFactor;
	double dXSrc = 0;

	for (int nX = 0; nX < sizeDest.cx; nX++)
	{
		double dYSrc = 0;

		for (int nY = 0; nY < sizeDest.cy; nY++)
		{
			pDestPixels[nY * sizeDest.cx + nX] = CalcWeightedColor(pSrcPixels, sizeSrc, dXSrc, dYSrc);

			dYSrc += dFactor; // next dest pixel in source coords
		}

		dXSrc += dFactor; // next dest pixel in source coords
	}

	return TRUE;
}

BOOL CImageResizer::Shrink(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest)
{
	ASSERT (m_dFactor < 1 && m_dFactor > 0);

	if (m_dFactor >= 1 || m_dFactor <= 0)
		return FALSE;

	double dFactor = 1 / m_dFactor;
	double dXEnd = -dFactor / 2;
	int nXStart, nXEnd = -1;

	for (int nX = 0; nX < sizeDest.cx; nX++)
	{
		int nYStart, nYEnd = -1;
		double dYEnd = -dFactor / 2;

		nXStart = nXEnd + 1;
		dXEnd += dFactor;
		nXEnd = min(sizeSrc.cx - 1, (int)dXEnd + 1);

		if (nXStart > nXEnd)
			continue;

		for (int nY = 0; nY < sizeDest.cy; nY++)
		{
			nYStart = nYEnd + 1;
			dYEnd += dFactor;
			nYEnd = min(sizeSrc.cy - 1, (int)dYEnd + 1);

			if (nYStart > nYEnd)
				continue;

			int nCount = 0, nRed = 0, nGreen = 0, nBlue = 0;

			// average the pixels over the range
			for (int nXSub = nXStart; nXSub <= nXEnd; nXSub++)
			{
				for (int nYSub = nYStart; nYSub <= nYEnd; nYSub++)
				{
					RGBX* pRGBSrc = &pSrcPixels[nYSub * sizeSrc.cx + nXSub];

					nRed += pRGBSrc->btRed;
					nGreen += pRGBSrc->btGreen;
					nBlue += pRGBSrc->btBlue;
					nCount++;
				}
			}

			RGBX* pRGBDest = &pDestPixels[nY * sizeDest.cx + nX];

			pRGBDest->btRed = nRed / nCount;
			pRGBDest->btGreen = nGreen / nCount;
			pRGBDest->btBlue = nBlue / nCount;
		}
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////

CImageNegator::CImageNegator()
{
}

CImageNegator::~CImageNegator()
{
}

BOOL CImageNegator::ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest)
{
	ASSERT (sizeSrc == sizeDest);

	DWORD dwTick = GetTickCount();

	for (int nX = 0; nX < sizeSrc.cx; nX++)
	{
		for (int nY = 0; nY < sizeSrc.cy; nY++)
		{
			RGBX* pRGBSrc = &pSrcPixels[nY * sizeSrc.cx + nX];
			RGBX* pRGBDest = &pDestPixels[nY * sizeSrc.cx + nX];

			pRGBDest->btRed = 255 - pRGBSrc->btRed;
			pRGBDest->btGreen = 255 - pRGBSrc->btGreen;
			pRGBDest->btBlue = 255 - pRGBSrc->btBlue;
		}
	}

	TRACE ("CImageNegator::ProcessPixels() took %0.03f seconds\n", (GetTickCount() - dwTick) / 1000.0f);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////

CImageFlipper::CImageFlipper(BOOL bHorz, BOOL bVert) : m_bHorz(bHorz), m_bVert(bVert)
{
}

CImageFlipper::~CImageFlipper()
{
}

BOOL CImageFlipper::ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest)
{
	ASSERT (sizeSrc == sizeDest);

	DWORD dwTick = GetTickCount();

	for (int nX = 0; nX < sizeSrc.cx; nX++)
	{
		int nDestX = m_bHorz ? sizeDest.cx - nX - 1 : nX;

		for (int nY = 0; nY < sizeSrc.cy; nY++)
		{
			RGBX* pRGBSrc = &pSrcPixels[nY * sizeSrc.cx + nX];

			int nDestY = m_bVert ? sizeDest.cy - nY - 1 : nY;
			RGBX* pRGBDest = &pDestPixels[nDestY * sizeDest.cx + nDestX];

			*pRGBDest = *pRGBSrc;
		}
	}

	TRACE ("CImageFlipper::ProcessPixels(horz = %d, vert = %d) took %0.03f seconds\n", 
			m_bHorz ? 1 : 0, m_bVert ? 1 : 0, (GetTickCount() - dwTick) / 1000.0f);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////

CColorReplacer::CColorReplacer(COLORREF crFrom, COLORREF crTo) : m_crFrom(crFrom), m_crTo(crTo)
{
}

CColorReplacer::~CColorReplacer()
{
}

BOOL CColorReplacer::ProcessPixels(RGBX* pSrcPixels, CSize sizeSrc, RGBX* pDestPixels, CSize sizeDest)
{
	DWORD dwTick = GetTickCount();
	BOOL bRes = TRUE;

	if (m_crFrom == m_crTo)
		bRes = C32BitImageProcessor::ProcessPixels(pSrcPixels, sizeSrc, pDestPixels, sizeDest);
	else
	{
		RGBX rgbFrom(m_crFrom), rgbTo(m_crTo);

		for (int nX = 0; nX < sizeSrc.cx; nX++)
		{
			for (int nY = 0; nY < sizeSrc.cy; nY++)
			{
				RGBX* pRGBSrc = &pSrcPixels[nY * sizeSrc.cx + nX];
				RGBX* pRGBDest = &pDestPixels[nY * sizeDest.cx + nX];

				if (pRGBSrc->Equals(rgbFrom))
					*pRGBDest = rgbTo;
				else
					*pRGBDest = *pRGBSrc;
			}
		}
	}

	TRACE ("CColorReplacer::ProcessPixels(from = %06x, to = %06x) took %0.03f seconds\n", 
			m_crFrom, m_crTo, (GetTickCount() - dwTick) / 1000.0f);

	return bRes;
}

//////////////////////////////////////////////////////////////////////

