/*
ID: caleb.h1
LANG: C++
PROG: wormhole
*/

#include <fstream>

#include <iostream>

#define MIN(a, b) a < b ? a : b
#define DEBUG(a) std::cout << "DEBUG " << a << std::endl;

struct wormhole {
    int x, y;
    wormhole* toRight = nullptr;
    wormhole* pair = nullptr;
};

struct scenario {
    wormhole *wormholes;
    int size;
};

struct allScenarios {
    scenario *scenarios;
    int size;
};

void pW(wormhole w[], int N);
void pS(scenario* s);

allScenarios calc(scenario s) {
    // Base case:
    // Only have 2 wormholes to connect
    allScenarios a;
    if (s.size == 2) {
        s.wormholes[0].pair = &s.wormholes[1];
        s.wormholes[1].pair = &s.wormholes[0];
        a.scenarios = &s; // Copy of s?
        a.size = 1;
        return a;
    }

    switch (s.size) {
        case 4:
            a.scenarios = new scenario[1*3];
            a.size = 1*3;
            break;
        case 6:
            a.scenarios = new scenario[1*3*5];
            a.size = 1*3*5;
            break;
        case 8:
            a.scenarios = new scenario[1*3*5*7];
            a.size = 1*3*5*7;
            break;
        case 10:
            a.scenarios = new scenario[1*3*5*7*9];
            a.size = 1*3*5*7*9;
            break;
        case 12:
            a.scenarios = new scenario[1*3*5*7*9*11];
            a.size = 1*3*5*7*9*11;
            break;
        default:
            DEBUG("Wrong size?? " << s.size)
    }

    // Recursive case:
    int counter = 0;
    for (int i = 1; i < s.size; ++i) {
        // pair w[0] and w[i]
        s.wormholes[0].pair = &s.wormholes[i];
        s.wormholes[i].pair = &s.wormholes[0];

        // Make new sub-scenario (without w[0] and w[i])
        scenario newS;
        newS.size = 0;
        newS.wormholes = new wormhole[s.size - 2];
        for (int k = 1; k < s.size; ++k) {
            if (k != i) {
                newS.wormholes[newS.size++] = s.wormholes[k];
            }
        }

        DEBUG("newS:")
        pS(&newS);

        // Find all the scenarios possible with sub-scenario
        allScenarios b = calc(newS);

        DEBUG("b.size: " << b.size)

        for (int i = 0; i < b.size; ++i) {
            std::cout << "b.sce[" << i << "].size: " << b.scenarios[i].size;
        }

        // Attach w[0] and w[i] with each scenario
        // Add the resulting scenario to returning allScenario
        for (int k = 0; k < b.size; ++k) {
            DEBUG("b.scenarios[" << k << "].size: " << b.scenarios[k].size << ':')
            pS(&(b.scenarios[k]));
            scenario foo;
            foo.size = s.size;
            foo.wormholes = new wormhole[foo.size];
            foo.wormholes[0] = s.wormholes[0];
            foo.wormholes[1] = s.wormholes[i];
            for (int j = 0; j < b.scenarios[k].size; ++j) {
                DEBUG("j " << j << " k " << k)
                foo.wormholes[j+2] = b.scenarios[k].wormholes[j];
            }
            a.scenarios[counter++] = foo;
        }
    }
    return a;
}

void pW(wormhole w[], int N) {
    std::cout << "Wormholes:\n"
              << "x y to x y" << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << w[i].x << ' ' << w[i].y;
        if (w[i].pair) {
            std::cout << " -> " << w[i].pair->x << ' ' << w[i].pair->y;
        }
        if (w[i].toRight) {
            std::cout << " --> " << w[i].toRight->x << ' ' << w[i].toRight->y;
        }
        std::cout << std::endl;
    }
}

void pS(scenario* s) {
    for (int i = 0; i < s->size; ++i) {
        pW(s->wormholes, s->size);
    }
}

int main() {
    std::ifstream fin("wormhole.in");
    int N, i, j;
    fin >> N;
    N = 4;
    wormhole wormholes[N];

    for (i = 0; i < N; ++i) {
        fin >> wormholes[i].x;
        fin >> wormholes[i].y;
    }

    pW(wormholes, N);

    for (i = 0; i < N; ++i) {
        wormhole* w1 = &wormholes[i];
        
        // find the closest wormhole to the +x of w1
        // and set w1->next to it
        for (j = 0; j < N; ++j) {
            wormhole *w2 = &wormholes[j];

            // new wormhole is on the same row
            if (w1->y == w2->y && w2->x > w1->x) {
                // w1 has no next
                if (w1->toRight == nullptr) {
                    w1->toRight = w2;
                    continue;
                }

                // new wormhole is closer
                if (w2->x < w1->toRight->x) {
                    w1->toRight = w2;
                }

            }

        }
    }

    std::cout << "\nMatched up\n" << std::endl;

    pW(wormholes, N);

    scenario s;
    s.size = N;
    s.wormholes = wormholes;

    allScenarios a = calc(s);

    for (i = 0; i < a.size; ++i) {
        pW(a.scenarios[i].wormholes, a.scenarios[i].size);
    }

    return 0;
}