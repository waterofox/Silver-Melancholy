#include "mygamemap.h"

MyGameMap::MyGameMap(const int& width, const int& height, QObject*parent)
{
    Q_UNUSED(parent)
    this->_width = width;
    this->_height = height;
    for(int i = 0; i < width*height;++i)
    {
        mapCell newCell;
        newCell.idCell = i;
        newCell.back_path = "qrc:/resources/GameAssets/void.png";
        newCell.front_path = "qrc:/resources/GameAssets/void.png";
        this->_tabel.append(newCell);
    }

    createMap();
}

MyGameMap::~MyGameMap()
{

}

int MyGameMap::getWidth()
{
    return this->_width;
}

int MyGameMap::getHeight()
{
    return this->_height;
}

void MyGameMap::createMap()
{

    ///COLLIISON
    this->_tabel[64].activeColision = true;
    this->_tabel[64].back_path = "qrc:/resources/GameAssets/col.png";

    this->_tabel[47].activeColision = true;
    this->_tabel[47].back_path = "qrc:/resources/GameAssets/col.png";

    this->_tabel[37].activeColision = true;
    this->_tabel[37].back_path = "qrc:/resources/GameAssets/col.png";

    this->_tabel[48].activeColision = true;
    this->_tabel[48].back_path = "qrc:/resources/GameAssets/col.png";

    this->_tabel[3].activeColision = true;
    this->_tabel[3].back_path = "qrc:/resources/GameAssets/col.png";

    this->_tabel[14].activeColision = true;
    this->_tabel[14].back_path = "qrc:/resources/GameAssets/col.png";

    //ACTIVE QUESTS

    this->_tabel[30].ActiveQuest = quests::TestQuest;
    this->_tabel[30].isActiveQuest =true;
    this->_tabel[30].back_path = "qrc:/resources/GameAssets/quest.png";
}


void MyGameMap::cleanMap()
{
    for(int i = 0; i < this->_width*this->_height;++i)
    {
        if(!_tabel[i].activeColision) this->_tabel[i].back_path = "qrc:/resources/GameAssets/void.png";
    }
}

QList<int> MyGameMap::targetCell(const int &x, const int &y)
{

    if (parentWidth ==0 or parentHeight == 0)
    {
        return QList<int>();
    }
    int ychek = 0;
    int xchek =0;

    int counter = 0;


    while(ychek < y)
    {
        ychek+=CellHeigth;
        counter += 11;
    }
    while(xchek < x)
    {
        xchek += CellWidth;
        ++counter;
    }
    QList<int> answer;
    answer.append(counter);
    answer.append(xchek);
    return answer;
}

void MyGameMap::updateParentScalw(const int &parentW, const int &parentH)
{
    this->parentHeight = parentH;
    this->parentWidth = parentW;

    this->CellWidth = parentW/11;
    this->CellHeigth = parentH/8;
}

bool MyGameMap::checkColision(const int &ActorX, const int &ActorY,const int &side)
{
    switch (side) {
    case side::Ds:{
        if(this->_tabel[targetCell(ActorX,ActorY-this->parentHeight/16)[0]].activeColision)
        {
            return false;
        }
        if(this->_tabel[targetCell(ActorX,ActorY)[0]].activeColision)
        {
            return false;
        }
    }break;
    case side::As:{
        if(this->_tabel[targetCell(ActorX-this->parentWidth/11,ActorY-this->parentHeight/16)[0]].activeColision)
        {
            return false;
        }
        if(this->_tabel[targetCell(ActorX-this->parentWidth/11,ActorY)[0]].activeColision)
        {
            return false;
        }
    }break;
    case side::Ws:{
        if(this->_tabel[targetCell(ActorX,ActorY-this->parentHeight/8)[0]].activeColision)
        {
            return false;
        }
        if(this->_tabel[targetCell(ActorX-this->parentWidth/11,ActorY-this->parentHeight/8)[0]].activeColision)
        {
            return false;
        }
    }break;
    case side::Ss:{
        if(this->_tabel[targetCell(ActorX,ActorY)[0]].activeColision)
        {
            return false;
        }
        if(this->_tabel[targetCell(ActorX-this->parentWidth/11,ActorY)[0]].activeColision)
        {
            return false;
        }
    }
    default:
        break;
    }


    return true;

}

int MyGameMap::getQuest(const int &idCell)
{
    return this->_tabel[idCell].ActiveQuest;
}

int MyGameMap::isQuest(const int &actorX, const int &actorY)
{
    if(this->_tabel[targetCell(actorX-this->parentWidth/22,actorY-this->parentHeight/16)[0]].isActiveQuest)
    {
        qDebug() << "Quest";
        return this->_tabel[targetCell(actorX-this->parentWidth/22,actorY-this->parentHeight/16)[0]].ActiveQuest;
    }
    qDebug() << "No quest";
    return -1;
}

int MyGameMap::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return this->_width*this->_height;
}

int MyGameMap::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return {};
}

QVariant MyGameMap::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case ModelRole::DisplayRole:{
        return this->_tabel[index.row()].idCell;
    }
        break;
    case ModelRole::WhatsThisRole:{
        return "MapCell";
    }
        break;
    case ModelRole::EditRole:{
        return {};
    }
        break;
    case ModelRole::FrontRole:{
        return this->_tabel[index.row()].front_path;
    }
        break;
    case ModelRole::BackRole:{
        return this->_tabel[index.row()].back_path;
    }
        break;
    default:
        break;
    }
}

QModelIndex MyGameMap::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return this->createIndex(row,column);
}

QModelIndex MyGameMap::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

QHash<int, QByteArray> MyGameMap::roleNames() const
{
    QHash<int, QByteArray> role;

    role[ModelRole::DisplayRole] = "display";
    role[ModelRole::WhatsThisRole]= "what_this";
    role[ModelRole::EditRole] = "edit";
    role[ModelRole::FrontRole] = "front_sprite;";
    role[ModelRole::BackRole] = "back_sprite";

    return role;
}
