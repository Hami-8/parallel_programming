#include <windows.h>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <iomanip>
#include <fstream>
using namespace std;

using Vector = vector<double>;

// ------------------ 三种求和算法 ------------------

// 1. 链式加法
double sum_naive(const Vector& v, int n) {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += v[i];
    }
    return sum;
}

// 2. 双路加法
double sum_2way(const Vector& v, int n) {
    double sum1 = 0, sum2 = 0;
    for (int i = 0; i < n; i += 2) {
        sum1 += v[i];
        if (i + 1 < n) sum2 += v[i + 1];
    }
    return sum1 + sum2;
}

// 3. 归约加法
double sum_reduction(Vector& v, int len) {
    int n = v.size();
    while (n > 1) {
        for (int i = 0; i < n / 2; ++i) {
            v[i] = v[2 * i] + v[2 * i + 1];
        }
        n /= 2;
    }

    /*for (int m = len; m > 1; m /= 2)
        for (int i = 0; i < m / 2; i++)
            v[i] = v[i * 2] + v[i * 2 + 1];*/
    return v[0];
}

// ------------------ 通用计时器 ------------------

template<typename Func>
double benchmark(Func func, int repeat = 100) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&start);
    for (int i = 0; i < repeat; ++i) {
        func();
    }
    QueryPerformanceCounter(&end);

    double elapsed_ms = (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    return elapsed_ms / repeat;
}

// ------------------ 主函数测试 ------------------

int main() {
    // === 全局运行时间开始 ===
    LARGE_INTEGER freq, start_all, end_all;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start_all);
    // ========================

    const int step = 64;
    const int max_n = 65536;

    cout << fixed << setprecision(6);
    cout << "n, naive(ms), 2way(ms), reduction(ms)\n";

    ofstream fout("result2_reduction.csv");
    fout << "n,naive(ms),2way(ms),reduction(ms)\n";

    for (int n = step; n <= max_n; n += step) {
        Vector v(n);
        for (int i = 0; i < n; ++i) v[i] = i;

        double t_naive = benchmark([&]() { sum_naive(v, n); });
        double t_2way = benchmark([&]() { sum_2way(v, n); });

        double t_red = benchmark([&]() { sum_reduction(v, n); });

        cout << n << ", " << t_naive << ", " << t_2way <<", " << t_red<< "\n";
        fout << n << "," << t_naive << "," << t_2way << "," << t_red << "\n";
    }

    // === 全局运行时间结束 ===
    QueryPerformanceCounter(&end_all);
    double total_ms = (end_all.QuadPart - start_all.QuadPart) * 1000.0 / freq.QuadPart;
    cout << "Total Runtime: " << total_ms << " ms\n";
    // fout << "Total Runtime(ms)," << total_ms << "\n";
    // ========================

    return 0;
}
