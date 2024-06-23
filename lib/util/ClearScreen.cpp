#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;

class ScreenActions
{
    public:
    inline void clearScreenWithPermission()
    {
        cout << endl
             << "Press any key to continue." << endl;
        fflush(stdin);
        getch();
        system("cls");
        return;
    }
};  