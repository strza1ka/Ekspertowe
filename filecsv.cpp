#include "filecsv.h"

#include <QFile>
#include <QDebug>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QDir>

FileCSV::FileCSV() :
    m_fileName("")
{

}

FileCSV::FileCSV(const char* fileName) :
    m_fileName(fileName)
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/");
    path.append(m_fileName);
    path = QDir::toNativeSeparators(path);

    QFile file(path);

    if (file.open(QIODevice::ReadOnly) == false)
    {
        qDebug() << file.errorString();
    }
    QTextStream in(&file);

    //first line:
    QString line = in.readLine();
    QList<QString> headers = line.split(m_split);

    while (headers.isEmpty() == false)
        m_headers.push_back(headers.takeFirst());


    //data:
    while ((line = in.readLine()) != QString::null)
    {
        QList<QString> words = line.split(m_split);

        std::vector<QVariant> cells;
        while (words.isEmpty() == false)
            cells.push_back(words.takeFirst().trimmed());

        m_data.push_back(cells);
    }
}

void FileCSV::saveAs(const char* fileName)
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/");
    path.append(fileName);
    path = QDir::toNativeSeparators(path);

    QFile file(path);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text) == false)
    {
        qDebug() << file.errorString();
        return ;
    }

    QTextStream out(&file);

    int i;
    for (i = 0; i < m_headers.size() - 1; ++i)
    {
        out << m_headers[i] << m_split;
    }
    out << m_headers[i] << "\n";

    for (int row = 0; row < m_data.size(); ++row)
    {
        int column;
        for (column = 0; column < m_data[row].size() - 1; ++column)
        {
            out << m_data[row][column].toString() << m_split;
        }
        out << m_data[row][column].toString() << "\n";
    }
}

QVariant FileCSV::getValue(int row, int column) const
{
    std::vector<QVariant> aaa = m_data[row];
    return aaa[column];
}

std::vector<QVariant> FileCSV::getColumn(int index) const
{
    std::vector<QVariant> toReturn;

    for (auto i: m_data)
    {
        toReturn.push_back(i[index]);
    }

    return toReturn;
}

size_t FileCSV::rows() const
{
    return m_data.size();
}

size_t FileCSV::columns() const
{
    return m_headers.size();
}

std::ostream &operator<<(std::ostream &out, const FileCSV &from)
{
    out << "|\t";
    for (int i = 0; i < from.m_headers.size(); ++i)
    {
        out << from.m_headers[i].toStdString() << "\t|\t";
    }
    out << "\n\n";

    int size = from.m_data.size();
    for (int i = 0; i < from.m_data.size(); ++i)
    {
        out << "|\t";

        for (int j = 0; j < from.m_data[i].size(); ++j)
        {
            out << from.m_data[i][j].toString().toStdString() << "\t|\t";
        }

        out << "\n";
    }

    return out;
}
