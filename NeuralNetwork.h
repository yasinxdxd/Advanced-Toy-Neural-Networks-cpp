#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <stdarg.h>
#include "Matrix.h"
#include "../src/Matrix.cpp"


class NeuralNetwork
{
public:
    NeuralNetwork(int numberOfLayers, ...);
    ~NeuralNetwork();
    void print();
    void train(std::vector<double> training_inputs, std::vector<double> training_outputs);
    void setLearningRate(double);
    void test(std::vector<double> test_inputs);
    void randomizeWeightsAndBias();

private:
///Variables:
///////////////////////////////////
    int numberOfLayers;
///////////////////////////////////
    int numberOfWeightLayers;
///////////////////////////////////
    double learningRate;
///////////////////////////////////
    int nuberOfInputLayers;
    int nuberOfHiddenLayers;
    int nuberOfOutputLayers;
///////////////////////////////////
    std::vector<int> numberOfInputNeurons;
    std::vector<int> numberOfHiddenNeurons;
    std::vector<int> numberOfOutputNeurons;
    std::vector<int> numberOfWeights;
///////////////////////////////////
    Matrix<double>* weights_i_h;
    Matrix<double>* weights_h_o;
    Matrix<double>* bias_h;
    Matrix<double>* bias_o;



private:
///Private Functions:
    double sigmoid(double x);
    Matrix<double> sigmoidMatrix(Matrix<double>);
    Matrix<double> derivetiveSigmoidedMatrix(Matrix<double>);


};

#endif // NEURALNETWORK_H
