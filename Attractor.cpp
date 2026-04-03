#include "Attractor.h"

using namespace std;

const Vector2 AutoAttractor::lessajous() const {
    Vector2 pos;
    pos.x = A*sin(a*lastAppear+delta)+A;
    pos.y = B*sin(b*lastAppear)+B;
    return pos;
}
