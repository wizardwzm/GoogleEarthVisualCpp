﻿
// GoogleEarthView.cpp: CGoogleEarthView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GoogleEarth.h"
#endif

#include "GoogleEarthDoc.h"
#include "GoogleEarthView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGoogleEarthView

IMPLEMENT_DYNCREATE(CGoogleEarthView, CView)

BEGIN_MESSAGE_MAP(CGoogleEarthView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGoogleEarthView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CGoogleEarthView 생성/소멸

CGoogleEarthView::CGoogleEarthView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGoogleEarthView::~CGoogleEarthView()
{
}

BOOL CGoogleEarthView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGoogleEarthView 그리기

void CGoogleEarthView::OnDraw(CDC* /*pDC*/)
{
	CGoogleEarthDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CGoogleEarthView 인쇄


void CGoogleEarthView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGoogleEarthView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGoogleEarthView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGoogleEarthView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CGoogleEarthView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGoogleEarthView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGoogleEarthView 진단

#ifdef _DEBUG
void CGoogleEarthView::AssertValid() const
{
	CView::AssertValid();
}

void CGoogleEarthView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGoogleEarthDoc* CGoogleEarthView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGoogleEarthDoc)));
	return (CGoogleEarthDoc*)m_pDocument;
}
#endif //_DEBUG


// CGoogleEarthView 메시지 처리기


void CGoogleEarthView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();

	m_hwndGEFrame = (HWND)pMainFrm->m_GE.GetMainHwnd();

	::ShowWindow(m_hwndGEFrame, SW_SHOWMINIMIZED);//! 최소화후 숨겨야 화면에 나타나지 않음
	::ShowWindow(m_hwndGEFrame, SW_HIDE); 

	if (pMainFrm->m_GE.IsInitialized() == S_OK && pMainFrm->m_GE.IsOnline() == S_OK)
	{
		m_hwndGE = (HWND)pMainFrm->m_GE.GetRenderHwnd();

		m_hwndOldParent = ::SetParent(m_hwndGE, m_hWnd);

		//윈도우 사이즈를 View에 딱 맞도록
		CRect rect;
		GetClientRect(rect);

		::SetWindowPos(m_hwndGE, NULL, 0, 0, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
	}
}


void CGoogleEarthView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_hwndGE) ::SetWindowPos(m_hwndGE, NULL, 0, 0, cx, cy, SWP_SHOWWINDOW);
}
