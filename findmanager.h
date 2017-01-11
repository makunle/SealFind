#ifndef FINDMANAGER_H
#define FINDMANAGER_H

#include <QVector>
#include <QString>
#include <chaptor.h>
#include <QMap>
#include <QDebug>
#include <QTextEdit>

#define min(a,b) a < b ? a : b
typedef QPair<QString, int> ListItem;
struct ToFind
{
    QVector<ListItem> findList;
    ToFind(){}
    ToFind(const ToFind& t)
    {
        for(int i = 0 ; i < t.findList.size(); i++)
        {
            QString name = t.findList.at(i).first;
            int num = t.findList.at(i).second;
            findList.push_back(qMakePair(name,num));
        }
    }
    int updateWithAGroup(const Group& g)
    {
        int total = 0;
        for(int i = 0 ; i < g.items.size(); i++)
        {
            for(int j = 0 ; j < findList.size(); j++)
            {
                if(g.items.at(i).name == findList.at(j).first)
                {
                    int delNum = min(findList.at(j).second, g.items.at(i).num);
                    findList[j].second -= delNum;
                    total += delNum;
                }
            }
        }
        return total;
    }
    int canUpdateWithAGroup(const Group& g)
    {
        int total = 0;
        for(int i = 0 ; i < g.items.size(); i++)
        {
            for(int j = 0 ; j < findList.size(); j++)
            {
                if(g.items.at(i).name == findList.at(j).first)
                {
                    int delNum = min(findList.at(j).second, g.items.at(i).num);
                    total += delNum;
                }
            }
        }
        return total;
    }
    int haveItem(const Item& item)
    {
        int num = 0;
        for(int i = 0 ; i < findList.size(); i++)
        {
            if(findList.at(i).first == item.name)
                num += item.num;
        }
        return num;
    }
};


class FindManager
{
public:
    FindManager();
    void clearFindItem();
    void addFindItem(QString name, int num);
    void setFindInfo(QVector<Chaptor> chaptorInfo);
    QString findWithMinSushi();
    void findWithMaxNum(QTextEdit *edit);
private:
    int findWithMinSushi(ToFind findTask, QVector<Group> &allGroup, int nowSushiNum, int nowGroupId, QString *way);
    ToFind toFind;
    QVector<Chaptor> chaptorInfo;
};

#endif // FINDMANAGER_H
