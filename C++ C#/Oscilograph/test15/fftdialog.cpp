#include "fftdialog.h"
#include "ui_fftdialog.h"
#include "analysiswindow.h"
#include "kissfft-master/kiss_fft.h"
#include "record.h"
#include <qmath.h>
FFTDialog::FFTDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FFTDialog),
    pOrigMap(0)
{
    ui->setupUi(this);
    initialize();
    connecting();

    updateDataSlot(ui->comboBoxInputSignal->currentIndex());
}

FFTDialog::~FFTDialog()
{
    delete ui;
}

void FFTDialog::connecting()
{
    connect(ui->comboBoxInputSignal, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateDataSlot(int)));
    connect(pAnalysWindow, SIGNAL(analysRectChanged()),
            this, SLOT(changeRangeSlot()));
}

void FFTDialog::initialize()
{
    pAnalysWindow = qobject_cast<AnalysisWindow*>(parent());
    setWindowTitle("FFT");
    QTableView *pTableView = new QTableView;
//    ui->comboBoxInputSignal->setView(pTableView);
    ui->comboBoxInputSignal->setModel(pAnalysWindow->getGraphItemModel());
    pTableView->hideColumn(2);
    pTableView->hideColumn(3);
    pTableView->hideColumn(4);
    pTableView->hideColumn(5);
    pTableView->horizontalHeader()->hide();
    pTableView->verticalHeader()->hide();
    pTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    pTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    pTableView->setShowGrid(false);
}

QCPDataMap* FFTDialog::loadOriginalData(QCPDataMap *pDataMapIn, double keyL, double keyR)
{
    QCPDataMap *pDataMap = new QCPDataMap;
    *(pDataMap)=*(pDataMapIn);
    // Erase data if analys rect exists
    if (!(keyL==0.0 && keyR==0.0)){
        QCPDataMap::iterator it = pDataMap->begin();
        while (it != pDataMap->end() && it.key() < keyL)
            it = pDataMap->erase(it);

        it = pDataMap->upperBound(keyR);
        while (it != pDataMap->end())
          it = pDataMap->erase(it);
    }
    return pDataMap;
}

void FFTDialog::updateOriginalData(int index)
{
    if (pOrigMap!=0){
        pOrigMap->clear();
        delete pOrigMap;
    }

    ui->exQCustomPlotAmp->clearGraphs();
    ui->exQCustomPlotPhase->clearGraphs();

    QPair<double, double> pair = pAnalysWindow->getAnalysRectPair();
    pOrigMap = loadOriginalData(pAnalysWindow->getGraphData(index),
                                     pair.first, pair.second);
}

void FFTDialog::updateDataSlot(int index)
{
    if (index==-1){
        ui->exQCustomPlotAmp->clearGraphs();
        ui->exQCustomPlotPhase->clearGraphs();
    }else{
        updateOriginalData(index);
        fftOriginalData(index);
    }

    ui->exQCustomPlotAmp->rescaleAxes();
    ui->exQCustomPlotPhase->rescaleAxes();
    ui->exQCustomPlotAmp->replot();
    ui->exQCustomPlotPhase->replot();
}

void FFTDialog::changeRangeSlot()
{
    if (ui->comboBoxInputSignal->count()>0)
        updateDataSlot(ui->comboBoxInputSignal->currentIndex());
}

void FFTDialog::fftOriginalData(int index)
{
    double step = pAnalysWindow->getRecordFun1Ptr(index)->getStepLength();
    int size = pOrigMap->size();
    qDebug()<< size;
    double baseFreq = 1/(step*size);
    QVector<double> xVector;
    QVector<QCPData> dataVector = pOrigMap->values().toVector();
    QVector<double> yVector;
    for (int i=0;i<size;++i)
        yVector<<dataVector[i].value;
    for (int i=0;i<(size/2);++i)
        xVector<<i*baseFreq;
    kiss_fft_cpx* cx_in = new kiss_fft_cpx[size];
    kiss_fft_cpx* cx_out = new kiss_fft_cpx[size];
    for (int i =0;i<size;++i){
        cx_in[i].r=yVector[i];
        cx_in[i].i=0.0;
    }
    kiss_fft_cfg cfg = kiss_fft_alloc(size,0,0,0);
    kiss_fft(cfg,cx_in, cx_out);
    QVector<double> amp;
    QVector<double> phase;
    for (int i=0;i<(size/2);++i){
        amp << sqrt(pow(cx_out[i].r,2)+pow(cx_out[i].i,2))/(size/2);
        phase << atan2(cx_out[i].i,cx_out[i].r)*180/M_PI;
    }
    free(cfg);

    ui->exQCustomPlotAmp->addGraph()->setData(xVector,amp);
    ui->exQCustomPlotPhase->addGraph()->setData(xVector,phase);
}
