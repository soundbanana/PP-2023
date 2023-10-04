#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

// Function to multiply a matrix by a vector
void matrixVectorMultiply(int m, int n, int** matrix, int* vector, int* result) {
#pragma omp parallel for shared(result)
    for (int i = 0; i < m; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += matrix[i][j] * vector[j];
        }
        result[i] = sum;
    }
}

int main() {
    int m = 1000; // Number of rows
    int n = 1000; // Number of columns

    // Initialize the matrix and vector
    int** matrix = new int*[m];
    for (int i = 0; i < m; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matrix[i][j] = i + j;
        }
    }

    int* vector = new int[n];
    for (int j = 0; j < n; j++) {
        vector[j] = j + 6;
    }

    int* result = new int[m];

    // Measure the start time
    auto start_time = chrono::high_resolution_clock::now();

    // Call the function for matrix-vector multiplication
    matrixVectorMultiply(m, n, matrix, vector, result);

    // Measure the end time
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    cout << "Elapsed time: " << duration.count() << " microseconds." << endl;

    // Output results (first 10 elements)
    cout << "Results (first 10 items): ";
    for (int i = 0; i < 10; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    // Free memory
    for (int i = 0; i < m; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] vector;
    delete[] result;

    return 0;
}