#include <time.h>
#include <vector>
#include <random>
#include <tuple>
#include "util\TextMessages.cpp"
#include "enums/MineFieldOptions.cpp"
#include "enums/MaskOptions.cpp"
using namespace std;

class Minefield
{
public:
    vector<vector<int>> minefield;
    vector<pair<int, int>> mineLocations;
    vector<vector<maskOptions>> maskMatrix;

    Minefield(const int size, const int mineCount) // constructs the minefield
    {
        this->size = size;
        this->mineCount = mineCount;
        this->safeTiles = (size * size) - mineCount;

        minefield.resize(size);
        mineLocations.resize(mineCount);
        maskMatrix.resize(size);

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                minefield[i].push_back(0);
            }
        }

        generateMines();

        for (auto mine : mineLocations)
        {
            minefield[mine.first][mine.second] = -1;
        }

        numberTheCells();
        generateMaskMatrix();
    }

    void printMaskedMinefield()
    {
        cout << endl;

        cout << "\033[0m   \033[32;40m  ";

        for (int i = 0; i < size; i++)
        {
            if (i < 9)
                cout << i << "   ";
            else
                cout << i << "  ";
        }
        cout << endl;
        for (int i = 0; i < size; i++)
        {
            if (i < 10)
                cout << i << "  | ";
            else
                cout << i << " | ";

            for (int j = 0; j < size; j++)
            {
                if (maskMatrix[i][j] == unmasked)
                {
                    if (minefield[i][j] == 0)
                    {
                        cout << " " << " | ";
                    }
                    else
                    {
                        cout << minefield[i][j] << " | ";
                    }
                }
                else if(maskMatrix[i][j] == flagged) 
                {
                    cout << "\033[36;40m\u25B6\033[32;40m" << " | ";
                }
                else
                { //print block
                    cout << "\u25FC" << " | ";
                }
            }
            cout << " " << i;
            cout << endl;
        }

        cout << "\033[0m   \033[32;40m  ";

        for (int i = 0; i < size; i++)
        {
            if (i < 9)
                cout << i << "   ";
            else
                cout << i << "  ";
        }
        cout << endl
             << endl;
        return;
    }
    
    void printMinefieldWithBombs()
    {
        cout << endl;

        cout << "\033[0m   \033[32;40m  ";

        for (int i = 0; i < size; i++)
        {
            if (i < 9)
                cout << i << "   ";
            else
                cout << i << "  ";
        }

        cout << endl;

        for (int i = 0; i < size; i++)
        {
            if (i < 10)
                cout << i << "  | ";
            else
                cout << i << " | ";
            for (int j = 0; j < size; j++)
            {
                if (minefield[i][j] == bomb)
                {
                    cout << "\033[31;40m\u26EF\033[32;40m" << " | ";
                }
                else if (maskMatrix[i][j] == unmasked)
                {
                    if (minefield[i][j] == 0)
                    {
                        cout << " " << " | ";
                    }
                    else
                    {
                        cout << minefield[i][j] << " | ";
                    }
                }
                else if (maskMatrix[i][j] == masked)
                {
                    cout << "\u25FC" << " | ";
                }
                else if(maskMatrix[i][j] == flagged) 
                {
                    cout << "\033[34;40m\u25B6\033[32;40m" << " | ";
                }
            }
            cout << " " << i;
            cout << endl;
        }

        cout << "\033[0m   \033[32;40m  ";

        for (int i = 0; i < size; i++)
        {
            if (i < 9)
                cout << i << "   ";
            else
                cout << i << "  ";
        }
        cout << endl;
        return;
    }

    int popTiles(tuple<int, int, char> &coordinates) // returns exit code
    {
        if (minefield[get<0>(coordinates)][get<1>(coordinates)] == bomb) // if its bomb, terminate game
        {
            return -1;
        }
        else if (minefield[get<0>(coordinates)][get<1>(coordinates)] == 0) // if its zero, pop all zero tiles
        {
            popZeroTiles(get<0>(coordinates), get<1>(coordinates));
            return 1;
        }
        else
        {
            unmaskTile(get<0>(coordinates), get<1>(coordinates)); // unmask that tile
            return 1;
        }
        return 0;
    }

    tuple<int, int, char> getCoordinates()
    {
        TextMessages *text = new TextMessages();
        tuple<int, int, char> coordinates(-1,-1, 'e');
        text->displayCoordinateInputMessage();
        int x, y;
        char mode;

    input:
        try
        {
            cin >> x >> y >> mode;
            mode = tolower(mode);
        }
        catch (const exception)
        {
            text->displayInvalidInputMessage();
            cin.clear();
            fflush(stdin);
            goto input;
        }

        if (x >= 0 && x < size && y >= 0 && y < size && mode == 'p' )
        {
            get<0>(coordinates) = x;
            get<1>(coordinates) = y;
            get<2>(coordinates) = mode;
        }
        else if (x >= 0 && x < size && y >= 0 && y < size && mode == 'f')
        {
            if(maskMatrix[x][y] == unmasked) 
            {
                text->displayInvalidFlagMessage();
                goto input;
            }
            if(maskMatrix[x][y] == flagged)
            {
                text->displayAlreadyFlaggedMessage();
                goto input;
            }
            else
            {
                get<0>(coordinates) = x;
                get<1>(coordinates) = y;
                get<2>(coordinates) = mode;
            }
        }
        else if (x >= 0 && x < size && y >= 0 && y < size && mode == 'r') 
        {
            if(maskMatrix[x][y] == flagged) 
            {
                maskMatrix[x][y] = masked;
            }
            else 
            {
                text->displayInvalidFlagRemovalMessage();
                goto input;
            }
        }
        else
        {
            text->displayInvalidInputMessage();
            goto input;
        }

        return coordinates;
    }

    int flagTile(int x, int y)
    {
        TextMessages* text = new TextMessages();
        if(maskMatrix[x][y] == masked)
        {
            text->displayInvalidFlagMessage();   
        }
            maskMatrix[x][y] = flagged;
        return 1;
    }

    int getSize()
    {
        return size;
    }

    int getMineCount()
    {
        return mineCount;
    }

    int getSafeTiles()
    {
        return safeTiles;
    }

private:
    int size;
    int mineCount;
    int safeTiles;

    void numberTheCells()
    {
        int i, j;
        for (auto mine : mineLocations)
        {
            i = mine.first, j = mine.second;
            if (i - 1 >= 0 && i - 1 < this->size && j - 1 >= 0 && j - 1 < this->size && minefield[i - 1][j - 1] != -1) // NW
            {
                minefield[i - 1][j - 1]++;
            }
            if (i - 1 >= 0 && i - 1 < this->size && j >= 0 && j < this->size && minefield[i - 1][j] != -1) // N
            {
                minefield[i - 1][j]++;
            }
            if (i - 1 >= 0 && i - 1 < this->size && j + 1 >= 0 && j + 1 < this->size && minefield[i - 1][j + 1] != -1) // NE
            {
                minefield[i - 1][j + 1]++;
            }
            if (i >= 0 && i < this->size && j - 1 >= 0 && j - 1 < this->size && minefield[i][j - 1] != -1) // W
            {
                minefield[i][j - 1]++;
            }

            if (i >= 0 && i < this->size && j + 1 >= 0 && j + 1 < this->size && minefield[i][j + 1] != -1) // E
            {
                minefield[i][j + 1]++;
            }
            if (i + 1 >= 0 && i + 1 < this->size && j - 1 >= 0 && j - 1 < this->size && minefield[i + 1][j - 1] != -1) // SW
            {
                minefield[i + 1][j - 1]++;
            }
            if (i + 1 >= 0 && i + 1 < this->size && j >= 0 && j < this->size && minefield[i + 1][j] != -1) // S
            {
                minefield[i + 1][j]++;
            }
            if (i + 1 >= 0 && i + 1 < this->size && j + 1 >= 0 && j + 1 < this->size && minefield[i + 1][j + 1] != -1)
            {
                minefield[i + 1][j + 1]++;
            }
        }
    }

    void generateMines()
    {
        srand(time(NULL));
        int r, x, y;
        bool isLocationUnique = true;

        for (int i = 0; i < this->mineCount; i++)
        {
            isLocationUnique = true;
            r = rand() % size;
            x = r;
            r = rand() % size;
            y = r;

            for (auto mine : mineLocations)
            {
                if (mine.first == x && mine.second == y)
                {
                    isLocationUnique = false;
                    break;
                }
            }

            if (isLocationUnique)
            {
                mineLocations[i].first = x;
                mineLocations[i].second = y;
            }
            else
            {
                i--;
            }
        }
    }

    void generateMaskMatrix()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                maskMatrix[i].push_back(masked);
            }
        }
    }

    void unmaskTile(int x, int y)
    {
        if (maskMatrix[x][y]) // only unmask if it is currently masked
        {
            maskMatrix[x][y] = unmasked;
            safeTiles--;
        }
        return;
    }

    void popZeroTiles(int x, int y)
    {
        if (x < 0 || x >= size || y < 0 || y >= size || (safeTiles == 0) || maskMatrix[x][y] == unmasked)
        {
            return;
        }

        if (minefield[x][y] != 0 && minefield[x][y] != bomb)
        {
            unmaskTile(x, y);
            return;
        }

        unmaskTile(x, y); // tile is zero, unmask it

        popZeroTiles(x, y + 1);     // E
        popZeroTiles(x + 1, y);     // S
        popZeroTiles(x - 1, y);     // N
        popZeroTiles(x, y - 1);     // W
        popZeroTiles(x + 1, y + 1); // SE
        popZeroTiles(x + 1, y - 1); // SW
        popZeroTiles(x - 1, y + 1); // NE
        popZeroTiles(x - 1, y - 1); // NW

        return;
    }

    // void printMinefield()  for testing purposes only
    // {
    //     cout << endl;
    //     cout << "   ";
    //     for (int i = 0; i < size; i++)
    //     {
    //         cout << i << " ";
    //     }
    //     cout << endl;
    //     for (int i = 0; i < size; i++)
    //     {
    //         cout << i << " |";
    //         for (int j = 0; j < size; j++)
    //         {
    //
    //             if (minefield[i][j] == 0)
    //             {
    //                 cout << " " << "|";
    //             }
    //             else
    //             {
    //                 if (minefield[i][j] == -1)
    //                 {
    //                     cout << "\033[31;40m*\033[32;40m" << "|";
    //                 }
    //                 else
    //                 {
    //                     cout << minefield[i][j] << "|";
    //                 }
    //             }
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    //     return;
    // }
};

    // {
    //     vector<vector<int>> minefield(size);
    //     vector<pair<int,int>> mineLocation;
    //
    //     for(int i = 0; i < size; i++)
    //     {
    //         for(int j = 0; j < size; j++)
    //         {
    //             minefield[i].push_back(0);
    //         }
    //     }
    //
    //     mineLocation = generateMines(size, mineCount);
    //
    //     for(auto mine : mineLocation)
    //     {
    //         minefield[mine.first][mine.second] = -1;
    //     }
    //
    //     numberTheCells(minefield, mineLocation, size);
    //     vector<vector<bool>> maskMatrix = generateMaskMatrix(size);
    //     //printMaskedminefield(minefield, maskMatrix, size);
    //     //printminefield(minefield, size);
    //
    //     return minefield;
    // }