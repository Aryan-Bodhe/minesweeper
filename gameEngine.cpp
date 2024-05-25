#include <iostream>
#include <vector>
#include <conio.h>
#include "userPrompts.cpp"
#include "printWizard.cpp"
using namespace std;

inline void clearScreen()
{
    cout << endl
         << "Press any key to continue." << endl;
    fflush(stdin);
    getch();
    system("cls");
    return;
}

void unmaskTile(vector<vector<bool>> &maskMatrix, int &safeTiles, int x, int y)
{
    if (maskMatrix[x][y]) // only unmask if it is currently masked
    { 
        maskMatrix[x][y] = false;
        safeTiles--;
    }
    return;
}

void popZeroTiles(vector<vector<int>> &board, vector<vector<bool>> &maskMatrix, const int size, int x, int y, int &safeTiles)
{
    if (x < 0 || x >= size || y < 0 || y >= size || (safeTiles == 0) || maskMatrix[x][y] == 0)
    {
        return;
    }

    if (board[x][y] != 0 && board[x][y] != -1)
    {
        unmaskTile(maskMatrix, safeTiles, x, y);
        return;
    }

    unmaskTile(maskMatrix, safeTiles, x, y); // tile is zero, unmask it

    popZeroTiles(board, maskMatrix, size, x, y + 1, safeTiles); // right
    popZeroTiles(board, maskMatrix, size, x + 1, y, safeTiles); // down
    popZeroTiles(board, maskMatrix, size, x - 1, y, safeTiles); // left
    popZeroTiles(board, maskMatrix, size, x, y - 1, safeTiles); // up
    popZeroTiles(board, maskMatrix, size, x+1, y + 1, safeTiles);
    popZeroTiles(board, maskMatrix, size, x+1, y - 1, safeTiles);
    popZeroTiles(board, maskMatrix, size, x-1, y + 1, safeTiles);
    popZeroTiles(board, maskMatrix, size, x-1, y - 1, safeTiles);

    return;
}

pair<int, int> getCoordinates(const int size)
{
    pair<int, int> coordinates;
    cout << "Enter coordinates of tile to pop as space separated values." << endl;
    int x, y;

input:
    try
    {
        cin >> x >> y;
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Invalid Input. Please enter again." << endl;
        fflush(stdin);
        goto input;
    }

    if (x >= 0 && x < size && y >= 0 && y < size)
    {
        coordinates.first = x;
        coordinates.second = y;
    }
    else
    {
        cout << "Invalid Input. Please enter again." << endl;
        goto input;
    }

    return coordinates;
}

int popTiles(vector<vector<int>> &board, vector<vector<bool>> &maskMatrix, pair<int, int> &coordinates,
             const int size, int &safeTiles) // returns exit code
{

    if (board[coordinates.first][coordinates.second] == -1) // if its bomb, terminate game
    {
        return -1;
    }
    else if (board[coordinates.first][coordinates.second] == 0) //if its zero, pop all zero tiles
    {
        popZeroTiles(board, maskMatrix, size, coordinates.first, coordinates.second, safeTiles);
    }
    else
    {
        unmaskTile(maskMatrix, safeTiles, coordinates.first, coordinates.second); // unmask that tile
    }
    return 0;
}

void gameEngine(vector<vector<int>> &board, vector<vector<bool>> &maskMatrix, const int size, int &safeTiles)
{
    while (safeTiles > 0)
    {
        //printBoard(board, size); used for testing purposes
        printMaskedBoard(board, maskMatrix, size);
        pair<int, int> coordinates = getCoordinates(size);
        cout << coordinates.first << " " << coordinates.second << endl;

        int exitCode = popTiles(board, maskMatrix, coordinates, size, safeTiles);
        
        if(safeTiles != 0)
            system("cls");

        if (exitCode == -1) // mine triggered
        {
            printBoardWithBombs(board, maskMatrix, size);
            displayGameLoseMessage();
            clearScreen();
            return;
        }
    }

    system("cls");
    printMaskedBoard(board, maskMatrix, size);
    displayGameWinnerMessage();
    clearScreen();
    return;
}