#include "Utilities.h"

int Utils::clamp(int min, int val, int max)
{
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}