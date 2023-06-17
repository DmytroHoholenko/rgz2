#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

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

void bin2let(fstream& binFile, fstream& bin2letFile, char* matrix[], int row, int col) {
    char bin1[9];
    char bin2[9];
    char let;
    for (int m = 1; m < row; m++) {
        for (int n = 1; n < col; n++) {
            binFile.get(bin1, 9);
            bin2letFile.seekg(0);
            while (!bin2letFile.eof()) {
                bin2letFile >> bin2;
                bin2letFile >> let;
                if (strcmp(bin1, bin2) == 0) {
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
        matrix[i][0] = w2[i - 1];
    }
    for (int i = 1; i < col; i++) {
        matrix[0][i] = w1[i - 1];
    }
}

void sortRows(char* matrix[], int row, int col) {
    for (int i = 1; i < col; i++) {
        int max = i;
        for (int j = i + 1; j < row; j++) {
            if (matrix[max][0] > matrix[j][0])
                max = j;
        }
        if (max != i) {
            for (int j = 0; j < row; j++) {
                int tmp = matrix[max][j];
                matrix[max][j] = matrix[i][j];
                matrix[i][j] = tmp;
            }
        }
    }
}

void sortCols(char** matrix, int rows, int cols) {
    char* tempRow = new char[cols];
    std::copy(matrix[0], matrix[0] + cols, tempRow);

    std::sort(tempRow, tempRow + cols);

    char** tempMatrix = new char* [rows];
    for (int i = 0; i < rows; i++)
        tempMatrix[i] = new char[cols];

    for (int j = 0; j < cols; j++) {
        char letter = tempRow[j];
        int originalIndex = -1;

        for (int k = 0; k < cols; k++) {
            if (matrix[0][k] == letter) {
                originalIndex = k;
                break;
            }
        }

        for (int i = 0; i < rows; i++)
            tempMatrix[i][j] = matrix[i][originalIndex];
    }

    for (int i = 0; i < rows; i++)
        std::copy(tempMatrix[i], tempMatrix[i] + cols, matrix[i]);

    for (int i = 0; i < rows; i++)
        delete[] tempMatrix[i];
    delete[] tempMatrix;
    delete[] tempRow;
}

int main() {
    fstream decFile;
    fstream binFile;
    fstream bin2letFile;

    // === get num ===============
    int numNum, number;
    decFile.open("dec.txt", std::fstream::out);
    cout << "Set number(double) of numbers: ";
    do {
        cin >> numNum;
        if (numNum % 2 != 0) {
            cout << "Set other number!\n";
        }
    } while (numNum % 2 != 0);

    cout << "Set digits: ";
    for (int i = 0; i < numNum; i++) {
        cin >> number;
        decFile << number;
        if (i + 1 != numNum)
            decFile << ' ';
    }
    decFile.close();
    // ===========================

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

    // === get key words =========
    char w1[10] = "";
    char w2[10] = "";
    int row, col;
    cout << "Set key words. Condition: len(w1)*len(w2) == number of numbers\n";
    do {
        cin >> w1;
        cin >> w2;
        row = strlen(w2);
        col = strlen(w1);
        if (row * col != numNum)
            cout << "Set other words!\n";
    } while (row * col != numNum);
    // ===========================

    // === bin2let ===============
    binFile.open("bin.txt", std::fstream::in);
    bin2letFile.open("bin2let.txt", std::fstream::in);
    if (!bin2letFile.is_open()) {
        cout << "'bin2let.txt' doesn't open";
        return 0;
    }

    row++;
    col++;
    char** matrix = new char* [row];
    for (int i = 0; i < row; i++) {
        matrix[i] = new char[col];
    }

    addKeyWords(matrix, w1, w2, row, col);
    bin2let(binFile, bin2letFile, matrix, row, col);

    binFile.close();
    bin2letFile.close();
    // ===========================

    // === sort ==================
    sortRows(matrix, row, col);
    sortCols(matrix, row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
    // ===========================

    // === del arr ===============
    for (int i = 0; i < row; i++)
        delete[] matrix[i];
    delete[] matrix;
    // ===========================

    return 0;
}
