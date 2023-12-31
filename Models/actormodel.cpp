#include "actormodel.h"

ActorModel::ActorModel(const int& xNewPosition,const int& yNewPosition,QObject* parent)
{
    Q_UNUSED(parent)

    this->_farmesList.append("qrc:/resources/GameAssets/f1.png");
    this->_farmesList.append("qrc:/resources/GameAssets/Sprite-0003.png");

    this->newStats._xRelativePosition = xNewPosition;
    this->newStats._yRelativePosition = yNewPosition;
    this->newStats._relativeFrame = this->_farmesList[1];

}

ActorModel::~ActorModel(){}

bool ActorModel::setRelativePositon(const int& set)
{
    switch (set) {
    case SetPositon::MoveToUp:{
        this->newStats._yRelativePosition -= 1*this->newStats._speed;
    }
        break;
    case SetPositon::MoveToDown:{
        this->newStats._yRelativePosition += 1*this->newStats._speed;
    }
        break;
    case SetPositon::MoveToRight:{
        this->newStats._xRelativePosition += 1*this->newStats._speed;
    }
        break;
    case SetPositon::MoveToLeft:{
        this->newStats._xRelativePosition -= 1*this->newStats._speed;
    }
        break;

    default:
        break;
    }
    emit this->dataChanged(createIndex(0, 1), createIndex(0, 1));
    return true;
}

bool ActorModel::updateRelativePosition(const int & new_x, const int & new_y)
{
    this->newStats._xRelativePosition = new_x;
    this->newStats._yRelativePosition = new_y;
    emit this->dataChanged(createIndex(0, 1), createIndex(0, 1));
    return true;
}

double ActorModel::getX()
{
    return this->newStats._xRelativePosition;
}

double ActorModel::getY()
{
    return this->newStats._yRelativePosition;
}

QVariant ActorModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index)
    switch (role) {
    case ModelRole::WhatsThisRole:{
        return "This is an actor";
    }
        break;
    case ModelRole::DisplayRole:{
        return "an Actor";
    }
        break;
    case ModelRole::RelativeColisionRole:{
        return QString::number(this->newStats._assetSize);
    }
        break;
    case ModelRole::RelativeXRole:{
        return this->newStats._xRelativePosition;
    }
        break;
    case ModelRole::RelativeYRole:{
        return this->newStats._yRelativePosition;
    }
        break;
    case ModelRole::RelativeFrameRole:{
        return this->newStats._relativeFrame;
    }
        break;
    default:
        break;
    }
    return "JOPA";    
}

int ActorModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 1;
}

int ActorModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QModelIndex ActorModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return this->createIndex(row, column);
}

QModelIndex ActorModel::parent(const QModelIndex& child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

QHash<int, QByteArray> ActorModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ModelRole::DisplayRole] = "display";
    roles[ModelRole::EditRole] = "edit";
    roles[ModelRole::WhatsThisRole] = "whats_this";
    roles[ModelRole::RelativeColisionRole] = "actor_";
    roles[ModelRole::RelativeXRole] = "actor_x";
    roles[ModelRole::RelativeYRole] = "actor_y";
    roles[ModelRole::RelativeFrameRole] = "actor_frame";
    return roles;
}
