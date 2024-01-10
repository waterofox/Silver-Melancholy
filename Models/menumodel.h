#ifndef MENUMODEL_H
#define MENUMODEL_H

#include <QAbstractItemModel>
#include <QObject>
class MenuModel : public QAbstractItemModel
{
    Q_OBJECT

private:
    int actorLv = 0;
    int actorHp = 0;
    QString actorName = "None";
    QString mainAsset = "qrc:/resources/GameAssets/void.png";

    enum ModelRole
    {
        DisplayRole = 0,
        EditRole = 2,
        WhatsThisRole = 5,
        LevelRole = 257,
        HpRole = 256,
        ActorNameRole = 258,
        ActoraMainFrame = 259,
    };

public:
    MenuModel(QObject *parent = nullptr);

    Q_INVOKABLE void setActorLV(const int& arg);
    Q_INVOKABLE void setActorHP(const int& arg);
    Q_INVOKABLE void setActorName(const QString&);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;

    QModelIndex parent(const QModelIndex &child) const override;

    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role) const override;



    ~MenuModel();
};

#endif // MENUMODEL_H
