#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>

#include <GL/glut.h>
#include "SOIL/SOIL.h"

#include "Core/Core.h"

using namespace std;

Core A(4,4);

namespace
{
    float WindowHeight=500, WindowWidth=500;
    GLuint Textures[15];
}


void DrawBoundary();
void WhenKeyIsPressed(unsigned char,int,int);
void WhenSpecialKeysPressed(int,int,int);
void TimerFunc(int);
void ControlWithMouse(int,int,int,int);
void StartDrawing();
void ChangeSize(int,int);
void Render();
void Initialize();

void LoadAllImages();
GLuint LoadPhoto(char*);
void DisplayIt(Core);
void DrawOne(float,float,GLuint);



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WindowWidth, WindowHeight);
    glutCreateWindow("2048 V1.0 by pranphy");
    glutReshapeFunc(ChangeSize);
    Initialize(); /*For some activities that should be carried only once in each program execution*/
    glutKeyboardFunc(WhenKeyIsPressed);
    glutMouseFunc(ControlWithMouse);
    glutDisplayFunc(Render);
    glutSpecialFunc(WhenSpecialKeysPressed);
    glutTimerFunc(60, TimerFunc, 0);
    glClearColor(1.0f,1.0f,1.0f,2);
    glutMainLoop();
    return 0;
}



void Initialize()
{
    glEnable(GL_DEPTH_TEST);

    LoadAllImages();
}


void LoadAllImages()
{

	char imgnm[90];
    for(int i=0;i<11;i++)
    {
        sprintf(imgnm,"./res/Files/C%d.png",i+1);
        Textures[i]=LoadPhoto(imgnm);
    }
}

GLuint LoadPhoto(char* Imagename)
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



void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    DisplayIt(A);
    glColor3f(0.0,0.0,1.0);
    glutSwapBuffers();
}


/*The following function is to test the converted coordinates in teh output window  */

void DrawBoundary()
{
    glLoadIdentity();
    glTranslatef(0,0,-.4);
    static float angle=0;
    //angle+=1;
    if(angle>360)
		angle=0;
    glRotatef(angle,0,0,1);
    glColor3f(1.0,1.0,0.0);
    glRectf(1,0,0,1);//down wallll
    //glLoadIdentity();
}


void DisplayIt(Core Kernal)
{
	float InitialX=-0.7,InitialY=0.7;
	static float y=InitialY;
	static float x=InitialX;
	glColor3f(0,1,1);
	glLoadIdentity();
	glTranslatef(0,0,-0.5);
	//glRectf(InitialX,InitialY,x,y);
	y=InitialY;
	x=InitialX;

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

void DrawOne(float PositionX,float PositionY,GLuint Texture)
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



void StartDrawing(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.2, 200.0);
}



void WhenKeyIsPressed(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


void WhenSpecialKeysPressed(int key,int x,int y)
{
    A.Display();

    switch (key)
    {
        case GLUT_KEY_DOWN:
			A.ArrowPressed(DOWN);
            break;
        case GLUT_KEY_LEFT:
			A.ArrowPressed(LEFT);
            break;
        case GLUT_KEY_RIGHT:
			A.ArrowPressed(RIGHT);
            break;
        case GLUT_KEY_UP:
			A.ArrowPressed(UP);
            break;
        default:
            break;
    }
    A.Display();
}


void ControlWithMouse(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)

                break;
        case GLUT_MIDDLE_BUTTON:

            if (state == GLUT_DOWN)

                break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)

                break;
        default:
            break;

    }
    glutPostRedisplay();
}


void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(10, TimerFunc, 0);
}
