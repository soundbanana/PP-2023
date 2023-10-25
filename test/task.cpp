#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

void matrixMultiplication(int** matrixA, int** matrixB, int** result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

// Функция для ленточного перемножения матриц
void tapeMatrixMultiplication(int** matrixA, int** matrixB, int** result, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
            for (int k = 0; k < size; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

// Функция для блочного перемножения матриц
void blockMatrixMultiplication(int** matrixA, int** matrixB, int** result, int size, int blockSize) {
    #pragma omp parallel for collapse(3)
    for (int i = 0; i < size; i += blockSize) {
        for (int j = 0; j < size; j += blockSize) {
            for (int k = 0; k < size; k += blockSize) {
                // Выполняем умножение блоков матриц
                for (int x = i; x < min(i + blockSize, size); x++) {
                    for (int y = j; y < min(j + blockSize, size); y++) {
                        for (int z = k; z < min(k + blockSize, size); z++) {
                            result[x][y] += matrixA[x][z] * matrixB[z][y];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    const int size = 1000; // Размер матриц
    const int blockSize = 100; // Размер блока для блочного перемножения

    setlocale(LC_ALL, "C");
    int** matrixA = new int*[size];
    int** matrixB = new int*[size];
    int** result = new int*[size];

    for (int i = 0; i < size; i++) {
        matrixA[i] = new int[size];
        matrixB[i] = new int[size];
        result[i] = new int[size];
    }

    // Заполняем матрицы
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrixA[i][j] = rand() % 10;
            matrixB[i][j] = rand() % 10;
        }
    }

    // Замер времени для последовательного перемножения
    auto startTime = high_resolution_clock::now();

    for (int cycle = 1; cycle <= 20; cycle++) {
        matrixMultiplication(matrixA, matrixB, result, size);
    }

    auto endTime = high_resolution_clock::now();
    auto time = duration_cast<microseconds>(endTime - startTime).count();

    // Замер времени для ленточного перемножения
    startTime = high_resolution_clock::now();

    for (int cycle = 1; cycle <= 20; cycle++) {
        tapeMatrixMultiplication(matrixA, matrixB, result, size);
    }

    endTime = high_resolution_clock::now();
    auto timeTape = duration_cast<microseconds>(endTime - startTime).count();

    // Замер времени для блочного перемножения
    startTime = high_resolution_clock::now();

    for (int cycle = 1; cycle <= 20; cycle++) {
        blockMatrixMultiplication(matrixA, matrixB, result, size, blockSize);
    }

    endTime = high_resolution_clock::now();
    auto timeBlock = duration_cast<microseconds>(endTime - startTime).count();

    cout << "Time complete list multiplication: " << time/20 << " mcs" << endl;
    cout << "Time complete list multiplication: " << timeTape/20 << " mcs" << endl;
    cout << "Time complete block multiplication: " << timeBlock/20 << " mcs" << endl;

    // Освобождаем память
    for (int i = 0; i < size; i++) {
        delete[] matrixA[i];
        delete[] matrixB[i];
        delete[] result[i];
    }

    delete[] matrixA;
    delete[] matrixB;
    delete[] result;

    return 0;
}