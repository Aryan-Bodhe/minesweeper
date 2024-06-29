#include <time.h>
using namespace std;

class Delay
{
public:
    /* Creates delay of specified duration in milliseconds */
    void delay(int duration)
    {
        clock_t time = clock();
        for (int i = 1; i <= duration; i++)
        {
            while ((float)(clock() - time) / 1000 * CLOCKS_PER_SEC < i)
            { /* do nothing */
            }
        }
    }
};