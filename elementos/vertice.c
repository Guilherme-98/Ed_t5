#include "vertice.h"

typedef struct stVertex{
    Point v;
    double dist, angle;
    bool start;
    Segment s;
} *VerticeImp;

