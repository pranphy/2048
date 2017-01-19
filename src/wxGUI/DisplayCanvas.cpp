#include "wxGUI/DisplayCanvas.h"

const long DisplayCanvas::ID_DisplayCanvas = wxNewId();
int DisplayCanvas::ActiveCard = -1;



BEGIN_EVENT_TABLE(DisplayCanvas,wxGLCanvas)
    EVT_PAINT(DisplayCanvas::OnPaint)
    EVT_KEY_DOWN(DisplayCanvas::OnKeyPress)
END_EVENT_TABLE()


DisplayCanvas::DisplayCanvas(wxWindow*Parent):
    wxGLCanvas(Parent, ID_DisplayCanvas,  wxDefaultPosition, wxSize(150,100),
            0, wxT("GLCanvas"))
{
    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
    glutInit(&argc,argv);
    MyContext = new wxGLContext(this);
    //Scrambled = true;
}

void DisplayCanvas::Initialize()
{
	SetCurrent(*MyContext);
	//LoadAllImages();
	//ShuffleCards();
}


void DisplayCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	SetCurrent();
	static bool OneTime = false;
	if(OneTime == false)
	{
		LoadAllImages();
		//ShuffleCards();
		OneTime = true;
	}
    glClearColor(0.0f,0.5f,0.4f,0);
    glClear(GL_COLOR_BUFFER_BIT);
    //DrawTriangle();
    Render();
    glFlush();
    SwapBuffers();
}

void DisplayCanvas::OnKeyPress(wxKeyEvent& event)
{
    //wxMessageBox(wxT(" You pressed a key "),wxT("Bravoo "));

    int Key = event.GetUnicodeKey();
    if(Key == 13)
    {
        //wxMessageBox(wxT(" You pressed enter "),wxT(" Ain't that great ??"));
        //ShuffleCards();
        //Scrambled = true;
    }
	else if(Key == 'r' or Key == 'R')
	{
		//BackId = (BackId ? 0 : 1);
	}
    switch(event.GetKeyCode())
    {
    case WXK_LEFT:
        A.ArrowPressed(LEFT);
        break;
    case WXK_RIGHT:
        A.ArrowPressed(RIGHT);
        break;
    case WXK_UP:
        A.ArrowPressed(UP);
        break;
    case WXK_DOWN:
        A.ArrowPressed(DOWN);
        break;
    default:
        break;

    }
    wxPaintEvent Dummy = wxPaintEvent();
    OnPaint(Dummy);
}


void DisplayCanvas::DrawTriangle()
{
    glPushMatrix();

    glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
        glColor3ub((GLubyte)255,(GLubyte)0,(GLubyte)0);
        glVertex3f(0.0f,0.5f,0.0f);
        // Green on the right bottom corner
        glColor3ub((GLubyte)0,(GLubyte)255,(GLubyte)0);
        glVertex3f(0.50f,-0.90f,0.0f);
        // Blue on the left bottom corner
        glColor3ub((GLubyte)0,(GLubyte)0,(GLubyte)255);
        glVertex3f(-0.50f, -0.9000f, -0.0f);
    glEnd();
    glColor3ub((GLubyte)255,(GLubyte)255,(GLubyte)255); //reset white color.
    glPopMatrix();
}


void DisplayCanvas::DisplayCards()
{

    glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
    float InitialX=-0.7,InitialY=0.7;
	static float y=InitialY;
	static float x=InitialX;
	glColor3f(0,1,1);
	glLoadIdentity();
	glTranslatef(0,0,-0.5);
	//glRectf(InitialX,InitialY,x,y);
	y=InitialY;
	x=InitialX;
    Core & Kernal  = A;

	for(int i=0;i<Kernal.Array.Row;i++)
	{
		x=InitialX;
		for(int j=0;j<Kernal.Array.Col;j++)
		{
			int Current=Kernal.Array[i][j];
			if(Current)
			{
				float  Power = (log(Current)/log(2)) - 1;
				int Index = static_cast<int>(ceil(Power));
				DrawOne(x,y,Textures[Index]);
			}
			x+=.4;
		}
		y-=.4;
	}


}
void DisplayCanvas::DrawOne(float PositionX,float PositionY,GLuint Texture)
{

	glLoadIdentity();
    glTranslatef(PositionX,PositionY,-0.3);
    glBindTexture(GL_TEXTURE_2D,Texture);
    glEnable(GL_TEXTURE_2D);
    float factor=1;
    float IMAGE_LENGTH=.3;
    float IMAGE_BREADTH=.3;
	glColor3f(1,1,0);

	glBegin(GL_QUADS);
        glTexCoord3f(1.0f,0.0f,0.0f); glVertex3f(factor*IMAGE_BREADTH/2,-factor*IMAGE_LENGTH/2,0);
        glTexCoord3f(1.0f,1.0f,0.0f); glVertex3f(factor*IMAGE_BREADTH/2,factor*IMAGE_LENGTH/2,0);
        glTexCoord3f(0.0f,1.0f,0.0f); glVertex3f(-factor*IMAGE_BREADTH/2,factor*IMAGE_LENGTH/2,0);
        glTexCoord3f(0.0f,0.0f,0.0f); glVertex3f(-factor*IMAGE_BREADTH/2,-factor*IMAGE_LENGTH/2,0);
    glEnd();
}


void DisplayCanvas::LoadAllImages()
{

    char imgnm[90];
    for(int i=0;i<11;i++)
    {
        sprintf(imgnm,"./res/Files/C%d.png",i+1);
        Textures[i]=LoadPhoto(imgnm);
    }

}

GLuint DisplayCanvas::LoadPhoto(char* Imagename)
{
    cout<< " Searching for >>  "<<Imagename;
    GLuint tex_2d = SOIL_load_OGL_texture
    (
        Imagename,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(!tex_2d)
        cout<< " NotFound "<<endl;
    else
        cout<<" Found. Load Success"<<endl;
    //cls();
    return tex_2d;

}


void DisplayCanvas::Render()
{

    DisplayCards();
    //DrawTriangle();
    //Image[i] =
    //GLuint OneImage = LoadImageFile(string("./Files/AllCards/Ascending/C41.png"));
    //cout<<" While OneImage has "<<OneImage<<endl;
    //DisplaySinglePhoto(0,0,OneImage);

    glPushMatrix();
    ostringstream Info;
    if(ActiveCard>-1)
        Info<<" Selected Card :- "<<ActiveCard+1;
    else
        Info<<"Press 1 through  9 to select corresponding card ";
    //glColor3f(0.0,0.8,1.0);
    //Cout(const_cast<char*>(Info.str().c_str()),-.8,0,0); //Printing function
    glPopMatrix();

}

void DisplayCanvas::DisplaySinglePhoto(float PositionX, float PositionY, GLuint ImageTexture)
{
	glPushMatrix();
    //glLoadIdentity();
    //glColor3f(1.0,1.0,1.0);
    //cout<<" Printing card "; if(CardTexture){ cout<<" Texture not null "<<endl;} else { cout<<" Texture null "<<endl;}

	float PictureWidth = 100;
	float PictureHeight = 300;
	float Factor = 0.002;

    glTranslatef(PositionX,PositionY,0);
    glRotatef(0,0,0,1);
    glBindTexture(GL_TEXTURE_2D,ImageTexture);

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glTexCoord3f(1.0f,0.0f,0.0f);   glVertex3f(Factor*PictureWidth/2,-Factor*PictureHeight/2,0);
        glTexCoord3f(1.0f,1.0f,0.0f);   glVertex3f(Factor*PictureWidth/2,Factor*PictureHeight/2,0);
        glTexCoord3f(0.0f,1.0f,0.0f);   glVertex3f(-Factor*PictureWidth/2,Factor*PictureHeight/2,0);
        glTexCoord3f(0.0f,0.0f,0.0f);   glVertex3f(-Factor*PictureWidth/2,-Factor*PictureHeight/2,0);
    glEnd();
    glPopMatrix();
}

void DisplayCanvas::StartDrawing(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DisplayCanvas::ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.2, 200.0);
}


void DisplayCanvas::TimerFunc(int value)
{
    glutPostRedisplay();
    //glutTimerFunc(10, TimerFunc, 0);
}


void DisplayCanvas::DrawCube()
{
	//
}

GLuint DisplayCanvas::LoadImageFile(string FileName)
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
