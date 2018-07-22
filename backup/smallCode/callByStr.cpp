#include <map>
#include <iostream>
using namespace std;

typedef void (*pFunc)();
std::map<std::string, pFunc> strFuncMap;

void func1() {
    cout<<"this is func1!\n";
}

void func2() {
    cout<<"this is func2!\n";
}



void buildMap() {
    strFuncMap["func1"] = &func1;
    strFuncMap["func2"] = &func2;
}

void callFunc(const std::string& str) {
    if(strFuncMap.count(str))
        (*strFuncMap[str])();
    else
        std::cout << "unsupported function str : " << str << endl;
}

int main() {
    buildMap();
    //begin call func
    callFunc("func1");
    callFunc("func2");
    callFunc("func3");
    return 0;
}