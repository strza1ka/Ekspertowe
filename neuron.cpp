#include "neuron.h"

double Neuron::eta = 1;    // overall net learning rate, [0.0..1.0]
double Neuron::alpha = 1;   // momentum, multiplier of last deltaWeight, [0.0..1.0]

void Neuron::updateInputWeights(Layer &prevLayer)
{

    // The weights to be updated are in the Connection container
    // in the neurons in the preceding layer

    for (unsigned n = 0; n < prevLayer.size(); ++n)
    {
        Neuron &neuron = prevLayer[n];
        double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

        double newDeltaWeight =
                // Individual input, magnified by the gradient and train rate:
                eta
                * neuron.getOutputVal()
                * m_gradient
                // Also add momentum = a fraction of the previous delta weight;
                + alpha
                * oldDeltaWeight;

        neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
        neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
    }
}

void Neuron::setWeights(const std::vector<double> &weights, const std::vector<double> &weightsDelta)
{
    m_outputWeights.resize(weights.size());

    for (size_t n = 0; n < m_outputWeights.size(); ++n)
    {
        m_outputWeights[n].weight = weights[n];
        m_outputWeights[n].deltaWeight = weightsDelta[n];
    }
}

double Neuron::sumDOW(const Layer &nextLayer) const
{
    double sum = 0.0;

    // Sum our contributions of the errors at the nodes we feed.

    for (unsigned n = 0; n < nextLayer.size() - 1; ++n)
    {
        sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
    }

    return sum;
}

vector<double> Neuron::getOutputWeights() const
{
    std::vector <double> ret;

    for (auto& i: m_outputWeights)
    {
        ret.push_back(i.weight);
    }

    return ret;
}

vector<double> Neuron::getOutputDeltaWeights() const
{
    std::vector <double> ret;

    for (auto& i: m_outputWeights)
    {
        ret.push_back(i.deltaWeight);
    }

    return ret;
}

void Neuron::calcHiddenGradients(const Layer &nextLayer)
{
    double dow = sumDOW(nextLayer);
    m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calcOutputGradients(double targetVal)
{
    double delta = targetVal - m_outputVal;
    m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

double Neuron::transferFunction(double x)
{
    // tanh - output range [-1.0..1.0]

    return tanh(x);
}

double Neuron::transferFunctionDerivative(double x)
{
    // tanh derivative
    return 1.0 - x * x;
}

void Neuron::feedForward(const Layer &prevLayer)
{
    double sum = 0.0;

    // Sum the previous layer's outputs (which are our inputs)
    // Include the bias node from the previous layer.

    for (unsigned n = 0; n < prevLayer.size(); ++n) {
        sum += prevLayer[n].getOutputVal() *
                prevLayer[n].m_outputWeights[m_myIndex].weight;
    }

    m_outputVal = Neuron::transferFunction(sum);
}

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
    for (unsigned c = 0; c < numOutputs; ++c)
    {
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeight();
    }

    m_myIndex = myIndex;
}



