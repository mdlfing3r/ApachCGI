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


    static uint8_t AunthSt;

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
                )+
                Body(L"align = \"center\"", L"<br> <br> <br>")
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

    //DEPRECATED Methods

#if 0
    //UTF-8  application/x-www-form-urlencoded


    std::wstring OLDDecodeRAWstring(const std::wstring& rawstr) {

        if (rawstr.find('%') != rawstr.npos) {
            std::wstring loginHex,
                passHex,
                temp;
            std::wstring retval = L"";
            std::vector<std::wstring> tempcontainer;
            std::vector<int>AlphasInUint;

            int NumCntr = 0,
                TempNum = 0;



            size_t SubstrDev = rawstr.find('&');

            if (rawstr.find('&') != std::wstring::npos) {
                passHex = rawstr.substr(SubstrDev + 1, rawstr.size() - SubstrDev - 1);
                passHex = passHex.substr(passHex.find('%') + 1, passHex.size() - 1);
                tempcontainer.push_back(passHex);
            }
            else {
                SubstrDev = rawstr.size();
            }
            loginHex = rawstr.substr(0, SubstrDev);
            loginHex = loginHex.substr(loginHex.find('%') + 1, loginHex.size() - loginHex.find('%'));
            tempcontainer.push_back(loginHex);


            for (auto& input_wstring : tempcontainer) {

                TempNum = 0;
                NumCntr = 0;
                temp.clear();

                for (size_t it = 0; it < loginHex.size() + 1; it++) {

                    if (input_wstring[it] != '%' && it != input_wstring.size()) {
                        temp += input_wstring[it];
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
                AlphasInUint.clear();
            }
            return retval;
        }
        else {
            return rawstr;
        }
    }
#endif

#if 0 
    std::wstring QueryTo_RawValue(std::wstring Name_var, std::wstring query) {

        std::wstring var;
        size_t SubstrDev = query.find(Name_var);

        if (SubstrDev != std::wstring::npos) {
            std::wstring tempVar = query.substr(SubstrDev + Name_var.size() + 1, query.size());
            var = tempVar;

            auto DeviderPos = tempVar.find('&');

            if (DeviderPos != std::wstring::npos) {
                var = tempVar.substr(0, DeviderPos);
            }
        }
        else {
            return L"";
        }
        return var;
    }
#endif

#if 0
    std::wstring DecodeRAWstring(const std::wstring& rawstr) {

        std::wstring temp,
            tempWStr;

        for (size_t it = 1; it < rawstr.size() + 1; it++) {
            if (rawstr[it] != '%' && it != rawstr.size()) {
                temp += rawstr[it];
            }
            else {
                tempWStr.push_back(std::stoi(temp, 0, 16) + 848);
                temp.clear();
                continue;
            }
        }

        std::wstring RV = tempWStr;
        return RV;
    }
#endif




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


    void CreateNewAccount() {
        std::wcout << 
            HTTP_methoods::Form(L"METHOD = \"POST\" action = UserRegistration.cgi",

                HTTP_methoods::Paragrah(L"align = \"center\"",
                    HTTP_methoods::AsIs(L"<input type = \"submit\"; style=\"background-color: Yellow\"; value = \"Зарегистрировать нового пользователя\">")
                )
            );
    }

    bool AuthService(std::pair<std::string, std::string> AuthDATa) {

        bool AllowLogging = false;

        std::string credentials;
        std::map<std::string, std::string> credentialVector;

        const std::string accounts_path = "account.properties";
        std::ifstream ifstr(accounts_path);

        if (!ifstr) {
            std::wcout << L"Конфигурационный файл не существует<br>";

            //Создаем файл с AuthDATa внутри
            std::ofstream ofstr(accounts_path);
            ofstr << AuthDATa.first << " " << AuthDATa.second << "\n";
            ofstr.close();
            AllowLogging = true;
        }
        else {

            if (ifstr.is_open())
            {
                while (std::getline(ifstr, credentials))
                {
                    if (credentials != "") {
                        size_t spaceSymb = credentials.find(" ");
                        credentialVector.emplace(credentials.substr(0, spaceSymb), credentials.substr(spaceSymb + 1, credentials.size() - spaceSymb));
                        credentials.clear();
                    }
                }
            }


            ifstr.close();
            if (!credentials.size()) {
                auto t = credentialVector.find(AuthDATa.first);
                if (credentialVector.find(AuthDATa.first) != credentialVector.end()) {


                    if (credentialVector.at(AuthDATa.first) == AuthDATa.second) {
                        AllowLogging = true;

                        std::wcout << HTTP_methoods::AsIs(L"<p style=\"color: green\";> Добро пожаловать!, для продолжения нажмите клавишу ПРОДОЛЖИТЬ </p>") <<

                            HTTP_methoods::Paragrah(L"align = \"center\"",
                                HTTP_methoods::Form(L"METHOD = \"POST\" action = FlightParams.cgi",
                                        HTTP_methoods::AsIs(L"<input type = \"submit\"; style=\"background-color: green\"; value = \"ПРОДОЛЖИТЬ\">")));
                    }
                    else 
                        std::wcout << L"Некорректный пароль";
                }
                else {
                    std::wcout << L"НЕ НАЙДЕН ПОЛЬЗОВАТЕЛЬ С ТАКИМИ ДАННЫМИ\n";
                    CreateNewAccount();
                    }
            }
        }
        return AllowLogging;     
    }




    int main() {


        setlocale(LC_ALL, "Russian");
        mainFunc::RunMainFunc();
        std::string body,
                    action;
        std::getline(std::cin, body);
        action = getenv("REQUEST_URI");

        if (getenv("REQUEST_METHOD") != "GET" && action == "/cgi-bin/login.cgi") {

            std::string Name,
                        Password;

            char* cPassword[20];


            if (body.find('%') != body.npos)
                std::wcout << HTTP_methoods::Paragrah(L"", L"<font color = \"red\"> <b> Логин и/или пароль содержат недопустимые символы <b> </font>");
            else {
                Name = QueryTo_RawValue("text", body);
                Password = QueryTo_RawValue("pass", body);


                for (auto it = 0; it < Password.size(); it++) 
                    *(cPassword + it) = &(Password.at(it));

                SHA256Crypt CrypthPass(*cPassword);

                if (AuthService(std::make_pair(Name, CrypthPass.Crypted))) {
                   // mainFunc::RunMainFunc();
                }
            }
        };
        return 0;
    }
