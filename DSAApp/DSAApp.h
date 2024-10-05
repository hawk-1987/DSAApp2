
// DSAApp.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CDSAAppApp:
// Сведения о реализации этого класса: DSAApp.cpp
//

class CDSAAppApp : public CWinApp
{
public:
	CDSAAppApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDSAAppApp theApp;
