#include <iostream>
#include "gradient_solver/gradient_solver.h"

using namespace std;

int main()
{
    auto cost = [](double x){return x*x + x;};
    GradientSolver solver(cost, 0.01);
    solver.solve();
}