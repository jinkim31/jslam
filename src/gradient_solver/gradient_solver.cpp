#include "gradient_solver.h"

GradientSolver::GradientSolver(function<double(double)> costFunction, double learningRate)
{
    this->costFunction = costFunction;
    this->learningRate = learningRate;
}

GradientSolver::GradientSolver() : GradientSolver([](double a){return 0;}, 0)
{

}

double GradientSolver::solve(int itr, bool debug)
{
    return 0;
}

void GradientSolver::setConstFunction(function<double(double)> costFunction)
{
    this->costFunction = costFunction;
}

void GradientSolver::setLearningRate(double learningRate)
{
    this->learningRate = learningRate;
}
