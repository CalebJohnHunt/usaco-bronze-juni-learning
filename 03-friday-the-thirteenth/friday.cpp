/*
ID: caleb.h1
LANG: C++
PROG: friday
*/

/*
   Test 1: TEST OK [0.004 secs, 1340 KB]
   Test 2: TEST OK [0.004 secs, 1420 KB]
   Test 3: TEST OK [0.004 secs, 1356 KB]
   Test 4: TEST OK [0.004 secs, 1420 KB]
   Test 5: TEST OK [0.004 secs, 1348 KB]
   Test 6: TEST OK [0.004 secs, 1352 KB]
   Test 7: TEST OK [0.007 secs, 1352 KB]
   Test 8: TEST OK [0.007 secs, 1360 KB]
*/

#include <fstream>
#include <unordered_set>

ushort get_days_from_month(const char month, const uint year) {
    // 0 - jan
    // 1 - feb
    std::unordered_set<char> month_31 = {0, 2, 4, 6, 7, 9, 11};
    if (month_31.find(month) != month_31.end())
        return 31;
    if (month == 1) {
        // Not divis by 4
        // or divis by 100 but not 400
        if (year % 4 || year % 100 == 0 && year % 400)
            return 28;
        // divis by 4 or by 400 but not 100
        else
            return 29;
    }
    return 30;
}
        

int main() {
    ushort day_counter[] = {0, 0, 0, 0, 0, 0, 0};
    char cur_day = 13 % 7;      // 13-Jan-1900

    std::ifstream infile("friday.in");
    uint num_years;
    infile >> num_years;
    infile.close();

    for (uint cur_year=0; cur_year < num_years; ++cur_year) {
        // repeat 12 for 12 months
        for (char cur_month=0; cur_month<12; ++cur_month) {
            ++day_counter[(cur_day+1) % 7];
            cur_day += get_days_from_month(cur_month, 1900 + cur_year);
            cur_day %= 7;
        } 
    }

    std::ofstream outfile("friday.out");
    for (char d=0; d<7; ++d) {
        outfile << day_counter[d];
        if (d != 6) {
            outfile << ' ';
        }
    }
    outfile << '\n';
    outfile.close();
}