#include "findmanager.h"
#include <QDebug>
#define MAX 9999

FindManager::FindManager()
{

}

void FindManager::clearFindItem()
{
    toFind.findList.clear();
}

void FindManager::addFindItem(QString name, int num)
{
    toFind.findList.push_back(qMakePair(name, num));
}

void FindManager::setFindInfo(QVector<Chaptor> cInfo)
{
    this->chaptorInfo = cInfo;
}

int nowMin;

QString FindManager::findWithMinSushi()
{
    QVector<Group> allGroup;
    for(int i = 0 ; i < chaptorInfo.size(); i++)
    {
        Chaptor chaptor = chaptorInfo.at(i);
        for(int j = 0; j < chaptor.groups.size(); j++)
        {
            Group group = chaptor.groups.at(j);
            group.brotherNum = chaptor.groups.size();
            if(toFind.canUpdateWithAGroup(group) > 0)
                allGroup.push_back(group);
        }
    }
    qDebug()<<allGroup.size();

    nowMin = MAX;

    QString way;
    int sushi = findWithMinSushi(toFind, allGroup, 0, 0, &way);

    QString result =  way + QString("\n体力: %1").arg(sushi);
//     qDebug()<<"all: "<<sushi<<" "<<result;
    return result;
}

bool compareUsable(const QPair<int,Chaptor> &p1, const QPair<int,Chaptor> &p2)
{
    return p1.first > p2.first;
}

void FindManager::findWithMaxNum(QTextEdit* edit)
{
    edit->clear();
    QVector<QPair<int,Chaptor> > canUseCaptor;
    for(int i = 0 ; i < chaptorInfo.size(); i++)
    {
        Chaptor chaptor = chaptorInfo.at(i);
        int num = 0;
        for(int j = 0 ; j < chaptor.groups.size(); j++)
        {
            Group group = chaptor.groups.at(j);
            for(int k = 0 ; k < group.items.size(); k++)
                num += toFind.haveItem(group.items.at(k));
        }
        if(num > 0)
        {
            canUseCaptor.push_back(qMakePair(num, chaptor));
        }
    }

    qSort(canUseCaptor.begin(), canUseCaptor.end(), compareUsable);
    for(int i = 0 ; i < canUseCaptor.size(); i++)
    {
        Chaptor chaptor = canUseCaptor.at(i).second;
        edit->append(chaptor.chaptorName);
        edit->append("");
        for(int j = 0 ; j < chaptor.groups.size(); j++)
        {
            Group group = chaptor.groups.at(j);
            edit->insertPlainText(group.groupName+" ");
//            QString groupInfo = group.groupName+" ";
            for(int k = 0; k < group.items.size(); k++)
            {
                Item item = group.items.at(k);
                if(toFind.haveItem(item) > 0)edit->setTextColor(QColor(255,0,0));
                edit->insertPlainText(item.name+QString("x%1").arg(item.num)+" ");
                edit->setTextColor(QColor(0,0,0));
//                groupInfo += item.name+QString("x%1").arg(item.num)+" ";
            }
            edit->append("");
        }
        edit->append("");
    }
//    return QString("123");
}

int FindManager::findWithMinSushi(ToFind findTask, QVector<Group>& allGroup, int nowSushiNum, int nowGroupId, QString* way)
{
//    qDebug()<<*way<<" nowSusi:"<<nowSushiNum;
//    if(nowSushiNum >= nowMin) return MAX;

    QString findName = "";
    for(int i = 0 ; i < findTask.findList.size(); i++)
    {
        if(findTask.findList.at(i).second > 0)
        {
            findName = findTask.findList.at(i).first;
            break;
        }
    }
    if(findName == "")
    {
        nowMin = min(nowSushiNum, nowMin);
        return nowSushiNum;
    }

    int canUseGroupID = -1;
    for(int i = nowGroupId ; i < allGroup.size(); i++)
    {
        if(allGroup[i].haveItemNum(findName) > 0)
        {
            canUseGroupID = i;
            break;
        }
    }

    if(canUseGroupID == -1) return MAX;

    Group toUseG = allGroup.at(canUseGroupID);
    ToFind updatedTask = findTask;
    updatedTask.updateWithAGroup(toUseG);

    QString useWay = toUseG.chaptorName + " " + toUseG.groupName+"\n";
    QString unuseWay = "";

    int tousesushi = nowSushiNum + toUseG.sushiNum;
    if(toUseG.isLast) tousesushi = nowSushiNum + toUseG.brotherNum * 3;

    int useSushi = findWithMinSushi(updatedTask, allGroup, tousesushi, canUseGroupID, &useWay);
    int unuseShusi = findWithMinSushi(findTask, allGroup, nowSushiNum, canUseGroupID + 1, &unuseWay);

    if(useSushi <= unuseShusi)
    {
        *way += useWay;
        return useSushi;
    }
    else
    {
        *way += unuseWay;
        return unuseShusi;
    }
}

