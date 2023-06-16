#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

void dec2bin(fstream& decFile, fstream& binFile) {
    while (!decFile.eof()) {
        int decNum;
        char binRev[] = "00000000";

        decFile >> decNum;
        for (int i = 0; decNum > 0; i++) {
            binRev[i] = decNum % 2 + 48;
            decNum /= 2;
        }
        for (int i = 0; i < 4; i++) {
            char buff = binRev[i];
            binRev[i] = binRev[8 - i - 1];
            binRev[8 - i - 1] = buff;
        }
        binFile << binRev;
    }
}

bool areEqual(char* str1, char* str2) {
    for (int i = 0; i < 8; i++)
        if (str1[i] != str2[i])
            return false;
    return true;
}

void bin2let(fstream& binFile, fstream& bin2letFile, char* matrix[], int row, int col) {
    char bin1[9];
    char bin2[9];
    char let;
    for (int m = 1; m < row; m++) {
        for (int n = 1; n < col; n++) {
            binFile.read(bin1, 8);
            bin2letFile.seekg(0);
            while (!bin2letFile.eof()) {
                bin2letFile >> bin2;
                bin2letFile >> let;
                if (areEqual(bin1, bin2)) {
                    matrix[m][n] = let;
                    break;
                }
            }
        }
    }
}

void addKeyWords(char* matrix[], const char* w1, const char* w2, int row, int col) {
    matrix[0][0] = ' ';
    for (int i = 1; i < row; i++) {
        matrix[0][i] = w1[i - 1];
    }
    for (int i = 1; i < col; i++) {
        matrix[i][0] = w2[i - 1];
    }
}


/*void sortRows(char* matrix[], int row, int col)
{
    for (int j = 1; j < col; j++)
    {
        for (int i = 0; i < row; i++) {
            sort(matrix[i] + 1, matrix[i] + col);
        }
    }
}

void sortColumns(char* matrix[], int row, int col) 
{
    for (int j = 0; j < col; j++) {
        char* column = new char [row];
        for (int i = 0; i < row; i++) {
            column[i] = matrix[i][j];
        }
        sort(column, column + row);
        for (int i = 1; i < row; i++) {
            matrix[i][j] = column[i];
        }
    }
}*/

/*void sortrow(char* matrix[], int row, int col)
{
    char** columnArray = new char* [row];
    for (int i = 0; i < row; i++) {
        columnArray[i] = new char[col];
    }
    for (int i = 0; i < row; i++) 
    {
        for (int j = 1; j < row; j++)
        {
            columnArray[i][j] = matrix[i][j];
        }
    }
    sort(columnArray, columnArray + row);
    for (int i = 0; i < row; i++) 
    {
        for (int j = 1; j < row; j++)
        {
            matrix[i][j] = columnArray[i][j];
        }
    }
    delete[] columnArray;
}*/

void sortRow(char* matrix[], int row, int col) {
    for (size_t colIndex = 1; colIndex < 5; colIndex++) {
        for (size_t i = 1; i < row; i++) {
            size_t min = i;

            for (size_t j = i + 1; j < row; j++) {
                if (matrix[j][colIndex] < matrix[min][colIndex]) {
                    min = j;
                }
            }

            if (min != i) {
                char* tmp = matrix[i];  
                matrix[i] = matrix[min];
                matrix[min] = tmp;
            }
        }
    }
}

void sortCols(char** matrix, int rows, int cols) {
   
    char* tempRow = new char[cols];
    std::copy(matrix[0], matrix[0] + cols, tempRow);

    std::sort(tempRow, tempRow + cols);


    char** tempMatrix = new char* [rows];
    for (int i = 0; i < rows; i++) {
        tempMatrix[i] = new char[cols];
    }

    for (int j = 0; j < cols; j++) {
        char letter = tempRow[j];
        int originalIndex = -1;

        for (int k = 0; k < cols; k++) {
            if (matrix[0][k] == letter) {
                originalIndex = k;
                break;
            }
        }

        for (int i = 0; i < rows; i++) {
            tempMatrix[i][j] = matrix[i][originalIndex];
        }
    }

    for (int i = 0; i < rows; i++) {
        std::copy(tempMatrix[i], tempMatrix[i] + cols, matrix[i]);
    }

    for (int i = 0; i < rows; i++) {
        delete[] tempMatrix[i];
    }
    delete[] tempMatrix;
    delete[] tempRow;
}


int main() {
    fstream decFile;
    fstream binFile;
    fstream bin2letFile;

    // === dec2bin ===============
    decFile.open("dec.txt", std::fstream::in);
    if (!decFile.is_open()) {
        cout << "'dec.txt' doesn't open";
        return 0;
    }
    binFile.open("bin.txt", std::fstream::out);

    dec2bin(decFile, binFile);

    decFile.close();
    binFile.close();
    // ===========================

    // === bin2let ===============
    binFile.open("bin.txt", std::fstream::in);
    bin2letFile.open("bin2let.txt", std::fstream::in);
    if (!bin2letFile.is_open()) {
        cout << "'bin2let.txt' doesn't open";
        return 0;
    }

    int row = 5;
    int col = 5;

    char** matrix = new char* [row];
    for (int i = 0; i < row; i++) {
        matrix[i] = new char[col];
    }

    bin2let(binFile, bin2letFile, matrix, 5, 5);
    addKeyWords(matrix, "save", "fish", 5, 5);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }

    cout << endl;

    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
    
    sortRow(matrix, row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
    cout << endl;

    sortCols(matrix, row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
    cout << endl;

    binFile.close();
    bin2letFile.close();
    // ===========================

    // === del arr ===============
    for (int i = 0; i < col; i++)
        delete[] matrix[i];
    delete[] matrix;
    // ===========================

    return 0;
}

