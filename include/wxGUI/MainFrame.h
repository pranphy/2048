/***************************************************************
 * Name:      MainFrame.h
 * Purpose:   Defines Application Frame
 * Author:    Prakash Gautam (pranphy@gmail.com)
 * Created:   2015-05-03
 * Copyright: Prakash Gautam (http://pranphy.com/)
 * License:
 **************************************************************/

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "wxGUI/DisplayCanvas.h"

//(*Headers(MainFrame)
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/gbsizer.h>
#include <wx/stattext.h>
#include <wx/aui/aui.h>
#include <wx/textctrl.h>
//*)

class MainFrame: public wxFrame
{
public:

	MainFrame(wxWindow* parent,wxWindowID id = -1);
	virtual ~MainFrame();

private:

	//(*Handlers(MainFrame)
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	//*)

	//(*Identifiers(MainFrame)
	static const long ID_GamePanel;
	static const long ID_PlayerNameSText;
	static const long ID_TEXTCTRL1;
	static const long ID_STATICTEXT1;
	static const long ID_COMBOBOX1;
	static const long ID_STATICTEXT2;
	static const long ID_TEXTCTRL2;
	static const long ID_PANEL2;
	static const long ID_AboutHelpSubItem;
	//*)

	//(*Declarations(MainFrame)
	wxMenuItem* MenuItem1;
	wxStaticText* PlayerNameSText;
	wxMenu* Menu1;
	wxPanel* GamePanel;
	wxStaticText* StaticText1;
	wxPanel* Panel2;
	wxComboBox* ComboBox1;
	wxTextCtrl* TextCtrl1;
	wxMenuBar* MenuBar1;
	wxStaticText* StaticText2;
	wxAuiManager* AuiManager1;
	wxTextCtrl* TextCtrl2;
	//*)
	DisplayCanvas* GameCanvas;

	DECLARE_EVENT_TABLE()
};

#endif // MAINFRAME_H
