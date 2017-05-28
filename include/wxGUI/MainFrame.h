/***************************************************************
 * Name:      GameWxMain.h
 * Purpose:   Defines Application Frame
 * Author:    Prakash Gautam (pranphy@gmail.com)
 * Created:   2015-05-03
 * Copyright: Prakash Gautam (http://pranphy.com/)
 * License:
 **************************************************************/

#ifndef KITTYWXMAIN_H
#define KITTYWXMAIN_H

#include "wxGUI/DisplayCanvas.h"

#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/gbsizer.h>
#include <wx/stattext.h>
#include <wx/aui/aui.h>
#include <wx/textctrl.h>

class MainFrame: public wxFrame
{
public:

	MainFrame(wxWindow* parent,wxWindowID id = -1);
	virtual ~MainFrame();

private:

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	static const long ID_GamePanel;
	static const long ID_PlayerNameSText;
	static const long ID_TEXTCTRL1;
	static const long ID_PANEL2;
	static const long ID_AboutHelpSubItem;

	wxMenuBar* OnlyMenuBar;
	wxMenu* HelpMenu;
	wxMenuItem* AboutMItem;

	wxAuiManager* OnlyAuiManager;
	wxPanel* GamePanel;
	wxPanel* InfoPanel;

	wxStaticText* PlayerNameSText;
    wxTextCtrl* PlayerNameTCtrl;

	DisplayCanvas* GameCanvas;
    void CreateGamePanel();
    void CreateMenuBar();
    void CreateInfoPanel();

	DECLARE_EVENT_TABLE()
};

#endif // KITTYWXMAIN_H

