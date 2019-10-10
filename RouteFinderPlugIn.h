#pragma once

#include <string>
#include <Windows.h>
#include <iostream>
#include <regex>
#include <fstream>
#include <thread>
#include <cpr/cpr.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <windows.data.json.h>
#include "./lib/include/EuroScopePlugIn.h"
#include "RouteFinder.h"

using namespace std;

class RouteFinderPlugIn :
	public EuroScopePlugIn::CPlugIn
{
public:
	RouteFinderPlugIn();
	virtual ~RouteFinderPlugIn();

	inline virtual bool OnCompileCommand(const char* sCommandLine);

	inline virtual vector<string> split(string str, string token);

	inline virtual void SetClipboardText(LPCTSTR pszText);

	inline virtual void getRoute();
private:
	bool _Enabled = true;
	string _KEY;
	string _origin;
	string _destination;
	string _altitude;
};

