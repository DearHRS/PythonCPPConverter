#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <fstream>
#include <vector>
#include "PythonToCpp.h"


//function that keeps asking for file path until given one correctly
void Setifstream(std::ifstream& ifstreamGiven, std::wstring invitation);

//function that returns all the lines from python file to a vector
void GetPythonLines(std::vector<std::vector<std::string>>& pythonLinesStorage);

//function that creates c++ file
void CreateCppFile(std::wstring name, std::vector<std::string>& cppLinesStorage);


int main()
{
    //setting console to use unicode hex characters
    _setmode(_fileno(stdin), 0x00020000);
    _setmode(_fileno(stdout), 0x00020000);


    //main loop
    while (true) {
        std::vector<std::vector<std::string>> pythonLinesStorage;   //storage for python lines
        std::vector<std::string> cppLinesStorage;                   //storage for c++ lines
        PythonToCpp pythonToCpp = PythonToCpp();

        GetPythonLines(pythonLinesStorage);

        for (unsigned int i = 0; i < pythonLinesStorage.size(); i++) {
            for (unsigned int j = 0; j < pythonLinesStorage[i].size(); j++) {
                std::wcout << " " << std::wstring(pythonLinesStorage[i][j].begin(), pythonLinesStorage[i][j].end()) << " ";
            }
            std::wcout << std::endl;
        }

        //checking if such file can be evaluated by this convertor
        if (pythonToCpp.IsConvertable(pythonLinesStorage)) {
            CreateCppFile(L"test", cppLinesStorage);
        }
        else {
            std::wcout << L"\tОшибка: во время расшифровки кода python встретился x, который еще не поддерживается\n";
        }

        //checking if user wants to continue
        std::wstring loopContinue;
        while (true) {
            std::wcout << L"\nВы хотите продолжить? (да/нет): ";
            std::wcin >> loopContinue;

            if (loopContinue == L"да" || loopContinue == L"нет") {
                break;
            }
            else {
                std::wcout << L"\tОшибка: >" << loopContinue << L"< не является 'да' или 'нет'\n";
            }
        }
        if (loopContinue == L"нет") {
            break;
        }
        system("cls");
    }
    return 0;
}


//function that keeps asking for file path until given one correctly
void Setifstream(std::ifstream& ifstreamGiven, std::wstring invitation) {
    std::wstring pythonFileName;    //path to python name

    //infinitly asking for correct file until given
    while (true)
    {
        std::wcout << invitation;
        std::wcin >> pythonFileName;

        ifstreamGiven.open(pythonFileName + L".py");
        //checking if file is open
        if (ifstreamGiven.is_open()) {
            //checking if file is empty
            if (ifstreamGiven.peek() == std::ifstream::traits_type::eof()) {
                std::wcout << L"\tОшибка: python файл >" + pythonFileName + L".py< пустой\n";
                ifstreamGiven.close();
            }
            else {
                break;
            }
        }
        else {
            std::wcout << L"\tОшибка: не удалось найти python файл с именем >" << pythonFileName << "<\n";
        }        
    }
}


//function that returns all the lines from python file to a vector
void GetPythonLines(std::vector<std::vector<std::string>>& pythonLinesStorage) {
    std::ifstream pythonFile;   //python input object

    //getting python file
    Setifstream(pythonFile, L"Введите имя файла python: ");

    std::string pythonFileLine[] = {"", ""};       //first index gets line from file; second index break that line in strings

    //storing lines into given vector
    while (std::getline(pythonFile, pythonFileLine[0])) {
        //temporary vector to put into python storage vector
        std::vector<std::string> tempVector;

        //breaking lines by spaces
        for (unsigned int i = 0; i < pythonFileLine[0].size(); i++) {
            if (pythonFileLine[0][i] == ' ') {
                tempVector.push_back(pythonFileLine[1]);
                pythonFileLine[1] = "";
            }
            else {
                pythonFileLine[1] += pythonFileLine[0][i];
            }
        }

        //adding last broken piece if line didn't end in space
        if (pythonFileLine[0][pythonFileLine[0].size() - 1] != ' ') {
            //if last line was empty
            if (pythonFileLine[0].size() == 0) {
                tempVector.push_back("*newline*");
            }
            else {
                tempVector.push_back(pythonFileLine[1]);
            }            
        }        
        pythonFileLine[1] = "";

        //storing temp vector into pythonLinesStorage vector
        pythonLinesStorage.push_back(tempVector);
    }
    std::wcout << "\n\n";
    pythonFile.close();
}


//function that creates c++ file
void CreateCppFile(std::wstring name, std::vector<std::string>& cppLinesStorage) {
    std::ofstream cppFile;          //c++ output object
    std::ifstream alreadyExist;     //c++ input object; used to check if file of given name already exists
    std::wstring nameAddon = L"";   //addition name addon if name already exist
    int repeatedNameCounter = 0;    //value for nameAddon 

    //creating a unique empty file
    while (true) {

        alreadyExist.open(name + nameAddon + L".cpp");

        if (alreadyExist.is_open()) {
            repeatedNameCounter++;
            
            nameAddon = L" (" + std::to_wstring(repeatedNameCounter) + L")";            
            
            alreadyExist.close();
        }
        else {
            break;
        }
    }
    cppFile.open(name + nameAddon + L".cpp");

    cppFile << "/*\n"
            << "this cpp file is written for c++14, file may not work if ran by other versions\n"
            << "*/\n\n";

    //storing data
    for (unsigned int i = 0; i < cppLinesStorage.size(); i++) {
        cppFile << cppLinesStorage[i] << '\n';
    }    

    cppFile.close();
}
