#ifndef BMTTASK_H
#define BMTTASK_H

#include <QAbstractListModel>
#include "bmtitem.h"
#include "arena.h"

class BMTTask: public QAbstractListModel{

    Q_OBJECT

public:
    BMTTask(QString taskType, Arena* arena);

    enum BMTRoles {
        SourceRole = Qt::UserRole + 1,
        SourceTypeRole,
        ObjectRole,
        DesitnationRole,
        DestinationTypeRole
    };


    BMTTask(QObject *parent = 0);

    void addItem(BMTItem* bmtItem);
    void removeItem(BMTItem* bmtItem);


    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;


    Q_INVOKABLE void itemSelected(int id);

signals:

    void addBNTRequest(BMTItem* bmtItem);
    void removeBNTRequest(BMTItem* bmtItem);


public slots:

    void doAddEmtpyItem();
    void doRemoveItem(int index);

    QString composeBMTTaskSpec();
    QString composeBTTTaskSpec();
    QString composeCBTTaskSpec();
    QString composePPTTaskSpec();

    QString generateBMTTaskSpec(int numOfSamples);
    QString generateBTTTaskSpec();
    QString generateCBTTaskSpec();
    QString generatePPTTaskSpec();

    void updateData(int index, QString source, QString sourceType, QString object, QString destination, QString destinationType);
    void updateObect(int index, QString object);
    void updateObect(int index, QString source, QString object, QString destination);

    void updateAllSource(QString source);
    void updateAllSourceType(QString sourceType);
    void updateAllDestination(QString destination);
    void updateAllDestinationType(QString destinationType);

    void updateStartPosition(QString start);
    void updateEndPosition(QString end);

private slots:

    void doAddItem(BMTItem* bmtItem);
    void doRemoveItem(BMTItem* bmtItem);



protected:

      QHash<int, QByteArray> roleNames() const;

private:

   void clearList();

   Arena* arena_;
   QList<BMTItem*> bmtItemList_;
   int selectedItem_;
   QString taskType_;
   QString startPos_;
   QString endPos_;

};

#endif // BMTTASK_H
