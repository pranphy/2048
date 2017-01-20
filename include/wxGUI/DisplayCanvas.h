#ifndef DISPLAYCANVAS_H
#define DISPLAYCANVAS_H

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <wx/msgdlg.h>
#include <string>


#include "Utility/ImageLoader.h"
#include "Base/OGL2048Stage.h"


class DisplayCanvas : public wxGLCanvas
{
    public:
        DisplayCanvas(wxWindow*);

        void   Initialize();

    protected:
        DECLARE_EVENT_TABLE()
    private:

        wxGLContext* MyContext;

        static const long ID_DisplayCanvas;

        OGL2048Stage GameStage;

        void OnKeyPress        (wxKeyEvent&);
        void OnPaint           (wxPaintEvent&);
        void Render            ();
        GLuint LoadImageFile   (std::string);
};

#endif // DISPLAYCANVAS_H
