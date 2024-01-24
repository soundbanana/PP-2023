#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

const int n = 1000000;
int a[n];

void merge(int l, int r) {
    if (r == l) return;

    if (r - l == 1) {
        if (a[r] < a[l]) swap(a[r], a[l]);
        return;
    }

    int m = (r + l) / 2;

    merge(l, m);
    merge(m + 1, r);

    int buf[n];
    int cur_l = l;
    int cur_r = m + 1;
    int cur = 0;

    while (r - l + 1 != cur) {
        if (cur_l > m)
            buf[cur++] = a[cur_r++];
        else if (cur_r > r)
            buf[cur++] = a[cur_l++];
        else if (a[cur_l] > a[cur_r])
            buf[cur++] = a[cur_r++];
        else
            buf[cur++] = a[cur_l++];
    }

    for (int i = 0; i < cur; i++)
        a[i + l] = buf[i];
}

int main() {

    for (int i = 0; i < n; ++i)
        a[i] = rand() % 1000 + 1;

    clock_t start = clock();

    merge(0, n - 1);

    clock_t end = clock();
    double duration = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000000.0);

    printf("Время выполнения программы: %f мкс\n", duration);

    return 0;
}