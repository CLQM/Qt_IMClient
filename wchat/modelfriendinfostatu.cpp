#include "modelfriendinfostatu.h"

#include "logiclayer.h"

QMap<quint16, FormChatting *> ModelFriendInfoStatu::m_mapPriChatForm; //User ID, chat form
QMap<quint16, quint16> ModelFriendInfoStatu::m_mapPriChatRecordNumber; //User ID, number of record
QMultiMap<quint16, QString> ModelFriendInfoStatu::m_multiMapPriChatRecord; //User ID, content

ModelFriendInfoStatu::ModelFriendInfoStatu(QObject *parent) :
    QAbstractTableModel(parent)
{
    populateModel();
}

void ModelFriendInfoStatu::populateModel()
{
    m_header << tr("UID") << tr("Name") << tr("Msg");

    for(int i = 0; i < LogicLayer::m_friendInfoList->size(); i++)
    {
        int uid = LogicLayer::m_friendInfoList->at(i).getUID().toInt();
        m_mapPriChatRecordNumber.insert(uid, 0);
    }
}

int ModelFriendInfoStatu::columnCount(const QModelIndex &parent) const
{
    return 3;
}

int ModelFriendInfoStatu::rowCount(const QModelIndex &parent) const
{
    return LogicLayer::m_friendInfoList->size();
}

QVariant ModelFriendInfoStatu::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role==Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0:
            return LogicLayer::m_friendInfoList->at(index.row()).getUID();
            break;
        case 1:
            return LogicLayer::m_friendInfoList->at(index.row()).getRName();
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

QVariant ModelFriendInfoStatu::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation==Qt::Horizontal)
    {
        return m_header[section];
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}

