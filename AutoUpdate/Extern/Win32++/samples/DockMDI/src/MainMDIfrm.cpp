////////////////////////////////////////////////////
// MainMDIfrm.cpp  - definitions for the CMainMDIFrame class

#include "stdafx.h"
#include "mainMDIfrm.h"
#include "SimpleMDIChild.h"
#include "Files.h"
#include "resource.h"


CMainMDIFrame::CMainMDIFrame()
{
	// Set the registry key name, and load the initial window position
	// Use a registry key name like "CompanyName\\Application"
	LoadRegistrySettings(_T("Win32++\\DockMDI Frame"));
}

CMainMDIFrame::~CMainMDIFrame()
{
}

void CMainMDIFrame::OnFileOpen()
{
	// Bring up the file open dialog
	CFile File;
	CString str = File.OpenFileDialog(0, 0, 0, 0);

	// TODO:
	// Add your own code here. Refer to the tutorial for additional information 
}

void CMainMDIFrame::OnFileSave()
{
	// Bring up the file save dialog.
	CFile File;
	CString str = File.SaveFileDialog(0, 0, 0, 0, 0);

	// TODO:
	// Add your own code here. Refer to the tutorial for additional information 
}

void CMainMDIFrame::OnFilePrint()
{
	// Bring up a dialog to choose the printer
	PRINTDLG pd = {0};
	pd.lStructSize = sizeof( pd );
	pd.Flags = PD_RETURNDC;
	pd.hwndOwner = m_hWnd;

	// Retrieve the printer DC
	PrintDlg( &pd );
	
	// TODO:
	// Add your own code here. Refer to the tutorial for additional information 
}

void CMainMDIFrame::OnInitialUpdate()
{
	TRACE("MDI Frame started \n");
	//The frame is now created.
	//Place any additional startup code here.

	// Add some Dockers to the MDI Frame
	DWORD dwStyle = DS_CLIENTEDGE; // The style added to each docker
	int DockWidth = 150;
	AddDockedChild(new CDockFiles, DS_DOCKED_LEFT | dwStyle, DockWidth);
	AddDockedChild(new CDockFiles, DS_DOCKED_RIGHT | dwStyle, DockWidth);

	// Add some  MDI children
	AddMDIChild(new CSimpleMDIChild);
	AddMDIChild(new CSimpleMDIChild); 
}

BOOL CMainMDIFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDM_FILE_NEW:			OnFileNew();				return TRUE;
	case IDM_FILE_CLOSE:		OnFileClose();				return TRUE;
	case IDM_FILE_OPEN:			OnFileOpen();				return TRUE;
	case IDM_FILE_SAVE:			OnFileSave();				return TRUE;
	case IDM_FILE_SAVEAS:		OnFileSave();				return TRUE;
	case IDM_FILE_PRINT:		OnFilePrint();				return TRUE;
	case IDW_VIEW_STATUSBAR:	OnViewStatusBar();			return TRUE;
	case IDW_VIEW_TOOLBAR:		OnViewToolBar();			return TRUE;
	case IDW_MDI_ARRANGE:		MDIIconArrange();			return TRUE;
	case IDW_MDI_CASCADE:		MDICascade();				return TRUE;
	case IDW_MDI_CLOSEALL:		RemoveAllMDIChildren();		return TRUE;
	case IDW_MDI_TILE:			MDITile();					return TRUE;
	case IDM_FILE_EXIT:			OnFileExit();				return TRUE;
	case IDM_HELP_ABOUT:		OnHelp();					return TRUE;
	default:
		{
			// Pass to active child...
			if (GetActiveMDIChild())
				GetActiveMDIChild()->SendMessage(WM_COMMAND, wParam, lParam);
		}
		break ;
	}
	return FALSE;
}

int CMainMDIFrame::OnCreate(LPCREATESTRUCT pcs)
{
	// OnCreate controls the way the frame is created.
	// Overriding CDockFrame::Oncreate is optional.
	// The default for the following variables is TRUE

	// m_UseIndicatorStatus = FALSE;	// Don't show keyboard indicators in the StatusBar
	// m_UseMenuStatus = FALSE;			// Don't show menu descriptions in the StatusBar
	// m_UseReBar = FALSE;				// Don't use a ReBar
	// m_UseThemes = FALSE;				// Don't use themes
	// m_UseToolBar = FALSE;			// Don't use a ToolBar


	// call the base class function
	return CMDIFrame::OnCreate(pcs);
}

void CMainMDIFrame::OnFileClose()
{
	GetActiveMDIChild()->SendMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
}

void CMainMDIFrame::OnFileExit()
{
	// Issue a close request to the frame
	CMDIFrame::PostMessage(WM_CLOSE);
}

void CMainMDIFrame::OnFileNew()
{
	// Create a new MDI child
	AddMDIChild(new CSimpleMDIChild); 
}

void CMainMDIFrame::SetupToolBar()
{
	// Define the resource IDs for the toolbar
	AddToolBarButton( IDM_FILE_NEW   );
	AddToolBarButton( IDM_FILE_OPEN  );
	AddToolBarButton( IDM_FILE_SAVE  );
	AddToolBarButton( 0 );				// Separator
	AddToolBarButton( IDM_EDIT_CUT   );
	AddToolBarButton( IDM_EDIT_COPY  );
	AddToolBarButton( IDM_EDIT_PASTE );
	AddToolBarButton( 0 );				// Separator
	AddToolBarButton( IDM_FILE_PRINT );
	AddToolBarButton( 0 );				// Separator
	AddToolBarButton( IDM_HELP_ABOUT );
}

LRESULT CMainMDIFrame::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//	switch (uMsg)
//	{
//		Add case statements for each messages to be handled here
//	}

//	pass unhandled messages on for default processing
	return CMDIFrame::WndProcDefault(uMsg, wParam, lParam);
}

