#include "record.h"
#include <QDebug>
#include <QBrush>
//#include <QHostInfo> todo
//RecordTreeItem
//RecordTreeItem::RecordTreeItem():
//    bUnsaved(false),
//    bDeleted(false)
//{
//}
// commented course of ambiguity

RecordTreeItem::RecordTreeItem(bool u, bool d):
    bUnsaved(u),
    bDeleted(d)
{
}

QVariant RecordTreeItem:: data(Qt::ItemDataRole role) const
{
    switch (role){
    case Qt::ForegroundRole:
        QBrush brush;
        if (bUnsaved==true)
            brush.setColor(Qt::darkGray);
        else
            brush.setColor(Qt::black);
        QVariant variant=brush;
        return variant;
        break;
    }
}

//Record
const QString Record::obtainingStrings[4]=
{
    "Import",
    "ImpModify",
    "Enter",
    "Calculate"
};

const QString Record::recordTypeStrings[3]=
{
    "Record2D",
    "Record2DFun",
    "RecordFun1"
};

Record::Record():
    RecordTreeItem(),
    compNameCreate(QString("Computer")),//todo
    userNameCreate(qgetenv("USERNAME")),
    dateCreate(QDate::currentDate()),
    timeCreate(QTime::currentTime())
{
}

Record::Record(RecordGroup *pGroup, bool u, bool d):
    RecordTreeItem(u,d),
    pRecordGroup(pGroup),
    compNameCreate(QString("Computer")),//todo
    userNameCreate(qgetenv("USERNAME")),
    dateCreate(QDate::currentDate()),
    timeCreate(QTime::currentTime())
{
}

Record::~Record()
{
}

Record* Record::recordFactory(RecordType type)
{
    switch (type){
    case rtRecordFun1:
        return new RecordFun1();
        break;
    default:
        return 0;
    }
}

Record* Record::recordFactory(RecordType type, RecordGroup* pGroup, bool u, bool d)
{
    switch (type){
    case rtRecordFun1:
        return new RecordFun1(pGroup, u, d);
        break;
    default:
        return 0;
    }
}

RecordTreeItem* Record::child(int number)
{
    Q_UNUSED(number)
    return 0;
}

int Record::childCount() const
{
    return 0;
}

QVariant Record::data(Qt::ItemDataRole role) const
{
    RecordTreeItem::data(role);
    switch (role){
    case (Qt::DisplayRole):
        return QVariant(name);
        break;
    case (Qt::ForegroundRole):
        return  RecordTreeItem::data(role);
        break;
    default:
        return QVariant();
    }
}

bool Record::insertChildren(int position, int count)
{
    Q_UNUSED(position)
    Q_UNUSED(count)
    return true; //Record has no childern
}

RecordTreeItem* Record::parent()
{
    return dynamic_cast<RecordTreeItem*>(pRecordGroup);
}

bool Record::removeChildren(int position, int count)
{
    Q_UNUSED(position)
    Q_UNUSED(count)
    return true; //Record has no childern
}

int Record::childNumber() const
{
    for (int i=0;i<pRecordGroup->childCount();++i){
            if (pRecordGroup->child(i)==this) return i;
        }
}

bool Record::setData(Qt::ItemDataRole, const QVariant &value)
{
    //it can be used for rename todo!
}

int Record::getProperties(QStringList& headerList, QStringList& valueList) const
{
    headerList<<"Record Type"<<
                "Obtaining"<<
                "Name"<<
                "Description"<<
                "Source Name"<<
                "Source File"<<
                "Source File Path"<<
                "Source File Type"<<
                "Computer Name (created)"<<
                "User Name (created)"<<
                "Date (created)"<<
                "Time (created)"<<
                "Computer Name (modified)"<<
                "User Name (modified)"<<
                "Date (modified)"<<
                "Time (modified)";
    valueList<<recordTypeStrings[recordType]<<
               obtainingStrings[obtaining]<<
               name<<
               description<<
               sourceName<<
               sourceFile<<
               sourceFilePath<<
               sourceFileType<<
               compNameCreate<<
               userNameCreate<<
               dateCreate.toString()<<
               timeCreate.toString()<<
               compNameModify<<
               userNameModify<<
               dateModify.toString()<<
               timeModify.toString();
    return headerList.count();;
}

ProbeFile* Record::getProbeFileObj()
{
    return pRecordGroup->getProbeFileObj();
}

int Record::myNumber() const
{
    QList<Record*>& recList = pRecordGroup->getRecordList();
    int i=0;
    while (recList.value(i)!=this)
        ++i;
    return i;
}

Record& Record::operator=(const Record& otherRecord)
{
    bUnsaved=otherRecord.bUnsaved;
    bDeleted=otherRecord.bDeleted;
//properties
    recordType=otherRecord.recordType;
    obtaining=otherRecord.obtaining;

    name=otherRecord.name;
    description=otherRecord.description;
    sourceName=otherRecord.sourceName;
    sourceFile=otherRecord.sourceFile;
    sourceFilePath=otherRecord.sourceFilePath;
    sourceFileType=otherRecord.sourceFileType;

    compNameCreate=otherRecord.compNameCreate;
    userNameCreate=otherRecord.userNameCreate;
    dateCreate=otherRecord.dateCreate;
    timeCreate =otherRecord.timeCreate;

    compNameModify=otherRecord.compNameCreate;
    userNameModify=otherRecord.userNameCreate;
    dateModify=otherRecord.dateCreate;
    timeModify =otherRecord.timeCreate;
//data
    dataOffset=otherRecord.dataOffset;
    dataFilePath=otherRecord.dataFilePath;
    tempFilesPathList=otherRecord.tempFilesPathList;

    pRecordGroup=otherRecord.pRecordGroup;
    return *this;
}

//RecordFun1

RecordFun1::RecordFun1():
    Record()
{
    recordType = rtRecordFun1;
}

RecordFun1::RecordFun1(RecordGroup *pGroup, bool u, bool d):
    Record(pGroup,u,d)
{
    recordType = rtRecordFun1;
}

RecordFun1::~RecordFun1()
{
}

int RecordFun1::getProperties(QStringList &headerList, QStringList &valueList) const
{
    Record::getProperties(headerList,valueList);

    headerList<<"Length"<<"X Units"<<"Y Units";
    valueList<<QString::number(length)<<xUnits<<yUnits;
    headerList<<"Fixed Step";
    valueList<<(isFixedStep?"true":"false");
    if (isFixedStep) {
        headerList<<"Step Length";
        valueList<<QString::number(stepLength);
    }
    headerList<<"Max"<<"Min";
    valueList<<QString::number(max)<<QString::number(min);
    return headerList.count();
}

bool RecordFun1::readMyData(QList<QVector<double> > &data) /*const*/
{
    if (!QFile::exists(dataFilePath))
        return false;
    QFile dataFile(dataFilePath);
    if (!dataFile.open(QIODevice::ReadOnly)){
        return false;
    }

    QDataStream inStream(&dataFile);
    dataFile.seek(dataOffset);
    QVector<double> xData;
    QVector<double> yData;
//    if (isFixedStep){
//        for (int i=0;i<length;++i)
//            xData<<(stepLength*i);
//    } else
    inStream>>xData;
    inStream>>yData;
    data<<xData<<yData;
    dataFile.close();
}

Record& RecordFun1::operator=(const Record& otherRecord)
{
    const RecordFun1* pOtherRecordFun1= dynamic_cast<const RecordFun1*>(&otherRecord);
    if (pOtherRecordFun1){
        Record::operator =(otherRecord);
        length=pOtherRecordFun1->length;
        xUnits=pOtherRecordFun1->xUnits;
        yUnits=pOtherRecordFun1->yUnits;
        isFixedStep=pOtherRecordFun1->isFixedStep;
        stepLength=pOtherRecordFun1->stepLength;
        max=pOtherRecordFun1->max;
        min=pOtherRecordFun1->min;
    }
    return *this;
}

//RecordGroup
const  QString RecordGroup::originStrings[3]={"Import","Probe","Combine"};

RecordGroup::RecordGroup()
{
}

RecordGroup::RecordGroup(ProbeFile* pProbeFile, bool u, bool d):
    RecordTreeItem(u,d),
    pProbeFileObj(pProbeFile),
    compNameCreate(QString("Computer")),//todo
    userNameCreate(qgetenv("USERNAME")),
    dateCreate(QDate::currentDate()),
    timeCreate(QTime::currentTime())
{
}

RecordGroup::~RecordGroup()
{
    for (int i=0; i<recordList.count(); ++i){
        delete recordList[i];
    }
}

RecordGroup& RecordGroup::operator=(const RecordGroup& otherGroup)
{
    //wise copy fields
    origin=otherGroup.origin;
    name=otherGroup.name;

    sourceFileName=otherGroup.sourceFileName;
    sourceFilePath=otherGroup.sourceFilePath;
    sourceFileType=otherGroup.sourceFileType;

    compNameCreate=otherGroup.compNameCreate;
    userNameCreate=otherGroup.userNameCreate;
    dateCreate=otherGroup.dateCreate;
    timeCreate=otherGroup.timeCreate;

    compNameModify=otherGroup.compNameModify;
    userNameModify=otherGroup.userNameModify;
    dateModify=otherGroup.dateModify;
    timeModify=otherGroup.timeModify;

    bHasUnsavedRecords=otherGroup.bHasUnsavedRecords;
    pProbeFileObj=otherGroup.pProbeFileObj;
    //deep copy of record list
    recordList.clear();
    for (int i=0;i<otherGroup.childCount();++i){
        recordList<<Record::recordFactory(otherGroup.getRecordList()[i]->getType());
        *recordList[i]=*(otherGroup.getRecordList()[i]);
        recordList[i]->setGroup(this);
    }
}

RecordTreeItem* RecordGroup::child(int number)
{
    int noDelNumber=-1;
    int i=-1;
    do {
            ++i;
            if (!recordList.value(i)->getDeleted())
                ++noDelNumber;
    } while (noDelNumber!=number);
    return recordList.value(i);
}

int RecordGroup::childCount() const
{
    int count=0;
    for (int i=0;i<recordList.count();++i){
        if (!recordList.value(i)->getDeleted())
            ++count;
    }
    return count;
}

QVariant RecordGroup::data(Qt::ItemDataRole role) const
{
    RecordTreeItem::data(role);
    switch (role){
    case (Qt::DisplayRole):
        return QVariant(name);
        break;
    case (Qt::ForegroundRole):
        return  RecordTreeItem::data(role);
        break;
    default:
        return QVariant();
    }
}

bool RecordGroup::insertChildren(int position, int count)
{
//    if (position < 0 || position > recordList.size())
//        return false;
//    for (int row = 0; row < count; ++row) {
//        Record* r = new  Record();
//        recordList.insert(position, r);
//    }
//    return true;
}

RecordTreeItem* RecordGroup::parent()
{
    return dynamic_cast<RecordTreeItem*>(pProbeFileObj);
}

bool RecordGroup::removeChildren(int position, int count)
{
//    if (position < 0 || position + count > recordList.size())
//        return false;

//    for (int row = 0; row < count; ++row)
//        delete recordList.takeAt(position);

//    return true;
}

int RecordGroup::childNumber() const
{
    for (int i=0;i<pProbeFileObj->childCount();++i){
        if (pProbeFileObj->child(i)==this)
            return i;
    }
}

bool RecordGroup::setData(Qt::ItemDataRole, const QVariant &value)
{
    //it could be used for rename todo
}

int RecordGroup::getProperties(QStringList& headerList, QStringList& valueList) const
{
    headerList<<"Origin"<<"Name";
    valueList<<originStrings[origin]<<name;
    if (origin==oImport||origin==oCombine){
        headerList<<"Source File Name"<<"Source File Path"<<"Source File Type";
        valueList<<sourceFileName<<sourceFilePath<<sourceFileType;
    }
    headerList<<"Computer Name (created)";
    headerList<<"User Name (created)";
    headerList<<"Date (created)";
    headerList<<"Time (created)";

    valueList<<compNameCreate<<userNameCreate<<
               dateCreate.toString()<<timeCreate.toString();

    headerList<<"Computer Name (modified)";
    headerList<<"User Name (modified)";
    headerList<<"Date (modified)";
    headerList<<"Time (modified)";

    valueList<<compNameModify<<userNameModify<<
               dateModify.toString()<<timeCreate.toString();

    return headerList.count();
}

int RecordGroup::myNumber() const
{
    QList<RecordGroup*>& groupList = pProbeFileObj->getRecordGroupList();
    int i=0;
    while (groupList.value(i)!=this)
        ++i;
    return i;
}

void RecordGroup::recordsNamesList(QStringList& namesList) const
{
    for (int i=0;i<recordList.count();++i)
        namesList<<recordList.value(i)->getName();
}

//ProbeFile
ProbeFile::ProbeFile()
{
}

ProbeFile::ProbeFile(RootItem* pRoot, bool u, bool d):
    RecordTreeItem(u,d),
    pRootItem(pRoot)
{
}

ProbeFile::ProbeFile(const QString& filePath, RootItem* pRoot, bool u, bool d):
    RecordTreeItem(u,d),
    pRootItem(pRoot),
    probeFilePath(filePath)
{
}

ProbeFile::~ProbeFile()
{
    for (int i=0; i<recordGroupList.count(); ++i){
        delete recordGroupList[i];
    }
}

RecordTreeItem* ProbeFile::child(int number)
{
    int noDelNumber=-1;
    int i=-1;
    do {
            ++i;
            if (!recordGroupList.value(i)->getDeleted())
                ++noDelNumber;
    } while (noDelNumber!=number);
    return recordGroupList.value(i);
}

int ProbeFile::childCount() const
{
    int count=0;
    for (int i=0;i<recordGroupList.count();++i){
        if (!recordGroupList.value(i)->getDeleted())
            ++count;
    }
    return count;
}

QVariant ProbeFile::data(Qt::ItemDataRole role) const
{
    RecordTreeItem::data(role);
    switch (role){
    case (Qt::DisplayRole):
        return QVariant(name);
        break;
    case (Qt::ForegroundRole):
        return  RecordTreeItem::data(role);
        break;
    default:
        return QVariant();
    }
}

bool ProbeFile::insertChildren(int position, int count)
{
//    if (position < 0 || position > recordGroupList.size())
//        return false;

//    for (int row = 0; row < count; ++row) {
//        RecordGroup* rg = new  RecordGroup();
//        recordGroupList.insert(position, rg);
//    }

//    return true;
}

RecordTreeItem* ProbeFile:: parent()
{
    return dynamic_cast<RecordTreeItem*>(pRootItem);
}

bool ProbeFile::removeChildren(int position, int count)
{
//    if (position < 0 || position + count > recordGroupList.size())
//        return false;

//    for (int row = 0; row < count; ++row)
//        delete recordGroupList.takeAt(position);

//    return true;
}

int ProbeFile::childNumber() const
{
    for (int i=0;i<pRootItem->childCount();++i){
        if (pRootItem->child(i)==this)
            return i;
    }
}

bool ProbeFile::setData(Qt::ItemDataRole, const QVariant &value)
{
    //could be used for rename todo
}

int ProbeFile::getProperties(QStringList& headerList, QStringList& valueList) const
{
    headerList<<"File Name";
    valueList<<name;
    return 1;
}

void ProbeFile::getGroupsNamesList(QStringList& namesList) const
{
    for (int i=0;i<recordGroupList.count();++i)
        namesList<<recordGroupList.value(i)->getName();
}

int ProbeFile::myNumber() const
{
    QList<ProbeFile*>& fileList = pRootItem->getProbeFilesList();
    int i=0;
    while (fileList.value(i)!=this)
        ++i;
    return i;
}


//RootItem
RootItem::RootItem():
    RecordTreeItem()
{
}

RootItem::~RootItem()
{
    for (int i=0; i<probeFilesList.count(); ++i){
        delete probeFilesList[i];
    }
}

RecordTreeItem* RootItem::child(int number)
{
    int noDelNumber=-1;
    int i=-1;
    do {
            ++i;
            if (!probeFilesList.value(i)->getDeleted())
                ++noDelNumber;
    } while (noDelNumber!=number);
    return probeFilesList.value(i);
}

int RootItem::childCount() const
{
    int count=0;
    for (int i=0;i<probeFilesList.count();++i){
        if (!probeFilesList.value(i)->getDeleted())
            ++count;
    }
    return count;
}

QVariant RootItem::data(Qt::ItemDataRole role) const
{
    return QVariant();
}

bool RootItem::insertChildren(int position, int count)
{
//    if (position < 0 || position > recordGroupList.size())
//        return false;

//    for (int row = 0; row < count; ++row) {
//        RecordGroup* rg = new  RecordGroup();
//        recordGroupList.insert(position, rg);
//    }

//    return true;
}

RecordTreeItem* RootItem:: parent()
{
    return 0;
}

bool RootItem::removeChildren(int position, int count)
{
//    if (position < 0 || position + count > recordGroupList.size())
//        return false;

//    for (int row = 0; row < count; ++row)
//        delete recordGroupList.takeAt(position);

//    return true;
}

int RootItem::childNumber() const
{
    return 0; //root item is only one
}

bool RootItem::setData(Qt::ItemDataRole, const QVariant &value)
{

}

void RootItem::getFilesNamesList(QStringList& namesList) const
{
    for (int i=0;i<probeFilesList.count();++i)
        namesList<<probeFilesList.value(i)->getName();
}
