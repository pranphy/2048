#include "wxGUI/DisplayCanvas.h"

const long DisplayCanvas::ID_DisplayCanvas = wxNewId();


BEGIN_EVENT_TABLE(DisplayCanvas,wxGLCanvas)
    EVT_PAINT(DisplayCanvas::OnPaint)
    EVT_KEY_DOWN(DisplayCanvas::OnKeyPress)
END_EVENT_TABLE()


DisplayCanvas::DisplayCanvas(wxWindow*Parent):
    wxGLCanvas(Parent, ID_DisplayCanvas,  wxDefaultPosition, wxSize(150,100),
            0, wxT("GLCanvas")),GameStage()
{
    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
    glutInit(&argc,argv);
    MyContext = new wxGLContext(this);
}

void DisplayCanvas::Initialize()
{
	SetCurrent(*MyContext);
}


void DisplayCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	SetCurrent();
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


GLuint DisplayCanvas::LoadImageFile(std::string FileName)
{
	//wxImage* img = new wxImage(wxString::FromUTF8(FileName.c_str()));
	wxImage* img = new wxImage(wxString::FromUTF8(FileName.c_str()));

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLubyte *bitmapData=img->GetData();
	GLubyte *alphaData=img->GetAlpha();

	int bytesPerPixel = img->HasAlpha() ?  4 : 3;
	int imageWidth = img->GetWidth();
	int imageHeight = img->GetHeight();

	int imageSize = imageWidth * imageHeight * bytesPerPixel;
	GLubyte *imageData=new GLubyte[imageSize];

	int rev_val=imageHeight-1;

	for(int y=0; y<imageHeight; y++)
	{
		for(int x=0; x<imageWidth; x++)
		{
			imageData[(x+y*imageWidth)*bytesPerPixel+0]=
					bitmapData[( x+(rev_val-y)*imageWidth)*3];

			imageData[(x+y*imageWidth)*bytesPerPixel+1]=
					bitmapData[( x+(rev_val-y)*imageWidth)*3 + 1];

			imageData[(x+y*imageWidth)*bytesPerPixel+2]=
					bitmapData[( x+(rev_val-y)*imageWidth)*3 + 2];

			if(bytesPerPixel==4) imageData[(x+y*imageWidth)*bytesPerPixel+3]=
					alphaData[ x+(rev_val-y)*imageWidth ];
		}
	}

	glTexImage2D(GL_TEXTURE_2D,
					0,
					bytesPerPixel,
					imageWidth,
					imageHeight,
					0,
					img->HasAlpha() ?  GL_RGBA : GL_RGB,
					GL_UNSIGNED_BYTE,
					imageData);

	delete[] imageData;
	wxDELETE(img);

	return texture;
}
