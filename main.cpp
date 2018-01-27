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


void showVectorVals(string label, const vector<double> &v)
{
//    cout << label << " ";
//    for (unsigned i = 0; i < v.size(); ++i)
//    {
//        cout << v[i] << " ";
//    }

//    cout << endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    cout<<"ajdsakjdjasnd"<<endl;
    cout<<"hfghkgmkmfg"<<endl;
    w.show();

    return a.exec();
}
