/***************************************************************
 * Name:      wx2048App.h
 * Purpose:   Defines Application Class
 * Author:    Prakash Gautam (pranphy@gmail.com)
 * Created:   2015-05-03
 * Copyright: Prakash Gautam (http://pranphy.com/)
 * License:
 **************************************************************/

#ifndef KITTYWXAPP_H
#define KITTYWXAPP_H

#include <wx/app.h>

class wx2048App : public wxApp
{
public:
	virtual bool OnInit();
};

#endif // KITTYWXAPP_H
