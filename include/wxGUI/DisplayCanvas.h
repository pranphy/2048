#ifndef DISPLAYCANVAS_H
#define DISPLAYCANVAS_H

#include <wx/glcanvas.h>
#include <wx/wx.h>
#include <wx/msgdlg.h>
#include <GL/glut.h>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

#include "SOIL/SOIL.h"

#include "Base/Core.h"
#include "Base/ScoresAndDisplays.h"
#include "Utility/ImageLoader.h"


#define REDBACK    0x34
#define BLUEBACK   0x35
#define MENUMODE   0x36
#define PLAYMODE   0x37



class DisplayCanvas : public wxGLCanvas
{
public:
	DisplayCanvas(wxWindow*);

	void OnPaint       (wxPaintEvent&);
	void DrawTriangle  ();
	void DrawCube      ();


	void   WhenKeyIsPressed           (unsigned char,int,int);
	void   WhenSpecialKeysPressed     (int,int,int);
	void   TimerFunc                  (int);
	void   ControlWithMouse           (int,int,int,int);
	void   StartDrawing               ();
	void   ChangeSize                 (int,int);
	void   Render                     ();
	//void   Initialize                 ();
	void   LoadAllImages              ();
	void   ShuffleCards               ();
	void   DisplayCards               ();
	void Initialize();


protected:
	DECLARE_EVENT_TABLE()
private:


	//int WindowWidth=800, WindowHeight=600;
	static int ActiveCard;
    Core A = Core(4,4);
	GLuint Textures[15];

	wxGLContext* MyContext;


	static const long ID_DisplayCanvas;
	void OnKeyPress(wxKeyEvent&);
	GLuint LoadImageFile(string);
	void DisplaySinglePhoto(float,float,GLuint);
    void DrawOne(float,float,GLuint);
    GLuint LoadPhoto(char*);
};

#endif // DISPLAYCANVAS_H
