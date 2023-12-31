#ifndef MYGAMEMAP_H
#define MYGAMEMAP_H

#include <QAbstractItemModel>

class MyGameMap : public QAbstractItemModel
{
    Q_OBJECT
private:

    struct mapCell
    {
        QString back_path = "None";
        QString front_path = "None";
        int idCell = 0;

        bool activeColision = false;
    };

    int parentWidth;
    int parentHeight;

public:

    MyGameMap(const int& width = 11, const int& height = 8, QObject*parent = nullptr);
    ~MyGameMap();

    int getWidth();
    int getHeight();
    void createMap();

    void cleanMap();

    Q_INVOKABLE bool targetCell(const int& x,const  int& y);
    Q_INVOKABLE void updateParentScalw(const int& parentW, const int& parentH);


    Q_INVOKABLE int rowCount(   const QModelIndex& parent) const override;
    Q_INVOKABLE int columnCount(const QModelIndex& parent) const override;
    Q_INVOKABLE QVariant data(const QModelIndex& index,int role ) const override;
    Q_INVOKABLE QModelIndex index(int row,int column,const QModelIndex& parent) const override;
    Q_INVOKABLE QModelIndex parent(const QModelIndex& child)const override;

    bool checkColision(const int& ActorX, const int& ActorY);



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


    int _width ;
    int _height;

    QList<mapCell> _tabel;
};
#endif // MYGAMEMAP_H
