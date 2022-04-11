#include <iostream>
#include "../gradient_solver/gradient_solver.h"
#include "../submap/prob_grid.h"

using namespace std;

int main()
{
    MatrixXd arg(2,1);
    arg<<
       10,
    100;

    GradientSolver::Jacobian<2,1> jacobian;
    jacobian<<
            [](double x){return 2*x;},
    [](double y){return 2*y;};

    auto cost = [](MatrixXd m){
        return m(0,0)*m(0,0) + m(1,0)*m(1,0);
    };

    GradientSolver solver(cost, jacobian, 0.01);
    solver.solve(arg, 1000, 0.001);


    ProbGrid g;
    for(double i=-10; i<10; i+=0.1)
    {
        cout<<i<<" -> "<<g.getGridIndex(i)<<endl;
    }
}