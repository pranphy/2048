/***************************************************************
 * Name:      wx2048App.cpp
 * Purpose:   Code for Application Class
 * Author:    Prakash Gautam (pranphy@gmail.com)
 * Created:   2015-05-03
 * Copyright: Prakash Gautam (http://pranphy.com/)
 * License:
 **************************************************************/

#include "wxGUI/wx2048App.h"
#include "wxGUI/DisplayCanvas.h"
#include "wxGUI/MainFrame.h"
#include <wx/image.h>

IMPLEMENT_APP(wx2048App);

bool wx2048App::OnInit()
{
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        MainFrame* Frame = new MainFrame(0);
        //new DisplayCanvas(Frame);
        Frame->Show();
        SetTopWindow(Frame);
    }
    return wxsOK;
}

