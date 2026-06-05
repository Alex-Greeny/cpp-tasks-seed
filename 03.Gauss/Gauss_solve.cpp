#include "Gauss_solve.h"
#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    int n = static_cast<int>(ab.rows());
    if (ab.cols() != n + 1)
    {
        throw std::invalid_argument("Матрица должна быть размера N x (N+1)");
    }

    for (int i = 0; i < n; ++i)
    {
        int max_row = i;
        double max_val = std::abs(ab(i, i));
        for (int k = i + 1; k < n; ++k)
        {
            if (std::abs(ab(k, i)) > max_val)
            {
                max_val = std::abs(ab(k, i));
                max_row = k;
            }
        }

        if (max_val < 1e-12)
        {
            throw std::runtime_error("Система вырождена: нет единственного решения");
        }

        if (max_row != i)
        {
            ab.row(i).swap(ab.row(max_row));
        }

        ab.row(i) /= ab(i, i);

        for (int k = 0; k < n; ++k)
        {
            if (k != i)
            {
                ab.row(k) -= ab.row(i) * ab(k, i);
            }
        }
    }

    return ab.col(n);
}