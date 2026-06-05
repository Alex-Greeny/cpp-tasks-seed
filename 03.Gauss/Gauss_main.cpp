#include <iostream>
#include "Gauss_solve.h"

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Использование: " << argv[0] << " <input.csv>\n";
        return 1;
    }

    try
    {
        GaussMatrix ab = load_csv_to_matrix(argv[1]);
        GaussVector x = Gauss_solve(ab);
        GaussMatrix out_mat = x;
        print_matrix_as_csv(std::cout, out_mat);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 2;
    }

    return 0;
}