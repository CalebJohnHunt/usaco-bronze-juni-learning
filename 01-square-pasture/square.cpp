#include <fstream>
#include <iostream>

#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b

int main() {
    std::ifstream infile("square.in");

    struct Point {
        uint x;
        uint y;
    } points[4];

    for (char i=0; i<4; ++i) {
        infile >> points[i].x;
        infile >> points[i].y;

    }

    infile.close();

    uint left = points[0].x;
    uint right = left;
    uint bottom = points[0].y;
    uint top = bottom;

    for (char i=1; i<4; ++i) {
        left = min(left, points[i].x);
        right = max(right, points[i].x);
        bottom = min(bottom, points[i].y);
        top = max(top, points[i].y);
    }

    uint ans = max(right - left, top - bottom);
    ans *= ans;
    
    std::ofstream outfile("square.out");
    outfile << ans << std::endl;

    return 0;
}