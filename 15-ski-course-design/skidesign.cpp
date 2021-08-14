/* 
ID: caleb.h1
LANG: C++
PROG: skidesign
*/

/*
 * This program solves skidesign by raising or lowering the
 * lowest or highest hills, repectively, for as cheap as possible.
 * If it's cheaper to raise all the shortest hills, then do that,
 * but if it's cheaper to lower all the tallest hills, do that.
 * We repeat until the difference from tallest and shortest hills <= 17
 * 
 * Complexity:
 * We use qsort, which I think is nlogn. Then with "repeat until <=17",
 * I'm really not sure what complexity that adds. Regardless, because I
 * only use qsort at the start 
*/

#include <fstream>

struct Hill {
    int height;
    int change=0;
};

// Fun fact:
// can technically be just an int compare
// since it'll just read the first int of Hill anyway
int HillCmpr(const void* a, const void* b) {
    return ((Hill*)a)->height - ((Hill*)b)->height;
}

// Checks upwards
// hills should point to the start of the possible hills
// ex: Short hills: points to start of hills; Tall hills: points a few hills from the end
int findPriceToChangeNHills(const Hill* hills, const int& N) {
    int price = 0;
    // Change in cost increases at a rate of 2n-1 where n is the new cost
    // ex: 3->4 : 4**2 - 3**2 == 2(4)-1 == 7
    for (int i = 0; i < N; ++i) {
        price += 2*(hills[i].change+1)-1;
    }
    return price;
}

int findNumOfEquallyShortHills(const Hill* hills, const int& size) {
    int count = 0;
    while (count < size && hills[count].height == hills[++count].height);

    return count;
}

int findNumOfEquallyTallHills(const Hill* hills, const int& size) {
    int count = 0;
    while (count < size && hills[size-1-count].height == hills[size-1-++count].height);

    return count;
}

void addToHills(Hill* hills, const int& size) {
    // Calculate the price to raise all the shortest hills
    const int equallyShortHills = findNumOfEquallyShortHills(hills, size);
    const int priceForShortHills = findPriceToChangeNHills(hills, equallyShortHills);

    // Calculate the price for tallest hills
    const int equallyTallHills  = findNumOfEquallyTallHills(hills, size);
    const int priceForTallHills  = findPriceToChangeNHills(hills + size - equallyTallHills, equallyTallHills);

    // If it's cheaper to raise the short hills, raise them
    // if it's cheaper to lower the tall  hills, do so
    if (priceForShortHills <= priceForTallHills) {
        for (int i = 0; i < equallyShortHills; ++i) {
            hills[i].height++;
            hills[i].change++;
            // Keep hills sorted by moving each hill up the list if needs be
            if (hills[i].height > hills[i+equallyShortHills].height) {
                const Hill temp = hills[i];
                hills[i] = hills[i+equallyShortHills];
                hills[i+equallyShortHills] = temp;
            }
        }
    } else {
        for (int i = 0; i < equallyTallHills; ++i) {
            const int curIndex = size-1 - i;
            hills[curIndex].height--;
            hills[curIndex].change++;
            // Keep hills sorted by moving each hill down the list if needs be
            if (hills[curIndex - i].height < hills[curIndex - equallyTallHills].height) {
                const Hill temp = hills[curIndex];
                hills[curIndex] = hills[curIndex - equallyTallHills];
                hills[curIndex - equallyTallHills] = temp;
            }
        }
    }
}

int main() {
    std::ifstream fin("skidesign.in");
    int N, i, price=0;
    fin >> N;

    Hill hills[N];
    for (i = 0; i < N; ++i)
        fin >> hills[i].height;

    fin.close();

    qsort(hills, N, sizeof(Hill), HillCmpr);

    // biggest differences in hills are too big
    while (hills[N-1].height - hills[0].height > 17) {
        addToHills(hills, N);
        // addToHills (despite its bad naming) sorts the hills after changing them. So no need to qsort again.
        // qsort(hills, N, sizeof(Hill), HillCmpr);
    }

    for (i = 0; i < N; ++i) {
        price += hills[i].change * hills[i].change;
    }

    std::ofstream fout("skidesign.out");
    fout << price << std::endl;
    fout.close();
    

    return 0;
}