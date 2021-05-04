#ifndef DIGITALFILTERSDIALOG_H
#define DIGITALFILTERSDIALOG_H

#include <QDialog>
#include <QList>
#include <QVector>
#include <QDebug>
#include "dspFilters/Dsp.h"
#include "exqcustomplot.h"

class AnalysisWindow;

namespace Ui {
class DigitalFiltersDialog;
}

class DigitalFiltersDialog : public QDialog
{
    Q_OBJECT

    enum ViewMode{
        vmAll,
        vmOrigRes,
        vmDiffFilt
    };

    enum FilterType{
        ftBessel,
        ftButterworth,
        ftChebyshev1,
        ftChebyshev2,
        ftElliptical
    };

    enum FilterMode{
        fmLowPass,
        fmHighPass,
        fmBandPass,
        fmBandStop
    };

struct FilterElement
{
    FilterElement(FilterType fT,FilterMode fM, Dsp::Filter* pF):
        filterType(fT),
        filterMode(fM),
        pFilter(pF) {}
    ~FilterElement(){delete pFilter; qDebug()<<Q_FUNC_INFO;}
    FilterElement& operator=(FilterElement other); //should be = delete! (c++ 11 syntax)
    FilterType const filterType;
    FilterMode const filterMode;
    Dsp::Filter * const pFilter;
};

public:
    explicit DigitalFiltersDialog(QWidget *parent = 0);
    ~DigitalFiltersDialog();

private:
    Ui::DigitalFiltersDialog *ui;
    AnalysisWindow* pAnalysWindow;
    ViewMode viewMode;
    FilterMode filterMode;

    //QList<FilterElement> filterList;
    FilterElement* pCurFilter;
    double sampleRate;

    void loadSettings();
    void setDefaultSettings();
    void initialize();
    void connecting();
    QCPGraph* pOrigGraph;
    QCPGraph* pFiltGraph;
    // Loading original data
    QCPDataMap* loadOriginalData(QCPDataMap *pDataMapIn, double keyL, double keyR);
    void updateOriginalData(int index);
    // Process original data
    void filterOriginalData(const FilterElement& filterElement);
    // Manage filters
    void paramsToGui(const FilterElement& filterElement);
    void guiToParams(const FilterElement& filterElement);
    void addBesselFilter(FilterMode filterMode, const int order);
    void addButterworthFilter(FilterMode filterMode, unsigned order);
    void addChebyshev1Filter(FilterMode filterMode, unsigned order);
    void addChebyshev2Filter(FilterMode filterMode, unsigned order);
    void addEllipticalFilter(FilterMode filterMode, unsigned order);
    void setupFilter(const FilterElement& filterElement);
    void takeFilter(int n);
    void takeLastFilter();

public slots:

private slots:
    void setViewModeSlot(ViewMode vm) {viewMode=vm; qDebug()<<vm;}
    void setFilterOptTypeSlot(int n);
    void setFilterOptModeSlot(int n);
    void changeRangeSlot();
    // Update data
    void updateDataSlot(int index);
    // Change filters
    void changeFilterSlot(int mode=-1);
    void changeParamsSlot();
    void changeFilterModeSlot(int mode);
};

#endif // DIGITALFILTERSDIALOG_H
