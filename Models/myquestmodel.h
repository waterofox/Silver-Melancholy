#ifndef QUESTMODEL_H
#define QUESTMODEL_H

#include <QAbstractItemModel>
#include <QMap>
#include <QString>
#include <QObject>
class MyQuestModel : public QAbstractItemModel
{
    Q_OBJECT
private:
    enum quests
    {
        VoidQuest = -1,
        TestQuest = 0,
    };
    enum QuestRole
    {
        DisplayRole = 0,
        EditRole = 2,
        WhatsThisRole = 5,
    };
    int ActiveQuest = quests::VoidQuest;
    QMap<int,QString> myQuests;
public:
    MyQuestModel(QObject *parent = nullptr);
    ~MyQuestModel();

    Q_INVOKABLE bool spokoynoSachenka(const int& idQ);
    Q_INVOKABLE int rowCount(   const QModelIndex& parent) const override;
    Q_INVOKABLE int columnCount(const QModelIndex& parent) const override;
    Q_INVOKABLE QVariant data(const QModelIndex& index,int role ) const override;
    Q_INVOKABLE QModelIndex index(int row,int column,const QModelIndex& parent) const override;
    Q_INVOKABLE QModelIndex parent(const QModelIndex& child)const override;

    QHash<int, QByteArray> roleNames() const override;

};

#endif // QUESTMODEL_H
