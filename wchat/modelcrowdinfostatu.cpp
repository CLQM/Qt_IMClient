#include "modelcrowdinfostatu.h"

#include "logiclayer.h"

QMap<quint16, CrowdChatting *> ModelCrowdInfoStatu::m_mapPriChatForm; //User ID, chat form
QMap<quint16, quint16> ModelCrowdInfoStatu::m_mapPriChatRecordNumber; //User ID, number of record
QMultiMap<quint16, QString> ModelCrowdInfoStatu::m_multiMapPriChatRecord; //User ID, content

ModelCrowdInfoStatu::ModelCrowdInfoStatu(QObject *parent) :
    QAbstractTableModel(parent)
{
    populateModel();
}

void ModelCrowdInfoStatu::populateModel()
{
    m_header << tr("CID") << tr("CName") << tr("CIntro");

    for(int i = 0; i < LogicLayer::m_crowdInfoList->size(); i++)
    {
        int cid = LogicLayer::m_crowdInfoList->at(i).getCID().toInt();
        m_mapPriChatRecordNumber.insert(cid, 0);
    }
}

int ModelCrowdInfoStatu::columnCount(const QModelIndex &parent) const
{
    return 3;
}

int ModelCrowdInfoStatu::rowCount(const QModelIndex &parent) const
{
    return LogicLayer::m_crowdInfoList->size();
}

QVariant ModelCrowdInfoStatu::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role==Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0:
            return LogicLayer::m_crowdInfoList->at(index.row()).getCID();
            break;
        case 1:
            return LogicLayer::m_crowdInfoList->at(index.row()).getCName();
            break;
        case 2:
            return m_mapPriChatRecordNumber[this->data(
                        this->index(index.row(), 0), 0).toInt()];
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QVariant ModelCrowdInfoStatu::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation==Qt::Horizontal)
    {
        return m_header[section];
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}
