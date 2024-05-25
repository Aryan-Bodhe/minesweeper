#include "gameEngine.cpp"
#include "boardGenerator.cpp"
using namespace std;

int runProgram()
{
    system("cls");
    cout << "\033[30;42m <---WELCOME TO MINESWEEPER ---> \033[32;40m" << endl << endl;
    int difficulty, size, mines;

    displayGameRules();

    clearScreen();

    displayGameDifficultyOptions();

    chooseDifficulty:
    try
    {
        cin >> difficulty;
    }
    catch(const std::exception& e)
    {
        //std::cerr << e.what() << '\n';
        cout << "Invalid Input. Please try again." << endl;
        goto chooseDifficulty;
    }

    if(difficulty == 1)
    {
        size = 9;
        mines = 10;
    }
    else if(difficulty == 2)
    {
        size = 15;
        mines = 35;
    }
    else if(difficulty == 3)
    {
        size = 20;
        mines = 80;
    }
    else
    {
        cout << "Invalid Input. Please try again." << endl;
        goto chooseDifficulty;
    }

    vector<vector<int>> gameBoard(size);
    vector<vector<bool>> maskMatrix(size);
    int safeTiles = (size * size) - mines;

    gameBoard = newBoard(size, mines);
    maskMatrix = generateMaskMatrix(size);

    system("cls");
    gameEngine(gameBoard, maskMatrix, size, safeTiles);

    displayNewGameMessage();
    char ch;

    input:
    try
    {
        cin >> ch;
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Invalid Input. Please try again." << endl;
        goto input;
    }

    ch = toupper(ch); 

    if(ch == 'Y')
    {
        return 1;
    }
    else if(ch == 'N')
    {
        displayGameTerminateMessage();
        return 0;
    }
    else
    {
        cout << "Invalid Input. Please try again." << endl;
        goto input;
    }
            
}

int main()
{
    while(runProgram());
}