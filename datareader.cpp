#include "datareader.h"
#include <QFile>
#include <QVector>
#include <QDebug>

DataReader::DataReader(QString filePath)
{
    dataFilePath = filePath;
}

QVector<Chaptor> DataReader::getAllData()
{
    QFile file(dataFilePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QVector<Chaptor> allData;
    QString block;
    QString s;
    while(!file.atEnd())
    {
        s = file.readLine();
        if(s.endsWith(":\n"))
        {
            bool ok = false;
            Chaptor c = getAnGroup(block, &ok);
            if(ok)allData.push_back(c);
            block = "";
        }
        block += " " + s;
    }
    file.close();
    return allData;
}

Chaptor DataReader::getAnGroup(QString block,bool* ok)
{
    Chaptor c;
    if(block.size() < 1)
    {
        *ok = false;
        return c;
    }

    QStringList aList = block.split(':');
    c.chaptorName = aList[0];
    QStringList cList = aList[1].split('\n');
    for(int i = 0 ; i < cList.size(); i++)
    {
        if(cList[i].size() < 3) continue;
        QStringList gList = cList[i].split('\t');
        Group g;
        g.groupName = gList[0];
        g.chaptorName = c.chaptorName;
        if(g.chaptorName.contains("御魂")) g.sushiNum = 4;
        else g.sushiNum = 3;
        if(g.groupName.contains("首领")) g.isLast = true;
        QStringList iList = gList[gList.size()-1].split(',');
        for(int j = 0 ; j < iList.size(); j++)
        {
            if(iList[j].size() < 2)continue;
            Item item;
            QStringList tlist = iList[j].split('x');
            item.name = tlist[0];
            item.num = 1;

            if(tlist.size() >=2 )item.num = tlist[1].toInt();
            g.items.push_back(item);
        }
        c.groups.push_back(g);
    }
    *ok = true;
    return c;
}

