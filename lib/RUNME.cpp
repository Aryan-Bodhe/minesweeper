#include "ProgramRunner.cpp"
using namespace std;

int main()
{
    std::cin.exceptions(std::ios::failbit | std::ios::badbit);

    ProgramRunner* program = new ProgramRunner();
    while (program->runProgram());
}
