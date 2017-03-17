/****************************************************************************
*                                                                           *
* Project64 - A Nintendo 64 emulator.                                      *
* http://www.pj64-emu.com/                                                  *
* Copyright (C) 2012 Project64. All rights reserved.                        *
*                                                                           *
* License:                                                                  *
* GNU/GPLv2 http://www.gnu.org/licenses/gpl-2.0.html                        *
*                                                                           *
****************************************************************************/

#pragma once

#include <Project64/UserInterface/resource.h>
#include <Project64/N64System/Debugger/Breakpoints.h>

class CEditReg64 : public CWindowImpl<CEditReg64, CEdit>
{

public:
	//uint64_t GetValue();
	//void SetValue(uint64_t value);

	static uint64_t ParseValue(char* wordPair);
	BOOL Attach(HWND hWndNew);
	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLostFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	uint64_t GetValue();
	void SetValue(uint32_t h, uint32_t l);
	void SetValue(uint64_t value);

	BEGIN_MSG_MAP_EX(CRegEdit64)
		MESSAGE_HANDLER(WM_CHAR, OnChar)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnLostFocus)
	END_MSG_MAP()
};

class CRegisterTabs : public CTabCtrl
{
private:
	vector<int> m_TabIds;
	vector<CWindow> m_TabWindows;
public:
	CWindow AddTab(char* caption, int dialogId, DLGPROC dlgProc);
	void ShowTab(int nPage);
	void ResetTabs();
	CRect GetPageRect();
	void RedrawCurrentTab();
	//LRESULT OnSelChange(NMHDR* lpNMHDR)
	//
	//BEGIN_MSG_MAP_EX(CRegisterTabs)
	//	REFLECTED_NOTIFY_CODE_HANDLER_EX(TCN_SELCHANGE, OnSelChange)
	//	DEFAULT_REFLECTION_HANDLER()
	//END_MSG_MAP()
};


class CCommandsList : public CListViewCtrl
{
public:
	BEGIN_MSG_MAP_EX(CCommandsList)
	END_MSG_MAP()
};

class CEditOp;
class CDebugCommandsView;

class CEditOp : public CWindowImpl<CEditOp, CEdit>
{
private:
	CDebugCommandsView* m_CommandsWindow;

	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (wParam == VK_RETURN || wParam == VK_ESCAPE)
		{
			bHandled = TRUE;
			return 0;
		}
		bHandled = FALSE;
		return 0;
	}
	
	BEGIN_MSG_MAP_EX(CEditOp)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
		MESSAGE_HANDLER(WM_CHAR, OnKeyUp)
	END_MSG_MAP()

public:
	void SetCommandsWindow(CDebugCommandsView* commandsWindow);
	BOOL Attach(HWND hWndNew);
};

class CDebugCommandsView :
	public CDebugDialog<CDebugCommandsView>,
	public CDialogResize<CDebugCommandsView>
{
	friend class CEditOp;

public:
	enum { IDD = IDD_Debugger_Commands };

	CDebugCommandsView(CDebuggerUI * debugger);
	virtual ~CDebugCommandsView(void);

	void ShowAddress(DWORD address, BOOL top);
	void ShowPIRegTab();

	static DWORD GPREditIds[32];
	static DWORD FPREditIds[32];
	static DWORD PIEditIds[13];
	static DWORD COP0EditIds[19];

	static int MapGPREdit(DWORD controlId);
	static int MapFPREdit(DWORD controlId);
	static int MapPIEdit(DWORD controlId);
	static int MapCOP0Edit(DWORD controlId);

	void Reset();

private:

	CBreakpoints* m_Breakpoints;

	CEditReg64 m_TestEdit;

	DWORD m_StartAddress;
	CRect m_DefaultWindowRect;

	CEditNumber m_AddressEdit;
	CCommandsList m_CommandList;
	int m_CommandListRows;
	//CAddBreakpointDlg m_AddBreakpointDlg;
	CListBox m_BreakpointList;
	CScrollBar m_Scrollbar;

	CListViewCtrl m_StackList;

	CRegisterTabs m_RegisterTabs;

	CWindow m_PITab;
	CEditNumber m_PIEdits[13];

	CWindow m_GPRTab;
	CEditReg64 m_GPREdits[32];
	CEditReg64 m_HIEdit;
	CEditReg64 m_LOEdit;
	
	CWindow m_FPRTab;
	CEditNumber m_FPREdits[32];

	CWindow m_COP0Tab;
	CEditNumber m_COP0Edits[24];
	
	bool m_bEditing;
	CEditOp m_OpEdit;
	uint32_t m_SelectedAddress;

	typedef struct {
		uint32_t address;
		uint32_t originalOp;
	} EditedOp;

	vector<EditedOp> m_EditedOps;
	void ClearEditedOps();
	void EditOp(uint32_t address, uint32_t op);
	void RestoreOp(uint32_t address);
	void RestoreAllOps();
	BOOL IsOpEdited(uint32_t address);
	void BeginOpEdit(uint32_t address);
	void EndOpEdit();

	void GotoEnteredAddress();
	void CheckCPUType();
	void RefreshBreakpointList();
	void RemoveSelectedBreakpoints();
	void RefreshRegisterEdits();
	void RefreshStackList();
	
	LRESULT	OnInitDialog         (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT	OnActivate           (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT	OnSizing             (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT	OnGetMinMaxInfo      (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseWheel         (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT	OnScroll             (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT	OnMeasureItem        (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnAddrChanged        (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnListBoxClicked     (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT	OnClicked            (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	
	LRESULT	OnOpKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	LRESULT	OnCommandListClicked(NMHDR* pNMHDR);
	LRESULT	OnCommandListDblClicked(NMHDR* pNMHDR);
	LRESULT	OnCommandListRightClicked (NMHDR* pNMHDR);
	LRESULT OnRegisterTabChange  (NMHDR* pNMHDR);
	LRESULT OnCustomDrawList     (NMHDR* pNMHDR);
	LRESULT OnDestroy            (void);

	// todo fix mousewheel
	// win10 - doesn't work while hovering over list controls
	// win7 - only works while a control has keyboard focus

	BEGIN_MSG_MAP_EX(CDebugCommandsView)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
		MESSAGE_HANDLER(WM_SIZING, OnSizing)
		MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
		MESSAGE_HANDLER(WM_VSCROLL, OnScroll)
		MESSAGE_HANDLER(WM_MEASUREITEM, OnMeasureItem)
		COMMAND_HANDLER(IDC_ADDR_EDIT, EN_CHANGE, OnAddrChanged)
		COMMAND_CODE_HANDLER(LBN_DBLCLK, OnListBoxClicked)
		COMMAND_CODE_HANDLER(BN_CLICKED, OnClicked)
		NOTIFY_HANDLER_EX(IDC_CMD_LIST, NM_CLICK, OnCommandListClicked)
		NOTIFY_HANDLER_EX(IDC_CMD_LIST, NM_DBLCLK, OnCommandListDblClicked)
		NOTIFY_HANDLER_EX(IDC_CMD_LIST, NM_RCLICK, OnCommandListRightClicked)
		NOTIFY_HANDLER_EX(IDC_REG_TABS, TCN_SELCHANGE, OnRegisterTabChange)
		NOTIFY_HANDLER_EX(IDC_CMD_LIST, NM_CUSTOMDRAW, OnCustomDrawList)
		CHAIN_MSG_MAP_MEMBER(m_CommandList)
		MSG_WM_DESTROY(OnDestroy)
		CHAIN_MSG_MAP(CDialogResize<CDebugCommandsView>)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(CDebugCommandsView)
		DLGRESIZE_CONTROL(IDC_GO_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_STEP_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_SKIP_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_ADDR_EDIT, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_SYMBOLS_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_OPCODE_BOX, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_BP_LIST, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_ADDBP_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_RMBP_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_CLEARBP_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_REG_TABS, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_STACK_LIST, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_CMD_LIST, DLSZ_SIZE_X | DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_SCRL_BAR, DLSZ_MOVE_X | DLSZ_SIZE_Y)
	END_DLGRESIZE_MAP()
};

//

