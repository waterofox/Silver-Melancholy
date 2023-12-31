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

public:

    MyGameMap(const int& width = 11, const int& height = 8, QObject*parent = nullptr);
    ~MyGameMap();

    int getWidth();
    int getHeight();
    void createMap();

    Q_INVOKABLE bool targetCell(const int& x,const  int& y,const  int& parent_width,const int& parent_height);
    Q_INVOKABLE bool checkColision(const int& x,const  int& y,const  int& parent_width,const int& parent_height,const int& side);

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


    int _width ;
    int _height;

    QList<mapCell> _tabel;
};
#endif // MYGAMEMAP_H
