#ifndef RECORDTREEMODEL_H
#define RECORDTREEMODEL_H

#include <QAbstractItemModel>

class DataManager;
class RecordTreeItem;

class RecordTreeModel: public QAbstractItemModel
{
    Q_OBJECT

public:
    RecordTreeModel(DataManager* pDataManager, QObject *parent = 0);
    ~RecordTreeModel(){}//TODO
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;



    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) Q_DECL_OVERRIDE;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()){} //Q_DECL_OVERRIDE
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()){} //Q_DECL_OVERRIDE
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
//particular methodes
    //void addExistProbeFile(const QString &filePath);
private:
    RecordTreeItem* getItem(const QModelIndex &index) const;
    DataManager* pDataManager;
public slots:
    void beginResetSlot();
    void endResetSlot();

    void newEmptyGroup(const QModelIndex &probeFileIndex);
    void newEmptyProbeFile();
    void deleteRecord(const QModelIndex &recordIndex);
    void deleteGroup(const QModelIndex& groupIndex);
    void deleteProbeFile(const QModelIndex& probeFileIndex);
    void cutRecord(const QModelIndex& recordIndex);
    void copyRecord(const QModelIndex& recordIndex);
    void pasteRecord(const QModelIndex& recordIndex);

    void copyGroup(const QModelIndex& itemIndex);
    void pasteGroup(const QModelIndex& itemIndex);

};

#endif // RECORDTREEMODEL_H
