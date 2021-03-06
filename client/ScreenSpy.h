// ScreenSpy.h: interface for the CScreenSpy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENSPY_H__5F74528D_9ABD_404E_84D2_06C96A0615F4__INCLUDED_)
#define AFX_SCREENSPY_H__5F74528D_9ABD_404E_84D2_06C96A0615F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define ALGORITHM_DIFF 1
#define COPY_ALL 1	// 拷贝全部屏幕，不分块拷贝（added by yuanyuanxiang 2019-1-7）
#include "CursorInfo.h"


class CScreenSpy  
{
public:
	CScreenSpy(ULONG ulbiBitCount);
	virtual ~CScreenSpy();

	ULONG GetBISize() const
	{
		ULONG	ColorNum = m_ulbiBitCount <= 8 ? 1 << m_ulbiBitCount : 0;

		return sizeof(BITMAPINFOHEADER) + (ColorNum * sizeof(RGBQUAD));
	}

	const LPBITMAPINFO& GetBIData() const
	{
		return m_BitmapInfor_Full;
	}

	ULONG  m_ulbiBitCount;
	LPBITMAPINFO m_BitmapInfor_Full;
	ULONG  m_ulFullWidth, m_ulFullHeight;               //屏幕的分辨率
	LPBITMAPINFO ConstructBI(ULONG ulbiBitCount, 
		ULONG ulFullWidth, ULONG ulFullHeight);

	HWND m_hDeskTopWnd;      //当前工作区的窗口句柄
	HDC  m_hFullDC;          //Explorer.exe 的窗口设备DC
	HDC  m_hFullMemDC;
	HBITMAP	m_BitmapHandle;
	PVOID   m_BitmapData_Full;
	DWORD  m_dwBitBltRop;
	LPVOID GetFirstScreenData();

	ULONG GetFirstScreenLength() const
	{
		return m_BitmapInfor_Full->bmiHeader.biSizeImage;
	}

	LPVOID GetNextScreenData(ULONG* ulNextSendLength);
	BYTE* m_RectBuffer;
	ULONG m_RectBufferOffset;
	BYTE   m_bAlgorithm;

	FORCEINLINE VOID WriteRectBuffer(LPBYTE szBuffer,ULONG ulLength)
	{
		memcpy(m_RectBuffer + m_RectBufferOffset, szBuffer, ulLength);   
		m_RectBufferOffset += ulLength;
	}

	CCursorInfo m_CursorInfor;
	HDC  m_hDiffMemDC;
	HBITMAP	m_DiffBitmapHandle;
	PVOID   m_DiffBitmapData_Full;
	ULONG CompareBitmap(LPBYTE CompareSourData, LPBYTE CompareDestData, 
		LPBYTE szBuffer, DWORD ulCompareLength);
	VOID ScanScreen(HDC hdcDest, HDC hdcSour, ULONG ulWidth, ULONG ulHeight);
	bool m_bZoomed;			// 屏幕被缩放
	double m_wZoom, m_hZoom; // 屏幕缩放比例
};

#endif // !defined(AFX_SCREENSPY_H__5F74528D_9ABD_404E_84D2_06C96A0615F4__INCLUDED_)
