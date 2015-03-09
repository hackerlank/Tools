/////////////////////////////////////////////
// Mainfrm.h

#ifndef MAINFRM_H
#define MAINFRM_H


#include "View.h"


// Declaration of the CMainFrame class
class CMainFrame : public CFrame
{
public:
	CMainFrame(void);
	virtual ~CMainFrame();

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual int  OnCreate(LPCREATESTRUCT pcs);
	virtual void OnFileExit();
	virtual LRESULT OnFileLoaded(LPCTSTR szFile);
	virtual void OnFileMRU(WPARAM wParam);
	virtual void OnFileNew();
	virtual void OnFileOpen();
	virtual void OnFileSaveAs();
	virtual void SetupToolBar();
	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	CView m_View;
};

#endif //MAINFRM_H
