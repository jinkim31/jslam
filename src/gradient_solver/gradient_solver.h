#ifndef JSLAM_GRADIENT_SOLVER_H
#define JSLAM_GRADIENT_SOLVER_H

#include <iostream>
#include <functional>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;


class GradientSolver
{
public:
    template <int T1, int T2>
    using Jacobian = Matrix<function<double(double)>, T1, T2>;

private:
    function<double(MatrixXd)> costFunc;
    Jacobian<Dynamic, Dynamic> jacobian;
    double learningRate;
public:
    GradientSolver(function<double(MatrixXd)> costFunction, Jacobian<Dynamic, Dynamic> jacobian, double learningRate);
    MatrixXd solve( MatrixXd &arg, int maxIteration, double termScore=0.0, bool debug=false);
};


#endif //JSLAM_GRADIENT_SOLVER_H
