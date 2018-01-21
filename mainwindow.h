#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
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
private slots:
    void on_pushButtonSearch_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);
    void getWeatherFromServer(const QString &city);

    void on_buttonZmienNazwe_clicked();

    void on_listCloths_currentTextChanged(const QString &currentText);

    void on_buttonChangeName_clicked();

private:
    void ShowClothsList();
    Ui::MainWindow *ui;
    Weather m_weather;
    std::vector<Cloth> cloths;      //to jest to do zalamiętania
};

#endif // MAINWINDOW_H
