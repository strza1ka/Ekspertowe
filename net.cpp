#include "net.h"

double Net::m_recentAverageSmoothingFactor = 100.0;

void Net::getResults(vector<double> &resultVals) const
{
    resultVals.clear();

    for (unsigned n = 0; n < m_layers.back().size() - 1; ++n)
    {
        resultVals.push_back(m_layers.back()[n].getOutputVal());
    }
}

double Net::getRecentAverageError() const
 {
    return m_recentAverageError;
}

void Net::loadFromCSV(const FileCSV &fileCSV, const FileCSV &fileCSV_delta, int layer)
{
    for (size_t n = 0; n < m_layers[layer].size(); ++n)
    {
        std::vector<QVariant> weightsVariant = fileCSV.getColumn(n);

        std::vector<double> weights;
        for (size_t i = 0; i < weightsVariant.size(); ++i)
            weights.push_back( weightsVariant[i].toDouble() );

        std::vector<QVariant> weightsDeltaVariant = fileCSV_delta.getColumn(n);
        std::vector<double> weightsDelta;
        for (size_t i = 0; i < weightsDeltaVariant.size(); ++i)
            weightsDelta.push_back( weightsDeltaVariant[i].toDouble() );

        m_layers[layer][n].setWeights(weights, weightsDelta);
    }
}

void Net::saveToCSV(FileCSV &outFileCSV, FileCSV &outFileCSVDelta, int layer)
{
    QString columnName      = "weight";
    QString columnNameDelta = "delta";

    FileCSV file;
    FileCSV fileDelta;

    for (size_t n = 0; n < m_layers[layer].size(); ++n)
    {
        std::vector<double> neuronWeights = m_layers[layer][n].getOutputWeights();
        file.pushColumn(columnName, neuronWeights);

        std::vector<double> neuronDelta = m_layers[layer][n].getOutputDeltaWeights();
        fileDelta.pushColumn(columnNameDelta, neuronDelta);
    }

    outFileCSV = file;
    outFileCSVDelta = fileDelta;
}

void Net::backProp(const vector<double> &targetVals)
{
    // Calculate overall net error (RMS of output neuron errors)

    Layer &outputLayer = m_layers.back();
    m_error = 0.0;

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        m_error += delta * delta;
    }
    m_error /= outputLayer.size() - 1; // get average error squared
    m_error = sqrt(m_error); // RMS

    // Implement a recent average measurement

    m_recentAverageError =
            (m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
            / (m_recentAverageSmoothingFactor + 1.0);

    // Calculate output layer gradients

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        outputLayer[n].calcOutputGradients(targetVals[n]);
    }

    // Calculate hidden layer gradients

    for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum) {
        Layer &hiddenLayer = m_layers[layerNum];
        Layer &nextLayer = m_layers[layerNum + 1];

        for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
            hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }

    // For all layers from outputs to first hidden layer,
    // update connection weights

    for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum) {
        Layer &layer = m_layers[layerNum];
        Layer &prevLayer = m_layers[layerNum - 1];

        for (unsigned n = 0; n < layer.size() - 1; ++n) {
            layer[n].updateInputWeights(prevLayer);
        }
    }
}

void Net::feedForward(const vector<double> &inputVals)
{
    assert(inputVals.size() == m_layers[0].size() - 1);

    // Assign (latch) the input values into the input neurons
    for (unsigned i = 0; i < inputVals.size(); ++i) {
        m_layers[0][i].setOutputVal(inputVals[i]);
    }

    // forward propagate
    for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {
        Layer &prevLayer = m_layers[layerNum - 1];
        for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n) {
            m_layers[layerNum][n].feedForward(prevLayer);
        }
    }
}

Net::Net()
{

}
Net::Net(const vector<unsigned> &topology)
{
    unsigned numLayers = topology.size();
    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
    {
        m_layers.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

        // We have a new layer, now fill it with neurons, and
        // add a bias neuron in each layer.
        for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
        {
            m_layers.back().push_back(Neuron(numOutputs, neuronNum));
            //cout << "Made a Neuron!" << endl;
        }

        // Force the bias node's output to 1.0 (it was the last neuron pushed in this layer):
        m_layers.back().back().setOutputVal(1.0);
    }
}

