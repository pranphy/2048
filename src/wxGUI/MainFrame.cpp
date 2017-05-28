/***************************************************************
 * Name:      MainFrame.cpp
 * Purpose:   Code for Application Frame
 * Author:    Prakash Gautam (pranphy@gmail.com)
 * Created:   2015-05-03
 * Copyright: Prakash Gautam (http://pgautam.com.np/)
 * License:
 **************************************************************/

#include "wxGUI/MainFrame.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(MainFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)


//(*IdInit(MainFrame)
const long MainFrame::ID_GamePanel = wxNewId();
const long MainFrame::ID_PlayerNameSText = wxNewId();
const long MainFrame::ID_TEXTCTRL1 = wxNewId();
const long MainFrame::ID_PANEL2 = wxNewId();
const long MainFrame::ID_AboutHelpSubItem = wxNewId();
//*)

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow* parent,wxWindowID id)
{


    Create(parent, id, _("Welcome Game 17.01.0.2"), wxDefaultPosition, 
            wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));

    SetClientSize(wxSize(400,439));
    SetMinSize(wxSize(400,300));

    OnlyAuiManager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);

    CreateGamePanel();
    CreateInfoPanel();

    OnlyAuiManager->AddPane(GamePanel, wxAuiPaneInfo().Name(_T("PaneName")).
            CenterPane().Caption(_("Game Play Area")).CaptionVisible().Row(1));


    OnlyAuiManager->AddPane(InfoPanel, wxAuiPaneInfo().Name(_T("PaneName")).
            DefaultPane().Caption(_("Game Controls")).CaptionVisible().Position(-2).
            Left().MinSize(wxSize(180,0)));

    OnlyAuiManager->Update();
    CreateMenuBar();
    GameCanvas->Initialize();
}

void MainFrame::CreateInfoPanel()
{

    wxStaticBoxSizer* StaticBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    InfoPanel = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, 
            wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    InfoPanel->SetMinSize(wxSize(180,0));
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, InfoPanel, _("Controls"));

    PlayerNameSText = new wxStaticText(InfoPanel, ID_PlayerNameSText, _("Player Name"), 
            wxDefaultPosition, wxDefaultSize, 0, _T("ID_PlayerNameSText"));

    PlayerNameTCtrl = new wxTextCtrl(InfoPanel, ID_TEXTCTRL1, _("Text"), wxDefaultPosition, 
            wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));


    FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);

    FlexGridSizer1->Add(PlayerNameSText, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(PlayerNameTCtrl, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(FlexGridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    InfoPanel->SetSizer(StaticBoxSizer1);
    StaticBoxSizer1->Fit(InfoPanel);
    StaticBoxSizer1->SetSizeHints(InfoPanel);
    
}
void MainFrame::CreateMenuBar()
{
    OnlyMenuBar = new wxMenuBar();
    HelpMenu = new wxMenu();
    AboutMItem = new wxMenuItem(HelpMenu, ID_AboutHelpSubItem, _("About\tCtrl+H"), 
            _("Show fetails of this application"), wxITEM_NORMAL);
    HelpMenu->Append(AboutMItem);
    OnlyMenuBar->Append(HelpMenu, _("Help"));
    SetMenuBar(OnlyMenuBar);
}

void  MainFrame::CreateGamePanel()
{

    wxGridBagSizer* GameGBSizer;
    GameGBSizer = new wxGridBagSizer(0, 0);
    GameGBSizer->AddGrowableCol(0);
    GameGBSizer->AddGrowableRow(0);


    GamePanel = new wxPanel(this,ID_GamePanel, wxDefaultPosition, wxDefaultSize, 
            wxTAB_TRAVERSAL,_T("ID_GamePanel"));
    wxStaticBoxSizer* GameSBSizer = new wxStaticBoxSizer(wxHORIZONTAL, GamePanel, "Move Cards");
    
    GameGBSizer->Add(GameSBSizer,wxGBPosition(0,0),wxDefaultSpan, 
            wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL,5);

    GamePanel->SetSizer(GameGBSizer);
    GameGBSizer->Fit(GamePanel);
    GameGBSizer->SetSizeHints(GamePanel);
    wxGLAttributes dispAttrs;
    dispAttrs.PlatformDefaults().DoubleBuffer().EndList();
    GameCanvas = new DisplayCanvas(GamePanel);
    GameSBSizer->Add(GameCanvas,1, 
            wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL,5);
}

MainFrame::~MainFrame()
{
    //(*Destroy(MainFrame)
    //*)
}

void MainFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxT("This is a message ");
    wxMessageBox(msg, _("Welcome to..."));
}

