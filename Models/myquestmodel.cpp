#include "myquestmodel.h"


MyQuestModel::MyQuestModel(QObject *parent)
{
    Q_UNUSED(parent)
    this->myQuests.insert(quests::VoidQuest,"Никто не пришёл...");
    this->myQuests.insert(quests::TestQuest,"Бип-Бип, это тестовый квест :3");
}

MyQuestModel::~MyQuestModel()
{

}

bool MyQuestModel::spokoynoSachenka(const int& idQ)
{
    this->ActiveQuest = idQ;
    emit this->dataChanged(createIndex(0,1),createIndex(0,1));
    return true;
}

int MyQuestModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int MyQuestModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant MyQuestModel::data(const QModelIndex &index, int role) const
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

QModelIndex MyQuestModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return this->createIndex(row,column);
}

QModelIndex MyQuestModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

QHash<int, QByteArray> MyQuestModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[QuestRole::DisplayRole] = "display";
    roles[QuestRole::EditRole] = "edit";
    roles[QuestRole::WhatsThisRole] = "whats_this";

    return roles;
}
