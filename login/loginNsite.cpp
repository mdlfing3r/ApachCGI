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
#include "WebLogger.h"
#include <fstream>



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

        std::wcout << AsIs(L"Content-Type: text/html; charset=windows-1251" + std::wstring(L"\n\n"));

        std::wcout <<
            AsIs(L"<!DOCTYPE HTML>\n") +
            AsIs(L"<HTML>\n") +
                AsIs(L"<meta encoding = \"windows-1251\">" +
                    AsIs(L"\n<title> Авторизация </title>")
                )+
                AsIs(L"\n<body align = \"center\">\n <br> <br> <br>\n");
    }


    void siteLogicRun(std::string input) {

        std::wcout << HTTP_methoods::AsIs(L"<h1 align = \"center\"> AeroPhlot tickets </h1>");


        /*std::wcout << HTTP_methoods::Paragrah(L"align = \"center\"", 
                HTTP_methoods::Form(L"METHOD = \"POST\" action = AeroPhlot.cgi", 
                    HTTP_methoods::Paragrah(L"", L"Город вылета<br>") +
                        HTTP_methoods::Select(L"name=\"Departure\"", { L"Moscow", L"Samara", L"Krasnoyarsk", L"Ulyanovsk", L"Saint-Peterburg", L"Rostov-na-Donu", L"Volgograd", L"Sochi", L"Kazan", L"Saratov", L"Novosibirsk" })+L"<br>" +
                    HTTP_methoods::Paragrah(L"", L"Город прилета<br>") +
                        HTTP_methoods::Select(L"name=\"Arrive\"", { L"Moscow", L"Samara", L"Krasnoyarsk", L"Ulyanovsk", L"Saint-Peterburg", L"Rostov-na-Donu", L"Volgograd", L"Sochi", L"Kazan", L"Saratov", L"Novosibirsk" }) + L"\n<br>\n<br>\n" +
                   L"<input type = \"submit\"; style=\"background-color: green\"; value = \"выбрать время\">")
        );*/

        std::wcout << HTTP_methoods::Paragrah(L"align = \"center\"",
             L"<br> <b> Для подтверждения личности загрузите следующие файлы : </b> " +
            HTTP_methoods::Form(L"enctype =\"multipart/form-data\" method = \"POST\" action = /cgi-bin/AeroPhlot.cgi ",
                HTTP_methoods::AsIs(L"<label align = \"left\" for=\"ProfilePic\"> Фото для профиля:   <\label>") +
                HTTP_methoods::AsIs(L"\n<input type = \"file\" id = \"ProfilePic\" name = \"ProfilePic\" accept=\"image/jpeg\"> <br><br>") +

                HTTP_methoods::AsIs(L"<label align = \"left\" for=\"VoiceRec\"> Образец голоса:    <\label>") +
                HTTP_methoods::AsIs(L"\n<input type = \"file\" id = \"VoiceRec\" name = \"VoiceRec\" accept = \"audio/*\"> <br><br>") +

                HTTP_methoods::AsIs(L"<label align = \"left\" for=\"VideoRec\"> Образец видео с вами:    <\label>") +
                HTTP_methoods::AsIs(L"\n<input type = \"file\" id = \"VideoRec\" name = \"VideoRec\" accept=\"video/*\"> <br><br>") +

                HTTP_methoods::AsIs(L"<label align = \"left\" for=\"PersonalDocument\"> Сканы всех страниц паспорта в формате pdf:    <\label>") +
                HTTP_methoods::AsIs(L"\n<input type = \"file\" id = \"PersonalDocument\" name = \"PersonalDocument\" accept=\"application/pdf\"> <br><br><br>") +

                HTTP_methoods::AsIs(L"<label align = \"left\" for=\"Archive\"> Если по какой-либо причине файл/ы не получается загрузить,<br> отправьте их архивом воспользовавшись кнопкой снизу:<br><\label>") +
                HTTP_methoods::AsIs(L"\n<input type = \"file\" id = \"Archive\" name = \"Archive\" accept=\"application/zip, application/x-gzip\"> <br>") +


                HTTP_methoods::AsIs(L"\n<br><br>\n <input type = \"submit\"; style=\"width: 10cm; height: 1cm\"; value = \"Загрузить\">\n")    
            )
        );

        std::wcout <<
            HTTP_methoods::AsIs(L"\n</body>\n<\HTML>");
            /// L"<select id = \"fruits\" name = \"fruits\"> <option value = \"apple\"> Яблоко </option> <option value = \"banana\"> Банан </option> <option value = \"orange\"> Апельсин </option> </select>");
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
                if (credentialVector.find(AuthDATa.first) != credentialVector.end()) {
                    if (credentialVector.at(AuthDATa.first) == AuthDATa.second) {
                        AllowLogging = true;
                        siteLogicRun(AuthDATa.first);
                    }
                    else {
                        std::wcout << HTTP_methoods::Paragrah(L"align = \"center\"", L"Некорректный пароль" +
                                HTTP_methoods::Form(L"METHOD = \"POST\" action = Autorization.cgi",
                                    HTTP_methoods::AsIs(L"<input type = \"submit\"; style=\"background-color: red\"; value = \"ВЕРНУТЬСЯ НАЗАД\">"))
                        );


                    }
                }
                else {
                    std::wcout << HTTP_methoods::Paragrah(L"", L"НЕ НАЙДЕН ПОЛЬЗОВАТЕЛЬ С ТАКИМИ ДАННЫМИ\n");
                    std::wcout <<
                        HTTP_methoods::Form(L"METHOD = \"POST\" action = UserRegistration.cgi",

                            HTTP_methoods::Paragrah(L"align = \"center\"",
                                HTTP_methoods::AsIs(L"<input type = \"submit\"; style=\"background-color: Yellow\"; value = \"Зарегистрировать нового пользователя\">")
                            )
                        );
                    }
            }
        }
        return AllowLogging;     
    }


    int main() {
        setlocale(LC_ALL, "Russian");

        mainFunc::RunMainFunc();

        std::string body,
            action,
            CONTENT;

        char buff;




        action = getenv("REQUEST_URI");
        new WebLogger("\nREQUEST_URI is: " + action);

        std::wcout << HTTP_methoods::Paragrah(L"align = \"center\"", HTTP_methoods::StringToWString("try to read content"));



       std::string RequestMethod = getenv("REQUEST_METHOD");
       std::string ContentType = getenv("CONTENT_TYPE");
       std::string ContentLength = getenv("CONTENT_LENGTH");

       new WebLogger("ContentType: " + ContentType);
       new WebLogger("ContentLength: " + ContentLength);
       new WebLogger("RequestMethod: " + RequestMethod);
       new WebLogger("action: " + action);



        if (RequestMethod != "GET" && action == "/cgi-bin/AeroPhlot.cgi") {

            std::cin >> body;

            new WebLogger("body: " + body);

            std::string Name,
                        Password;

            char* cPassword[20];


            
            if (body.find('%') != body.npos) {
                std::wcout << HTTP_methoods::Paragrah(L"align = \"center\"", L"Логин и/или пароль содержат недопустимые символы" +
                    HTTP_methoods::Form(L"METHOD = \"POST\" action = Autorization.cgi",
                        HTTP_methoods::AsIs(L"<input type = \"submit\"; style=\"background-color: red\"; value = \"ВЕРНУТЬСЯ НАЗАД\">"))
                );
                std::wcout << HTTP_methoods::AsIs(L"\n</body>\n<\HTML>");
            }else{


                if (body.find("WebKitFormBoundary") != body.npos) {


                }
                else {
                    Name = QueryTo_RawValue("login", body);
                    Password = QueryTo_RawValue("password", body);

                    new WebLogger("User trying to auth with login: \"" + Name + "\" and pass: \"" + Password +"\"");




                    for (auto it = 0; it < Password.size(); it++)
                        *(cPassword + it) = &(Password.at(it));

                    SHA256Crypt CrypthPass(*cPassword);

                    AuthService(std::make_pair(Name, CrypthPass.Crypted));
                }
                
            }
        };
        return 0;
    }
