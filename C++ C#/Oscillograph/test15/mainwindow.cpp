#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datamanager.h"
#include "recordtreemodel.h"
#include <QPluginLoader>
#include <QStringList>
//MainWindow
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Probe");
    initContexMenus();
    setSizes();
    setActions();
    setDirs();
    initDataManager();
    setImportManager();
    setPropertiesTable();
    setRecordTreeView();
    setPreview();
    setConnections();
    QDir dir("C:/");
    if (!dir.exists("ProbeWorkDir"))
        dir.mkdir("ProbeWorkDir");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPreview()
{
    ui->customPlotPreview->hide();
}

void MainWindow::setRecordTreeView()
{
    ui->treeViewRecords->setHeaderHidden(true);
    ui->treeViewRecords->setStyle(QStyleFactory::create("windowsxp"));
    pRecordTreeModel = new RecordTreeModel(pDataManager,this);
    ui->treeViewRecords->setModel(pRecordTreeModel/*pFileSystemModel*/);
//    ui->treeView->setModel(pRecordTreeModel);
}

void MainWindow::setActions()
{
    ui->actionNew_File->setShortcut(QKeySequence::New);
    connect(ui->actionNew_File,SIGNAL(triggered()),SLOT(newViewFile()));
}

void MainWindow::setDirs()
{
    pImportDir = new QDir("C:/");
}

void MainWindow::setConnections()
{
    QItemSelectionModel* pSelModel=ui->treeViewRecords->selectionModel();
    connect(ui->actionGenerate_Record_File,SIGNAL(triggered()),SLOT(generateRecordFile()));
    connect(pSelModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)),SLOT(displayProperties(QModelIndex)));
    connect(pSelModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)),SLOT(displayPreview(QModelIndex)));
    connect(ui->treeViewRecords, SIGNAL(doubleClicked(QModelIndex)),SLOT(addToAnalyzeWindow(QModelIndex)));
    connect(ui->treeExport, SIGNAL(doubleClicked(QModelIndex)), SLOT(importFile(QModelIndex)));
    connect(ui->treeViewRecords, SIGNAL(showContextMenu(QModelIndex,QPoint)),SLOT(showRecTreeViewCM(QModelIndex,QPoint)));
    connect(pAddNewGroupAct, SIGNAL(triggered()), ui->treeViewRecords, SLOT(newEmptyGroup()));
    connect(pAddNewProbeAct, SIGNAL(triggered()), ui->treeViewRecords, SLOT(newEmptyProbeFile()));
    connect(pDeleteRecordAct, SIGNAL(triggered()), ui->treeViewRecords, SLOT(deleteRecord()));
    connect(pDeleteGroupAct, SIGNAL(triggered()), ui->treeViewRecords, SLOT(deleteGroup()));
    connect(pDeleteProbeAct, SIGNAL(triggered()), ui->treeViewRecords, SLOT(deleteProbeFile()));
    connect(pCutRecordsAct, SIGNAL(triggered()), ui->treeViewRecords, SLOT(cutRecord()));
    connect(pPasteRecordsAct, SIGNAL(triggered()), ui->treeViewRecords, SLOT(pasteRecord()));
    connect(pCopyRecordsAct, SIGNAL(triggered()), ui->treeViewRecords, SLOT(copyRecord()));
    connect(pCopyGroupAct, SIGNAL(triggered()), ui->treeViewRecords, SLOT(copyGroup()));
    connect(pPasteGroupAct, SIGNAL(triggered()), ui->treeViewRecords, SLOT(pasteGroup()));

    connect(pDataManager, SIGNAL(pasteRecordIsEnabled(bool)), pPasteRecordsAct,SLOT(setEnabled(bool)));
    connect(pDataManager, SIGNAL(pasteGroupIsEnabled(bool)), pPasteGroupAct,SLOT(setEnabled(bool)));
}

void MainWindow::setSizes()
{
//    ui->ExportManagerLayout->resize(100,100);
//    ui->ExportManagerTree->resize(300,100);
}

void MainWindow::initDataManager()
{
    pDataManager = new DataManager("C:/ProbeWorkDir", this);
    pDataManager->readWorkDir();
}

void MainWindow::initContexMenus()
{
    pTreeViewRecordsCM = new QMenu(this);
    pProbeFileCM = new QMenu(this);
    pRecordGroupCM = new QMenu(this);
    pRecordCM = new QMenu(this);

    pAddNewProbeAct = new QAction(tr("Add New Probe File"), this);
    pCutProbeAct = new QAction(tr("Cut Probe File"), this);
    pCopyProbeAct = new QAction(tr("Copy Probe File"), this);
    pPasteProbeAct = new QAction(tr("Paste Probe File"), this);
    pPasteProbeAct->setEnabled(false);
    pDeleteProbeAct = new QAction(tr("Delete Probe File"), this);

    pAddNewGroupAct = new QAction(tr("Add New Group"), this);
    pCutGroupAct = new QAction(tr("Cut Group"), this);
    pCopyGroupAct = new QAction(tr("Copy Group"), this);
    pPasteGroupAct = new QAction(tr("Paste Group"), this);
    pPasteGroupAct->setEnabled(false);
    pDeleteGroupAct = new QAction(tr("Delete Group"), this);

    pCutRecordsAct = new QAction(tr("Cut Record"), this);
    pCopyRecordsAct = new QAction(tr("Copy Record"), this);
    pPasteRecordsAct = new QAction(tr("Paste Record"), this);
    pDeleteRecordAct = new QAction(tr("Delete Record"), this);
    pPasteRecordsAct->setEnabled(false);

    pProbeFileCM->insertAction(0, pAddNewGroupAct);
    pProbeFileCM->insertAction(0, pPasteGroupAct);
    pProbeFileCM->insertSeparator(pAddNewProbeAct);
    pProbeFileCM->insertAction(0, pAddNewProbeAct);
    pProbeFileCM->insertAction(0, pCutProbeAct);
    pProbeFileCM->insertAction(0, pCopyProbeAct);
    pProbeFileCM->insertAction(0, pPasteProbeAct);
    pProbeFileCM->insertAction(0, pDeleteProbeAct);

    pRecordGroupCM->insertAction(0, pPasteRecordsAct);
    pRecordGroupCM->insertSeparator(pAddNewGroupAct);
    pRecordGroupCM->insertAction(0, pAddNewGroupAct);
    pRecordGroupCM->insertAction(0, pCutGroupAct);
    pRecordGroupCM->insertAction(0, pCopyGroupAct);
    pRecordGroupCM->insertAction(0, pPasteGroupAct);
    pRecordGroupCM->insertAction(0, pDeleteGroupAct);

    pRecordCM->insertAction(0, pCutRecordsAct);
    pRecordCM->insertAction(0, pCopyRecordsAct);
    pRecordCM->insertAction(0, pPasteRecordsAct);
    pRecordCM->insertAction(0, pDeleteRecordAct);
}

void MainWindow::newViewFile() const
{
    AnalysisWindow* pAnalysisWindow = new AnalysisWindow;
    ui->mdiArea->addSubWindow(pAnalysisWindow);
    pAnalysisWindow->showMaximized();
}

void MainWindow::setImportManager()
{
    ui->treeExport->setStyle(QStyleFactory::create("windowsxp"));
    pFileSystemModel=new QFileSystemModel(this);
    pFileSystemModel->setRootPath(pImportDir->path());
    if (!(pDataManager->getImportExtList()).empty()){
        QStringList strList = pDataManager->getImportExtList();
        for (int i=0;i<strList.count();++i)
            strList[i].prepend("*.");
        pFileSystemModel->setNameFilters(strList);
        qDebug()<<"Plugins loaded: "<<strList;
    }
    else{
        pFileSystemModel->setFilter(QDir::Dirs);
        qDebug()<<"No plugins!";
    }
    ui->treeExport->setModel(pFileSystemModel);
    ui->treeExport->setCurrentIndex(pFileSystemModel->index(pImportDir->path()));
    ui->treeExport->setColumnHidden(3,true);
    ui->treeExport->setColumnHidden(2,true);
    ui->treeExport->setColumnHidden(1,true);
    ui->treeExport->setHeaderHidden(true);
}

void MainWindow::setPropertiesTable()
{
    ui->tableProperties->setStyle(QStyleFactory::create("windowsxp"));
    QTableWidget* table = ui->tableProperties;
    table->resizeColumnsToContents();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->hide();
    table->verticalHeader()->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QFont font = table->verticalHeader()->font();
    font.setPointSize(8);
    font.setBold(true);
    table->verticalHeader()->setFont(font);
    font = table->font();
    font.setPointSize(8);
    table->setFont(font);
//    table->verticalHeader()->setDefaultSectionSize(20);
}

bool MainWindow::importFile(QModelIndex index) const
{
    if (pFileSystemModel->isDir(index)) return false;
    QString filePath = pFileSystemModel->filePath(index);
    return pDataManager->importFile(filePath);
}

void MainWindow::displayProperties(const QModelIndex& index) const
{
    RecordTreeItem* pItem=static_cast<RecordTreeItem*>(index.internalPointer());
    QStringList headerList;
    QStringList valueList;
    int propNum = pItem->getProperties(headerList, valueList);
    QTableWidget* pProperties=ui->tableProperties;
    pProperties->clear();
    pProperties->setColumnCount(1);
    pProperties->setRowCount(propNum);
    pProperties->setVerticalHeaderLabels(headerList);
    QTableWidgetItem* pTableItem;
    for (int i=0;i<propNum;++i){
        pTableItem = new QTableWidgetItem(valueList[i]);
        pProperties->setItem(i,0,pTableItem);
    }
}

void MainWindow::displayPreview(const QModelIndex &index) const
{
    ui->customPlotPreview->clearGraphs();
    RecordTreeItem* pRTI=static_cast<RecordTreeItem*>(index.internalPointer());
    Record* pRecord=dynamic_cast<Record*>(pRTI);
    if (pRecord){
        ui->labelPreview->hide();
        ui->customPlotPreview->show();
        switch (pRecord->getType()){
            case Record::rtRecordFun1:
            QList<QVector<double> > data;
            pRecord->readMyData(data);
            QCPGraph* pGraph=ui->customPlotPreview->addGraph();
            pGraph->setData(data[0],data[1]);
            pGraph->setPen(QPen(QColor(Qt::red)));
            ui->customPlotPreview->rescaleAxes();
            ui->customPlotPreview->replot();
            break;
        }
    }
    RecordGroup* pRecordGroup=dynamic_cast<RecordGroup*>(pRTI);
    if(pRecordGroup){
        ui->customPlotPreview->hide();
        ui->labelPreview->show();
    }
    ProbeFile* pProbeFile=dynamic_cast<ProbeFile*>(pRTI);
    if(pProbeFile){
        ui->customPlotPreview->hide();
        ui->labelPreview->show();
    }
}

bool MainWindow::addToAnalyzeWindow(const QModelIndex& index) const
{
    RecordTreeItem* pRTI=static_cast<RecordTreeItem*>(index.internalPointer());
    Record* pRecord=dynamic_cast<Record*>(pRTI);
    if (pRecord){
        switch(pRecord->getType()){
        case Record::rtRecordFun1:
            if (ui->mdiArea->activeSubWindow()){
                AnalysisWindow* pAnalysisWindow =
                qobject_cast<AnalysisWindow*>(ui->mdiArea->activeSubWindow()->widget());
                if (!pAnalysisWindow) return false;
                int graphNum=pAnalysisWindow->getGraphNumber();
                pAnalysisWindow->loadRecord(pRecord, graphNum);
                return true;
            }
            break;
        }
    }
}

void MainWindow::showRecTreeViewCM(const QModelIndex& index, QPoint point)
{
    RecordTreeItem* pRTI;
    QPoint localPoint = ui->treeViewRecords->mapToGlobal(point);
    if (index!=QModelIndex()){
        pRTI=static_cast<RecordTreeItem*>(index.internalPointer());
        if (dynamic_cast<Record*>(pRTI))
            pRecordCM->popup(localPoint);
        else if (dynamic_cast<RecordGroup*>(pRTI))
            pRecordGroupCM->popup(localPoint);
        else if (dynamic_cast<ProbeFile*>(pRTI))
            pProbeFileCM->popup(localPoint);
    }
    else
        pTreeViewRecordsCM->popup(localPoint);

}

void MainWindow::generateRecordFile() const
{
    pDataManager->generateProbeFile("New Project");
}


