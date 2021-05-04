#ifndef IMPORTFILEINTERFACE
#define IMPORTFILEINTERFACE
#include <QtPlugin>


class QFileInfo;
class QStringList;

class ImportFileInterface
{
public:
    virtual ~ImportFileInterface(){}
    virtual QStringList extentions()=0;
    virtual bool importFile(const QString& fileName, const QString& destinationDir,
                            QFileInfo& probeFileInfo)=0;

};
QT_BEGIN_NAMESPACE

#define ImportFileInterface_iid "org.AntonKushnir.Probe.ImportFileInterface"
Q_DECLARE_INTERFACE(ImportFileInterface, ImportFileInterface_iid)

QT_END_NAMESPACE
#endif // IMPORTFILEINTERFACE

