#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QAbstractItemModel>
#include "analysiswindow.h"
#include "record.h"

class DataManager;
class RecordTreeModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

// Constants

static const uint EXPORT_MANAGER_W=250;
static const uint RECORD_MANAGER_W=250;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QDir* pImportDir;
    QFileSystemModel* pFileSystemModel;
    RecordTreeModel* pRecordTreeModel;
    DataManager* pDataManager;

    //actions
    QAction* pAddNewProbeAct;
    QAction* pCutProbeAct;
    QAction* pCopyProbeAct;
    QAction* pPasteProbeAct;
    QAction* pDeleteProbeAct;

    QAction* pAddNewGroupAct;
    QAction* pCutGroupAct;
    QAction* pCopyGroupAct;
    QAction* pPasteGroupAct;
    QAction* pDeleteGroupAct;

    QAction* pCutRecordsAct;
    QAction* pCopyRecordsAct;
    QAction* pPasteRecordsAct;
    QAction* pDeleteRecordAct;

    //context menus
    QMenu* pTreeViewRecordsCM;
    QMenu* pProbeFileCM;
    QMenu* pRecordGroupCM;
    QMenu* pRecordCM;

    void initDataManager();
    void initContexMenus();
    void setImportManager();
    void setPropertiesTable();
    void setRecordTreeView();
    void setSizes();
    void setActions();
    void setDirs();
    void setConnections();
    void setPreview();

    //void readProbeFile(RecordGroupsFile& rgFile);
    //void ReadRecord(const RecordGroupsFile& rgFile, int index);

public slots:
    void newViewFile() const;//temp
    void generateRecordFile() const;//temp
    bool importFile(QModelIndex index) const;

    //void OpenViewFile();
    //void SaveViewFile();
private slots:
    void displayProperties(const QModelIndex& index) const;
    void displayPreview(const QModelIndex& index) const;
    bool addToAnalyzeWindow(const QModelIndex& index) const;
    void showRecTreeViewCM(const QModelIndex& index, QPoint point);

};

#endif // MAINWINDOW_H
