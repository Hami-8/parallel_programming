#include <windows.h>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <fstream>
using namespace std;

using Matrix = vector<vector<double>>;
using Vector = vector<double>;

// ------------------ 实验一：矩阵列与向量内积 ------------------

// 平凡算法（列主访问）
void matrix_vector_naive(const Matrix& A, const Vector& v, Vector& result, int n) {
    for (int j = 0; j < n; ++j) {
        result[j] = 0;
        for (int i = 0; i < n; ++i) {
            result[j] += A[i][j] * v[i];
        }
    }
}

// 优化算法（行主访问）
void matrix_vector_optimized(const Matrix& A, const Vector& v, Vector& result, int n) {
    fill(result.begin(), result.end(), 0);
    for (int i = 0; i < n; ++i) {
#pragma loop(no_vector)
#pragma loop(no_unroll)
        for (int j = 0; j < n; ++j) {
            result[j] += A[i][j] * v[i];
        }
    }
}

// 进阶优化算法：行主访问 + 列方向循环展开
//void matrix_vector_unrolled(const Matrix& A, const Vector& v, Vector& result, int n) {
//    fill(result.begin(), result.end(), 0);
//    for (int i = 0; i < n; ++i) {
//        int j = 0;
//        for (; j + 63 < n; j += 64) {
//            // 64路展开内积计算
//            result[j + 0] += A[i][j + 0] * v[i];
//            result[j + 1] += A[i][j + 1] * v[i];
//            result[j + 2] += A[i][j + 2] * v[i];
//            result[j + 3] += A[i][j + 3] * v[i];
//            result[j + 4] += A[i][j + 4] * v[i];
//            result[j + 5] += A[i][j + 5] * v[i];
//            result[j + 6] += A[i][j + 6] * v[i];
//            result[j + 7] += A[i][j + 7] * v[i];
//            result[j + 8] += A[i][j + 8] * v[i];
//            result[j + 9] += A[i][j + 9] * v[i];
//            result[j + 10] += A[i][j + 10] * v[i];
//            result[j + 11] += A[i][j + 11] * v[i];
//            result[j + 12] += A[i][j + 12] * v[i];
//            result[j + 13] += A[i][j + 13] * v[i];
//            result[j + 14] += A[i][j + 14] * v[i];
//            result[j + 15] += A[i][j + 15] * v[i];
//            result[j + 16] += A[i][j + 16] * v[i];
//            result[j + 17] += A[i][j + 17] * v[i];
//            result[j + 18] += A[i][j + 18] * v[i];
//            result[j + 19] += A[i][j + 19] * v[i];
//            result[j + 20] += A[i][j + 20] * v[i];
//            result[j + 21] += A[i][j + 21] * v[i];
//            result[j + 22] += A[i][j + 22] * v[i];
//            result[j + 23] += A[i][j + 23] * v[i];
//            result[j + 24] += A[i][j + 24] * v[i];
//            result[j + 25] += A[i][j + 25] * v[i];
//            result[j + 26] += A[i][j + 26] * v[i];
//            result[j + 27] += A[i][j + 27] * v[i];
//            result[j + 28] += A[i][j + 28] * v[i];
//            result[j + 29] += A[i][j + 29] * v[i];
//            result[j + 30] += A[i][j + 30] * v[i];
//            result[j + 31] += A[i][j + 31] * v[i];
//            result[j + 32] += A[i][j + 32] * v[i];
//            result[j + 33] += A[i][j + 33] * v[i];
//            result[j + 34] += A[i][j + 34] * v[i];
//            result[j + 35] += A[i][j + 35] * v[i];
//            result[j + 36] += A[i][j + 36] * v[i];
//            result[j + 37] += A[i][j + 37] * v[i];
//            result[j + 38] += A[i][j + 38] * v[i];
//            result[j + 39] += A[i][j + 39] * v[i];
//            result[j + 40] += A[i][j + 40] * v[i];
//            result[j + 41] += A[i][j + 41] * v[i];
//            result[j + 42] += A[i][j + 42] * v[i];
//            result[j + 43] += A[i][j + 43] * v[i];
//            result[j + 44] += A[i][j + 44] * v[i];
//            result[j + 45] += A[i][j + 45] * v[i];
//            result[j + 46] += A[i][j + 46] * v[i];
//            result[j + 47] += A[i][j + 47] * v[i];
//            result[j + 48] += A[i][j + 48] * v[i];
//            result[j + 49] += A[i][j + 49] * v[i];
//            result[j + 50] += A[i][j + 50] * v[i];
//            result[j + 51] += A[i][j + 51] * v[i];
//            result[j + 52] += A[i][j + 52] * v[i];
//            result[j + 53] += A[i][j + 53] * v[i];
//            result[j + 54] += A[i][j + 54] * v[i];
//            result[j + 55] += A[i][j + 55] * v[i];
//            result[j + 56] += A[i][j + 56] * v[i];
//            result[j + 57] += A[i][j + 57] * v[i];
//            result[j + 58] += A[i][j + 58] * v[i];
//            result[j + 59] += A[i][j + 59] * v[i];
//            result[j + 60] += A[i][j + 60] * v[i];
//            result[j + 61] += A[i][j + 61] * v[i];
//            result[j + 62] += A[i][j + 62] * v[i];
//            result[j + 63] += A[i][j + 63] * v[i];
//
//        }
//        //for (; j < n; ++j) {
//        //    result[j] += A[i][j] * v[i];
//        //}
//    }
//}

void matrix_vector_unrolled(const Matrix& A, const Vector& v, Vector& result, int n) {
    fill(result.begin(), result.end(), 0);
    for (int i = 0; i < n; ++i) {
#pragma unroll(64)
//#pragma loop(no_vector)
//#pragma loop(no_unroll)
        for (int j = 0; j < n; ++j) {
            result[j] += A[i][j] * v[i];
        }
    }
}

// ------------------ 通用计时器 ------------------

template<typename Func>
double benchmark(Func func, int repeat = 50) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&start);
    for (int i = 0; i < repeat; ++i) {
        func();  // 执行待测试函数
    }
    QueryPerformanceCounter(&end);

    double elapsed_ms = (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    return elapsed_ms / repeat;  // 返回平均毫秒
}

// ------------------ 数据生成 ------------------

void generate_data(Matrix& A, Vector& v, int n) {
    A.resize(n, Vector(n));
    v.resize(n);
    for (int i = 0; i < n; ++i) {
        v[i] = i;
        for (int j = 0; j < n; ++j) {
            A[i][j] = i + j;
        }
    }
}

// ------------------ 主函数测试 ------------------

int main() {
    const int step = 64;
    const int max_n = 4096;

    ofstream fout("result.csv");
    fout << "n,naive_ms,optimized_ms,unrolled_ms\n";

    for (int n = step; n <= max_n; n += step) {
        Matrix A;
        Vector v, result(n);
        generate_data(A, v, n);

        cout << "n = " << n << ":\n";

        double t1 = benchmark([&]() {
            matrix_vector_naive(A, v, result, n);
            });
        cout << "  平凡算法时间（ms）: " << t1 << endl;

        

        double t2 = benchmark([&]() {
            matrix_vector_optimized(A, v, result, n);
            });
        cout << "  行主访问时间（ms）: " << t2 << endl;

        double t3 = benchmark([&]() {
            matrix_vector_unrolled(A, v, result, n);
            });
        cout << "  展开优化时间（ms）: " << t3 << endl;

        

        cout << "----------------------------------\n";

        fout << n << "," << t1 << "," << t2 << "," << t3 << "\n";
    }

    return 0;
}
