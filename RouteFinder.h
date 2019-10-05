// RouteFinder.h : main header file for the RouteFinder DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "RouteFinderPlugIn.h"

// CRouteFinderApp
// See RouteFinder.cpp for the implementation of this class
//

class CRouteFinderApp : public CWinApp
{
public:
	CRouteFinderApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
