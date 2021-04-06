#ifndef FFTDIALOG_H
#define FFTDIALOG_H

#include <QDialog>
#include "exqcustomplot.h"

namespace Ui {
class FFTDialog;
}

class AnalysisWindow;
class QCPGraph;

class FFTDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FFTDialog(QWidget *parent = 0);
    ~FFTDialog();

private:
    Ui::FFTDialog *ui;
    AnalysisWindow* pAnalysWindow;
    QCPDataMap *pOrigMap;

    void connecting();
    void initialize();

    QCPDataMap* loadOriginalData(QCPDataMap *pDataMapIn, double keyL, double keyR);
    void updateOriginalData(int index);
    void fftOriginalData(int index);
private slots:
    void updateDataSlot(int index);
    void changeRangeSlot();
};

#endif // FFTDIALOG_H
