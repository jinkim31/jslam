#include "gradient_solver.h"

GradientSolver::GradientSolver(function<double(MatrixXd)> costFunction, Jacobian<Dynamic, Dynamic> jacobian, double learningRate)
{
    this->costFunc = costFunction;
    this->jacobian = jacobian;
    this->learningRate = learningRate;
}

MatrixXd GradientSolver::solve(MatrixXd &arg, int maxIteration, double minCost, bool debug)
{
    for(int i=0; i<maxIteration; i++)
    {
        // gradient descent
        MatrixXd diff(this->jacobian.rows(), this->jacobian.cols());
        for(int x=0; x<diff.rows(); x++)
        {
            for(int y=0; y<diff.cols(); y++)
            {
                diff(x,y) = this->jacobian(x,y)(arg(x,y));
            }
        }
        arg -= arg*this->learningRate;


        // get cost
        double cost = this->costFunc(arg);

        // print debug
        if(debug)
        cout << "iter:" << i+1 << " cost:" << cost << endl;

        // check break state
        if(cost <= minCost) break;
    }

    return arg;
}
