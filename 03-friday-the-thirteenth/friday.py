"""
ID: caleb.h1
LANG: PYTHON3
PROG: friday
"""

'''
   Test 1: TEST OK [0.025 secs, 9280 KB]
   Test 2: TEST OK [0.025 secs, 9276 KB]
   Test 3: TEST OK [0.022 secs, 9428 KB]
   Test 4: TEST OK [0.025 secs, 9324 KB]
   Test 5: TEST OK [0.025 secs, 9284 KB]
   Test 6: TEST OK [0.025 secs, 9428 KB]
   Test 7: TEST OK [0.025 secs, 9332 KB]
   Test 8: TEST OK [0.027 secs, 9348 KB]
'''

def get_days_from_month(month:int, year:int=1) -> int:
    # 0 - jan
    # 1 - feb
    month_31 = {0, 2, 4, 6, 7, 9, 11}
    if month in month_31:
        return 31
    if month == 1:
        # definitely not a leap year
        if year % 4:
            return 28
        # divisible by 100 and NOT 400
        if year % 100 == 0 and year % 400:
            return 28
        # divis by 4 or by 400 but not 100
        return 29
    return 30
        

def main():

    day_counter = [0] * 7
    cur_day = 13 % 7      # 13-Jan-1900

    with open('friday.in', 'r') as f:
        num_years = int(f.read())

    for cur_year in range(num_years):
        # repeat 12 for 12 months
        for cur_month in range(12): 
            day_counter[cur_day] += 1
            cur_day += get_days_from_month(cur_month, 1900 + cur_year)
            cur_day %= 7

    day_counter = [str(i) for i in day_counter]

    with open('friday.out', 'w') as f:
        f.write(' '.join([day_counter[-1]] + day_counter[:-1]))
        f.write('\n')

if __name__ == '__main__':
    main()