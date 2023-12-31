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
}

void MyGameMap::cleanMap()
{
    for(int i = 0; i < this->_width*this->_height;++i)
    {
        if(!_tabel[i].activeColision) this->_tabel[i].back_path = "qrc:/resources/GameAssets/void.png";
    }
}

bool MyGameMap::targetCell(const int &x, const int &y, const int &parent_width, const int& parent_height)
{

    if (parent_width ==0 or parent_height == 0)
    {
        return false;
    }

    int relaheight = parent_height/8;
    int relawidth = parent_width/11;

    int ychek = 0;
    int xchek =0;

    int counter = 0;


    while(ychek < y)
    {
        ychek+=relaheight;
        counter += 11;
    }
    while(xchek < x)
    {
        xchek += relawidth;
        ++counter;
    }

    if(this->_tabel[counter].activeColision == false)
    {
        cleanMap();
        this->_tabel[counter].back_path = "qrc:/resources/GameAssets/bar.png";
    }
    emit this->dataChanged(createIndex(0, 1), createIndex(_width * _height, 1));
    return true;
}

bool MyGameMap::checkColision(const int &x, const int &y, const int &parent_width, const int &parent_height, const int& side)
{
    if (parent_width ==0 or parent_height == 0)
    {
        return false;
    }
    int relaheight = parent_height/8;
    int relawidth = parent_width/11;

    int ychek = 0;
    int xchek =0;

    int counter = 0;

    int xInModel = x*640/parent_width;
    int yInModel = y*640/parent_width;

    while(ychek < y)
    {
        ychek+=relaheight;
        counter += 11;
    }
    while(xchek < x)
    {
        xchek += relawidth;
        ++counter;
    }



    if(side == 1)
    {

        if(this->_tabel[counter+1].activeColision == true)
        {
            xchek =+ parent_width/11;
            if((xInModel+200)*parent_width/640 > xchek)
            {
                return false;
            }
        }
    }
    if(side == 2)
    {
        if(this->_tabel[counter-1].activeColision == true)
        {

            if((xInModel-200)*parent_width/640 < xchek)
            {
                return false;
            }
        }
    }
    if(side == 3)
    {
        if(counter-11 < 0)
        {
            return false;
        }
        if(this->_tabel[counter-11].activeColision == true)
        {
            if((yInModel-200)*parent_width/640 < ychek)
            {
                return false;
            }
        }
    }
    if(side == 4)
    {
        if(counter+11 > this->_tabel.size()-1)
        {
            return false;
        }
        if(this->_tabel[counter+11].activeColision == true)
        {
            ychek =+ parent_height/11;
            if((yInModel+200)*parent_width/640 > ychek)
            {
                return false;
            }
        }
    }

    return true;
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
