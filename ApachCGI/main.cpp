#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "SimpleHTTPConstruct.h"
#include <set>


using namespace std;
using namespace SimpleHTTPConstruct;

class mainFunc : public SimpleHTTPConstruct {
public:
    static const std::string action(void) {
        if (StringToWString(getenv("REQUEST_METHOD")) != "") {
            return Paragrah("", StringToWString(getenv("QUERY_STRING")) );
        }
    }

    static void RunMainFunc(void) {
        std::cout << AsIs("Content-Type: text/html; charset=utf-8" + std::string("\n\n"));

        std::cout <<
            AsIs("<!DOCTYPE HTML>") +

            HTML("",
                Head("",
                    AsIs("<title> S14 airlines </title>")
                ) +
                Body("",
                    Paragrah(
                        "align = \"center\"",
                        AsIs("<font color = \"green\" face = \"Comic Sans MS\"> Save the <b>trees!!!<b> </font>")
                    ) +
                    Paragrah("align = \"center\" ",
                        Img("src = \"https://upload.wikimedia.org/wikipedia/commons/thumb/8/82/VQ-BEI_%286919052100%29.jpg/1200px-VQ-BEI_%286919052100%29.jpg\" alt = \"Can`t load airplane image\" width = \"500\"")
                    ) +
                    Form("METHOD=\"POST\" action = Autorization.cgi",
                        Paragrah("align = \"center\"",
                            AsIs("<input type = \"submit\" value=\"By a Fli-Ticket for lowest price\"  style=\"background: rgb(102, 247, 102); border-radius: 0.1cm; width: 10cm;\" > ")
                            
                        )
                    ) 
                   + action()
                )
            );
    }
};

int main()
{
    mainFunc::RunMainFunc();
    return -1;
}

