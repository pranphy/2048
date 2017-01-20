#pragma once


#include "Base/Core.h"
#include <GL/glut.h>

//Jan 20, 2017, 23:02:09 
//@pranphy

class OGL2048Stage
{
    private:
        Core A;
        int Row,Col;
        GLuint Textures[15];
        void ChangeSize(int,int);
    public:
        OGL2048Stage(int=4,int=4);
        ~OGL2048Stage();
        void StartDrawing();
        void DrawTriangle();
        void DisplayBlocks(int,int);
        void DrawOne(float,float,GLuint);
        void LoadAllImages();
        GLuint LoadPhoto(char*);
        void ArrowPressed(int);
        void CleanStage();
};
