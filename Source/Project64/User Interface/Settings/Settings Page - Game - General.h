#pragma once

#include "../WTL Controls/ModifiedCheckBox.h"
#include <N64 System/N64 Types.h>

class CGameGeneralPage :
	public CSettingsPageImpl<CGameGeneralPage>,
	public CSettingsPage
{

	BEGIN_MSG_MAP_EX(CGameGeneralPage)
		COMMAND_HANDLER_EX(IDC_RDRAM_SIZE,LBN_SELCHANGE,ComboBoxChanged)
		COMMAND_HANDLER_EX(IDC_SAVE_TYPE,LBN_SELCHANGE,ComboBoxChanged)
		COMMAND_HANDLER_EX(IDC_COUNTFACT,LBN_SELCHANGE,ComboBoxChanged)
		COMMAND_ID_HANDLER_EX(IDC_SYNC_AUDIO,CheckBoxChanged)
		COMMAND_ID_HANDLER_EX(IDC_ROM_SPHACK,CheckBoxChanged)
		COMMAND_ID_HANDLER_EX(IDC_ROM_FIXEDAUDIO,CheckBoxChanged)
		COMMAND_ID_HANDLER_EX(IDC_USE_TLB,CheckBoxChanged)
		COMMAND_ID_HANDLER_EX(IDC_DELAY_SI,CheckBoxChanged)
		COMMAND_ID_HANDLER_EX(IDC_AUDIO_SIGNAL,CheckBoxChanged)
	END_MSG_MAP()

	enum { IDD = IDD_Settings_GameGeneral };

public:
	CGameGeneralPage(HWND hParent, const RECT & rcDispay );

	LanguageStringID PageTitle     ( void ) { return TAB_ROMSETTINGS; }
	void             HidePage      ( void );
	void             ShowPage      ( void );
	void             ApplySettings ( bool UpdateScreen );
	bool             EnableReset   ( void );
	void             ResetPage     ( void );

private:
};