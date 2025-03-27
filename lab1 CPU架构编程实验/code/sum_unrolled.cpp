#include <windows.h>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <iomanip>
#include <fstream>
using namespace std;

using Vector = vector<double>;

// ------------------ 四种求和算法 ------------------

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
    for (int m = len; m > 1; m /= 2)
        for (int i = 0; i < m / 2; i++)
            v[i] = v[i * 2] + v[i * 2 + 1];
    return v[0];
}

// 4. 四路展开加法
double sum_unrolled_4(const Vector& v, int n) {
    double sum = 0;
    int i = 0;
    for (; i + 3 < n; i += 4) {
        sum += v[i] + v[i + 1] + v[i + 2] + v[i + 3];
    }
    for (; i < n; ++i) {
        sum += v[i];
    }
    return sum;
}

double sum_unrolled_64(const Vector& v, int n) {
    double sum = 0;
    int i = 0;
    for (; i + 63 < n; i += 64) {
        sum += v[i + 0] + v[i + 1] + v[i + 2] + v[i + 3] + v[i + 4] + v[i + 5] + v[i + 6] + v[i + 7] + v[i + 8] + v[i + 9] + v[i + 10] + v[i + 11] + v[i + 12] + v[i + 13] + v[i + 14] + v[i + 15] + v[i + 16] + v[i + 17] + v[i + 18] + v[i + 19] + v[i + 20] + v[i + 21] + v[i + 22] + v[i + 23] + v[i + 24] + v[i + 25] + v[i + 26] + v[i + 27] + v[i + 28] + v[i + 29] + v[i + 30] + v[i + 31] + v[i + 32] + v[i + 33] + v[i + 34] + v[i + 35] + v[i + 36] + v[i + 37] + v[i + 38] + v[i + 39] + v[i + 40] + v[i + 41] + v[i + 42] + v[i + 43] + v[i + 44] + v[i + 45] + v[i + 46] + v[i + 47] + v[i + 48] + v[i + 49] + v[i + 50] + v[i + 51] + v[i + 52] + v[i + 53] + v[i + 54] + v[i + 55] + v[i + 56] + v[i + 57] + v[i + 58] + v[i + 59] + v[i + 60] + v[i + 61] + v[i + 62] + v[i + 63];
    }
    for (; i < n; ++i) {
        sum += v[i];
    }
    return sum;
}

double sum_unrolled_128(const Vector& v, int n) {
    double sum = 0;
    int i = 0;
    for (; i + 127 < n; i += 128) {
        sum += v[i + 0] + v[i + 1] + v[i + 2] + v[i + 3] + v[i + 4] + v[i + 5] + v[i + 6] + v[i + 7] + v[i + 8] + v[i + 9] + v[i + 10] + v[i + 11] + v[i + 12] + v[i + 13] + v[i + 14] + v[i + 15] + v[i + 16] + v[i + 17] + v[i + 18] + v[i + 19] + v[i + 20] + v[i + 21] + v[i + 22] + v[i + 23] + v[i + 24] + v[i + 25] + v[i + 26] + v[i + 27] + v[i + 28] + v[i + 29] + v[i + 30] + v[i + 31] + v[i + 32] + v[i + 33] + v[i + 34] + v[i + 35] + v[i + 36] + v[i + 37] + v[i + 38] + v[i + 39] + v[i + 40] + v[i + 41] + v[i + 42] + v[i + 43] + v[i + 44] + v[i + 45] + v[i + 46] + v[i + 47] + v[i + 48] + v[i + 49] + v[i + 50] + v[i + 51] + v[i + 52] + v[i + 53] + v[i + 54] + v[i + 55] + v[i + 56] + v[i + 57] + v[i + 58] + v[i + 59] + v[i + 60] + v[i + 61] + v[i + 62] + v[i + 63] + v[i + 64] + v[i + 65] + v[i + 66] + v[i + 67] + v[i + 68] + v[i + 69] + v[i + 70] + v[i + 71] + v[i + 72] + v[i + 73] + v[i + 74] + v[i + 75] + v[i + 76] + v[i + 77] + v[i + 78] + v[i + 79] + v[i + 80] + v[i + 81] + v[i + 82] + v[i + 83] + v[i + 84] + v[i + 85] + v[i + 86] + v[i + 87] + v[i + 88] + v[i + 89] + v[i + 90] + v[i + 91] + v[i + 92] + v[i + 93] + v[i + 94] + v[i + 95] + v[i + 96] + v[i + 97] + v[i + 98] + v[i + 99] + v[i + 100] + v[i + 101] + v[i + 102] + v[i + 103] + v[i + 104] + v[i + 105] + v[i + 106] + v[i + 107] + v[i + 108] + v[i + 109] + v[i + 110] + v[i + 111] + v[i + 112] + v[i + 113] + v[i + 114] + v[i + 115] + v[i + 116] + v[i + 117] + v[i + 118] + v[i + 119] + v[i + 120] + v[i + 121] + v[i + 122] + v[i + 123] + v[i + 124] + v[i + 125] + v[i + 126] + v[i + 127];
    }
    for (; i < n; ++i) {
        sum += v[i];
    }
    return sum;
}

int unroll_algo_64(const Vector& arr, int len)
{
    Vector total(64);
    for (int i = 0; i < len; i += 64)
    {
        total[0] += arr[i + 0];
        total[1] += arr[i + 1];
        total[2] += arr[i + 2];
        total[3] += arr[i + 3];
        total[4] += arr[i + 4];
        total[5] += arr[i + 5];
        total[6] += arr[i + 6];
        total[7] += arr[i + 7];
        total[8] += arr[i + 8];
        total[9] += arr[i + 9];
        total[10] += arr[i + 10];
        total[11] += arr[i + 11];
        total[12] += arr[i + 12];
        total[13] += arr[i + 13];
        total[14] += arr[i + 14];
        total[15] += arr[i + 15];
        total[16] += arr[i + 16];
        total[17] += arr[i + 17];
        total[18] += arr[i + 18];
        total[19] += arr[i + 19];
        total[20] += arr[i + 20];
        total[21] += arr[i + 21];
        total[22] += arr[i + 22];
        total[23] += arr[i + 23];
        total[24] += arr[i + 24];
        total[25] += arr[i + 25];
        total[26] += arr[i + 26];
        total[27] += arr[i + 27];
        total[28] += arr[i + 28];
        total[29] += arr[i + 29];
        total[30] += arr[i + 30];
        total[31] += arr[i + 31];
        total[32] += arr[i + 32];
        total[33] += arr[i + 33];
        total[34] += arr[i + 34];
        total[35] += arr[i + 35];
        total[36] += arr[i + 36];
        total[37] += arr[i + 37];
        total[38] += arr[i + 38];
        total[39] += arr[i + 39];
        total[40] += arr[i + 40];
        total[41] += arr[i + 41];
        total[42] += arr[i + 42];
        total[43] += arr[i + 43];
        total[44] += arr[i + 44];
        total[45] += arr[i + 45];
        total[46] += arr[i + 46];
        total[47] += arr[i + 47];
        total[48] += arr[i + 48];
        total[49] += arr[i + 49];
        total[50] += arr[i + 50];
        total[51] += arr[i + 51];
        total[52] += arr[i + 52];
        total[53] += arr[i + 53];
        total[54] += arr[i + 54];
        total[55] += arr[i + 55];
        total[56] += arr[i + 56];
        total[57] += arr[i + 57];
        total[58] += arr[i + 58];
        total[59] += arr[i + 59];
        total[60] += arr[i + 60];
        total[61] += arr[i + 61];
        total[62] += arr[i + 62];
        total[63] += arr[i + 63];
    }
    return sum_naive(total, 64);
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
    const int step = 64;
    const int max_n = 65536;

    cout << fixed << setprecision(6);
    cout << "n, naive(ms), 2way(ms), unrolled_4(ms), unrolled_64(ms), unrolled_128(ms)\n";

    ofstream fout("result_unrolled.csv");
    fout << "n,naive(ms),2way(ms),unrolled(ms),unrolled_64(ms),unrolled_128(ms)\n";

    for (int n = step; n <= max_n; n += step) {
        Vector v(n);
        for (int i = 0; i < n; ++i) v[i] = i;

        double t_naive = benchmark([&]() { sum_naive(v, n); });
        double t_2way = benchmark([&]() { sum_2way(v, n); });
        double t_unroll_4 = benchmark([&]() { sum_unrolled_4(v, n); });
        double t_unroll_64 = benchmark([&]() { sum_unrolled_64(v, n); });
        double t_unroll_128 = benchmark([&]() { sum_unrolled_128(v, n); });

        // double t_unroll_algo_64 = benchmark([&]() { unroll_algo_64(v, n); });
        // double t_red     = benchmark([&]() { Vector tmp = v; return sum_reduction(tmp, n); });

        cout << n << ", " << t_naive << ", " << t_2way << ", " << t_unroll_4<<", " << t_unroll_64 << ", " << t_unroll_128 << "\n";
        fout << n << "," << t_naive << "," << t_2way << "," << t_unroll_4<<"," << t_unroll_64 <<"," << t_unroll_128<< "\n";
    }

    return 0;
}
