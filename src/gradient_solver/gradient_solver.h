#ifndef JSLAM_GRADIENT_SOLVER_H
#define JSLAM_GRADIENT_SOLVER_H

#include <functional>

using namespace std;

class GradientSolver
{
private:
    function<double(double)> costFunction;
    double learningRate;
public:
    GradientSolver(function<double(double)> costFunction, double learningRate);
    GradientSolver();
    double solve(int itr=1, bool debug=false);
    void setConstFunction(function<double(double)> costFunction);
    void setLearningRate(double learningRate);
};


#endif //JSLAM_GRADIENT_SOLVER_H
