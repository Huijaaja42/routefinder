#include "pch.h"
#include "RouteFinderPlugIn.h"

#define MY_PLUGIN_NAME      "RouteFinder"
#define MY_PLUGIN_VERSION   "0.8"
#define MY_PLUGIN_DEVELOPER "Christian Kovanen"
#define MY_PLUGIN_COPYRIGHT "(c)2019"

RouteFinderPlugIn::RouteFinderPlugIn(void) : CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE,
	MY_PLUGIN_NAME,
	MY_PLUGIN_VERSION,
	MY_PLUGIN_DEVELOPER,
	MY_PLUGIN_COPYRIGHT) {

	ifstream t("key.txt");
	_KEY = string ((istreambuf_iterator<char>(t)),
		istreambuf_iterator<char>());
	if (_KEY == "") {
		_Enabled = false;
		DisplayUserMessage("RouteFinder", "ERROR", "KEYFILE ERROR", true, true, false, true, false);
	}
}


RouteFinderPlugIn::~RouteFinderPlugIn() {
}

vector<string> RouteFinderPlugIn::split(string str, string token) {
	vector<string>result;
	while (str.size()) {
		int index = str.find(token);
		if (index != string::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + token.size());
			if (str.size() == 0)result.push_back(str);
		}
		else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}

bool RouteFinderPlugIn::OnCompileCommand(const char* sCommandLine) {
	if (strncmp(sCommandLine, ".route", 4) || !_Enabled)
		return false;
	vector<string> args = split(sCommandLine, " ");
	if (args.size() != 4 || !regex_match(args[1], regex("([A-Z]){4}")) || !regex_match(args[2], regex("([A-Z]){4}")) || !regex_match(args[3], regex("(FL(?=[0-9]*[1-9])[0-9]{1,3})"))) {
		if (args.size() == 2 && FlightPlanSelect(args[1].c_str()).IsValid()) {
			EuroScopePlugIn::CFlightPlan  fp = FlightPlanSelect(args[1].c_str());
			_origin = fp.GetFlightPlanData().GetOrigin();
			_destination = fp.GetFlightPlanData().GetDestination();
			int alt = fp.GetFlightPlanData().GetFinalAltitude() / 100;
			_altitude = "FL" + to_string(alt);
		}
		else {
			if (args.size() == 1 && RadarTargetSelectASEL().IsValid()) {
				EuroScopePlugIn::CFlightPlan  fp = FlightPlanSelect(RadarTargetSelectASEL().GetCallsign());
				_origin = fp.GetFlightPlanData().GetOrigin();
				_destination = fp.GetFlightPlanData().GetDestination();
				int alt = fp.GetFlightPlanData().GetFinalAltitude() / 100;
				_altitude = "FL" + to_string(alt);
			}
			else {
				return false;
			}
		}
	}
	else {
		_origin = args[1];
		_destination = args[2];
		_altitude = args[3];
	}
	thread  th(&RouteFinderPlugIn::getRoute, this);
	th.detach();
	return true;
}

void RouteFinderPlugIn::getRoute() {
	rapidjson::Document json;
	json.SetObject();
	rapidjson::Document::AllocatorType& allocator = json.GetAllocator();
	size_t sz = allocator.Size();
	rapidjson::Value origin(rapidjson::kObjectType);
	origin.SetString( _origin.c_str(), static_cast<rapidjson::SizeType>(_origin.length()), allocator);	
	json.AddMember("ADEP", origin, allocator);
	rapidjson::Value destination(rapidjson::kObjectType);
	destination.SetString(_destination.c_str(), static_cast<rapidjson::SizeType>(_destination.length()), allocator);
	json.AddMember("ADES", destination, allocator);
	rapidjson::Value altitude(rapidjson::kObjectType);
	altitude.SetString( _altitude.c_str(), static_cast<rapidjson::SizeType>(_altitude.length()), allocator);
	json.AddMember("FL", altitude, allocator);
	rapidjson::StringBuffer strbuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(strbuf);
	json.Accept(writer);
	auto r = cpr::Post(cpr::Url{ "144.91.67.59:3600" },
		cpr::Authentication{ "basic", _KEY },
		cpr::Header{ {"Content-Type", "application/json"}, {"User-Agent", "RouteFinder/0.8"} },
		cpr::Body{ {strbuf.GetString()} });
	rapidjson::Document response;
	if (r.text.empty()) {
		DisplayUserMessage("RouteFinder", "ERROR", "Undefined error", true, true, false, true, false);
	}
	else {
		response.Parse(r.text.c_str());
		if (r.status_code >= 400) {
			if (response.HasMember("error")) {
				const char* error = response["error"].GetString();
				DisplayUserMessage("RouteFinder", "ERROR", error, true, true, false, true, false);
			}
			else {
				DisplayUserMessage("RouteFinder", "ERROR", "Undefined error", true, true, false, true, false);
			}
		}
		else {
			const char* route = response["route"].GetString();
			SetClipboardText(route);
			DisplayUserMessage("RouteFinder", "FPL", route, true, true, false, true, false);
		}
	}
}

void RouteFinderPlugIn::SetClipboardText(LPCTSTR pszText) {
	if (OpenClipboard(NULL)) {
		HGLOBAL hMem = GlobalAlloc(GMEM_SHARE | GMEM_MOVEABLE,
			(lstrlen(pszText) + 1) * sizeof(pszText[0]));
		LPTSTR ptxt = (LPTSTR)GlobalLock(hMem);
		lstrcpy(ptxt, pszText);
		GlobalUnlock(hMem);
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
	}
}