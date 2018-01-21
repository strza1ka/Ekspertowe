#ifndef FILECSV_H
#define FILECSV_H

#include <QString>
#include <QVariant>

#include <vector>
#include <map>

class FileCSV
{
public:
    FileCSV();
    FileCSV(const char *fileName);
    void saveAs(const char *fileName);
    QVariant getValue(int rows, int column) const;

    std::vector<QVariant> getColumn(int index) const;

    template <class T>
    void pushColumn(const QString &header, std::vector<T> column)
    {
        m_headers.push_back(header);

        std::vector<QVariant> columnToPush;
        for (int i = 0; i < column.size(); ++i)
        {
            columnToPush.push_back(column[i]);
        }

        m_data.push_back(columnToPush);
    }

    size_t rows() const;
    size_t columns() const;

    friend std::ostream &operator<< (std::ostream &out, const FileCSV &from);
private:
    QString                                     m_fileName;
    std::vector<QString>                        m_headers;
    std::vector<std::vector<QVariant>>          m_data;

    static const char                           m_split = ',';
};

#endif // FILECSV_H
