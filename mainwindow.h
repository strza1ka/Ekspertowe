#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "net.h"
#include <QMainWindow>
#include <vector>
#include "filecsv.h"

typedef QString Cloth;

struct Weather
{
    float m_temperature;
    float m_pressure;
    float m_windSpeed;
    int m_clouds;
    int m_humidity;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int siec(const std::vector<double> &inputVals);
    void loadNames(const std::string &fileName);
    void saveNames(const std::string &fileName);
private slots:
    void on_pushButtonSearch_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);
    void getWeatherFromServer(const QString &city);

    void on_buttonChangeName_clicked();
    void loadFromCSV(const std::string &fileName, const std::string &layer2, const string &delta1, const string &delta2);

    void on_pushButtonOk_clicked();

    void on_pushButtonNotOk_clicked();

private:
    void ShowClothsList();
    void TeachNet(int target);
    void SetChoice(int cloth);

    int numberWeather = 5;
    int numberHidden = 6;

    Ui::MainWindow *ui;
    Net m_myNet;
    Weather m_weather;
    std::vector<Cloth> cloths;      //to jest to do zapisania
    int output;
};

#endif // MAINWINDOW_H
