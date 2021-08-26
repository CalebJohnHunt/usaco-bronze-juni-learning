/*
ID: caleb.h1
LANG: C++
PROG: skidesign
*/

#include <fstream>

int main() {
    std::ifstream fin("skidesign.in");
    int N, maxHeight=0;
    fin >> N;
    int hills[N];
    for (int i=0; i<N; ++i) {
        fin >> hills[i];
        maxHeight = std::max(maxHeight, hills[i]);
    }
    fin.close();

    uint minPrice = -1;
    for (int i=0; i+17<=maxHeight; ++i) {
        uint oneHillPrice = 0, cost=0;
        for (int j=0; j<N; ++j) {
            if (hills[j] < i) {
                oneHillPrice = i - hills[j];
            } else if (hills[j] > i+17) {
                oneHillPrice = hills[j] - i - 17;
            } else {
                oneHillPrice = 0;
            }
            cost += oneHillPrice * oneHillPrice;
        }
        minPrice = std::min(minPrice, cost);
    }

    std::ofstream fout("skidesign.out");
    fout << minPrice << std::endl;
    fout.close();

    return 0;
}