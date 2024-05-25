#include <iostream>
#include <vector>
using namespace std;

void printMaskedBoard(vector<vector<int>> &board, vector<vector<bool>> &maskMatrix, const int size)
{
    cout << endl;
    
    cout << "\033[0m   \033[32;40m  ";

    for (int i = 0; i < size; i++)
    {
        if(i < 9)
            cout << i << "   ";
        else
            cout << i << "  ";
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {     
        if(i < 10)
            cout << i << "  | ";
        else
            cout << i << " | ";
    
        for (int j = 0; j < size; j++)
        {
            if (maskMatrix[i][j] == false)
            {
                if (board[i][j] == 0)
                {
                    cout << " " << " | ";
                }
                else
                {
                    cout << board[i][j] << " | ";
                }
            }
            else
            {
                cout << (char)254 << " | ";
            }
        }
        cout << " " << i;
        cout << endl;
    }
    
    cout << "\033[0m   \033[32;40m  ";

    for (int i = 0; i < size; i++)
    {
        if(i < 9)
            cout << i << "   ";
        else
            cout << i << "  ";
    }
    cout << endl << endl;
    return;
}

void printBoardWithBombs(vector<vector<int>>& board, vector<vector<bool>> &maskMatrix, const int size)
{
    cout << endl;
    
    cout << "\033[0m   \033[32;40m  ";

    for (int i = 0; i < size; i++)
    {
        if(i < 9)
            cout << i << "   ";
        else
            cout << i << "  ";
    }

    cout << endl;

    for (int i = 0; i < size; i++)
    {
        if(i < 10)
            cout << i << "  | ";
        else
            cout << i << " | ";
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == -1)
            {
                cout << "\033[31;40m*\033[32;40m" << " | ";
            }
            else if (maskMatrix[i][j] == 0)
            {
                if (board[i][j] == 0)
                {
                    cout << " " << " | ";
                }
                else
                {
                    cout << board[i][j] << " | ";
                }
            }
            else if (maskMatrix[i][j] == 1)
            {
                cout << (char)254 << " | ";
            }             
        }
        cout << " " << i;
        cout << endl;
    }
    
    cout << "\033[0m   \033[32;40m  ";

    for (int i = 0; i < size; i++)
    {
        if(i < 9)
            cout << i << "   ";
        else
            cout << i << "  ";
    }
    cout << endl;
    return;
}

void printBoard(vector<vector<int>> &board, const int size) //for testing purposes only
{
    cout << endl;
    cout << "   ";
    for (int i = 0; i < size; i++)
    {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << i << " |";
        for (int j = 0; j < size; j++)
        {

            if (board[i][j] == 0)
            {
                cout << " " << "|";
            }
            else
            {
                if(board[i][j] == -1)
                {
                    cout << "\033[31;40m*\033[32;40m" << "|";
                }
                else
                {
                    cout << board[i][j] << "|";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
    return;
}