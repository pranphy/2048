#pragma once


#include "Base/Core.h"
#include <GL/glut.h>
#include <string>

//Jan 20, 2017, 23:02:09 
//@pranphy

class OGL2048Stage
{
    private:
        Core A;
        int BlockRow,BlockCol;
        GLuint* Textures;
        void InitializeParameters();
        void ChangeSize(int,int);
        void DrawOne(float,float,GLuint);
        GLuint LoadPhoto(std::string);

        float BlockWidth;
        float BlockHeight;
        float InterBlockGap;
    public:
        OGL2048Stage(int=5,int=5);
        ~OGL2048Stage();
        void StartDrawing();
        void DrawTriangle();
        void DisplayBlocks(int,int);
        void LoadAllImages();
        void ArrowPressed(int);
        void CleanStage();
};
