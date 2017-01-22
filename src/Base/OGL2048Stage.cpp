#include "Base/OGL2048Stage.h"
#include "SOIL/SOIL.h"
#include <cmath>

OGL2048Stage::OGL2048Stage(int Rw,int Cl):A(Rw,Cl),BlockRow(Rw),BlockCol(Cl) { 
    InitializeParameters();
    Textures = new GLuint[BlockRow * BlockCol + 1];
}

OGL2048Stage::~OGL2048Stage() 
{
    delete [] Textures;
}

void OGL2048Stage::InitializeParameters()
{
    BlockWidth = 0.2;
    BlockHeight = 0.2;
    InterBlockGap = 0.05;
}


void OGL2048Stage::DisplayBlocks(int width, int height)
{
    glViewport(0, 0, width, height);
    float InitialX = -(BlockCol/2 * BlockWidth + (BlockCol/2-1)*InterBlockGap); 
    float InitialY =  (BlockRow/2 * BlockHeight + (BlockRow/2-1)*InterBlockGap);
	static float y = InitialY;
	static float x = InitialX;
    float HorizontalIncrement = BlockWidth + InterBlockGap;
    float VerticalIncrement = BlockWidth + InterBlockGap;
	glLoadIdentity();
	glTranslatef(0,0,-0.5);
	//glRectf(InitialX,InitialY,x,y);
	y=InitialY;
	x=InitialX;
    Core & Kernal = A;

	for(int i=0;i<Kernal.Array.Row;i++)
	{
		x=InitialX;
		for(int j=0;j<Kernal.Array.Col;j++)
		{
			int Current=Kernal.Array[i][j];
			if(Current)
			{
				float  Power = (std::log(Current)/std::log(2)) - 1;
				int Index = static_cast<int>(std::ceil(Power));
				DrawOne(x,y,Textures[Index]);
			}
			x += HorizontalIncrement;
		}
		y -= VerticalIncrement;
	}
    glFlush();
}

void OGL2048Stage::LoadAllImages()
{

    char imgnm[90];
    for(int i=0;i<11;i++)
    {
        sprintf(imgnm,"./res/Files/C%d.png",i+1);
        Textures[i]=LoadPhoto(imgnm);
    }

}


GLuint OGL2048Stage::LoadPhoto(char* Imagename)
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

void OGL2048Stage::StartDrawing(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGL2048Stage::CleanStage()
{
    glClearColor(0.0f,0.5f,0.4f,0);
    glClear(GL_COLOR_BUFFER_BIT);
}
void OGL2048Stage::ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.2, 200.0);
}


void OGL2048Stage::DrawOne(float PositionX,float PositionY,GLuint Texture)
{

	glLoadIdentity();
    glTranslatef(PositionX,PositionY,-0.3);
    glBindTexture(GL_TEXTURE_2D,Texture);
    glEnable(GL_TEXTURE_2D);
    float factor=1;
    float IMAGE_LENGTH  = BlockHeight;
    float IMAGE_BREADTH = BlockWidth;
	//glColor3f(1,1,0); //gives overlay color over the texture

	glBegin(GL_QUADS);
        glTexCoord3f(1.0f,0.0f,0.0f); glVertex3f(factor*IMAGE_BREADTH/2,-factor*IMAGE_LENGTH/2,0);
        glTexCoord3f(1.0f,1.0f,0.0f); glVertex3f(factor*IMAGE_BREADTH/2,factor*IMAGE_LENGTH/2,0);
        glTexCoord3f(0.0f,1.0f,0.0f); glVertex3f(-factor*IMAGE_BREADTH/2,factor*IMAGE_LENGTH/2,0);
        glTexCoord3f(0.0f,0.0f,0.0f); glVertex3f(-factor*IMAGE_BREADTH/2,-factor*IMAGE_LENGTH/2,0);
    glEnd();
}

void OGL2048Stage::DrawTriangle()
{
    glPushMatrix();

    int Width = 200, Height = 200;
    glViewport(0, 0, (GLint)Width, (GLint)Height);
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
void OGL2048Stage::ArrowPressed(int Direction)
{
    A.ArrowPressed(Direction);
}
