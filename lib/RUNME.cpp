#include <windows.h>
#include "ProgramRunner.cpp"
using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::cin.exceptions(std::ios::failbit | std::ios::badbit);

    ProgramRunner* program = new ProgramRunner();
    while (program->runProgram());
}