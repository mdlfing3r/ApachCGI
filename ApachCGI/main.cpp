#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "SimpleHTTPConstruct.h"
#include <set>


using namespace std;
using namespace SimpleHTTPConstruct;

class mainFunc : public SimpleHTTPConstruct {
public:
    static const std::wstring action(void) {
        if (StringToWString(getenv("REQUEST_METHOD")) != L"") {
            return Paragrah(L"", StringToWString(getenv("QUERY_STRING")) );
        }
    }
    static void RunMainFunc(void) {
        std::wcout << AsIs(L"Content-Type: text/html; charset=utf-8" + std::wstring(L"\n\n"));

        std::wcout <<
            AsIs(L"<!DOCTYPE HTML>") +

            HTML(L"",
                Head(L"",
                    AsIs(L"<title> My First HTML proj </title>")
                ) +
                Body(L"",
                    Paragrah(
                        L"align = \"center\"",
                        AsIs(L"<font color = \"green\" face = \"Comic Sans MS\"> Save the <b>trees!!!<b> </font>")
                    ) +
                    Paragrah(L"align = \"center\" ",
                        Img(L"src = \"http://www.sololearn.com/images/tree.jpg\" alt = \"Can`t load http://www.sololearn.com/images/tree.jpg\"")
                    ) +
                    Form(L"METHOD=\"POST\" action = login.cgi",
                        Paragrah(L"align = \"center\"",
                            AsIs(L"<input type = \"submit\" value=\"By a Tesla for 9999999999$\"  style=\"background: rgb(102, 247, 102); border-radius: 0.1cm; width: 10cm;\" > ")
                            
                        )
                    ) 
                   + action()
                )
            );


                /*                Form(
                                    "action = login.cgi",
                                    Paragrah("",
                                        AsIs("<input name = \"login\"> ") +
                                        AsIs("<input type = \"password\" name = \"pass\">")
                                    ) +
                                    Paragrah("",
                                        AsIs("<input type = \"submit\">")
                                    )
                                )
                            )*/
            

    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    mainFunc::RunMainFunc();
    return -1;
}

