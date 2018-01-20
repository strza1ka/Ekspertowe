#include "mainwindow.h"
#include <QApplication>
#include "network.cpp"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
#include "trainingdata.h"
#include "net.h"
using namespace std;


void showVectorVals(string label, vector<double> &v)
{
    cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }

    cout << endl;
}


int siec()
{
    //liczba ciuchów: 6
    int numberCloths = 8;
    int numberWeather = 5;
    int numberHidden = 6;
    //TrainingData trainData("/tmp/trainingData.txt");

    // e.g., { 3, 2, 1 }
    vector<unsigned> topology;
    topology = {numberWeather, numberHidden, numberCloths};
    //trainData.getTopology(topology);

    Net myNet(topology);

    vector<double> inputVals, targetVals, resultVals;

    int target;

    double max = -1.0;
    int maxIndex = -1;

    for(int i = 0; i < numberCloths; ++i)
    {
        targetVals.push_back(0.0);
    }

    while(target != 15)
    {
        //tutaj ma być podpięta pogoda
        inputVals = {4.81, 1019.0, 1.5, 90, 70};

        showVectorVals(": Inputs:", inputVals);
        myNet.feedForward(inputVals);

        myNet.getResults(resultVals);
        showVectorVals("Outputs:", resultVals);

        //wybór najlepszego dopasowania
        max = -1.0;
        maxIndex = -1;
        for (int i = 0; i < resultVals.size(); i++)
        {
            if (resultVals[i] >= max)
            {
                max = resultVals[i];
                maxIndex = i;
            }
        }
        cout << "Wybrano ubranie numer : " << maxIndex << endl;

        //tutaj wybór własciwego ciucha przez typka
        cout << "Które ubranie nadałoby się najlepiej?" << endl;
        cout << "Podaj nr: " << endl;

        target = 4;
        cout << endl;
        for (int i = 0; i < numberHidden; i++)
        {
            if(i == target)
                targetVals[i] = 1;
            else
                targetVals[i] = 0;
        }
        myNet.backProp(targetVals);
    }
    //------------początek trenowania-------------
    //    int trainingPass = 0;

    //    while (!trainData.isEof()) {
    //        ++trainingPass;
    //        cout << endl << "Pass " << trainingPass;

    //        // Get new input data and feed it forward:
    //        if (trainData.getNextInputs(inputVals) != topology[0]) {
    //            break;
    //        }
    //        showVectorVals(": Inputs:", inputVals);
    //        myNet.feedForward(inputVals);

    //        // Collect the net's actual output results:
    //        myNet.getResults(resultVals);
    //        showVectorVals("Outputs:", resultVals);

    //        // Train the net what the outputs should have been:
    //        trainData.getTargetOutputs(targetVals);
    //        showVectorVals("Targets:", targetVals);
    //        assert(targetVals.size() == topology.back());

    //        myNet.backProp(targetVals);

    //        // Report how well the training is working, average over recent samples:
    //        cout << "Net recent average error: "
    //             << myNet.getRecentAverageError() << endl;
    //    }

    cout << endl << "Done" << endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    cout<<"ajdsakjdjasnd"<<endl;
    //siec();
    cout<<"hfghkgmkmfg"<<endl;
    w.show();

    return a.exec();
}
