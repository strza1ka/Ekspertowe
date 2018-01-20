#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

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

private:
    Ui::MainWindow *ui;
    Weather m_weather;
};

#endif // MAINWINDOW_H
