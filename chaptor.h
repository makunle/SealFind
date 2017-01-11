#ifndef CHAPTOR_H
#define CHAPTOR_H

#include <QVector>
#include <QString>
#include <QPair>

struct Group;
struct Item         //一个资源
{
    QString name;   //资源名称
    int num;        //资源数量
    QString groupName;
};

struct Group        //一个小组
{
    QString groupName;          //组标识名称
    bool isLast;                //是否是最后一个
    QVector<Item> items;        //组里资源数量
    int sushiNum;
    Group(){isLast = false;}
    int haveItemNum(QString name)
    {
        int num = 0;
        for(int i = 0 ; i < items.size(); i++)
        {
            if(items.at(i).name == name) num += items.at(i).num;
        }
        return num;
    }

    QString chaptorName;
    int brotherNum;
};

class Chaptor       //一个章节
{
public:
    QString chaptorName;
    QVector<Group> groups;  //章节内的资源
};

#endif // CHAPTOR_H
