#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "net.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getWeatherFromServer("Warszawa");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSearch_clicked()
{
    vector<double> inputVals = {m_weather.m_temperature, m_weather.m_pressure, m_weather.m_windSpeed,
                                m_weather.m_clouds, m_weather.m_humidity};
    siec(inputVals);
}

int MainWindow::siec(const std::vector<double> &inputVals)
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

    std::vector<double> targetVals;
    std::vector<double> resultVals;

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

        //showVectorVals(": Inputs:", inputVals);
        myNet.feedForward(inputVals);

        myNet.getResults(resultVals);
        //showVectorVals("Outputs:", resultVals);

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
        std::cout << "Wybrano ubranie numer : " << maxIndex << std::endl;

        //tutaj wybór własciwego ciucha przez typka
        std::cout << "Które ubranie nadałoby się najlepiej?" << std::endl;
        std::cout << "Podaj nr: " << std::endl;

        target = 4;
        std::cout << std::endl;
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

    std::cout << "\nDone" << std::endl;
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    getWeatherFromServer(arg1);
}

void MainWindow::getWeatherFromServer(const QString &city)
{
    m_weather = { 4.81, 1019.0, 1.5, 90, 70 };
}
