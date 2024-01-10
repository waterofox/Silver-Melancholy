#include "menumodel.h"

MenuModel::MenuModel(QObject *parent)
{
    Q_UNUSED(parent)


}

void MenuModel::setActorLV(const int &arg)
{
    this->actorLv = arg;
}

void MenuModel::setActorHP(const int &arg)
{
    this->actorHp = arg;
}

void MenuModel::setActorName(const QString & arg)
{
    this->actorName = arg;
}

int MenuModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int MenuModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QModelIndex MenuModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return this->createIndex(row,column);
}

QModelIndex MenuModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

QHash<int, QByteArray> MenuModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ModelRole::DisplayRole] = "display";
    roles[ModelRole::EditRole] = "edit";
    roles[ModelRole::WhatsThisRole] = "huh";
    roles[ModelRole::HpRole] = "hp_stat";
    roles[ModelRole::LevelRole] = "lv_stat";
    roles[ModelRole::ActorNameRole] = "name_stat";
    roles[ModelRole::ActoraMainFrame] = "frame_stat";

    return roles;
}

QVariant MenuModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    switch (role) {
    case ModelRole::DisplayRole:{
        return "huh?";
    }
    break;
    case ModelRole::EditRole:{
        return 1;
    }
    break;
    case ModelRole::WhatsThisRole:{
        return "its is menu";
    }
    break;
    case ModelRole::HpRole:{
        return this->actorHp;
    }
    break;
    case ModelRole::LevelRole:{
        return this->actorLv;
    }
    break;
    case ModelRole::ActorNameRole:{
        return this->actorName;
    }
    break;
    case ModelRole::ActoraMainFrame:{
        return this->mainAsset;
    }
    break;
    default:
        break;
    }
}
MenuModel::~MenuModel()
{

}
