#include <iostream>
using namespace std;

class TextMessages
{
    public:
    void displayAlreadyPoppedMessage()
    {
        cout << "\033[31;40mSelected tile has already been popped. Try again with different coordinates.\033[32;40m" << endl;
    }

    void displayAlreadyFlaggedMessage()
    {
        cout << "\033[31;40mSelected tile is already flagged. Try again with different coordinates.\033[32;40m" << endl;
    }

    void displayInvalidFlagRemovalMessage() 
    {
        cout << "\033[31;40mSelected tile is not flagged. Try again with different coordinates.\033[32;40m" << endl;
    }

    void displayCoordinateInputMessage() 
    {
        cout << "Enter coordinates of tile to pop as space separated values followed \nby 'p' to pop the cell, 'f' to flag it, or 'r' to remove a flag." << endl;
        cout << "Example: '2 3 f', '7 2 p', '13 11 r' etc." << endl;
    }

    void displayInvalidFlagMessage()
    {
        cout << "\033[31;40mTile has been popped already. Cannot flag it. Please input different coordinates.\033[32;40m" << endl;
    }

    void displayWelcomeMessage() 
    {
        cout << "\033[30;42m <---WELCOME TO MINESWEEPER ---> \033[32;40m\n" << endl;
    }
    
    void displayInvalidInputMessage() 
    {
        cout << "\033[31;40mInvalid Input. Please try again.\033[32;40m" << endl;
    }

    void displayGameLoseMessage()
    {
        cout << (char)7 << endl;
        cout << endl
                << "\033[31;40mA MINE EXPLODED!! YOU LOST.\033[32;40m" << endl; // red text
    }

    void displayGameTerminateMessage()
    {
        system("cls");
        cout << "Thanks for playing Minesweeper!!\033[0m" << endl
                << endl;
    }

    void displayNewGameMessage()
    {
        cout << "Would you like to play another round? (Y/N)" << endl;
    }

    void displayGameWinnerMessage()
    {
        cout << endl
                << "\033[30;42mALL MINES DISCOVERED!!\033[32;40m" << endl; // green text
    }

    void displayGameDifficultyOptions()
    {
        cout << "\033[32;40mChoose difficulty level." << endl
                << endl;
        cout << "1. Beginner 9x9 grid with 10 mines. (Enter 1)" << endl;
        cout << "2. Intermediate 14x14 with 30 mines. (Enter 2)" << endl;
        cout << "3. Expert 20x20 with 60 mines. (Enter 3)" << endl;
    }

    void displayGameRules()
    {
        cout << "1. There are some mines distributed across the grid. Your task is to find them all." << endl;
        cout << "2. Each number signifies the number of mines in the cells adjacent to it." << endl;
        cout << "3. In order to sweep a tile, enter the coordinates. Be careful not to trigger a mine!" << endl;
        cout << "4. Sweeping a tile having zero mines uncovers all tiles having zero adjacent mines." << endl;
        cout << endl
                << "HAPPY MINESWEEPING!!" << endl;
    }
};
