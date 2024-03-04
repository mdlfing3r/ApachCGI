#define _CRT_SECURE_NO_WARNINGS 



#include "SimpleHTTPConstruct.h"
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <map>
#include "SHA256.h"
#include "string"
#include <list>



class mainFunc : public SimpleHTTPConstruct::SimpleHTTPConstruct {
public:
    static void RunMainFunc(void);
};

#define HTTP_methoods SimpleHTTPConstruct::SimpleHTTPConstruct

//Вернуть RawValue 
std::string QueryTo_RawValue(std::string Name_var, std::string query) {

    std::string retval;
    size_t VarDev_Pos = query.find(Name_var);

    if (VarDev_Pos != std::wstring::npos) {
        std::string tempVar = query.substr(VarDev_Pos + Name_var.size() + 1, query.size());
        retval = tempVar;

        auto DeviderPos = tempVar.find('&');

        if (DeviderPos != std::wstring::npos) {
            retval = tempVar.substr(0, DeviderPos);
        }
    }
    else {
        return "";
    }
    return retval;
}

void mainFunc::RunMainFunc() {

    auto cookie = HTTP_methoods::GetCookies();
    std::string body, Name, Password;
    std::getline(std::cin, body);

    Name = QueryTo_RawValue("text", body);
    Password = QueryTo_RawValue("pass", body);
    std::wcout << L"Set-Cookie: name=" << SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(Name) << std::endl;
    std::wcout << L"Set-Cookie: password=" << SimpleHTTPConstruct::SimpleHTTPConstruct::StringToWString(Password) << std::endl;
    std::wcout << AsIs(L"Content-Type: text/html; charset=windows-1251" + std::wstring(L"\n\n"));

    std::wcout <<
        AsIs(L"<!DOCTYPE HTML>") +
        HTML(L"",
            Head(L"",
                L"<meta encoding = \"windows-1251\">" +
                AsIs(L"\n<title> Авторизация </title>")
            ) +
            Body(L"align = \"center\"",
                Form(L"METHOD = \"POST\" action = AeroPhlot.cgi",
                    AsIs(L"<h1 align = \"center\" > For continue enter your Account data </h1>\n") +
                    Paragrah(L"align = \"center\"",
                        Paragrah(L"", L"Логин") +
                        AsIs(L"<input name = \"login\" value =\"" +
                             StringToWString(cookie["name"] + "\"> ")
                        )+

                        Paragrah(L"", L"Пароль") +
                        AsIs(L"<input name = \"password\" value =\"" +
                             StringToWString(cookie["password"] + "\"> ")   
                        )
                    ) +
                    Paragrah(L"align = \"center\"",
                        AsIs(L"<input type = \"submit\"; style=\"background-color: green\"; value = \"Вход\">")
                    )
                )
            )
        );


}



int main() {
    setlocale(LC_ALL, "Russian");
    mainFunc::RunMainFunc();
    return 0;
}