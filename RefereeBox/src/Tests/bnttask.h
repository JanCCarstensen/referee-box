#ifndef BNTTASK_H
#define BNTTASK_H


#include <QAbstractListModel>
#include "bntitem.h"
#include "arena.h"

class BNTTask : public QAbstractListModel{

    Q_OBJECT


public:

    enum BNTRoles {
        PlaceRole = Qt::UserRole + 1,
        OrientationRole
    };


    BNTTask(Arena* arena, QObject *parent = 0);

    void addItem(BNTItem* bntItem);
    void removeItem(BNTItem* bntItem);


    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;


    Q_INVOKABLE void itemSelected(int id);

signals:

    void addBNTRequest(BNTItem* bntItem);
    void removeBNTRequest(BNTItem* bntItem);


public slots:

    void doAddEmtpyItem();
    void doRemoveItem(int index);
    QString composeTaskSpec();
    void updateData(int index, QString place, QString orientation);

    QString autogenerateBNT(int numberOfPlaces, QList<QString> orientations);

    QString getItemPlace(int index);
    int getItemPlaceIndex(int index, QList<QString> places);
    QString getItemOrientation(int index);
    int getItemOrientationIndex(int index, QList<QString> orientations);

private slots:

    void doAddItem(BNTItem* bntItem);
    void doRemoveItem(BNTItem* bntItem);
    void clearList();



protected:

      QHash<int, QByteArray> roleNames() const;

private:

   QList<BNTItem*> bntItemList_;
   int selectedItem_;
   Arena* arena_;
};

#endif // BNTTASK_H
