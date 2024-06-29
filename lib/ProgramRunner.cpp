#include "Minefield.cpp"
#include "util\ClearScreen.cpp"
#include "enums/DifficultyOptions.cpp"
#include "util/Delay.cpp"
using namespace std;

class ProgramRunner
{
private:
    Minefield *minefield = NULL;
    TextMessages *text = new TextMessages();
    ScreenActions *screen = new ScreenActions();

    void gameEngine()
    {
        while (minefield->getSafeTiles() > 0)
        {
            minefield->printMaskedMinefield();
            tuple<int, int, char> coordinates = minefield->getCoordinates();
            int exitCode = 1;

            if (get<0>(coordinates) != -1 && get<1>(coordinates) != -1 && get<2>(coordinates) == 'p')
                exitCode = minefield->popTiles(coordinates);
            else if ((get<0>(coordinates) != -1 && get<1>(coordinates) != -1 && get<2>(coordinates) == 'f'))
                exitCode = minefield->flagTile(get<0>(coordinates), get<1>(coordinates));

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

        if (difficulty == beginner)
        {
            size = 9;
            mines = 10;
        }
        else if (difficulty == intermediate)
        {
            size = 15;
            mines = 30;
        }
        else if (difficulty == expert)
        {
            size = 20;
            mines = 60;
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
            Delay::delay(3000);
            return 0;
        }
        else
        {
            text->displayInvalidInputMessage();
            goto input;
        }
    }
};
