#ifndef ANALYSISWINDOW_H
#define ANALYSISWINDOW_H

#include <QMainWindow>

#include "global.h"
#include "graphitemmodel.h"

class Record;
class RecordGroup;
class RecordsGroupFile;
class DigitalFiltersDialog;

namespace Ui {
class AnalysisWindow;
}

//AnalisisWindow
class QSignalMapper;
class DigitalFiltersDialog;
class FFTDialog;
class AnalysisWindow : public QMainWindow
{
    Q_OBJECT
    struct ScalePair
    {
        ScalePair(double xl,double xr):xL(xl),xR(xr){}
        double xL;
        double xR;
    };
    struct ScaleSquare
    {
        ScaleSquare(double xl, double xr, double yb, double yt):xL(xl),xR(xr),yB(yb),yT(yt){}
        double xL;
        double xR;
        double yB;
        double yT;
    };

public:
    enum InteractionMode{
        imSelection,
        imDrag,
        imTracer,
        imZoomLine,
        imZoomSquare,
        imAnalysBand,
        imAnalysFrame
    };

    enum ZoomMode {
        zmNoZoom,
        zmZoomLine,
        zmZoomSquare
    };

    enum RectRegion{
        rrOutside,
        rrInside,
        rrLeft,
        rrRight,
        rrTop,
        rrBottom,
        rrLeftTop,
        rrLeftBottom,
        rrRightTop,
        rrRightBottm
    };

    explicit AnalysisWindow(QWidget *parent = 0);
    ~AnalysisWindow();
    // Pointer to Record object, which know hot to load its data from file
    void loadRecord(Record *pRecord, int insertIndex);
    // Getters for outer objects
    int getGraphNumber() const {graphList.count();}
    GraphItemModel* getGraphItemModel() const {return pGraphItemModel;}
    QCPDataMap* getGraphData(int graphIndex) const;
    RecordFun1* getRecordFun1Ptr(int graphIndex) const;
    QPair<double, double> getAnalysRectPair() const;

private:
    Ui::AnalysisWindow *ui;
    QList<GraphItem> graphList;
    int activeGraphIndex;
    GraphItemModel* pGraphItemModel;
    QCustomPlot* pCustomPlot;
    //Digital Filters Dialog
    DigitalFiltersDialog* pDigFiltDialog;
    //FFT Dialog
    FFTDialog* pFFTDialog;
    //Modes
    InteractionMode interactionMode;
    ZoomMode zoomMode;
    //Actions
    QAction* pSelectionAction;
    QAction* pDragAction;
    QAction* pTracerAction;
    QAction* pZoomLineAction;
    QAction* pZoomSquareAction;
    QSignalMapper* pSignMapInteraction;

    QAction* pAnalysisWindowAction;

    QAction* pDigitalFiltersAction;
    QAction* pFftAction;
    //Tracer properties
    bool bFirstTracerEnter;
    QCPItemTracer* pTracer;
    QCPItemText* pTracerText;
    QCPItemRect* pTracerRect;
    //Zoom properties
    QList<ScalePair> ZoomPairList;
    QList<ScaleSquare> ZoomSquareList;
    QCPItemRect* pLineZoomRect;
    QCPItemRect* pSquareZoomRect;
    //Analysis Window properties
    QCPItemRect* pAnalysRect;
    RectRegion mouseInRegion;
    bool bAnalysRectExist;

    double beginMoveKey;
    double beginMoveValue;
    double beginMoveTopLeftKey;
    double beginMoveTopLeftValue;
    double beginMoveBotRightKey;
    double beginMoveBotRightValue;
    //Setup methodes
    void AddActions();
    void Connecting();
    void SetupModes();
    void SetupCustomPlots();
    void SetupModelView();
    //Tracer methodes
    void CreateTracer(QCustomPlot* pCustomPlot, QCPItemTracer* &pItemTracer,
                      QCPItemRect* &pItemRect, QCPItemText *&pItemText);
    void ManageTracer(QCustomPlot* pCustomPlot, QCPItemTracer* pItemTracer,
                      QCPItemRect* pItemRect, QCPItemText* pItemText, double key);
    //Zoom methodes
    void CreateZoomRect(QCPItemRect* &itemRect, int x, int y, const QRect& rect);
    void SetRangeZoomLine(QCPItemRect* &itemRect);
    void SetRangeZoomSquare(QCustomPlot* customPlot, QCPItemRect* &itemRect);
    //Analysis Window methodes
    void analysRectChange(QMouseEvent* event);
    void deleteAnalysRect();
    void setMouseInRegion(RectRegion region);
    void normalizeAnalysRect(QMouseEvent* event);//grab always bottomRight
    //Exit modes methodes
    void ExitInteractionMode(InteractionMode mode);
    void ExitZoomMode(ZoomMode mode);
    //Other
    void createRect(QCPItemRect* &itemRect, int x, int y, const QRect& axisRect,
                    QColor color);
public slots:
    void slotReplot();
    void slotRescaleReplot();

private slots:
    //Modes slots
    void SetInteractionMode(int interactionmode);
    void SetZoomMode(int zoommode);
    //Tracer slots
    void SetTracerPosition(QMouseEvent *event);
    //Zoom slots
    void MousePressMapper(QMouseEvent* event);

    void BeginLineZoomRectDraw(QMouseEvent *event);
    void LineZoomRectDraw(QMouseEvent *event);
    void EndLineZoomRectDraw(QMouseEvent *event);
    void LineZoomOneStepBack();

    void BeginSquareZoomRectDraw(QMouseEvent* event);
    void SquareZoomRectDraw(QMouseEvent* event);
    void EndSquareZoomRectDraw(QMouseEvent* event);
    void SquareZoomOneStepBack(QCustomPlot *sender);
    //Analys Window slots
    RectRegion getBandRegion(int x, int y);
    RectRegion getFrameRegion(QMouseEvent* event);

    void beginAnalysRectMove(QMouseEvent* event);
    void analysRectMove(QMouseEvent* event);
    void endAnalysRectMove(QMouseEvent* event);

    void beginAnalysRectResize(QMouseEvent* event, RectRegion rRegion);
    void analysRectResize(QMouseEvent* event, RectRegion rRegion);
    void endAnalysRectResize(QMouseEvent* event);

    void beginAnalysRectDraw(QMouseEvent *event);
    void analysRectDraw(QMouseEvent *event);
    void endAnalysRectDraw(QMouseEvent* event);
    //Other slots
    void cursorChange(QMouseEvent * event);
    //Digital Filters
    void createDigFiltWindow();
    //FFT
    void createFFTWindow();

signals:
    void analysRectChanged();
    void graphsNumberChanged();

};

#endif // ANALYSISWINDOW_H

