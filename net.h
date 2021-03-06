#ifndef NET_H
#define NET_H

#include "neuron.h"
#include "filecsv.h"


typedef vector<Neuron> Layer;

class Net
{
public:
    Net();
    Net(const vector<unsigned> &topology);
    void feedForward(const vector<double> &inputVals);
    void backProp(const vector<double> &targetVals);
    void getResults(vector<double> &resultVals) const;
    double getRecentAverageError(void) const;
    void loadFromCSV(const FileCSV &fileCSV, const FileCSV &fileCSV_delta, int layer);
    void saveToCSV(FileCSV &outFileCSV, FileCSV &outFileCSVDelta, int layer);

private:
    vector<Layer> m_layers; // m_layers[layerNum][neuronNum]
    double m_error;
    double m_recentAverageError;
    static double m_recentAverageSmoothingFactor;
};



#endif // NET_H
