#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QVariant>
#include <QDate>
#include <QTime>
#include <QDataStream>

class RecordGroup;
class ProbeFile;
class RootItem;
//abstract class for (interface) for RecordTreeModel
class RecordTreeItem
{
public:
//    RecordTreeItem();
    RecordTreeItem(bool u=false, bool d=false);
    virtual ~RecordTreeItem() {}

    virtual RecordTreeItem *child(int number)=0;
    virtual int childCount() const=0;
    virtual QVariant data(Qt::ItemDataRole role) const;
    virtual bool insertChildren(int position, int count)=0;
    virtual RecordTreeItem *parent()=0;
    virtual bool removeChildren(int position, int count)=0;
    virtual int childNumber() const=0;
    virtual bool setData(Qt::ItemDataRole, const QVariant &value)=0;
    virtual int getProperties(QStringList& headerList, QStringList& valueList) const =0;
//getters
    bool getUnsaved() const         {return bUnsaved;}
    bool getDeleted() const         {return bDeleted;}
//setters
    void setUnsaved(bool b=true)    {bUnsaved=b;}
    void setDeleted(bool b=true)    {bDeleted=b;}

protected:
    bool bUnsaved;
    bool bDeleted;
};

class Record: public RecordTreeItem
{
//const
    static const int MAX_NAME=256;
    static const int MAX_DESCRIPTION=8192;
    static const int MAX_UNITS=256;
    static const int MAX_SOURCE_FILE=256;
    static const int MAX_SOURCE_FILE_PATH=8192;
    static const int MAX_SOURCE_TYPE=4;

public:
    enum Obtaining {
        oImport,
        oImpModify,
        oEnter,
        oCalculate
    };
    enum RecordType {
        rtRecord2D,
        rtRecord2DFun,
        rtRecordFun1
    };

    Record();
    Record(RecordGroup* pGroup, bool u=false, bool d=false);
    virtual ~Record();
//const getters
    RecordType getType() const                      {return recordType;}
    Obtaining getObtaining() const                  {return obtaining;}

    const QString& getName() const                  {return name;}
    const QString& getDescription() const           {return description;}
    const QString& getSourceName() const            {return sourceName;}
    const QString& getSourceFile() const            {return sourceFile;}
    const QString& getSourceFilePath() const        {return sourceFilePath;}
    const QString& getSourceFileType() const        {return sourceFileType;}

    const QString& getCompNameCreate() const        {return compNameCreate;}
    const QString& getUserNameCreate() const        {return userNameCreate;}
    QDate getDateCreate() const                     {return dateCreate;}
    QTime getTime() const                           {return timeCreate;}

    const QString& getCompNameModify() const        {return compNameModify;}
    const QString& getUserNameModify() const        {return userNameModify;}
    QDate getDateModify() const                     {return dateModify;}
    QTime getTimeModify() const                     {return timeModify;}

    qint64 getDataOffset() const                    {return dataOffset;}
    const QString& getDataFilePath() const          {return dataFilePath;}
    const QStringList& getTempFilePathList() const
                                                    {return tempFilesPathList;}
//non-const getters
    ProbeFile* getProbeFileObj();
    RecordGroup* getRecordGroup()                   {return pRecordGroup;}

//setters
    void setType(RecordType recordType)             {this->recordType=recordType;}
    void setObtaining(Obtaining o)                  {obtaining=o;}

    void setName(const QString& name)               {this->name=name;}
    void setDescription(const QString& s)           {description=s;}
    void setSourceName(const QString& s)            {sourceName=s;}
    void setSourceFile(const QString& s)            {sourceFile=s;}
    void setSourceFilePath(const QString& s)        {sourceFilePath=s;}
    void setSourceFileType(const QString& s)        {sourceFileType=s;}

    void setCompNameCreate(const QString& s)        {compNameCreate=s;}
    void setUserNameCreate(const QString& s)        {userNameCreate=s;}
    void setDateCreate(QDate d)                     {dateCreate=d;}
    void setTimeCreate(QTime t)                     {timeCreate=t;}

    void setCompNameModify(const QString& s)        {compNameModify=s;}
    void setUserNameModify(const QString& s)        {userNameModify=s;}
    void setDateModify(QDate d)                     {dateModify=d;}
    void setTimeModify(QTime t)                     {timeModify=t;}

    void setDataOffset(qint64 dataOffset)           {this->dataOffset=dataOffset;}
    void setDataFilePath(const QString& s)          {dataFilePath=s;}

    void setGroup(RecordGroup* p)                   {pRecordGroup=p;}
//other
    int myNumber() const;
    static Record* recordFactory(RecordType type);
    static Record* recordFactory(RecordType type, RecordGroup* pGroup,
                                 bool u=false, bool d=false);
    static Record* recordFactory(Record* pRecord, RecordGroup* pNewGroup,
                                 bool u=false, bool d=false);

//virtual introduced
    virtual bool readMyData(QList<QVector<double> >& data) /*const*/=0;
    virtual Record& operator=(const Record& otherRecord);

//pure virtual implementation
    RecordTreeItem *child(int number);
    int childCount() const;
    QVariant data(Qt::ItemDataRole) const;
    bool insertChildren(int position, int count);
    RecordTreeItem *parent();
    bool removeChildren(int position, int count);
    int childNumber() const;
    bool setData(Qt::ItemDataRole, const QVariant &value);
    int getProperties(QStringList& headerlist, QStringList& valuelist) const;

protected:
    static const QString obtainingStrings[4];
    static const QString recordTypeStrings[3];
//properties
    RecordType recordType;
    Obtaining obtaining;

    QString name;
    QString description;
    QString sourceName;
    QString sourceFile;
    QString sourceFilePath;
    QString sourceFileType;

    QString compNameCreate;
    QString userNameCreate;
    QDate dateCreate;
    QTime timeCreate;

    QString compNameModify;
    QString userNameModify;
    QDate dateModify;
    QTime timeModify;

//data
    qint64 dataOffset;
    QString dataFilePath;
    QStringList tempFilesPathList;
//ptr to Group
    RecordGroup* pRecordGroup;
};

class RecordFun1: public Record
{
public:
    RecordFun1();
    RecordFun1(RecordGroup* pGroup, bool u=false, bool d=false);
    ~RecordFun1();
    // Virtual implementation
    int getProperties(QStringList& headerList, QStringList& valueList) const;
    bool readMyData(QList<QVector<double> > &data) /*const*/;
    // Getters
    int getLength() const {return length;}
    QString getXUnits() const {return xUnits;}
    QString getYUnits() const {return yUnits;}
    bool getIsFixetStep() const {return isFixedStep;}
    double getStepLength () const {return isFixedStep?stepLength:0;}
    double getMax() const {return max;}
    double getMin() const {return min;}
    // Setters
    void setLength(int length){this->length=length;}
    void setUnits(const QString& xU, const QString& yU) {xUnits=xU, yUnits=yU;}
    void setIsFixedStep(bool b){isFixedStep=b;}
    void setStepLength(double steplength){stepLength=steplength;}
    void setMax(double m) {max=m;}
    void setMin(double m) {min=m;}
    // Other
    Record& operator=(const Record& otherRecord);
protected:
    int length;
    QString xUnits;
    QString yUnits;
    bool isFixedStep;
    double stepLength;
    double max;
    double min;
};


/*
  RecordGroup is just a logical container for Records of any type.
  Important feature of RecordGroup is it origin. If RecordGroup was
  obtained by importing (the assosiated .probe file was created with
  this RecrodGroup, and no modifications of any kind were made in this
  group) than it has oImport origin. RecordGroup still has oImport origin
  if it was copied or inserted to another .probe file without any internal
  modifications. If RecordGroup was obtained by any kind of manipulations
  within Probe, and it holds only Records which were obtained in Probe,
  then it will have oProbe origin. In all other cases RecordGroup will have
  oCombine origin.
*/

class RecordGroup: public RecordTreeItem
{
public:
    enum Origin {
        oImport,//whole group was imported from source file
        oProbe,//all record in group was obtained in probe
        oCombine//if originally oImported group, which later was modified
    };
    RecordGroup();
    RecordGroup(ProbeFile* pProbeFile, bool u=false, bool d=false);
    ~RecordGroup();
    RecordGroup& operator=(const RecordGroup& otherGroup);
//virtual reimplemented
    RecordTreeItem *child(int number);
    int childCount() const;
    QVariant data(Qt::ItemDataRole role) const;
    bool insertChildren(int position, int count);
    RecordTreeItem *parent();
    bool removeChildren(int position, int count);
    int childNumber() const;
    bool setData(Qt::ItemDataRole, const QVariant &value);
    int getProperties(QStringList& headerList, QStringList& valueList) const;

//const getters
    const Origin getOrigin() const           {return origin;}
    const QString& getName() const           {return name;}

    const QString& getSourceFileName() const {return sourceFileName;}
    const QString& getSourceFilePath() const {return sourceFilePath;}
    const QString& getSourceFileType() const {return sourceFileType;}

    const QString& getCompNameCreate() const {return compNameCreate;}
    const QString& getUserNameCreate() const {return userNameCreate;}
    const QDate getDateCreate() const        {return dateCreate;}
    const QTime getTimeCreate() const        {return timeCreate;}

    const QString& getCompNameModify() const {return compNameCreate;}
    const QString& getUserNameModify() const {return userNameCreate;}
    const QDate getDateModify() const        {return dateCreate;}
    const QTime getTimeModify() const        {return timeCreate;}

    const  QList<Record*>& getRecordList() const
                                             {return recordList;}
    const  ProbeFile* getProbeFileObj() const
                                             {return pProbeFileObj;}
//non-const getters
    QList<Record*>& getRecordList()          {return recordList;}
    ProbeFile* getProbeFileObj()             {return pProbeFileObj;}

//setters
    void setOrigin(Origin origin)            {this->origin=origin;}
    void setName(const QString& name)        {this->name=name;}

    void setSourceFileName(const QString& s) {sourceFileName=s;}
    void setSourceFilePath(const QString& s) {sourceFilePath=s;}
    void setSourceFileType(const QString& s) {sourceFileType=s;}

    void setCompNameCreate(const QString& s) {compNameCreate=s;}
    void setUserNameCreate(const QString& s) {userNameCreate=s;}
    void setDateCreate(QDate d)              {dateCreate=d;}
    void setTimeCreate(QTime t)              {timeCreate=t;}

    void setCompNameModify(const QString& s) {compNameModify=s;}
    void setUserNameModify(const QString& s) {userNameModify=s;}
    void setDateModify(QDate d)              {dateModify=d;}
    void setTimeModify(QTime t)              {timeModify=t;}

    void setProbeFileObj(ProbeFile* p)       {pProbeFileObj=p;}

//other
    int myNumber() const;
    void recordsNamesList(QStringList& namesList) const;
private:
    static const QString  originStrings[3];

    Origin origin;

    QString name;

    //if RecordGroup has oImport origin, than thous fields matter, otherwise empty strings
    QString sourceFileName;
    QString sourceFilePath;
    QString sourceFileType;

    QString compNameCreate;
    QString userNameCreate;
    QDate dateCreate;
    QTime timeCreate;

    QString compNameModify;
    QString userNameModify;
    QDate dateModify;
    QTime timeModify;

    bool bHasUnsavedRecords;
    QList<Record*> recordList;
    ProbeFile* pProbeFileObj;
};

class ProbeFile: public RecordTreeItem
{
public:
    ProbeFile();
    ProbeFile(RootItem* pRoot, bool u=false, bool d=false);
    ProbeFile(const QString &filePath, RootItem* pRoot, bool u=false, bool d=false);
    ~ProbeFile();

    RecordTreeItem *child(int number);
    int childCount() const;
    QVariant data(Qt::ItemDataRole role) const;
    bool insertChildren(int position, int count);
    RecordTreeItem *parent();
    bool removeChildren(int position, int count);
    int childNumber() const;
    bool setData(Qt::ItemDataRole, const QVariant &value);
    int getProperties(QStringList& headerList, QStringList& valueList) const;
//setters
    void setName(const QString& name){this->name=name;}
    void setProbeFilePath(const QString& filePath){probeFilePath=filePath;}
//getters
    const QString& getName(){return name;}

    void getGroupsNamesList(QStringList& namesList) const;
    QList<RecordGroup*>& getRecordGroupList(){return recordGroupList;}
    const QString& getProbeFilePath(){return probeFilePath;}
//other
    int myNumber() const;
private:
    bool bHasUnsavedGroups;
    QString name;
    RootItem* pRootItem;
    QString probeFilePath;
    QList<RecordGroup*> recordGroupList;
};

class RootItem: public RecordTreeItem
{
public:
    RootItem();
    ~RootItem();
//virtual impl
    RecordTreeItem *child(int number);
    int childCount() const;
    QVariant data(Qt::ItemDataRole role) const;
    bool insertChildren(int position, int count);
    RecordTreeItem *parent();
    bool removeChildren(int position, int count);
    int childNumber() const;
    bool setData(Qt::ItemDataRole, const QVariant &value);
    int getProperties(QStringList& headerlist, QStringList& valuelist) const{}
//non-const getters
    void getFilesNamesList(QStringList& namesList) const;
    QList<ProbeFile*>& getProbeFilesList(){return probeFilesList;}
private:
    QList<ProbeFile*> probeFilesList;
};

#endif // RECORD_H

