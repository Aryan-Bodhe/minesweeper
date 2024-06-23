#include "Minefield.cpp"
#include "util\ClearScreen.cpp"
using namespace std;

class ProgramRunner
{
    Minefield *minefield = NULL;
    TextMessages *text = new TextMessages();
    ScreenActions *screen = new ScreenActions();

    void gameEngine()
    {
        while (minefield->getSafeTiles() > 0)
        {
            minefield->printMaskedMinefield();
            pair<int, int> coordinates = minefield->getCoordinates();
            cout << coordinates.first << " " << coordinates.second << endl;

            int exitCode = minefield->popTiles(coordinates);

            if (minefield->getSafeTiles() != 0)
                system("cls");

            if (exitCode == -1) // mine triggered
            {
                minefield->printMinefieldWithBombs();
                text->displayGameLoseMessage();
                screen->clearScreenWithPermission();
                return;
            }
        }

        system("cls");
        minefield->printMaskedMinefield();
        text->displayGameWinnerMessage();
        screen->clearScreenWithPermission();
        return;
    }

public:
    int runProgram()
    {
        system("cls");
        text->displayWelcomeMessage();
        int difficulty, size, mines;

        text->displayGameRules();

        screen->clearScreenWithPermission();

        text->displayGameDifficultyOptions();

    chooseDifficulty:
        try
        {
            cin >> difficulty;
        }
        catch (const exception)
        {
            text->displayInvalidInputMessage();
            cin.clear();
            fflush(stdin);
            goto chooseDifficulty;
        }

        if (difficulty == 1)
        {
            size = 9;
            mines = 10;
        }
        else if (difficulty == 2)
        {
            size = 15;
            mines = 35;
        }
        else if (difficulty == 3)
        {
            size = 20;
            mines = 80;
        }
        else
        {
            text->displayInvalidInputMessage();
            goto chooseDifficulty;
        }

        minefield = new Minefield(size, mines);

        system("cls");
        gameEngine();

        text->displayNewGameMessage();
        char ch;

    
    // exit point of the program
    input:
        try
        {
            cin >> ch;
        }
        catch (const std::exception &e)
        {
            text->displayInvalidInputMessage();
            cin.clear();
            fflush(stdin);
            goto input;
        }

        ch = toupper(ch);

        if (ch == 'Y')
        {
            delete minefield;
            return 1;
        }
        else if (ch == 'N')
        {
            delete minefield;
            text->displayGameTerminateMessage();
            return 0;
        }
        else
        {
            text->displayInvalidInputMessage();
            goto input;
        }
    }
};
