#ifndef ACTORMODEL_H
#define ACTORMODEL_H

#include <QAbstractItemModel >
#include <QObject>
#include <QKeyEvent>
#include <QEvent>
#include <QKeyEvent>
#include <QString>
#include <QList>
#include <QKeyEvent>
class ActorModel : public QAbstractItemModel
{
    Q_OBJECT

private:
    struct ActorStats
    {
        //move stats
        double _xRelativePosition = 0.0;
        double _yRelativePosition = 0.0;
        int _xyRelativeSide = 0; // 0 -> 1 <- 2^ 3 down
        //front stats
        double _assetSize = 1.0;
        double _speed = 150.0;
        QString _relativeFrame;
    };
    QList<QString> _farmesList;
    ActorStats newStats;

    enum ModelRole
    {
        DisplayRole = 0,
        EditRole = 2,
        WhatsThisRole = 5,
        RelativeXRole = 257,
        RelativeYRole = 256,
        RelativeFrameRole = 258,
        RelativeColisionRole = 259,
    };
    enum SetPositon
    {
        MoveToRight = 1,
        MoveToLeft = 2,
        MoveToUp = 3,
        MoveToDown = 4,
    };
public:

    ActorModel(const int& xNewPosition = 100.0,const int& yNewPosition = 100.0,QObject* parent = nullptr);
    ~ActorModel();

    Q_INVOKABLE bool setRelativePositon(const int&);
    Q_INVOKABLE bool updateRelativePosition(const int&,const int&);

    Q_INVOKABLE double getX();
    Q_INVOKABLE double getY();

    QVariant data(const QModelIndex &index, int role) const override;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;

    QModelIndex parent(const QModelIndex &child) const override;

    QHash<int, QByteArray> roleNames() const override;

};

#endif // ACTORMODEL_H
