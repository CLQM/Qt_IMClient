#ifndef MODELCROWDINFOSTATU_H
#define MODELCROWDINFOSTATU_H

#include <QAbstractTableModel>
#include <QVector>
#include <QMultiMap>
#include <QStringList>

#include "crowdchatting.h"

class ModelCrowdInfoStatu : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModelCrowdInfoStatu(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent= QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent= QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    static QMap<quint16, CrowdChatting *> m_mapPriChatForm; //User ID, chat form
    static QMap<quint16, quint16> m_mapPriChatRecordNumber; //User ID, number of record
    static QMultiMap<quint16, QString> m_multiMapPriChatRecord; //User ID, content

private:
    QStringList m_header;

    void populateModel();
};

#endif // MODELCROWDINFOSTATU_H
