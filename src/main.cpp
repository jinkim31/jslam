#include <iostream>
#include "gradient_solver/gradient_solver.h"

using namespace std;

int main()
{
    MatrixXd arg(2,1);
    arg<<
    1,
    2;

    GradientSolver::Jacobian<2,1> jacobian;
    jacobian<<
    [](double x){return 2*x;},
    [](double x){return 2*x;};

    auto cost = [](MatrixXd m){
        return m(0,0)*m(0,0) + m(1,0)*m(1,0);
    };

    GradientSolver solver(cost, jacobian, 0.01);
    solver.solve(arg, 1000);
}