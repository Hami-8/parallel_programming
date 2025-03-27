#include <windows.h>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <fstream>
using namespace std;

using Matrix = vector<vector<double>>;
using Vector = vector<double>;

// ------------------ ʵ��һ���������������ڻ� ------------------

// ƽ���㷨���������ʣ�
void matrix_vector_naive(const Matrix& A, const Vector& v, Vector& result, int n) {
    for (int j = 0; j < n; ++j) {
        result[j] = 0;
        for (int i = 0; i < n; ++i) {
            result[j] += A[i][j] * v[i];
        }
    }
}

// �Ż��㷨���������ʣ�
void matrix_vector_optimized(const Matrix& A, const Vector& v, Vector& result, int n) {
    fill(result.begin(), result.end(), 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[j] += A[i][j] * v[i];
        }
    }
}

// ------------------ ͨ�ü�ʱ�� ------------------

template<typename Func>
double benchmark(Func func, int repeat = 50) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&start);
    for (int i = 0; i < repeat; ++i) {
        func();  // ִ�д����Ժ���
    }
    QueryPerformanceCounter(&end);

    double elapsed_ms = (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    return elapsed_ms / repeat;  // ����ƽ������
}

// ------------------ �������� ------------------

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

// ------------------ ���������� ------------------

int main() {
    //vector<int> sizes = { 512, 1024, 2048 ,4096};
    //for (int n : sizes) {
    //    Matrix A;
    //    Vector v, result(n);
    //    generate_data(A, v, n);

    //    cout << "n = " << n << ":\n";

    //    double t1 = benchmark([&]() {
    //        matrix_vector_naive(A, v, result, n);
    //        });
    //    cout << "  ƽ���㷨ʱ�䣨ms��: " << t1 << endl;

    //    double t2 = benchmark([&]() {
    //        matrix_vector_optimized(A, v, result, n);
    //        });
    //    cout << "  �Ż��㷨ʱ�䣨ms��: " << t2 << endl;
    //    cout << "----------------------------------\n";
    //}

    const int step = 64;
    const int max_n = 4096;

    ofstream fout("result.csv");
    fout << "n,naive_ms,optimized_ms\n";

    for (int n = step; n <= max_n; n += step) {
        Matrix A;
        Vector v, result(n);
        generate_data(A, v, n);

        cout << "n = " << n << ":\n";

        double t1 = benchmark([&]() {
            matrix_vector_naive(A, v, result, n);
            });
        cout << "  ƽ���㷨ʱ�䣨ms��: " << t1 << endl;

        double t2 = benchmark([&]() {
            matrix_vector_optimized(A, v, result, n);
            });
        cout << "  �Ż��㷨ʱ�䣨ms��: " << t2 << endl;

        cout << "----------------------------------\n";

        fout << n << "," << t1 << "," << t2 << "\n";
    }


    return 0;
}
