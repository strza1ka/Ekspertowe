#include "mainwindow.h"
#include "ui_mainwindow.h"

typedef QString Cloth;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getWeatherFromServer("Warszawa");
    cloths = {"ubranie 1", "ubranie 2", "ubranie 3", "ubranie 4", "ubranie 5", "ubranie 6"};  //tu załadować zapamiętane ciuchy

    vector<unsigned> topology = {numberWeather, numberHidden, cloths.size()};

    //Net tmp(topology);
    Net tmp = topology;
    myNet = tmp;
    output = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSearch_clicked()
{
    vector<double> inputVals = {m_weather.m_temperature, m_weather.m_pressure, m_weather.m_windSpeed,
                                m_weather.m_clouds, m_weather.m_humidity};
    output = siec(inputVals);
    SetChoice(output);
    cout << output << endl;
}

void MainWindow::ShowClothsList()
{
    for(int i = 0; i < cloths.size(); ++i)
    {
        ui->listCloths->addItem(cloths[i]);
    }
}

int MainWindow::siec(const std::vector<double> &inputVals)
{
    ShowClothsList();

    std::vector<double> resultVals;

    int target;

    double max = -1.0;
    int maxIndex = -1;



    int i = 0;
    while(i != 15)
    {
        i++;
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

    }

    std::cout << "\nDone" << std::endl;
    return maxIndex;
}

void MainWindow::TeachNet(int target)
{

    std::vector<double> targetVals;

    for(int i = 0; i < cloths.size(); ++i)
    {
        targetVals.push_back(0.0);
    }

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

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    getWeatherFromServer(arg1);
}

void MainWindow::getWeatherFromServer(const QString &city)
{
    m_weather = { 4.81, 1019.0, 1.5, 90, 70 };
}

void MainWindow::on_buttonZmienNazwe_clicked()
{
    //tego nie umiem usunąć bez błędu kompilacji
}

void MainWindow::on_listCloths_currentTextChanged(const QString &currentText)
{
    //a tego też nie potrzeba
}

void MainWindow::on_buttonChangeName_clicked()
{
    ui->listCloths->currentItem()->setText(ui->lineEdit->text());
    cloths[ui->listCloths->currentRow()] = ui->lineEdit->text();
}

void MainWindow::on_pushButtonOk_clicked()
{
    TeachNet(output);
}

void MainWindow::SetChoice(int cloth)
{
    ui->listCloths->setCurrentRow(cloth);
}
