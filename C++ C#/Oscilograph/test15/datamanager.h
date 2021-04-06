#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QDir>
#include "record.h"
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = 0);
    DataManager(const QString& workDirPath, QObject *parent = 0);
    //read directory, and create tree
/*temp!*/void generateProbeFile(const QString &projectName);
    void readWorkDir();
    bool importFile(const QString& filePath);
    void newEmptyProbeFile(const QString& fileName="ProbeFile", int index=0);
    void newEmptyGroup(ProbeFile* probeFileObj, const QString& groupName="Group",
                       int index=0);
    void deleteRecord(Record* pRecord, bool bDelFile=true);
    void deleteGroup(RecordGroup* recordGroup, bool bDelFiles=true);
    void deleteProbeFile(ProbeFile* probeFileObj, bool bDelFiles=true );
    void copyRecords(const QList<Record*>& recordList);
    void copyGroups(const QList<RecordGroup*>& groupsList);
    void copyProbeFiles(const QList<ProbeFile*>& probeFileList);
    void cutRecords(const QList<Record*>& recordList);
    void cutGroups(const QList<RecordGroup*>& groupList);
    void cutProbeFiles(const QList<ProbeFile*>& recordList);
    void pasteRecords(RecordGroup* newGroup, int index);
    void pasteGroups(ProbeFile* pNewProbeFile, int index);
    void pasteProbeFiles(int index);
    void renameTreeItem(const QString& newName, RecordTreeItem* treeItem);
    void rewriteRecord(Record* record);
    void cancelDeletion();
    void confirmDeletion();
    void renameTreeItem(RecordTreeItem* item);

    //setters
    void setWorkDir(const QString& dirPath);
    //getters
    const QString& getWorkDirPath() const {return workDir.absolutePath();}
    RootItem* getRootItem(){return pRootItem;}
    const QStringList& getImportExtList() const {return importExtList;}
    const QList<QObject*>& getPluginList()const {return pluginList;}
private:
    RootItem* pRootItem;
    QDir workDir;
    QDir pluginsDir;
    QList<QObject*> pluginList;
    QStringList importExtList;
    ProbeFile* readProbeFile(const QString& probePath);
    QList<Record*> cutRecordsList;
    QList<RecordGroup*> cutGroupsList;
    QList<ProbeFile*> cutProbeFilesList;
    QList<Record*> copyRecordsList;
    QList<RecordGroup*> copyGroupsList;
    QList<ProbeFile*> copyProbeFilesList;
    void loadPlugins();
    int readGroupHeader(QDataStream& inStream, RecordGroup *pRecordGroup);
    QList<Record *> readGroupRecords(QDataStream& inStream, QString dirPath,
                                     int recNum, RecordGroup *pRecordGroup);
    void addProbeFile(const QString& filePath);
    void writeProbeFile(ProbeFile* probeFileObj);
    void writeDataFile(Record* record, QList<QVector<double> > data);
    bool nameHasNumber(const QString& name, QString &chopedName, int& number) const;
    bool hasSameName(const QString& name, QString& newName, const QStringList& nameList) const;
public slots:

signals:
    void beginChangeData();
    void endChangeData();
    void pasteRecordIsEnabled(bool b);
    void pasteGroupIsEnabled(bool b);
    void pasteProbeIsEnabled(bool b);
};

#endif // DATAMANAGER_H
