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



void mainFunc::RunMainFunc() {

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
                        AsIs(L"<input name = \"text\"> ") +
                        Paragrah(L"", L"Пароль") +
                        AsIs(L"<input name = \"pass\">")
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