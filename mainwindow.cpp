#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>

typedef QString Cloth;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getWeatherFromServer("Warszawa");

    loadNames("names.csv");
    loadFromCSV("layer1.csv", "layer2.csv", "layer1_delta.csv", "layer2_delta.csv");

    ShowClothsList();
    ui->label->setVisible(false);
    ui->label->setText("Czy to był dobry wybór?");
    ui->pushButtonNotOk->setVisible(false);
    ui->pushButtonOk->setVisible(false);
}

MainWindow::~MainWindow()
{
    FileCSV layer1;
    FileCSV layer2;
    FileCSV layer1_delta;
    FileCSV layer2_delta;

    m_myNet.saveToCSV(layer1, layer1_delta, 0);
    m_myNet.saveToCSV(layer2, layer2_delta, 1);

    layer1.saveAs("layer1.csv");
    layer2.saveAs("layer2.csv");

    layer1_delta.saveAs("layer1_delta.csv");
    layer2_delta.saveAs("layer2_delta.csv");

    saveNames("names.csv");

    delete ui;
}

void MainWindow::on_pushButtonSearch_clicked()
{
    vector<double> inputVals = {m_weather.m_temperature, m_weather.m_pressure, m_weather.m_windSpeed,
                                m_weather.m_clouds, m_weather.m_humidity};
    output = siec(inputVals);
    SetChoice(output);
    ui->label->setVisible(true);
    ui->label->setText("Czy to był dobry wybór?");
    ui->pushButtonNotOk->setVisible(true);
    ui->pushButtonOk->setVisible(true);
    //cout << output << endl;
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
    std::vector<double> resultVals;

    double max = -1.0;
    int maxIndex = -1;

    int i = 0;
    while(i != 15)
    {
        i++;
        //tutaj ma być podpięta pogoda

        //showVectorVals(": Inputs:", inputVals);
        m_myNet.feedForward(inputVals);

        m_myNet.getResults(resultVals);
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
        //std::cout << "Wybrano ubranie numer : " << maxIndex << std::endl;

        //tutaj wybór własciwego ciucha przez typka

    }
    return maxIndex;
}

void MainWindow::TeachNet(int target)
{

    std::vector<double> targetVals;

    for(int i = 0; i < cloths.size(); ++i)
    {
        targetVals.push_back(0.0);
    }

    for (int i = 0; i < numberHidden; i++)
    {
        if(i == target)
            targetVals[i] = 1;
        else
            targetVals[i] = 0;
    }
    m_myNet.backProp(targetVals);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    getWeatherFromServer(arg1);
}

void MainWindow::getWeatherFromServer(const QString &city)
{
    m_weather = { 4.81, 1019.0, 1.5, 90, 70 };
}

void MainWindow::loadFromCSV(const std::string &layer1, const std::string &layer2, const std::string &delta1, const std::string &delta2)
{
    FileCSV fileLayer1(layer1.c_str());
    FileCSV fileLayer2(layer2.c_str());

    FileCSV fileLayer1Delta(delta1.c_str());
    FileCSV fileLayer2Delta(delta2.c_str());

    int numberCloths = cloths.size();
    int numberWeather = 5;
    int numberHidden = 6;

    vector<unsigned> topology;
    topology = {numberWeather, numberHidden, numberCloths};

    Net myNet(topology);
    myNet.loadFromCSV(fileLayer1, fileLayer1Delta, 0);
    myNet.loadFromCSV(fileLayer2, fileLayer2Delta, 1);

    m_myNet = myNet;
}

void MainWindow::loadNames(const std::string &fileName)
{
    FileCSV fileLayer1(fileName.c_str());

    cloths.clear();
    for (auto& i: fileLayer1.getColumn(0))
    {
        cloths.push_back(i.toString());
    }
}

void MainWindow::saveNames(const std::string &fileName)
{
    FileCSV file;
    file.pushColumn("Cloaths", cloths);

    file.saveAs(fileName.c_str());
}

void MainWindow::on_pushButtonOk_clicked()
{
    TeachNet(output);
    //cout << "nauczone!" <<endl;
    ui->label->setText("Dzięki!");
    ui->pushButtonOk->setVisible(false);
    ui->pushButtonNotOk->setVisible(false);
}

void MainWindow::SetChoice(int cloth)
{
    ui->listCloths->setCurrentRow(cloth);
}

void MainWindow::on_pushButtonNotOk_clicked()
{
    TeachNet(ui->listCloths->currentRow());

    ui->label->setText("Dzięki, następnym razem spróbuję podpowiedzieć lepiej :)");
    ui->pushButtonNotOk->setVisible(false);
    ui->pushButtonOk->setVisible(false);
}

void MainWindow::on_listCloths_doubleClicked(const QModelIndex &index)
{
    QString name = QInputDialog::getText(this, "Zmiana nazwy", "Podaj nazwę:");

    ui->listCloths->currentItem()->setText(name);
    cloths[ui->listCloths->currentRow()] = name;
}
