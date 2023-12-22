#define _CRT_SECURE_NO_WARNINGS 



#include "SimpleHTTPConstruct.h"
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <map>
#include "SHA256.h"
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
                AsIs(L"\n<title> login page </title>")
            ) +
            Body(L"align = \"center\"",
                Form(L"METHOD = \"POST\"",
                    AsIs(L"<h1 align = \"center\" > Добавление нового пользователя </h1>\n") +
                    Paragrah(L"align = \"center\"",
                        Paragrah(L"", L"Логин") +
                        AsIs(L"<input name = \"text\"> ") +
                        Paragrah(L"", L"Пароль") +
                        AsIs(L"<input name = \"pass\">")
                    ) +
                    Paragrah(L"align = \"center\"",
                        AsIs(L"<input type = \"submit\"; style=\"background-color: green\"; value = \"Создать\">")
                    )
                )+
                Form(L"METHOD = \"POST\" action = login.cgi",

                    Paragrah(L"align = \"center\"",
                        AsIs(L"<input type = \"submit\"; style=\"background-color: white\"; value = \"к авторизации\">")
                    )
                )+

                Form(L"METHOD = \"POST\" action = MainPage.cgi",
                   
                    Paragrah(L"align = \"center\"",
                        AsIs(L"<input type = \"submit\"; style=\"background-color: Yellow\"; value = \"На главную\">")
                    )
                )
            )
        );
}




std::wstring rawURLDecode(std::wstring raw) {
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


std::wstring StringToWString(const std::string& s)
{
    std::wstring retWstr(s.begin(), s.end());
    return retWstr;
}



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



bool IsPersonExist(std::string Username) {

    const std::string accounts_path = "account.properties";
    std::ifstream ifstr(accounts_path);
    std::string Credential, UserName;

    std::set<std::string>UserNames;

    while (std::getline(ifstr, Credential)) { // пока не достигнут конец файла класть очередную строку в переменную (s)
        UserName = Credential.substr(0, Credential.find(' '));
        UserNames.emplace(UserName);
    }

    std::string NamesStr = "Names: ";
    for (auto& it : UserNames)
        NamesStr += it;

   // std::wcout << HTTP_methoods::Paragrah(L"", StringToWString(NamesStr));

    return (UserNames.find(Username) != UserNames.end());
}


int main() {

    setlocale(LC_ALL, "Russian");
    const std::string accounts_path = "account.properties";

    mainFunc::RunMainFunc();
    std::string body,
        action;
    std::getline(std::cin, body);
    action = getenv("REQUEST_URI");
    
    if (getenv("REQUEST_METHOD") != "GET") {

        IsPersonExist("Name");

        std::string Name,
            Password;

        if (body.find('%') != body.npos)
            std::wcout << HTTP_methoods::Paragrah(L"", L"<font color = \"red\"> <b> Логин и/или пароль содержат недопустимые символы <b> </font>");
        else {
            Name = QueryTo_RawValue("text", body);

            if (!IsPersonExist(Name)) {
                Password = QueryTo_RawValue("pass", body);
                char* cPassword[20];
                for (auto it = 0; it < Password.size(); it++)
                    *(cPassword + it) = &(Password.at(it));//at(it);
                SHA256Crypt CrypthPass(*cPassword);

                std::ofstream ofstr(accounts_path, std::ios::app);
                ofstr << Name << " " << CrypthPass.Crypted << "\n";
                ofstr.close();
            }
            else {
                std::wcout << HTTP_methoods::Paragrah(L"", L"Данное имя уже занято\n");
            }

        }
    };
    return 0;
}
