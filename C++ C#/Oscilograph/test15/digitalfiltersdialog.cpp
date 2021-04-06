#include "digitalfiltersdialog.h"
#include "ui_digitalfiltersdialog.h"
#include "analysiswindow.h"
#include "record.h"

#define ADD_FILTER(FilterName, FilterEnumName, order)\
\
switch (filterMode){\
case fmLowPass:\
    newFilter = new Dsp::FilterDesign\
            <Dsp::FilterName::Design::LowPass <order>, 1>;\
    break;\
case fmHighPass:\
    newFilter = new Dsp::FilterDesign\
            <Dsp::FilterName::Design::HighPass <order>, 1>;\
    break;\
case fmBandPass:\
    newFilter = new Dsp::FilterDesign\
            <Dsp::FilterName::Design::BandPass <order>, 1>;\
    break;\
case fmBandStop:\
    newFilter = new Dsp::FilterDesign\
            <Dsp::FilterName::Design::BandStop <order>, 1>;\
    break;\
}\
pCurFilter = new FilterElement(FilterEnumName,filterMode,newFilter);

DigitalFiltersDialog::DigitalFiltersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DigitalFiltersDialog),
    pOrigGraph(0),
    pFiltGraph(0),
    pCurFilter(0),
    filterMode(fmLowPass)
{
    ui->setupUi(this);
    initialize();

    if (false) //fix!!!
        loadSettings(); //load settings if needed, else default settings
    else
        setDefaultSettings();
    //updateDataSlot(ui->comboBoxInputData->currentIndex());
    connecting();
    updateOriginalData(ui->comboBoxInputData->currentIndex());
    changeFilterSlot();
}

DigitalFiltersDialog::~DigitalFiltersDialog()
{
    delete ui;
}

void DigitalFiltersDialog::setDefaultSettings()
{
    viewMode=vmOrigRes;
    ui->radioButtonLowPass->setChecked(true);
    ui->saveOrigCheckBox->setChecked(false);
    ui->comboBoxFilterType->setCurrentIndex(0);
    setFilterOptModeSlot(0);
    setFilterOptTypeSlot(0);
}

void DigitalFiltersDialog::initialize()
{
    pAnalysWindow = qobject_cast<AnalysisWindow*>(parent());
    setWindowTitle("Digital Filters");
    QStringList filterNamesList;
    filterNamesList <<"Bessel"<<"Butterworth"<<"Chebyshev I"<<"Chebyshev II"
                    <<"Elliptical";
    ui->comboBoxFilterType->addItems(filterNamesList);

    ui->buttonGroupFilterMode->setId(ui->radioButtonLowPass, 0);
    ui->buttonGroupFilterMode->setId(ui->radioButtonHightPass, 1);
    ui->buttonGroupFilterMode->setId(ui->radioButtonBandPass, 2);
    ui->buttonGroupFilterMode->setId(ui->radioButtonBandStop, 3);

    QTableView *pTableView = new QTableView;
//    ui->comboBoxInputData->setView(pTableView);
    ui->comboBoxInputData->setModel(pAnalysWindow->getGraphItemModel());
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

void DigitalFiltersDialog::connecting()
{
    connect(ui->comboBoxFilterType, SIGNAL(activated(int)),
            this, SLOT(setFilterOptTypeSlot(int)));
    connect(ui->buttonGroupFilterMode, SIGNAL(buttonPressed(int)),
            this, SLOT(setFilterOptModeSlot(int)));
    connect(ui->comboBoxInputData, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateDataSlot(int)));
    connect(pAnalysWindow, SIGNAL(analysRectChanged()),
            this, SLOT(changeRangeSlot()));
    // Filter type
    connect(ui->comboBoxFilterType, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeFilterSlot()));
    // Filter mode
    connect(ui->buttonGroupFilterMode, SIGNAL(buttonPressed(int)),
            this, SLOT(changeFilterModeSlot(int)));
    // Params change
    connect(ui->spinBoxFilterOrder, SIGNAL(editingFinished()),
            this, SLOT(changeParamsSlot()));
    connect(ui->doubleSpinBoxCutoffFr, SIGNAL(editingFinished()),
            this, SLOT(changeParamsSlot()));
    connect(ui->doubleSpinBoxCenterFr, SIGNAL(editingFinished()),
            this, SLOT(changeParamsSlot()));
    connect(ui->doubleSpinBoxFrWidth, SIGNAL(editingFinished()),
            this, SLOT(changeParamsSlot()));
    connect(ui->doubleSpinBoxRipple, SIGNAL(editingFinished()),
            this, SLOT(changeParamsSlot()));
    connect(ui->doubleSpinBoxRollOff, SIGNAL(editingFinished()),
            this, SLOT(changeParamsSlot()));
    connect(ui->doubleSpinBoxStopBand, SIGNAL(editingFinished()),
            this, SLOT(changeParamsSlot()));
}

void DigitalFiltersDialog::setFilterOptTypeSlot(int n)
{
    ui->labelRipple->hide(); ui->doubleSpinBoxRipple->hide();
    ui->labelStopBand->hide(); ui->doubleSpinBoxStopBand->hide();
    ui->labelRollOff->hide(); ui->doubleSpinBoxRollOff->hide();
    switch (n){
    case 2:
        ui->labelRipple->show(); ui->doubleSpinBoxRipple->show();
        break;
    case 3:
        ui->labelStopBand->show(); ui->doubleSpinBoxStopBand->show();
        break;
    case 4:
        ui->labelRipple->show(); ui->doubleSpinBoxRipple->show();
        ui->labelRollOff->show(); ui->doubleSpinBoxRollOff->show();
        break;
    }
}

void DigitalFiltersDialog::setFilterOptModeSlot(int n)
{
    if (n==0||n==1){
        ui->labelCenterFr->hide(); ui->doubleSpinBoxCenterFr->hide();
        ui->labelFrWidth->hide(); ui->doubleSpinBoxFrWidth->hide();
        ui->labelCutOffFr->show(); ui->doubleSpinBoxCutoffFr->show();
    } else if (n==2 || n==3){
        ui->labelCenterFr->show(); ui->doubleSpinBoxCenterFr->show();
        ui->labelFrWidth->show(); ui->doubleSpinBoxFrWidth->show();
        ui->labelCutOffFr->hide(); ui->doubleSpinBoxCutoffFr->hide();
    }
}

QCPDataMap* DigitalFiltersDialog::loadOriginalData(QCPDataMap *pDataMapIn,
                                                   double keyL, double keyR)
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

void DigitalFiltersDialog::updateOriginalData(int index)
{
    if (pOrigGraph!=0)
        ui->exQCustomPlot->removeGraph(pOrigGraph);
    pOrigGraph=0;
    pOrigGraph = ui->exQCustomPlot->addGraph();
    pOrigGraph->setPen(QPen(Qt::blue));
    QPair<double, double> pair = pAnalysWindow->getAnalysRectPair();
    pOrigGraph->setData(loadOriginalData(pAnalysWindow->getGraphData(index),
                                     pair.first, pair.second));

    double stepLength = pAnalysWindow->getRecordFun1Ptr(index)->getStepLength();
    sampleRate = 1/stepLength;
    ui->labelSamplRateValue->setText(QString::number(sampleRate));

}

void DigitalFiltersDialog::changeRangeSlot()
{
    updateDataSlot(ui->comboBoxInputData->currentIndex());
}

void DigitalFiltersDialog::filterOriginalData(const FilterElement &filterElement)
{
    if (pOrigGraph==0) return;

    QVector<double> keys;
    QVector<double> values;

    keys=pOrigGraph->data()->keys().toVector();
    QVector<QCPData> qcpDataValues = pOrigGraph->data()->values().toVector();
    for (int i=0;i<qcpDataValues.size();++i)
        values<<qcpDataValues[i].value;

    // Filter code
    float* filterData[1];
    double offset=-values[0];//offset to zero!
    filterData[0] = new float[values.size()];
    for (int i=0;i<values.size();++i)
        filterData[0][i]=static_cast<float>(values[i]+offset);
    filterElement.pFilter->process(values.size(),filterData);
    if (filterMode==fmHighPass) offset =0.0;
        for (int i=0;i<values.size();++i)
            values[i]=static_cast<double>(filterData[0][i])-offset;
    delete[] filterData[0];

    if (pFiltGraph!=0)
        ui->exQCustomPlot->removeGraph(pFiltGraph);
    pFiltGraph=ui->exQCustomPlot->addGraph();
    QPen pen(Qt::red);
    pen.setWidth(2);
    pFiltGraph->setPen(pen);
    pFiltGraph->setData(keys,values);
}

void DigitalFiltersDialog::updateDataSlot(int index)
{
    if (index==-1){
        ui->exQCustomPlot->clearGraphs();
        pOrigGraph=0;
        pFiltGraph=0;
    }else{

        updateOriginalData(index);
        filterOriginalData(*(pCurFilter));
    }
    if (filterMode==0)
        pOrigGraph->rescaleAxes();
    else
        ui->exQCustomPlot->rescaleAxes();
    ui->exQCustomPlot->replot();
}

void DigitalFiltersDialog::changeFilterSlot(int mode)
{
    FilterMode filterMode;
    if (pCurFilter!=0)
        delete pCurFilter;
    if (mode==-1)
        filterMode= static_cast<FilterMode>(ui->buttonGroupFilterMode->checkedId());
    else
        filterMode = static_cast<FilterMode>(mode);
    const unsigned order = ui->spinBoxFilterOrder->value();
    switch (ui->comboBoxFilterType->currentIndex()){
    case 0:
        addBesselFilter(filterMode, order);
        break;
    case 1:
        addButterworthFilter(filterMode, order);
        break;
    case 2:
        addChebyshev1Filter(filterMode, order);
        break;
    case 3:
        addChebyshev2Filter(filterMode, order);
        break;
    case 4:
        addEllipticalFilter(filterMode, order);
        break;
    }

    guiToParams(*pCurFilter);

    filterOriginalData(*pCurFilter);

    if (filterMode==0)
        pOrigGraph->rescaleAxes();
    else
        ui->exQCustomPlot->rescaleAxes();
    ui->exQCustomPlot->replot();
}

void DigitalFiltersDialog::changeParamsSlot()
{
    qDebug()<<Q_FUNC_INFO;
    changeFilterSlot();
}

void DigitalFiltersDialog::changeFilterModeSlot(int mode)
{
    if (mode==ui->buttonGroupFilterMode->checkedId())
        return;
    filterMode = static_cast<FilterMode>(mode);
    changeFilterSlot(mode);
}

void DigitalFiltersDialog::paramsToGui(const FilterElement& filterElement)
{
    Dsp::Params params = filterElement.pFilter->getParams();
    FilterMode filterMode = filterElement.filterMode; //Filter Mode

    ui->spinBoxFilterOrder->setValue(params[1]); //Filter Order

    switch (filterElement.filterType){
    case ftBessel:
        if (filterMode==fmLowPass || filterMode==fmHighPass)
            ui->doubleSpinBoxCutoffFr->setValue(params[2]);
        else if (filterMode==fmBandPass || filterMode==fmBandStop){
            ui->doubleSpinBoxCenterFr->setValue(params[2]);
            ui->doubleSpinBoxFrWidth->setValue(params[3]);
        }
        break;
    case ftButterworth:
        if (filterMode==fmLowPass || filterMode==fmHighPass)
            ui->doubleSpinBoxCutoffFr->setValue(params[2]);
        else if (filterMode==fmBandPass || filterMode==fmBandStop){
            ui->doubleSpinBoxCenterFr->setValue(params[2]);
            ui->doubleSpinBoxFrWidth->setValue(params[3]);
        }
        break;
    case ftChebyshev1:
        if (filterMode==fmLowPass || filterMode==fmHighPass){
            ui->doubleSpinBoxCutoffFr->setValue(params[2]);
            ui->doubleSpinBoxRipple->setValue(params[3]);
        }
        else if (filterMode==fmBandPass || filterMode==fmBandStop){
            ui->doubleSpinBoxCenterFr->setValue(params[2]);
            ui->doubleSpinBoxFrWidth->setValue(params[3]);
            ui->doubleSpinBoxRipple->setValue(params[4]);
        }
        break;
    case ftChebyshev2:
        if (filterMode==fmLowPass || filterMode==fmHighPass){
            ui->doubleSpinBoxCutoffFr->setValue(params[2]);
            ui->doubleSpinBoxStopBand->setValue(params[3]);
        }
        else if (filterMode==fmBandPass || filterMode==fmBandStop){
            ui->doubleSpinBoxCenterFr->setValue(params[2]);
            ui->doubleSpinBoxFrWidth->setValue(params[3]);
            ui->doubleSpinBoxStopBand->setValue(params[4]);
        }
        break;
    case ftElliptical:
        if (filterMode==fmLowPass || filterMode==fmHighPass){
            ui->doubleSpinBoxCenterFr->setValue(params[2]);
            ui->doubleSpinBoxRipple->setValue(params[3]);
            ui->doubleSpinBoxRollOff->setValue(params[4]);
        }
        else if (filterMode==fmBandPass || filterMode==fmBandStop){
            ui->doubleSpinBoxCenterFr->setValue(params[2]);
            ui->doubleSpinBoxFrWidth->setValue(params[3]);
            ui->doubleSpinBoxRipple->setValue(params[4]);
            ui->doubleSpinBoxRollOff->setValue(params[5]);
        }
        break;
    }
}

void DigitalFiltersDialog::guiToParams(const FilterElement& filterElement)
{
    Dsp::Params params;
    FilterMode filterMode = filterElement.filterMode; //Filter Mode

    params[1] = ui->spinBoxFilterOrder->value(); //Filter Order
    params[0] = sampleRate; //Sample Rate

    switch (filterElement.filterType){
    case ftBessel:
        if (filterMode==fmLowPass || filterMode==fmHighPass)
            params[2] = ui->doubleSpinBoxCutoffFr->value();
        else if (filterMode==fmBandPass || filterMode==fmBandStop){
            params[2] = ui->doubleSpinBoxCenterFr->value();
            params[3] = ui->doubleSpinBoxFrWidth->value();
        }
        break;
    case ftButterworth:
        if (filterMode==fmLowPass || filterMode==fmHighPass)
            params[2] = ui->doubleSpinBoxCutoffFr->value();
        else if (filterMode==fmBandPass || filterMode==fmBandStop){
            params[2] = ui->doubleSpinBoxCenterFr->value();
            params[3] = ui->doubleSpinBoxFrWidth->value();
        }
        break;
    case ftChebyshev1:
        if (filterMode==fmLowPass || filterMode==fmHighPass){
            params[2] = ui->doubleSpinBoxCutoffFr->value();
            params[3] = ui->doubleSpinBoxRipple->value();
        }
        else if (filterMode==fmBandPass || filterMode==fmBandStop){
            params[2] = ui->doubleSpinBoxCenterFr->value();
            params[3] = ui->doubleSpinBoxFrWidth->value();
            params[4] = ui->doubleSpinBoxRipple->value();
        }
        break;
    case ftChebyshev2:
        if (filterMode==fmLowPass || filterMode==fmHighPass){
            params[2] = ui->doubleSpinBoxCutoffFr->value();
            params[3] = ui->doubleSpinBoxStopBand->value();
        }
        else if (filterMode==fmBandPass || filterMode==fmBandStop){
            params[2] = ui->doubleSpinBoxCenterFr->value();
            params[3] = ui->doubleSpinBoxFrWidth->value();
            params[4] = ui->doubleSpinBoxStopBand->value();
        }
        break;
    case ftElliptical:
        if (filterMode==fmLowPass || filterMode==fmHighPass){
            params[2] = ui->doubleSpinBoxCenterFr->value();
            params[3] = ui->doubleSpinBoxRipple->value();
            params[4] = ui->doubleSpinBoxRollOff->value();
        }
        else if (filterMode==fmBandPass || filterMode==fmBandStop){
            params[2] = ui->doubleSpinBoxCenterFr->value();
            params[3] = ui->doubleSpinBoxFrWidth->value();
            params[4] = ui->doubleSpinBoxRipple->value();
            params[5] = ui->doubleSpinBoxRollOff->value();
        }
        break;
    }

    filterElement.pFilter->setParams(params);
}

void DigitalFiltersDialog::addBesselFilter(FilterMode filterMode, const int order)
{
    Dsp::Filter* newFilter;
    switch (order){
    case 1: ADD_FILTER(Bessel, ftBessel, 1) break;
    case 2: ADD_FILTER(Bessel, ftBessel, 2) break;
    case 3: ADD_FILTER(Bessel, ftBessel, 3) break;
    case 4: ADD_FILTER(Bessel, ftBessel, 4) break;
    case 5: ADD_FILTER(Bessel, ftBessel, 5) break;
    case 6: ADD_FILTER(Bessel, ftBessel, 6) break;
    case 7: ADD_FILTER(Bessel, ftBessel, 7) break;
    case 8: ADD_FILTER(Bessel, ftBessel, 8) break;
    case 9: ADD_FILTER(Bessel, ftBessel, 9) break;
    case 10: ADD_FILTER(Bessel, ftBessel, 10) break;
    }
}

void DigitalFiltersDialog::addButterworthFilter(FilterMode filterMode, unsigned order)
{
    Dsp::Filter* newFilter;
    switch (order){
    case 1: ADD_FILTER(Butterworth, ftButterworth, 1) break;
    case 2: ADD_FILTER(Butterworth, ftButterworth, 2) break;
    case 3: ADD_FILTER(Butterworth, ftButterworth, 3) break;
    case 4: ADD_FILTER(Butterworth, ftButterworth, 4) break;
    case 5: ADD_FILTER(Butterworth, ftButterworth, 5) break;
    case 6: ADD_FILTER(Butterworth, ftButterworth, 6) break;
    case 7: ADD_FILTER(Butterworth, ftButterworth, 7) break;
    case 8: ADD_FILTER(Butterworth, ftButterworth, 8) break;
    case 9: ADD_FILTER(Butterworth, ftButterworth, 9) break;
    case 10: ADD_FILTER(Butterworth, ftButterworth, 10) break;
    }
}

void DigitalFiltersDialog::addChebyshev1Filter(FilterMode filterMode, unsigned order)
{
    Dsp::Filter* newFilter;
    switch (order){
    case 1: ADD_FILTER(ChebyshevI, ftChebyshev1, 1) break;
    case 2: ADD_FILTER(ChebyshevI, ftChebyshev1, 2) break;
    case 3: ADD_FILTER(ChebyshevI, ftChebyshev1, 3) break;
    case 4: ADD_FILTER(ChebyshevI, ftChebyshev1, 4) break;
    case 5: ADD_FILTER(ChebyshevI, ftChebyshev1, 5) break;
    case 6: ADD_FILTER(ChebyshevI, ftChebyshev1, 6) break;
    case 7: ADD_FILTER(ChebyshevI, ftChebyshev1, 7) break;
    case 8: ADD_FILTER(ChebyshevI, ftChebyshev1, 8) break;
    case 9: ADD_FILTER(ChebyshevI, ftChebyshev1, 9) break;
    case 10: ADD_FILTER(ChebyshevI, ftChebyshev1, 10) break;
    }
}

void DigitalFiltersDialog::addChebyshev2Filter(FilterMode filterMode, unsigned order)
{
    Dsp::Filter* newFilter;
    switch (order){
    case 1: ADD_FILTER(ChebyshevII, ftChebyshev2, 1) break;
    case 2: ADD_FILTER(ChebyshevII, ftChebyshev2, 2) break;
    case 3: ADD_FILTER(ChebyshevII, ftChebyshev2, 3) break;
    case 4: ADD_FILTER(ChebyshevII, ftChebyshev2, 4) break;
    case 5: ADD_FILTER(ChebyshevII, ftChebyshev2, 5) break;
    case 6: ADD_FILTER(ChebyshevII, ftChebyshev2, 6) break;
    case 7: ADD_FILTER(ChebyshevII, ftChebyshev2, 7) break;
    case 8: ADD_FILTER(ChebyshevII, ftChebyshev2, 8) break;
    case 9: ADD_FILTER(ChebyshevII, ftChebyshev2, 9) break;
    case 10: ADD_FILTER(ChebyshevII, ftChebyshev2, 10) break;
    }
}

void DigitalFiltersDialog::addEllipticalFilter(FilterMode filterMode, unsigned order)
{
    Dsp::Filter* newFilter;
    switch (order){
    case 1: ADD_FILTER(Elliptic, ftElliptical, 1) break;
    case 2: ADD_FILTER(Elliptic, ftElliptical, 2) break;
    case 3: ADD_FILTER(Elliptic, ftElliptical, 3) break;
    case 4: ADD_FILTER(Elliptic, ftElliptical, 4) break;
    case 5: ADD_FILTER(Elliptic, ftElliptical, 5) break;
    case 6: ADD_FILTER(Elliptic, ftElliptical, 6) break;
    case 7: ADD_FILTER(Elliptic, ftElliptical, 7) break;
    case 8: ADD_FILTER(Elliptic, ftElliptical, 8) break;
    case 9: ADD_FILTER(Elliptic, ftElliptical, 9) break;
    case 10: ADD_FILTER(Elliptic, ftElliptical, 10) break;
    }
}
