#include "datamanager.h"
#include "importfileinterface.h"
#include "qmath.h"
#include <QPluginLoader>
#include <QApplication>
#include <QDebug>

DataManager::DataManager(QObject *parent) : QObject(parent)
{
}

DataManager::DataManager(const QString& workDirPath, QObject *parent):
    QObject(parent)
{
    workDir.setPath(workDirPath);
    pRootItem = new RootItem();
    loadPlugins();
}

void DataManager::loadPlugins()
{
    pluginsDir.setPath(qApp->applicationDirPath());
    if (pluginsDir.dirName().toLower() == "debug" ||
        pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
    pluginsDir.cd("plugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)){
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *pPlugin = loader.instance();
        if (pPlugin) {
            ImportFileInterface *iFileImport = qobject_cast<ImportFileInterface *>(pPlugin);
            if (iFileImport){
                importExtList<<(iFileImport->extentions());
                pluginList<<pPlugin;
            }
        }
    }
}

bool DataManager::importFile(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    QString extention = fileInfo.suffix();
    ImportFileInterface* pImportInterface;
    bool success=false;
    for (int i=0;i<pluginList.count();++i){
        pImportInterface = qobject_cast<ImportFileInterface*>(pluginList[i]);
        if (pImportInterface->extentions().contains(extention)){
            QFileInfo probeFI;
            success=pImportInterface->importFile(fileInfo.canonicalFilePath(),
                                                 workDir.absolutePath(), probeFI);
            if (success){
                addProbeFile(probeFI.canonicalFilePath());
                return true;
            }
        }
    }
    return false;
}

void DataManager::addProbeFile(const QString& filePath)
{
    emit beginChangeData();
    pRootItem->getProbeFilesList()<<readProbeFile(filePath);
    emit endChangeData();
}

void DataManager::readWorkDir()
{
    QStringList dirList = workDir.entryList(QDir::Dirs|QDir::NoDotAndDotDot,QDir::Name);
    QStringList nameFilter;
    nameFilter<<"*.probe";
    QStringList fileList;
    QDir projectDir;
    QFileInfo probeInfo;
    for (int i=0;i<dirList.count();++i){
        projectDir.setPath(workDir.path()+"/"+dirList.value(i));
        fileList=projectDir.entryList(nameFilter,QDir::Files,QDir::Name);
        if (fileList.count()!=1){
            //no probe file, or more than one prob file
            return;
        }
        QDir::setCurrent(projectDir.absolutePath());
        probeInfo.setFile(fileList.value(0));
        pRootItem->getProbeFilesList()<<readProbeFile(probeInfo.canonicalFilePath());
    }
}

ProbeFile* DataManager::readProbeFile(const QString &probePath)
{
    QFileInfo probeInfo(probePath);
    ProbeFile* pProbeFileObj = new ProbeFile(probeInfo.filePath(), pRootItem);
    pProbeFileObj->setName(probeInfo.baseName());
    RecordGroup* pRecordGroup;
    QFile probeFile(probePath);
    probeFile.open(QIODevice::ReadOnly);
    QDataStream inStream(&probeFile);
    //read probe file header TODO
    qint16 groupsNum;
    inStream>>groupsNum;
    for (int i=0;i<static_cast<int>(groupsNum);++i){
        pRecordGroup = new RecordGroup(pProbeFileObj);
        int recNum=readGroupHeader(inStream, pRecordGroup);
        pRecordGroup->getRecordList()<<readGroupRecords(inStream, probeInfo.canonicalPath(),
                                                        recNum, pRecordGroup);
        pProbeFileObj->getRecordGroupList()<<pRecordGroup;
    }
    return pProbeFileObj;
}

int DataManager::readGroupHeader(QDataStream& inStream, RecordGroup *pRecordGroup)
{
    qint8 origin;
    QString inString;
    QDate inDate;
    QTime inTime;
    qint16 recNum;

    inStream>>origin;
    pRecordGroup->setOrigin(static_cast<RecordGroup::Origin>(origin));

    inStream>>inString;
    pRecordGroup->setName(inString);  inString.clear();

    inStream>>inString;
    pRecordGroup->setSourceFileName(inString); inString.clear();

    inStream>>inString;
    pRecordGroup->setSourceFilePath(inString); inString.clear();

    inStream>>inString;
    pRecordGroup->setSourceFileType(inString); inString.clear();

    inStream>>inString;
    pRecordGroup->setCompNameCreate(inString); inString.clear();

    inStream>>inString;
    pRecordGroup->setUserNameCreate(inString); inString.clear();

    inStream>>inDate;
    pRecordGroup->setDateCreate(inDate);

    inStream>>inTime;
    pRecordGroup->setTimeCreate(inTime);

    inStream>>inString;
    pRecordGroup->setCompNameModify(inString); inString.clear();

    inStream>>inString;
    pRecordGroup->setUserNameModify(inString); inString.clear();

    inStream>>inDate;
    pRecordGroup->setDateModify(inDate);

    inStream>>inTime;
    pRecordGroup->setTimeModify(inTime);

    inStream>>recNum;
    return static_cast<int>(recNum);
}

QList<Record *> DataManager::readGroupRecords(QDataStream& inStream, QString dirPath,
                                              int recNum, RecordGroup* pRecordGroup)
{
    QList<Record *> recList;
    Record* pRecord;
    qint8 qi8RecType;
    qint8 qi8Obtaining;
    QFile recordFile;
    QString recordName;
    QDataStream inRecStream;
    QString inString;
    QDate inDate;
    QTime inTime;
    for (int i=0;i<recNum;++i){
        inStream >> inString;
        recordName = inString;
        inString.clear();
        recordFile.setFileName(dirPath+"/"+recordName+"_"+pRecordGroup->getName()+".pdata");
        if (!recordFile.open(QIODevice::ReadOnly)){
            //no record file!
        }
        inRecStream.setDevice(&recordFile);
        //record type
        inRecStream>>qi8RecType;
        pRecord = Record::recordFactory(static_cast<Record::RecordType>(qi8RecType),
                                        pRecordGroup);
        pRecord->setDataFilePath(QFileInfo(recordFile).absoluteFilePath());
        //obtaining
        inRecStream>>qi8Obtaining;
        pRecord->setObtaining(static_cast<Record::Obtaining>(qi8Obtaining));
        //name
        inRecStream>>inString;
        pRecord->setName(inString); inString.clear();
        //description
        inRecStream>>inString;
        pRecord->setDescription(inString); inString.clear();
        //name in source file
        inRecStream>>inString;
        pRecord->setSourceName(inString); inString.clear();
        //source file name
        inRecStream>>inString;
        pRecord->setSourceFile(inString); inString.clear();
        //source file path
        inRecStream>>inString;
        pRecord->setSourceFilePath(inString); inString.clear();
        //source file type
        inRecStream>>inString;
        pRecord->setSourceFileType(inString); inString.clear();
        //computer name create
        inRecStream>>inString;
        pRecord->setCompNameCreate(inString); inString.clear();
        //user name create
        inRecStream>>inString;
        pRecord->setUserNameCreate(inString); inString.clear();
        //date create
        inRecStream>>inDate;
        pRecord->setDateCreate(inDate);
        //time create
        inRecStream>>inTime;
        pRecord->setTimeCreate(inTime);
        //computer name modify
        inRecStream>>inString;
        pRecord->setCompNameModify(inString); inString.clear();
        //user name modify
        inRecStream>>inString;
        pRecord->setUserNameModify(inString); inString.clear();
        //date modify
        inRecStream>>inDate;
        pRecord->setDateModify(inDate);
        //time modify
        inRecStream>>inTime;
        pRecord->setTimeModify(inTime);

        switch (pRecord->getType()){
//        case Record::rtRecord2D:
//            break;
//        case Record::rtRecord2DFun:
//            break;
        case Record::rtRecordFun1:
            RecordFun1* pRecordOscil = dynamic_cast<RecordFun1*>(pRecord);
            //length
            qint32 length;
            inRecStream>>length;
            pRecordOscil->setLength(static_cast<int>(length));
            //x units
            QString xUnits;
            inRecStream>>xUnits;
            //y units
            QString yUnits;
            inRecStream>>yUnits;
            pRecordOscil->setUnits(xUnits,yUnits);
            //is fixed step
            bool isFixedStep;
            inRecStream>>isFixedStep;
            pRecordOscil->setIsFixedStep(isFixedStep);
            //step length
            double stepLength;
            inRecStream>>stepLength;
            pRecordOscil->setStepLength(stepLength);
            //min
            double min;
            inRecStream>>min;
            pRecordOscil->setMin(min);
            //max
            double max;
            inRecStream>>max;
            pRecordOscil->setMax(max);
        }
        //data offset
        pRecord->setDataOffset(recordFile.pos());
        recList<<pRecord;
        recordFile.close();
    }
    return recList;
}

void DataManager::generateProbeFile(const QString& projectName)
{
    QDir::setCurrent(workDir.absolutePath());
    qint16 groupsNum=2;
    workDir.mkdir(projectName);
    QDir projectDir(workDir.absolutePath()+"/"+projectName);
    QDir::setCurrent(projectDir.absolutePath());
    QFile probeFile(projectName+".probe");
    QFile recordFile;
    if (!probeFile.open(QIODevice::WriteOnly)) return;
    QDataStream outStream(&probeFile);
    QDataStream outRecStream;
    outStream << groupsNum;
    for (int i=0;i<groupsNum;++i){
        //write group header
        outStream << static_cast<qint8>(RecordGroup::oImport);
        outStream << QString("Group %0").arg(i).toUtf8();
        outStream << QString("MyComputer").toUtf8();
        outStream<<QString(qgetenv("USERNAME")).toUtf8();
        outStream<<QDate::currentDate();
        outStream<<QTime::currentTime();
        outStream<<QString("SourceFile").toUtf8();
        outStream<<QString("C:/TestDir").toUtf8();
        qint16 recordsNum=6;
        outStream<<recordsNum;
        //write record list and pdat files
        for (int j=0;j<static_cast<int>(recordsNum);++j){
            outStream<<QString("Record%0%1").arg(i).arg(j).toUtf8();
            recordFile.setFileName(QString("Record%0%1").arg(i).arg(j)+"_"+
                                   QString("Group %0").arg(i)+".pdata");
            recordFile.open(QIODevice::WriteOnly);
            outRecStream.setDevice(&recordFile);
            outRecStream << static_cast<qint8>(Record::rtRecordFun1);
            outRecStream << QString("Record %0 %1").arg(i).arg(j).toUtf8();
            outRecStream << QString("Description").toUtf8();
            outRecStream << QString();
            outRecStream << QString();
            outRecStream << QString();
            outRecStream << QString();
            outRecStream << QString();
            outRecStream << QString();
            outRecStream << QDate::currentDate();
            outRecStream << QTime::currentTime();
            outRecStream << static_cast<qint8>(Record::oImport);
            outRecStream << QString();
            outRecStream << QString();
            outRecStream << true;

            QVector<double> testData;
            double step=0.01;
            for (int k=0;k<1000;++k){
                testData<<qSin(k*step+i+j);
            }
            outRecStream << step;
            outRecStream << testData.length();
            outRecStream << testData;
            recordFile.close();
        }
    }
    probeFile.close();
}

void DataManager::newEmptyGroup(ProbeFile* probeFileObj,const QString& groupName,
                                int index)
{
    RecordGroup* pG = new RecordGroup(probeFileObj);
    QStringList namesList;
    probeFileObj->getGroupsNamesList(namesList);
    QString name;
    hasSameName(groupName,name,namesList);
    pG->setName(name);
    pG->setOrigin(RecordGroup::oProbe);
    probeFileObj->getRecordGroupList().insert(index, pG);
    writeProbeFile(probeFileObj);
    //probeFileObj->setUnsaved();
}

void DataManager::newEmptyProbeFile(const QString& fileName, int index)
{
    ProbeFile* pPF = new ProbeFile(pRootItem);
    QStringList namesList;
    pRootItem->getFilesNamesList(namesList);
    QString name;
    hasSameName(fileName,name,namesList);
    pPF->setName(name);
    pRootItem->getProbeFilesList().insert(index, pPF);
    workDir.mkdir(name);
    QFile probeFile(workDir.canonicalPath()+"/"+name+"/"+name+".probe");
    probeFile.open(QIODevice::WriteOnly);
    QDataStream outStream(&probeFile);
    outStream<<qint16(0);
    probeFile.close();
    pPF->setProbeFilePath(QFileInfo(probeFile).canonicalFilePath());
}

void DataManager::deleteRecord(Record* pRecord, bool bDelFile)
{
    if (bDelFile){
        RecordGroup* pG = dynamic_cast<RecordGroup*>(pRecord->parent());
        pG->getRecordList().removeAt(pRecord->childNumber());
        QFile pDataFile(pRecord->getDataFilePath());
        pDataFile.remove();
        writeProbeFile(pRecord->getProbeFileObj());
        delete pRecord;
        //TODO: rewrite probe file
    }else
        pRecord->setDeleted();
}

void DataManager::deleteGroup(RecordGroup* pRecordGroup, bool bDelFiles)
{
    if (bDelFiles){
        ProbeFile* pPF = dynamic_cast<ProbeFile*>(pRecordGroup->parent());
        QList<Record*>& recList = pRecordGroup->getRecordList();
        QFile pDataFile;
        int recNum = recList.count();
        for (int i=0;i<recNum;++i){
            pDataFile.setFileName(recList.value(i)->getDataFilePath());
            pDataFile.remove();
        }
        pPF->getRecordGroupList().removeAt(pRecordGroup->childNumber());
        writeProbeFile(pRecordGroup->getProbeFileObj());
        delete pRecordGroup;
    }else{
        for (int i=0;i<pRecordGroup->getRecordList().count();++i){
            pRecordGroup->getRecordList().value(i)->setDeleted();
        }
        pRecordGroup->setDeleted();
    }
}

void DataManager::deleteProbeFile(ProbeFile* probeFileObj, bool bDelFiles)
{
    if (bDelFiles){
        QFileInfo probeFileInfo(probeFileObj->getProbeFilePath());
        QDir probeDir(probeFileInfo.absoluteDir());
        pRootItem->getProbeFilesList().removeAt(probeFileObj->myNumber());
        delete probeFileObj;
        probeDir.removeRecursively();
    }else{
        QList<RecordGroup*>& groupList= probeFileObj->getRecordGroupList();
        for (int i=0;i<groupList.count();++i){
            QList<Record*>& recordList=groupList.value(i)->getRecordList();
            for (int j=0;j<recordList.count();++j){
                recordList.value(j)->setDeleted();
            }
            groupList.value(i)->setDeleted();
        }
        probeFileObj->setDeleted();
    }
}

void DataManager::cutRecords(const QList<Record*>& recordList)
{
    copyRecordsList.clear();
    if (!cutRecordsList.empty()){
        for (int i=0;i<cutRecordsList.count();++i){
            cutRecordsList.value(i)->setDeleted(false);
        }
    }
    cutRecordsList.clear();
    for (int i=0;i<recordList.count();++i)
        recordList.value(i)->setDeleted();
    cutRecordsList<<recordList;
    emit pasteRecordIsEnabled(true);
}

void DataManager::copyRecords(const QList<Record*>& recordList)
{
    copyRecordsList.clear();
    if (!cutRecordsList.empty()){
        for (int i=0;i<cutRecordsList.count();++i){
            cutRecordsList.value(i)->setDeleted(false);//todo
        }
    }
    cutRecordsList.clear();
    copyRecordsList<<recordList;
    emit pasteRecordIsEnabled(true);
}

void DataManager::copyGroups(const QList<RecordGroup*>& groupsList)
{
    copyGroupsList.clear();
    //...
    copyGroupsList<<groupsList;
    emit pasteGroupIsEnabled(true);
}

void DataManager::pasteGroups(ProbeFile* pNewProbeFile, int index)
{
    RecordGroup* pGroup;
    RecordGroup* pNewGroup;
    ProbeFile* pOldProbeFile;
    QString newGroupName;
    QStringList namesList;
    pNewProbeFile->getGroupsNamesList(namesList);
    if (!copyGroupsList.empty()){
        for (int i=0;i<copyGroupsList.count();++i){
            pOldProbeFile = copyGroupsList.value(i)->getProbeFileObj();
            pGroup=copyGroupsList.value(i);
            pNewGroup = new RecordGroup();//write copy constructor and = operator for recordgorup
            hasSameName(pGroup->getName(),newGroupName,namesList);
            *pNewGroup=*pGroup;
            if (pNewProbeFile!=pOldProbeFile)
                pNewGroup->setProbeFileObj(pNewProbeFile);
            pNewGroup->setName(newGroupName);
            pNewProbeFile->getRecordGroupList().insert(index+i, pNewGroup);
            //copy record files
            QFile dataFile;
            QString copyFilePath;
            for (int i=0;i<pNewGroup->childCount();++i){
                dataFile.setFileName(pNewGroup->getRecordList()[i]->getDataFilePath());
                copyFilePath=QFileInfo(pNewProbeFile->getProbeFilePath()).canonicalPath()+
                        "/"+pNewGroup->getRecordList()[i]->getName()+"_"+pNewGroup->getName()+
                        ".pdata";
                dataFile.copy(copyFilePath);
                pNewGroup->getRecordList()[i]->setDataFilePath(copyFilePath);
            }
            //end copy record files
        }
        writeProbeFile(pNewProbeFile);
        writeProbeFile(pOldProbeFile);
    }
}

void DataManager::pasteRecords(RecordGroup *newGroup, int index)
{
    ProbeFile* pProbeFileObj1;
    ProbeFile* pProbeFileObj2=newGroup->getProbeFileObj();
    RecordGroup* pGroup;
    Record* pRecord;
    Record* pNewRecord;
    QString newName;
    QStringList namesList;
    if (!copyRecordsList.empty()){
        //when copy, can paste any number of times
        for (int i=0;i<copyRecordsList.count();++i){
            newGroup->recordsNamesList(namesList);
            pGroup=copyRecordsList.value(i)->getRecordGroup();
            pRecord=copyRecordsList.value(i);
            pNewRecord = Record::recordFactory(pRecord->getType());
            *pNewRecord=*pRecord;//virtual assign operator
            pProbeFileObj1=pGroup->getProbeFileObj();           
            hasSameName(pNewRecord->getName(),newName,namesList);
            pNewRecord->setName(newName);
            newGroup->getRecordList().insert(index+i, pNewRecord);
            QFileInfo copyFileInfo(pProbeFileObj2->getProbeFilePath());
            //copy file
            QFile dataFile(pRecord->getDataFilePath());
            QFile newDataFile(copyFileInfo.canonicalPath()+"/"+newName+"_"+newGroup->getName()+
                              ".pdata");
            dataFile.open(QIODevice::ReadOnly);
            QDataStream inStream(&dataFile);
            inStream.skipRawData(2*sizeof(qint8));//skip type and obtaining
            QString oldName;
            inStream>>oldName;//read old name of the record
            qint64 fileSize = dataFile.size();
            int rawSize = static_cast<int>(fileSize)-2*oldName.size()-2*sizeof(qint8);
            char* rawDataBuf = new char[rawSize];
            inStream.readRawData(rawDataBuf, rawSize);
            dataFile.close();
            newDataFile.open(QIODevice::WriteOnly);
            QDataStream outStream(&newDataFile);
            outStream<<static_cast<qint8>(pNewRecord->getType());
            outStream<<static_cast<qint8>(pNewRecord->getObtaining());
            outStream<<newName;
            outStream.writeRawData(rawDataBuf,rawSize);
            newDataFile.close();
            //copy file end
            pNewRecord->setDataFilePath(QFileInfo(newDataFile).canonicalFilePath());
            pNewRecord->setDataOffset(pRecord->getDataOffset()+
                                      static_cast<qint64>(2*newName.size()-2*oldName.size()));
            if (pGroup!=newGroup)
                pNewRecord->setGroup(newGroup);
            writeProbeFile(pProbeFileObj1);
            writeProbeFile(pProbeFileObj2);
        }
    }else if (!cutRecordsList.empty()){
        //when cut, can paste only one time
        for (int i=0;i<cutRecordsList.count();++i){
            pGroup=cutRecordsList.value(i)->getRecordGroup();
            pProbeFileObj1 = pGroup->getProbeFileObj();
            pRecord = pGroup->getRecordList().takeAt(cutRecordsList.value(i)->myNumber());
            newGroup->recordsNamesList(namesList);
            hasSameName(pRecord->getName(),newName,namesList);
            pRecord->setName(newName);
            pRecord->setDeleted(false);
            newGroup->getRecordList().insert(index+i, pRecord);//TODO
            if (newGroup!=pGroup){
                pRecord->setGroup(newGroup);
                QFileInfo probeInfo(pProbeFileObj1->getProbeFilePath());
                QFile pDataFile(pRecord->getDataFilePath());
                if (pProbeFileObj1!=pProbeFileObj2){
                    probeInfo.setFile(pProbeFileObj2->getProbeFilePath());
                }
                pDataFile.rename(probeInfo.canonicalPath()+"/"+newName+"_"+newGroup->getName()+
                             ".pdata");
                pRecord->setDataFilePath(pDataFile.fileName());
            }
        }
        cutRecordsList.clear();
        emit pasteRecordIsEnabled(false);
        writeProbeFile(pProbeFileObj1);
        writeProbeFile(pProbeFileObj2);
    }
}

void DataManager::writeProbeFile(ProbeFile* probeFileObj)
{
    QFile probeFile(probeFileObj->getProbeFilePath());
    probeFile.open(QIODevice::WriteOnly);
    QDataStream outStream(&probeFile);
    RecordGroup* pGroup;
    int groupsNum = probeFileObj->childCount();
    outStream<< static_cast<qint16>(groupsNum);
    int recordsNum = 0;
    for (int i=0;i<groupsNum;++i){
        //write group header
        pGroup = probeFileObj->getRecordGroupList().value(i);
        outStream << static_cast<qint8>(pGroup->getOrigin());
        outStream << pGroup->getName();
        outStream << pGroup->getSourceFileName();
        outStream << pGroup->getSourceFilePath();
        outStream << pGroup->getSourceFileType();
        outStream << pGroup->getCompNameCreate();
        outStream << pGroup->getUserNameCreate();
        outStream << pGroup->getDateCreate();
        outStream << pGroup->getTimeCreate();
        outStream << pGroup->getCompNameModify();
        outStream << pGroup->getUserNameModify();
        outStream << pGroup->getDateModify();
        outStream << pGroup->getTimeModify();
        recordsNum=pGroup->getRecordList().count();
        outStream<<static_cast<qint16>(recordsNum);
        QStringList namesList;
        pGroup->recordsNamesList(namesList);
        //write record list
        for (int j=0;j<namesList.count();++j){
            outStream<<namesList.value(j);
        }
    }
    probeFile.close();
}

bool DataManager::nameHasNumber(const QString& name, QString& chopedName, int& number) const
{
    bool hasNumber=false;
    int num=-1;
    int index1=name.lastIndexOf("(");
    int index2=name.lastIndexOf(")");
    if (index2==name.length()-1&&index1>0&&(index2-index1)>1){
        QString subStr = name.right(index2-index1);
        subStr.chop(1);
        if (subStr[0]!=QChar('0')&&subStr[0]!=QChar('-')){
            num=subStr.toInt(&hasNumber,10);
            chopedName=name;
            chopedName.chop(index2-index1+1);
        }
    }
    number=num;
    return hasNumber;
}

bool DataManager::hasSameName(const QString& name, QString& newName, const QStringList& nameList) const
{
    newName=name;
    int nameNumber;
    QString chopedName;
    bool hasNumber=nameHasNumber(newName, chopedName, nameNumber);
    if (nameList.contains(name, Qt::CaseInsensitive)){
        if (hasNumber==true){
            for (int i=0;i<nameList.size();++i){
                int valueNumber;
                QString chopedValue;
                bool valueHasNumber = nameHasNumber(nameList.value(i),chopedValue, valueNumber);
                if (valueHasNumber &&
                    valueNumber>=nameNumber &&
                    chopedValue.compare(chopedName,Qt::CaseInsensitive)==0)
                        nameNumber=valueNumber+1;
            }
            newName = chopedName+"("+QString::number(nameNumber)+")";
        }else{
            int i=1;
            while (nameList.contains(name+"("+QString::number(i)+")")){
                ++i;
            }
            newName+="("+QString::number(i)+")";
        }
        return true;
    } else
        return false;
}

