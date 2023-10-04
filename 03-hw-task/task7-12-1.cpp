// 1. Algorithm Complexity: Matrix-vector multiplication has O(m * n) complexity.
#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

int main() {
    int m = 4; // Number of rows
    int n = 2; // Number of columns
    int matrix[m][n];
    int* vector = new int[n];
    int* result = new int[m];

    // Initialize the matrix and vector
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = i + j;
        }
    }

    for (int j = 0; j < n; j++) {
        vector[j] = j + 6;
    }

    int num_procs = omp_get_max_threads();
    int num_cols_per_proc = n / num_procs;

    int middleMatrix[m][n];

    // Measure the start time
    auto start_time = chrono::high_resolution_clock::now();

#pragma omp parallel shared(middleMatrix)
    {
        int proc_id = omp_get_thread_num();

        int start_col = proc_id * num_cols_per_proc;
        int end_col = (proc_id == num_procs - 1) ? n : (proc_id + 1) * num_cols_per_proc;

        for (int i = start_col; i < end_col; i++) {
            for (int j = 0; j < m; j++) {
                middleMatrix[j][i] = matrix[j][i] * vector[i];
            }
        }
    }

#pragma omp parallel for shared(result)
    for (int i = 0; i < m; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += middleMatrix[i][j];
        }
        result[i] = sum;
    }

    // Measure the end time
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    cout << "Elapsed time: " << duration.count() << " microseconds." << endl;

    // Calculate and output theoretical estimates
    double theoretical_time = (double)m * n / num_procs; // Simplified estimate
    cout << "Theoretical time (simplified): " << theoretical_time << " microseconds." << endl;

    // Output results
    for (int i = 0; i < m; i++) {
        cout << "Result[" << i << "] = " << result[i] << endl;
    }

    // Free memory
    delete[] vector;
    delete[] result;

    return 0;
}