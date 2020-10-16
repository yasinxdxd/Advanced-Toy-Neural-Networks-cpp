#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int numberOfLayers, ...)
{
    this->learningRate = 0.1;
    this->numberOfLayers = numberOfLayers;
    va_list layers;
    va_start(layers, numberOfLayers);
    for(int i = 0; i<numberOfLayers; i++)
    {
        int parameter = va_arg(layers, int);
        if(i == 0)
            this->numberOfInputNeurons.push_back(parameter);
        else if(i == numberOfLayers-1)
            this->numberOfOutputNeurons.push_back(parameter);
        else
            this->numberOfHiddenNeurons.push_back(parameter);
    }
    va_end(layers);


/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
    this->nuberOfInputLayers = 1;
    this->nuberOfOutputLayers = 1;
    this->nuberOfHiddenLayers = this->numberOfLayers - (this->nuberOfOutputLayers + this->nuberOfInputLayers);
    this->numberOfWeightLayers = this->numberOfLayers - 1;


    ///*//////Weights:
    this->numberOfWeights.push_back(numberOfInputNeurons.front()*numberOfHiddenNeurons.front());
    for(int i = 0; i<numberOfWeightLayers-2; i++)
    {
        this->numberOfWeights.push_back(numberOfHiddenNeurons[i]*numberOfHiddenNeurons[i+1]);
    }
    this->numberOfWeights.push_back(numberOfOutputNeurons.front()*numberOfHiddenNeurons.back());
    ///*////////////////////////////////////////////////////////////////////////////////////////




    this->weights_i_h = new Matrix<double>(this->numberOfHiddenNeurons[0], this->numberOfInputNeurons[0]);
    this->weights_h_o = new Matrix<double>(this->numberOfOutputNeurons[0], this->numberOfHiddenNeurons[0]);

    this->bias_h = new Matrix<double>(this->numberOfHiddenNeurons[0],1);
    this->bias_o = new Matrix<double>(this->numberOfOutputNeurons[0],1);

    this->randomizeWeightsAndBias();


}

NeuralNetwork::~NeuralNetwork()
{
    delete this->weights_i_h;
    delete this->weights_h_o;
    delete this->bias_h;
    delete this->bias_o;
}



void NeuralNetwork::print()
{
    std::cout<<"input neurons: "<<this->numberOfInputNeurons[0]<<std::endl;
    std::cout<<"hidden neurons: ";
    for(int i = 0; i<this->nuberOfHiddenLayers; i++)
    {
        std::cout<<this->numberOfHiddenNeurons[i];
        std::cout<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"output neurons: "<<this->numberOfOutputNeurons[0]<<std::endl;
    std::cout<<std::endl;
    std::cout<<"weights: "<<std::endl;
    for(unsigned int i = 0; i<this->numberOfWeights.size(); i++)
    {
        std::cout<<this->numberOfWeights[i];
        std::cout<<" ";
    }

    std::cout<<std::endl;
    std::cout<<std::endl;

}

void NeuralNetwork::randomizeWeightsAndBias()
{
    weights_i_h->randomize();
    weights_h_o->randomize();

    bias_h->randomize();
    bias_o->randomize();

//    weights_i_h->printToConsole();
//    weights_h_o->printToConsole();
//
//    bias_h->printToConsole();
//    bias_o->printToConsole();

}

void NeuralNetwork::setLearningRate(double l)
{
    this->learningRate = l;
}

void NeuralNetwork::test(std::vector<double> test_inputs)
{
    auto input = Matrix<double>::fromArray(test_inputs);

    auto hidden=(*this->weights_i_h)*input;
    hidden=hidden+(*this->bias_h);
    hidden=sigmoidMatrix(hidden);


    auto output=(*this->weights_h_o)*hidden;
    output=output+(*this->bias_o);
    output=sigmoidMatrix(output);

    output.printToConsole();
}

//template<class T>
void NeuralNetwork::train(std::vector<double> training_inputs, std::vector<double> training_outputs)
{
    ///Feed Forward:

    auto input = Matrix<double>::fromArray(training_inputs);

    auto hidden=(*this->weights_i_h)*input;
    hidden=hidden+(*this->bias_h);
    hidden=sigmoidMatrix(hidden);


    auto output=(*this->weights_h_o)*hidden;
    output=output+(*this->bias_o);
    output=sigmoidMatrix(output);

//    input.printToConsole();
//    hidden.printToConsole();
//    output.printToConsole();


    ///Back Propagation:

    auto target = Matrix<double>::fromArray(training_outputs);

    auto error_o =  target - output;
    auto gradient_o = derivetiveSigmoidedMatrix(output)%error_o*this->learningRate;        //  "%" for hamard product
    (*this->weights_h_o) = (*this->weights_h_o) + (gradient_o*hidden.transpose());
    (*this->bias_o) = (*this->bias_o) + gradient_o;

    auto error_h = this->weights_h_o->transpose()*error_o;
    auto gradient_h = derivetiveSigmoidedMatrix(hidden)%error_h*this->learningRate;        //  "%" for hamard product
    (*this->weights_i_h) = (*this->weights_i_h) + (gradient_h*input.transpose());
    (*this->bias_h) = (*this->bias_h) + gradient_h;

    //weights_h_o->printToConsole();
    //weights_i_h->printToConsole();
//    error_o.printToConsole();
//    error_h.printToConsole();

}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


double NeuralNetwork::sigmoid(double x)
{
     float exp_value;
     double return_value;
     /*** Exponential calculation ***/
     exp_value = exp(-x);
     /*** Final sigmoid value ***/
     return_value = 1 / (1 + exp_value);

     return return_value;
}

Matrix<double> NeuralNetwork::sigmoidMatrix(Matrix<double> m)
{
    Matrix<double> result(m.getNumRows(),m.getNumCols());
    result=m;
    for(int x = 0; x<m.getNumRows(); x++)
    {
        for(int y = 0; y<m.getNumCols(); y++)
        {
            result.setValue(x, y, sigmoid(m.getValue(x, y)));
        }
    }
    return result;
}

Matrix<double> NeuralNetwork::derivetiveSigmoidedMatrix(Matrix<double> m)
{
    Matrix<double> result(m.getNumRows(),m.getNumCols());
    result=m;
    for(int x = 0; x<m.getNumRows(); x++)
    {
        for(int y = 0; y<m.getNumCols(); y++)
        {
            result.setValue(x, y, (m.getValue(x, y)*(1-(m.getValue(x, y)))));
        }
    }
    return result;
}









/*
`void NeuralNetwork::train(std::vector<double> training_inputs, std::vector<double> training_outputs)
{
    ///Feed Forward:

    auto input = Matrix<double>::fromArray(training_inputs);

    auto hidden=(*weights_i_h)*input;
    hidden=hidden+(*bias_h);
    hidden=this->sigmoidMatrix(hidden);


    auto output=(*weights_h_o)*hidden;
    output=output+(*bias_o);
    output=this->sigmoidMatrix(output);


    ///Back Propagation:

    auto target = Matrix<double>::fromArray(training_outputs);

    auto error_o =  target - output;
    auto gradient_o = (derivetiveSigmoidedMatrix(output)%error_o)*this->learningRate;        //  "%" iþareti hamard product
    (*weights_h_o) = (*weights_h_o) + (gradient_o*hidden.transpose());
    (*bias_o) = (*bias_o) + gradient_o;

    auto error_h = weights_h_o->transpose()*error_o;
    auto gradient_h = (derivetiveSigmoidedMatrix(hidden)%error_h)*this->learningRate;        //  "%" iþareti hamard product
    (*weights_i_h) = (*weights_i_h) + (gradient_h*input.transpose());
    (*bias_h)= (*bias_h) + gradient_h;


}`
*/



