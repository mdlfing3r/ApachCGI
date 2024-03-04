#pragma once
#include "SimpleHTTPConstruct.h"

std::wstring SimpleHTTPConstruct::SimpleHTTPConstruct::Paragrah(std::wstring attributes, std::wstring content)
{
    std::wstring retString;
    retString = L"\n<p" + (attributes != L"" ? L" " + attributes + L">" : L">") + L"\n" + content + L"\n</p>";
    return retString;
}

std::wstring SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(const std::string& s)
{
    std::wstring retWstr(s.begin(), s.end());
    return retWstr;
}

std::wstring SimpleHTTPConstruct::SimpleHTTPConstruct::Meta(std::wstring attributes)
{
    return L"<meta" + (attributes == L"" ? L">" : L" " + attributes + L" >") + L"\n";
}

std::wstring SimpleHTTPConstruct::SimpleHTTPConstruct::Body(std::wstring attributes, std::wstring content)
{
    return L"<body" + (attributes == L"" ? L">" : L" " + attributes + L" >") + content + L"\n</body>";
}

std::wstring SimpleHTTPConstruct::SimpleHTTPConstruct::Head(std::wstring attributes, std::wstring content)
{
    return L"<head" + (attributes == L"" ? L">" : attributes + L" >") + L"\n" + content + L"\n</head>\n";
}

std::wstring SimpleHTTPConstruct::SimpleHTTPConstruct::HTML(std::wstring attributes, std::wstring content)
{
    return L"\n<html" + (attributes == L"" ? L">" : attributes + L" >") + L"\n" + content + L"\n</html>";
}

std::wstring SimpleHTTPConstruct::SimpleHTTPConstruct::Form(std::wstring  attributes, std::wstring content)
{
    return L"\n<form" + (attributes == L"" ? L">" : L" "+ attributes + L" >") + content + L"</form>";
}

std::wstring SimpleHTTPConstruct::SimpleHTTPConstruct::Select(std::wstring attributes, std::vector<std::wstring> options)
{
    std::wstring options_wstr;
    
    for (auto& it : options) {
        options_wstr += L"<option value =\"" + it + L"\"> " + it + L" </option>\n";
    }


    return L"\n<select" + (attributes == L"" ? L">" : L" " + attributes + L" >") + options_wstr + L"</select>";
}



std::wstring SimpleHTTPConstruct::SimpleHTTPConstruct::AsIs(std::wstring content)
{
    return content;
}

std::wstring SimpleHTTPConstruct::SimpleHTTPConstruct::Img(std::wstring params)
{
    return L"<img " + params + L" >";
}

std::map<std::string, std::string> SimpleHTTPConstruct::SimpleHTTPConstruct::GetCookies() {
	auto res = std::map<std::string, std::string>();
	if (getenv("HTTP_COOKIE")) {
		std::string cookie_string = getenv("HTTP_COOKIE");
		std::string delimiter = "; ";
		std::string name, value;
		size_t pos = 0, pos_ = 0;;
		std::string token;
		while ((pos = cookie_string.find(delimiter)) != std::string::npos) {
			token = cookie_string.substr(0, pos);
			pos_ = token.find("=");
			name = token.substr(0, pos_);
			token.erase(0, pos_ + std::string("=").length());//I suck cocks
			value = token;
			res.emplace(name, value);
			cookie_string.erase(0, pos + delimiter.length());
		}
		token = cookie_string;
		pos_ = token.find("=");
		name = token.substr(0, pos_);
		token.erase(0, pos_ + std::string("=").length());//I suck cocks
		value = token;
		res.emplace(name, value);
	}
	return res;
}

std::wstring SimpleHTTPConstruct::SimpleHTTPConstruct::rawURLDecode(std::wstring raw) {
    int NumCntr = 0,
        TempNum = 0;

    std::wstring loginHex,
        passHex,
        temp,
        retval;
    std::vector<int>AlphasInUint;

    for (size_t it = 0; it < raw.size() + 1; it++) {

        if (raw[it] != '%' && it != raw.size()) {
            temp += raw[it];
        }
        else {
            NumCntr++;
            TempNum += std::stoi(temp, 0, 16);
            if (NumCntr == 2) {
                AlphasInUint.push_back(TempNum);
                TempNum = 0;
                NumCntr = 0;
            }
            temp.clear();
            continue;
        }
    }

    for (auto it = 0; it < AlphasInUint.size(); it++)
    {
        if (AlphasInUint.at(it) >= 352)
            AlphasInUint.at(it) += 688;
        else {
            AlphasInUint.at(it) += 751;

        }
        retval.push_back((AlphasInUint.at(it)));
    }
    return retval;
}