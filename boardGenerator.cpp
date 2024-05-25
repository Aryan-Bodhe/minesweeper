#include <time.h>
using namespace std;

void numberTheCells(vector<vector<int>>& board, vector<pair<int,int>> mineLocation, const int size)
{
    int i,j;
    
    for(auto mine : mineLocation)
    {
        i = mine.first, j = mine.second;
        if(i-1 >= 0 && i-1 < size && j-1 >=0 && j-1 < size && board[i-1][j-1] != -1) //NW
        {
            board[i-1][j-1]++;
        }
        if(i-1 >= 0 && i-1 < size && j >=0 && j < size && board[i-1][j] != -1) //N
        {
            board[i-1][j]++;
        }
        if(i-1 >= 0 && i-1 < size && j+1 >=0 && j+1 < size && board[i-1][j+1] != -1) //NE
        {
            board[i-1][j+1]++;
        }
        if(i >= 0 && i < size && j-1 >=0 && j-1 < size && board[i][j-1] != -1) //W
        {
            board[i][j-1]++;
        }
        
        if(i >= 0 && i < size && j+1 >=0 && j+1 < size && board[i][j+1] != -1) //E
        {
            board[i][j+1]++;
        }
        if(i+1 >= 0 && i+1 < size && j-1 >=0 && j-1 < size && board[i+1][j-1] != -1) //SW
        {
            board[i+1][j-1]++;
        }
        if(i+1 >= 0 && i+1 < size && j >=0 && j < size && board[i+1][j] != -1) //S
        {
            board[i+1][j]++;
        }
        if(i+1 >= 0 && i+1 < size && j+1 >=0 && j+1 < size && board[i+1][j+1] != -1)
        {
            board[i+1][j+1]++;
        }
    }
}

vector<pair<int,int>> generateMines(const int size, const int mineCount)
{
    srand(time(NULL));
    vector<pair<int,int>> mineLocation(mineCount);
    int r,x,y;
    bool isLocationUnique = true;

    for(int i = 0; i < mineCount; i++)
    {
        isLocationUnique = true;
        r = rand() % size;
        x = r;
        r = rand() % size;
        y = r;

        for(auto mine : mineLocation)
        {
            if(mine.first == x && mine.second == y)
            {
                isLocationUnique = false;
                break;
            }
        }

        if(isLocationUnique)
        {
            mineLocation[i].first = x;
            mineLocation[i].second = y;
        }
        else
        {
            i--;
        }
    }

    return mineLocation;
}

vector<vector<bool>> generateMaskMatrix(const int size)
{
    vector<vector<bool>> maskMatrix(size);

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            maskMatrix[i].push_back(1);
        }
    }
    return maskMatrix;
}

vector<vector<int>> newBoard(const int size, const int mineCount)
{
    vector<vector<int>> board(size);
    vector<pair<int,int>> mineLocation;

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            board[i].push_back(0);
        }
    }

    mineLocation = generateMines(size, mineCount);

    for(auto mine : mineLocation)
    {
        board[mine.first][mine.second] = -1;
    }

    numberTheCells(board, mineLocation, size);
    vector<vector<bool>> maskMatrix = generateMaskMatrix(size);
    //printMaskedBoard(board, maskMatrix, size);
    //printBoard(board, size);

    return board;
}