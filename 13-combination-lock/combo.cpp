/*
ID: caleb.h1
LANG: C++
PROG: combo
*/

#include <fstream>
#include <set>
#include <array>

#include <iostream>

#define MIN(a, b) a < b ? a : b

int main() {
    std::ifstream fin("combo.in");
    int N, farmerLock[3], masterLock[3];
    int i, j, k;
    fin >> N
        >> farmerLock[0] >> farmerLock[1] >> farmerLock[2]
        >> masterLock[0] >> masterLock[1] >> masterLock[2];
    fin.close();

    std::set<std::array<int, 3>> combos;
    int num;

    auto a = new std::array<int, 3>;
    for (i = -2; i < 3; ++i) {
        for (j = -2; j < 3; ++j) {
            for (k = -2; k < 3; ++k) {
                
                num = (farmerLock[0] + i) % N;
                if (num <= 0)
                    num += N;
                else if (num > N)
                    num -= N;
                (*a)[0] = num;
                num = (farmerLock[1] + j) % N;
                if (num <= 0)
                    num += N;
                else if (num > N)
                    num -= N;
                (*a)[1] = num;
                num = (farmerLock[2] + k) % N;
                if (num <= 0)
                    num += N;
                else if (num > N)
                    num -= N;
                (*a)[2] = num;

                combos.insert(*a);
                
                num = (masterLock[0] + i) % N;
                if (num <= 0)
                    num += N;
                else if (num > N)
                    num -= N;
                (*a)[0] = num;
                num = (masterLock[1] + j) % N;
                if (num <= 0)
                    num += N;
                else if (num > N)
                    num -= N;
                (*a)[1] = num;
                num = (masterLock[2] + k) % N;
                if (num <= 0)
                    num += N;
                else if (num > N)
                    num -= N;
                (*a)[2] = num;

                combos.insert(*a);

            }
        }
    }
    delete a;

    std::ofstream fout("combo.out");
    fout << combos.size() << std::endl;
    fout.close();


}
