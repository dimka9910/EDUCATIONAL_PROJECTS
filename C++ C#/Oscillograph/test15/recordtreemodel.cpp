#include "recordtreemodel.h"
#include "datamanager.h"

//RecordTree
RecordTreeModel::RecordTreeModel(DataManager *pDataManager, QObject *parent)
{
    this->pDataManager=pDataManager;
    connect(pDataManager,SIGNAL(beginChangeData()),SLOT(beginResetSlot()));
    connect(pDataManager,SIGNAL(endChangeData()),SLOT(endResetSlot()));
}

QVariant RecordTreeModel::data(const QModelIndex &index, int role) const
{
    //return QVariant();
    if (!index.isValid() || index==QModelIndex())
        return QVariant();
    RecordTreeItem* item = getItem(index);
    if (item)
        return item->data(static_cast<Qt::ItemDataRole>(role));
    else
        return QVariant();
}

QVariant RecordTreeModel::headerData(int section, Qt::Orientation orientation,
                    int role) const
{
    return QVariant();
}

QModelIndex RecordTreeModel::index(int row, int column,
                  const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    RecordTreeItem* parentItem;

    if (!parent.isValid())
        parentItem = pDataManager->getRootItem();
    else
        parentItem = getItem(parent);
    RecordTreeItem* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex RecordTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();
    RecordTreeItem* thisItem = getItem(index);
    RecordTreeItem* parentItem = thisItem->parent();
    if (/*parentItem == 0 || */parentItem == pDataManager->getRootItem())
        return QModelIndex();
    return createIndex(parentItem->childNumber(), 0, parentItem);
}

int RecordTreeModel::rowCount(const QModelIndex &parent) const
{
    RecordTreeItem* parentItem;
    if (!parent.isValid())
        parentItem =pDataManager->getRootItem();
    else
        parentItem = getItem(parent);
    return parentItem->childCount();
//    return 0;
}

int RecordTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
//    return 0;
}

Qt::ItemFlags RecordTreeModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index);
}

bool RecordTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
}

bool RecordTreeModel::setHeaderData(int section, Qt::Orientation orientation,
                   const QVariant &value, int role)
{
}

bool RecordTreeModel::insertRows(int position, int rows, const QModelIndex &parent)

{
    beginInsertRows(parent, position, position+rows-1);
    RecordTreeItem* pRTI=reinterpret_cast<RecordTreeItem*>(parent.internalPointer());
    pRTI->insertChildren(position, rows);
    endInsertRows();
}

bool RecordTreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{

}

RecordTreeItem* RecordTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        RecordTreeItem* item = reinterpret_cast<RecordTreeItem*>(index.internalPointer());
        return item;
    }
    return 0;
}

void RecordTreeModel::beginResetSlot()
{
    this->beginResetModel();
}

void RecordTreeModel::endResetSlot()
{
    this->endResetModel();
}

void RecordTreeModel::newEmptyGroup(const QModelIndex& probeFileIndex)
{
    RecordTreeItem* pRTI = getItem(probeFileIndex);
    beginInsertRows(probeFileIndex,0,0);
    pDataManager->newEmptyGroup(dynamic_cast<ProbeFile*>(pRTI));
    endInsertRows();
}

void RecordTreeModel::newEmptyProbeFile()
{
    beginInsertRows(QModelIndex(),0,0);
    pDataManager->newEmptyProbeFile();
    endInsertRows();
}

void RecordTreeModel::deleteRecord(const QModelIndex &recordIndex)
{
    RecordTreeItem* pRTI = getItem(recordIndex);
    beginRemoveRows(recordIndex.parent(),recordIndex.row(),recordIndex.row());
    pDataManager->deleteRecord(dynamic_cast<Record*>(pRTI));
    endRemoveRows();
}

void RecordTreeModel::deleteGroup(const QModelIndex& groupIndex)
{
    RecordTreeItem* pRTI = getItem(groupIndex);
    beginRemoveRows(groupIndex.parent(),groupIndex.row(),groupIndex.row());
    pDataManager->deleteGroup(dynamic_cast<RecordGroup*>(pRTI));
    endRemoveRows();
}

void RecordTreeModel::deleteProbeFile(const QModelIndex& probeFileIndex)
{
    RecordTreeItem* pRTI = getItem(probeFileIndex);
    beginRemoveRows(probeFileIndex.parent(),probeFileIndex.row(),probeFileIndex.row());
    pDataManager->deleteProbeFile(dynamic_cast<ProbeFile*>(pRTI));
    endRemoveRows();
}

void RecordTreeModel::cutRecord(const QModelIndex& recordIndex)
{
    RecordTreeItem* pRTI = getItem(recordIndex);
    QList<Record*> recordList;
    recordList<<dynamic_cast<Record*>(pRTI);
    beginRemoveRows(recordIndex.parent(),recordIndex.row(),recordIndex.row());
    pDataManager->cutRecords(recordList);
    endRemoveRows();
}

void RecordTreeModel::copyRecord(const QModelIndex& recordIndex)
{
    RecordTreeItem* pRTI = getItem(recordIndex);
    QList<Record*> recordList;
    recordList<<dynamic_cast<Record*>(pRTI);
    pDataManager->copyRecords(recordList);
}

void RecordTreeModel::pasteRecord(const QModelIndex& recordIndex)
{
   int firstRow, lastRow, insertIndex;
   QModelIndex parentIndex;
   RecordGroup* pNewGroup;
   RecordTreeItem* pRTI = getItem(recordIndex);
   if (dynamic_cast<Record*>(pRTI)){
        pNewGroup = dynamic_cast<RecordGroup*>(pRTI->parent());
        firstRow=recordIndex.row();
        lastRow=recordIndex.row();//todo
        insertIndex=firstRow+1;
        parentIndex=recordIndex.parent();
   }
   else if(dynamic_cast<RecordGroup*>(pRTI)){
       pNewGroup = dynamic_cast<RecordGroup*>(pRTI);
       firstRow=0;
       lastRow=0;//todo
       insertIndex=firstRow;
       parentIndex=recordIndex;
   }
   beginInsertRows(parentIndex,firstRow,lastRow);
   pDataManager->pasteRecords(pNewGroup,insertIndex);
   endInsertRows();
}

void RecordTreeModel::copyGroup(const QModelIndex& itemIndex)
{
    RecordTreeItem* pRTI = getItem(itemIndex);
    QList<RecordGroup*> recordList;
    recordList<<dynamic_cast<RecordGroup*>(pRTI);
    pDataManager->copyGroups(recordList);
}

void RecordTreeModel::pasteGroup(const QModelIndex& itemIndex)
{
    int firstRow, lastRow;
    firstRow=lastRow=itemIndex.row();
    RecordTreeItem* pRTI = getItem(itemIndex);
    ProbeFile* pNewProbeFile = dynamic_cast<ProbeFile*>(pRTI->parent());
    beginInsertRows(itemIndex.parent(),firstRow,lastRow);
    pDataManager->pasteGroups(pNewProbeFile,itemIndex.row()+1);
    endInsertRows();
}
