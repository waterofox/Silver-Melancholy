#ifndef MYGAMEMAP_H
#define MYGAMEMAP_H

#include <QAbstractItemModel>
#include <QList>
class MyGameMap : public QAbstractItemModel
{
    Q_OBJECT
private:


    enum quests
    {
        VoidQuest = -1,
        TestQuest = 0,
    };
    struct mapCell
    {
        QString back_path = "None";
        QString front_path = "None";
        int idCell = 0;

        bool activeColision = false;

        bool isActiveQuest = false;
        int ActiveQuest = quests::VoidQuest; //means none
    };

    int parentWidth;
    int parentHeight;

    int CellHeigth;
    int CellWidth;

public:

    MyGameMap(const int& width = 11, const int& height = 8, QObject*parent = nullptr);
    ~MyGameMap();

    int getWidth();
    int getHeight();
    void createMap();

    void cleanMap();

    Q_INVOKABLE  QList<int> targetCell(const int& x,const  int& y);
    Q_INVOKABLE void updateParentScalw(const int& parentW, const int& parentH);
    Q_INVOKABLE bool checkColision(const int& ActorX, const int& ActorY,const int& side);
    Q_INVOKABLE int getQuest(const int& idCell);
    Q_INVOKABLE int isQuest(const int& actorX, const int& actorY);

    Q_INVOKABLE int rowCount(   const QModelIndex& parent) const override;
    Q_INVOKABLE int columnCount(const QModelIndex& parent) const override;
    Q_INVOKABLE QVariant data(const QModelIndex& index,int role ) const override;
    Q_INVOKABLE QModelIndex index(int row,int column,const QModelIndex& parent) const override;
    Q_INVOKABLE QModelIndex parent(const QModelIndex& child)const override;

    QHash<int, QByteArray> roleNames() const override;

private:

    enum ModelRole
    {
        DisplayRole = 0,
        EditRole = 2,
        WhatsThisRole = 5,
        FrontRole = 257,
        BackRole = 256,
    };
    enum side
    {
        Ws = 1,
        As = 2,
        Ss = 3,
        Ds = 4,
    };



    int _width ;
    int _height;

    QList<mapCell> _tabel;
};
#endif // MYGAMEMAP_H
