/*
ID: caleb.h1
LANG: C++
PROG: transform
*/

#include <iostream>
#include <fstream>

#define BLACK '@'
#define WHITE '-'

bool isSame(char **first, char **second, const size_t& N);
void debugPrint2dArray(char **array, const size_t& N);
void print2dArray(char **array, const size_t& N);
char** copy2dArray(char **array, const size_t& N);
void rotate2dArray(char **array, const size_t& N);
void flip2dArray(char **array, const size_t& N);
char** create2dArray(const size_t& N);
void delete2dArray(char **array, const size_t& N);

bool isSame(char **first, char **second, const size_t& N) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (first[i][j] != second[i][j])
                return false;
        }
    }
    return true;
}

void debugPrint2dArray(char **array, const size_t& N) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            std::cout << "i: " << i << " j: " << j << ' ' << array[i][j] << std::endl;
        }
    }
}

void print2dArray(char **array, const size_t& N) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            std::cout << array[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

char** copy2dArray(char **array, const size_t& N) {
    char **newArray = new char *[N];
    for (size_t i = 0; i < N; ++i) {
        newArray[i] = new char[N];
        for (size_t j = 0; j < N; ++j) {
            newArray[i][j] = array[i][j];
        }
    }
    return newArray;
}

void rotate2dArray(char **array, const size_t& N) {
    char **copy = copy2dArray(array, N);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            array[i][j] = copy[N-j-1][i];
        }
    }
    delete2dArray(copy, N);
}

void flip2dArray(char **array, const size_t& N) {
    char **copy = copy2dArray(array, N);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            array[i][j] = copy[i][N-j-1];
        }
    }
    delete2dArray(copy, N);
}

char** create2dArray(const size_t& N) {
    char **array = new char *[N];
    for (size_t i = 0; i < N; ++i)
        array[i] = new char[N];
    return array;
}

void delete2dArray(char **array, const size_t& N) {
    for (size_t i = 0; i < N; ++i) {
        delete [] array[i];
    }
    delete [] array;
}

// Find the manipulations needed to get the startSquare to the endSquare
int findPattern(char **startSquare, char **endSquare, const size_t& N) {
    
    // 1, 2, 3: N 90 degrees rotations
    for (int i = 1; i < 4; ++i) {
        rotate2dArray(startSquare, N);
        if (isSame(startSquare, endSquare, N))
            return i;
    }

    // rotate startSquare so it's normal again
    rotate2dArray(startSquare, N);

    // 4: Flipped
    flip2dArray(startSquare, N);
    if (isSame(startSquare, endSquare, N))
        return 4;

    // 5: Combination (Flip + any rotate)
    for (int i = 0; i < 3; ++i) {
        rotate2dArray(startSquare, N);
        if (isSame(startSquare, endSquare, N))
            return 5;
    }
    
    // 6: No change
    if (isSame(startSquare, endSquare, N))
        return 6;

    // 7: Invalid
    return 7;
}

int main() {
    // Read in file
    std::ifstream infile("transform.in");
    size_t N;
    infile >> N;

    // startSquare is a pointer to a new array of char pointers
    // each pointer leads to somewhere in the heap
    // and has N chars allocated
    // startSquare[0] is the first pointer to an array, etc.
    char **startSquare = create2dArray(N);
    char **endSquare = create2dArray(N);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            infile >> startSquare[i][j];
        }
    }
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            infile >> endSquare[i][j];
        }
    }

    infile.close();

    std::ofstream outfile("transform.out");
    outfile << findPattern(startSquare, endSquare, N) << std::endl;
    outfile.close();


    
    delete2dArray(startSquare, N);
    delete2dArray(endSquare, N);
    return 0;
}