#include "wxGUI/DisplayCanvas.h"
#include <wx/msgdlg.h>

const long DisplayCanvas::ID_DisplayCanvas = wxNewId();


BEGIN_EVENT_TABLE(DisplayCanvas,wxGLCanvas)
    EVT_PAINT(DisplayCanvas::OnPaint)
    EVT_KEY_DOWN(DisplayCanvas::OnKeyPress)
END_EVENT_TABLE()


DisplayCanvas::DisplayCanvas(wxWindow*Parent):
    wxGLCanvas(Parent),
    GameStage()
{
    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
    glutInit(&argc,argv);
    MyContext = new wxGLContext(this);
 }

void DisplayCanvas::Initialize()
{


    if(MyContext->IsOK())
        wxMessageBox("I am ok ","I am ok");
    else
        wxMessageBox("Alas I am not ok ");

}


void DisplayCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    SetCurrent(*MyContext);

	static bool OneTime = false;
	if(OneTime == false)
	{
        GameStage.LoadAllImages();
		OneTime = true;
	}
    GameStage.CleanStage();
    Render();
}

void DisplayCanvas::OnKeyPress(wxKeyEvent& event)
{
    //wxMessageBox(wxT(" You pressed a key "),wxT("Bravoo "));

    int Key = event.GetUnicodeKey();
    if(Key == 13)
    {
        //wxMessageBox(wxT(" You pressed enter "),wxT(" Ain't that great ??"));
    }
	else if(Key == 'r' or Key == 'R')
	{
		//BackId = (BackId ? 0 : 1);
	}
    switch(event.GetKeyCode())
    {
    case WXK_LEFT:
        GameStage.ArrowPressed(LEFT);
        break;
    case WXK_RIGHT:
        GameStage.ArrowPressed(RIGHT);
        break;
    case WXK_UP:
        GameStage.ArrowPressed(UP);
        break;
    case WXK_DOWN:
        GameStage.ArrowPressed(DOWN);
        break;
    default:
        break;

    }
    wxPaintEvent Dummy = wxPaintEvent();
    OnPaint(Dummy);
}


void DisplayCanvas::Render()
{

    GameStage.DisplayBlocks(GetSize().x,GetSize().y);
    
    SwapBuffers();
}

