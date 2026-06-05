#include <gtest/gtest.h>
#include <random>
#include "Gauss_solve.h"

TEST(GaussSolve, SmallSolve)
{
    GaussMatrix ab(2, 3);
    ab << 2,  1, 5,
    1, -1, 1;

    GaussVector expected(2);
    expected << 2, 1;

    GaussVector actual = Gauss_solve(ab);

    EXPECT_NEAR(actual(0), expected(0), 1e-9);
    EXPECT_NEAR(actual(1), expected(1), 1e-9);
}

TEST(GaussSolve, LargeRandomSolve)
{
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    int n = 100;
    GaussMatrix A(n, n);
    GaussVector X_true(n);

    // Случайная матрицу A и случайный вектор ответов X_true
    for(int i = 0; i < n; ++i)
    {
        X_true(i) = dist(rng);
        for(int j = 0; j < n; ++j)
        {
            A(i, j) = dist(rng);
        }
    }

    GaussVector B = A * X_true;
    GaussMatrix ab(n, n + 1);
    ab.leftCols(n) = A;
    ab.rightCols(1) = B;
    GaussVector X_solved = Gauss_solve(ab);
    // Сверка
    for(int i = 0; i < n; ++i)
    {
        EXPECT_NEAR(X_solved(i), X_true(i), 1e-5);
    }
}