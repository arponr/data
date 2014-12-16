#include "tools.h"

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a < b ? b : a;
}

int less(int a, int b, int c, int d)
{
    return a < c || a == c && b < d;
}

int hom(int x)
{
    return x ? -1 : 1;
}
