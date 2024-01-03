#include "questmodel.h"

QuestModel::QuestModel(QObject *parent)
    : QAbstractItemModel{parent}
{
    this->myQuests.insert(quests::VoidQuest,"Никто не пришёл...");
    this->myQuests.insert(quests::TestQuest,"Бип-Бип, это тестовый квест :3");
}

QuestModel::~QuestModel()
{

}

void QuestModel::setActiveQuest(const int &newQ)
{
    this->ActiveQuest = newQ;
}

int QuestModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int QuestModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant QuestModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    switch (role) {
    case QuestRole::DisplayRole:{
        if(this->myQuests.isEmpty() or !this->myQuests.contains(this->ActiveQuest))
        {
            qDebug() << "ERROR: active quest does not exist";
            return -1;
        }
        return this->myQuests.value(this->ActiveQuest);
    }
    break;
    case QuestRole::EditRole:{
        return "huh";
    }
    break;
    case QuestRole::WhatsThisRole:{
        return "this is a quest";
    }
    break;
    default:
        break;
    }
}

QModelIndex QuestModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return this->createIndex(row,column);
}

QModelIndex QuestModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

QHash<int, QByteArray> QuestModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[QuestRole::DisplayRole] = "display";
    roles[QuestRole::EditRole] = "edit";
    roles[QuestRole::WhatsThisRole] = "whats_this";

    return roles;
}
