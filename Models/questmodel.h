#ifndef QUESTMODEL_H
#define QUESTMODEL_H

#include <QAbstractItemModel>

class QuestModel : public QAbstractItemModel
{
public:
    explicit QuestModel(QObject *parent = nullptr);
};

#endif // QUESTMODEL_H
