#ifndef DATAREADER_H
#define DATAREADER_H

#include <chaptor.h>

class DataReader
{
public:
    DataReader(QString filePath);
    QVector<Chaptor> getAllData();
    Chaptor getAnGroup(QString block, bool *ok);
private:
    QString dataFilePath;
};

#endif // DATAREADER_H
