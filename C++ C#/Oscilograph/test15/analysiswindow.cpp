#include "analysiswindow.h"
#include "ui_analysiswindow.h"
#include "record.h"
#include "dspFilters/Dsp.h"
#include "digitalfiltersdialog.h"
#include "fftdialog.h"

//AnalysisWindow
AnalysisWindow::AnalysisWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnalysisWindow),
    pAnalysRect(0),
    bAnalysRectExist(false)
{
    ui->setupUi(this);
    pCustomPlot=ui->exQCustomPlot;
    AddActions();
    SetupModes();
    SetupCustomPlots();
    SetupModelView();
    Connecting();
    //temp
    activeGraphIndex=0;
}

AnalysisWindow::~AnalysisWindow()
{
    delete ui;
}

QCPDataMap* AnalysisWindow::getGraphData(int graphIndex) const
{
    return graphList[graphIndex].getGraph()->data();
}

RecordFun1* AnalysisWindow::getRecordFun1Ptr(int graphIndex) const
{
    return graphList[graphIndex].getRecordFun1Ptr();
}

QPair<double, double> AnalysisWindow::getAnalysRectPair() const
{
    if (!bAnalysRectExist)
        return QPair<double,double>(0.0,0.0);
    else{
        double xL = pAnalysRect->topLeft->coords().x();
        double xR = pAnalysRect->bottomRight->coords().x();
        double buf;
        if (xL>xR){
            buf = xL;
            xL=xR;
            xR=buf;
        }
        return QPair<double, double>(xL,xR);
    }
}

void AnalysisWindow::AddActions()
{
    QIcon testIcon(QApplication::style()->standardIcon(QStyle::SP_CustomBase));
    pSelectionAction = ui->toolBar->addAction(testIcon, tr("Selection"));
    pDragAction = ui->toolBar->addAction(testIcon, tr("Drag"));
    pTracerAction = ui->toolBar->addAction(testIcon, tr("Tracer"));
    pZoomLineAction = ui->toolBar->addAction(testIcon, tr("Band Zoom"));
    pZoomSquareAction = ui->toolBar->addAction(testIcon, tr("Frame Zoom"));
    ui->toolBar->addSeparator();
    pAnalysisWindowAction=ui->toolBar->addAction(testIcon, tr("Analysis Band"));
    ui->toolBar->addSeparator();
    pDigitalFiltersAction=ui->toolBar->addAction(testIcon, tr("Digital Filters"));
    pFftAction=ui->toolBar->addAction(testIcon, tr("FFT"));

}

void AnalysisWindow::Connecting()
{
    pSignMapInteraction =new QSignalMapper(this);
    connect(pSelectionAction,SIGNAL(triggered()),pSignMapInteraction,SLOT(map()));
    connect(pDragAction, SIGNAL(triggered()), pSignMapInteraction, SLOT(map()));
    connect(pTracerAction,SIGNAL(triggered()),pSignMapInteraction,SLOT(map()));
    connect(pZoomLineAction,SIGNAL(triggered()),pSignMapInteraction,SLOT(map()));
    connect(pZoomSquareAction,SIGNAL(triggered()),pSignMapInteraction,SLOT(map()));
    connect(pAnalysisWindowAction,SIGNAL(triggered()),pSignMapInteraction,SLOT(map()));


    pSignMapInteraction->setMapping(pSelectionAction,0);
    pSignMapInteraction->setMapping(pDragAction,1);
    pSignMapInteraction->setMapping(pTracerAction,2);
    pSignMapInteraction->setMapping(pZoomLineAction,3);
    pSignMapInteraction->setMapping(pZoomSquareAction,4);
    pSignMapInteraction->setMapping(pAnalysisWindowAction,5);
    connect(pSignMapInteraction, SIGNAL(mapped(int)),SLOT(SetInteractionMode(int)));

    connect(pDigitalFiltersAction, SIGNAL(triggered()), SLOT(createDigFiltWindow()));
    connect(pFftAction, SIGNAL(triggered(bool)), SLOT(createFFTWindow()));

    connect(pGraphItemModel, SIGNAL(needReplot()),SLOT(slotReplot()));
    connect(pGraphItemModel, SIGNAL(needRescaleReplot()),SLOT(slotRescaleReplot()));

    connect(pCustomPlot,SIGNAL(mouseMove(QMouseEvent*)),SLOT(cursorChange(QMouseEvent*)));
}

void AnalysisWindow::SetupModes()
{
    SetInteractionMode(imSelection);
    SetZoomMode(zmNoZoom);
}

void AnalysisWindow::SetupCustomPlots()
{
    QFont font(pCustomPlot->xAxis->labelFont());
    QString fontfamily(font.family());
    pCustomPlot->xAxis->setLabelFont(QFont(fontfamily, 12));
    pCustomPlot->yAxis->setLabelFont(QFont(fontfamily, 12));
}

void AnalysisWindow::SetupModelView()
{
    pGraphItemModel = new GraphItemModel(&graphList, ui->exQCustomPlot ,this);
    ui->tableView->setModel(pGraphItemModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionsClickable(false);
    ui->tableView->horizontalHeader()->setHighlightSections(false);
    ui->tableView->verticalHeader()->setSectionsClickable(false);
    ui->tableView->verticalHeader()->setHighlightSections(false);
    ui->tableView->setItemDelegateForColumn(0, new NameDelegate());
    ui->tableView->setItemDelegateForColumn(1, new SourceDelegate());
    ui->tableView->setItemDelegateForColumn(2, new ColorDelegate());
    ui->tableView->setItemDelegateForColumn(3, new LineStyleDelegate());
    ui->tableView->setItemDelegateForColumn(4, new LineWidthDelegate());
    ui->tableView->setItemDelegateForColumn(5, new ScatterDelegate());
    QList<QString> ColorList;
    for (int i=0; i<pGraphItemModel->getCOLOR_NUMBER(); ++i)
        ColorList<<pGraphItemModel->getColorMapString(i);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void AnalysisWindow::ExitInteractionMode(InteractionMode mode)
{
    switch (mode){
    case imSelection:
        break;
    case imDrag:
        pCustomPlot->setInteractions(0);
        break;
    case imTracer:
        disconnect(pCustomPlot, SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(SetTracerPosition(QMouseEvent*)));
        pCustomPlot->removeItem(pTracerText);
        pCustomPlot->removeItem(pTracerRect);
        pCustomPlot->removeItem(pTracer);
        pCustomPlot->replot();
        break;
    case imZoomLine:
        disconnect(pCustomPlot, SIGNAL(mousePress(QMouseEvent*)),this,SLOT(MousePressMapper(QMouseEvent*)));
        break;
    case imZoomSquare:
        disconnect(pCustomPlot, SIGNAL(mousePress(QMouseEvent*)),this,SLOT(MousePressMapper(QMouseEvent*)));
        break;
    case imAnalysBand:
        if (bAnalysRectExist)
            deleteAnalysRect();
        disconnect(pCustomPlot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(MousePressMapper(QMouseEvent*)));
        break;
    }
}

void AnalysisWindow::SetInteractionMode(int interactionmode)
{
//    interactionMode=static_cast<InteractionMode>(interactionmode);

    switch (interactionmode){
    case imSelection:
        if (interactionMode==imSelection) return;
        ExitInteractionMode(interactionMode);
        interactionMode=imSelection;
        break;
    case imDrag:
        if (interactionMode==imDrag) return;
        ExitInteractionMode(interactionMode);
        switch (zoomMode){
        case zmNoZoom:
            //do nothing!
            break;
        case zmZoomLine:
            pCustomPlot->setInteraction(QCP::iRangeDrag);
            pCustomPlot->axisRect()->setRangeDrag(Qt::Horizontal);
            break;
        case zmZoomSquare:
            if (!ZoomSquareList.empty()){
                pCustomPlot->setInteraction(QCP::iRangeDrag);
                pCustomPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
            }
            break;
        }
        interactionMode=imDrag;
        break;
    case imTracer:
        if (interactionMode==imTracer) return;
        ExitInteractionMode(interactionMode);
        if (graphList.empty()==true) return;
        bFirstTracerEnter=true;
        connect(pCustomPlot, SIGNAL(mouseMove(QMouseEvent*)),SLOT(SetTracerPosition(QMouseEvent*)));
        interactionMode=imTracer;
        break;
    case imZoomLine:
        if (interactionMode==imZoomLine) return;
        ExitInteractionMode(interactionMode);
        if (zoomMode==zmZoomSquare){
            ExitZoomMode(zoomMode);
            SetZoomMode(zmNoZoom);
            pCustomPlot->replot();
        }
        connect(pCustomPlot, SIGNAL(mousePress(QMouseEvent*)),SLOT(MousePressMapper(QMouseEvent*)));
        interactionMode=imZoomLine;
        break;
    case imZoomSquare:
        if (interactionMode==imZoomSquare) return;
        ExitInteractionMode(interactionMode);
        if (zoomMode==zmZoomLine){
            ExitZoomMode(zoomMode);
            SetZoomMode(zmNoZoom);
            pCustomPlot->replot();
        }
        connect(pCustomPlot, SIGNAL(mousePress(QMouseEvent*)),SLOT(MousePressMapper(QMouseEvent*)));
        interactionMode=imZoomSquare;
        break;
    case imAnalysBand:
        if (interactionMode==imAnalysBand) return;
        ExitInteractionMode(interactionMode);
        mouseInRegion==rrOutside;
        connect(pCustomPlot,SIGNAL(mousePress(QMouseEvent*)),SLOT(MousePressMapper(QMouseEvent*)));
        interactionMode=imAnalysBand;
        break;
    }
}

void AnalysisWindow::ExitZoomMode(ZoomMode mode)
{
    switch (mode){
    case zmNoZoom:
        break;
    case zmZoomLine:
        ZoomPairList.clear();
        break;
    case zmZoomSquare:
        ZoomSquareList.clear();
        break;
    }
}

void AnalysisWindow::SetZoomMode(int zoommode)
{
    switch (zoommode){
    case zmNoZoom:
        pCustomPlot->EXrescaleAxes();
        pCustomPlot->setInteractions(0);
        zoomMode=zmNoZoom;
        break;
    case zmZoomLine:
        zoomMode=zmZoomLine;
        break;
    case zmZoomSquare:
        zoomMode=zmZoomSquare;
        break;
    }
}

void AnalysisWindow::CreateTracer(QCustomPlot* pCustomPlot, QCPItemTracer* &pItemTracer,
                                  QCPItemRect* &pItemRect, QCPItemText* &pItemText)
{
    int tracerRectMarginX=8;
    int tracerRectMarginY=-8;
    int tracerRectWidth=70;//var!
    int tracerRectHeight=40;

    //add Tracer Item
    pItemTracer=new QCPItemTracer(pCustomPlot);
    pItemTracer->setInterpolating(false);
    pItemTracer->setAntialiased(false);
    pItemTracer->setPen(QPen(QColor(Qt::black)));
    pItemTracer->setStyle(QCPItemTracer::tsCrosshair);
    qDebug()<<"active graph: "<<activeGraphIndex;
    pItemTracer->setGraph(graphList[activeGraphIndex].getGraph());
    pCustomPlot->addItem(pItemTracer);
    qDebug()<<"add Tracer Item OK!";
    //add Rect Item
    pItemRect= new QCPItemRect(pCustomPlot);
    QPen pen(Qt::NoPen);
    pItemRect->setPen(pen);
    QColor brushColor(Qt::black);
    brushColor.setAlpha(200);
    pItemRect->setBrush(QBrush(brushColor));
    pItemRect->setAntialiased(false);
    pItemRect->topLeft->setType(QCPItemPosition::ptAbsolute);
    pItemRect->bottomRight->setType(QCPItemPosition::ptAbsolute);
    pItemRect->bottomRight->setParentAnchor(pItemTracer->position, true);
    pItemRect->topLeft->setParentAnchor(pItemTracer->position, true);
    pItemRect->bottomRight->setCoords(tracerRectMarginX, tracerRectMarginY);
    pItemRect->topLeft->setCoords(tracerRectMarginX+tracerRectWidth,
                                       tracerRectMarginY-tracerRectHeight);
    pCustomPlot->addItem(pItemRect);
    //add Text Item
    pItemText=new QCPItemText(pCustomPlot);
    pItemText->setColor(QColor(Qt::white));
    pItemText->position->setType( QCPItemPosition::ptAbsolute);
    pItemText->setTextAlignment(Qt::AlignLeft);
    pItemText->setPositionAlignment(Qt::AlignLeft);
    pItemText->position->setParentAnchor(pItemRect->topLeft);
    pItemText->position->setCoords(5,6);
    QFont font("Times",9);
    //font.setBold(true);
    pItemText->setFont(font);
    pCustomPlot->addItem(pItemText);
    qDebug()<<"Create Tracer OK!";
}

void AnalysisWindow::ManageTracer(QCustomPlot* pCustomPlot, QCPItemTracer* pItemTracer,
                                  QCPItemRect* pItemRect, QCPItemText* pItemText, double key)
{
    QRect plotRect;
    plotRect=pCustomPlot->axisRect()->rect();

    int tracerRectMarginX=8;
    int tracerRectMarginY=-8;
    int tracerRectWidth=70;//var!
    int tracerRectHeight=40;

    int plotRectX=plotRect.x();
    int plotRectY=plotRect.y();
    int plotRectW=plotRect.width();
    int plotRectH=plotRect.height();

    double tracerX;
    double tracerY;
    qDebug()<<"Before EXsetGraphKey OK!";
    pItemTracer->EXsetGraphKey(key);

    tracerX=pItemTracer->position->coords().x();
    tracerY=pItemTracer->position->coords().y();
    pItemText->setText("x: "+QString::number(tracerX,'g',6)+"\n"+
                       "y: "+QString::number(tracerY,'g',6));
    tracerRectWidth=pItemText->right->pixelPoint().x()-pItemText->left->pixelPoint().x()+10;
    tracerX=pCustomPlot->xAxis->coordToPixel(tracerX);
    tracerY=pCustomPlot->yAxis->coordToPixel(tracerY);
    qDebug()<<"Before Area manage OK!";
//following code manage Tracer Rect and Tracer Text position relative to Tracer
//area 1
    if (tracerX<plotRectX+plotRectW-(tracerRectWidth+tracerRectMarginX) &&
        tracerY<=plotRectY+(tracerRectHeight-tracerRectMarginY) &&
        tracerY>plotRectY){
          pItemRect->bottomRight->setParentAnchor(pItemTracer->position, true);
          pItemRect->topLeft->setParentAnchor(pItemTracer->position, true);
          pItemRect->topLeft->setCoords(tracerRectMarginX, -tracerRectMarginY);
          pItemRect->bottomRight->setCoords(tracerRectMarginX+tracerRectWidth, -tracerRectMarginY+tracerRectHeight);
          qDebug()<<"1";
//area 2
    } else if (tracerX>=plotRectX+plotRectW-(tracerRectWidth+tracerRectMarginX) &&
               tracerY>plotRectY+(tracerRectHeight-tracerRectMarginY) &&
               tracerY<plotRectY+plotRectH){
          pItemRect->bottomRight->setParentAnchor(pItemTracer->position, true);
          pItemRect->topLeft->setParentAnchor(pItemTracer->position, true);
          pItemRect->topLeft->setCoords(-tracerRectMarginX-tracerRectWidth, tracerRectMarginY-tracerRectHeight);
          pItemRect->bottomRight->setCoords(-tracerRectMarginX,tracerRectMarginY);
          qDebug()<<"2";
//area 3
    } else if (tracerX>=plotRectX+plotRectW-(tracerRectWidth+tracerRectMarginX) &&
               tracerY<=plotRectY+(tracerRectHeight-tracerRectMarginY) &&
               tracerY>plotRectY){
          pItemRect->bottomRight->setParentAnchor(pItemTracer->position, true);
          pItemRect->topLeft->setParentAnchor(pItemTracer->position, true);
          pItemRect->topLeft->setCoords(-tracerRectMarginX-tracerRectWidth,-tracerRectMarginY);
          pItemRect->bottomRight->setCoords(-tracerRectMarginX, -tracerRectMarginY+tracerRectHeight);
          qDebug()<<"3";
//area 4
    } else if (tracerX<plotRectX+plotRectW-(tracerRectWidth+tracerRectMarginX) &&
               tracerY<=plotRectY){
          pItemRect->bottomRight->setParentAnchor(0);
          pItemRect->topLeft->setParentAnchor(0);
          pItemRect->bottomRight->setParentAnchorX(pItemTracer->position, true);
          pItemRect->topLeft->setParentAnchorX(pItemTracer->position, true);
          pItemRect->topLeft->setCoords(tracerRectMarginX,plotRectY-tracerRectMarginY);
          pItemRect->bottomRight->setCoords(tracerRectMarginX+tracerRectWidth, plotRectY-tracerRectMarginY+tracerRectHeight);
          qDebug()<<"4";
//area 5
    } else if (tracerX<plotRectX+plotRectW-(tracerRectWidth+tracerRectMarginX) &&
               tracerY>=plotRectY+plotRectH){
          pItemRect->bottomRight->setParentAnchor(0);
          pItemRect->topLeft->setParentAnchor(0);
          pItemRect->bottomRight->setParentAnchorX(pItemTracer->position, true);
          pItemRect->topLeft->setParentAnchorX(pItemTracer->position, true);
          pItemRect->topLeft->setCoords(tracerRectMarginX, plotRectY+plotRectH+tracerRectMarginY-tracerRectHeight);
          pItemRect->bottomRight->setCoords(tracerRectMarginX+tracerRectWidth,plotRectY+plotRectH+tracerRectMarginY);
          qDebug()<<"5";
//area 6
    } else if (tracerX>=plotRectX+plotRectW-(tracerRectWidth+tracerRectMarginX) &&
               tracerY<=plotRectY){
          pItemRect->bottomRight->setParentAnchor(0);
          pItemRect->topLeft->setParentAnchor(0);
          pItemRect->bottomRight->setParentAnchorX(pItemTracer->position, true);
          pItemRect->topLeft->setParentAnchorX(pItemTracer->position, true);
          pItemRect->topLeft->setCoords(-tracerRectMarginX-tracerRectWidth,plotRectY-tracerRectMarginY);
          pItemRect->bottomRight->setCoords(-tracerRectMarginX,plotRectY-tracerRectMarginY+tracerRectHeight);
          qDebug()<<"6";
//area 7
    } else if (tracerX>=plotRectX+plotRectW-(tracerRectWidth+tracerRectMarginX) &&
               tracerY>=plotRectY+plotRectH){
          pItemRect->bottomRight->setParentAnchor(0);
          pItemRect->topLeft->setParentAnchor(0);
          pItemRect->bottomRight->setParentAnchorX(pItemTracer->position, true);
          pItemRect->topLeft->setParentAnchorX(pItemTracer->position, true);
          pItemRect->topLeft->setCoords(-tracerRectMarginX-tracerRectWidth,plotRectY+plotRectH+tracerRectMarginY-tracerRectHeight);
          pItemRect->bottomRight->setCoords(-tracerRectMarginX,plotRectY+plotRectH+tracerRectMarginY);
          qDebug()<<"7";
//area 8
    } else {
          pItemRect->bottomRight->setParentAnchor(pItemTracer->position, true);
          pItemRect->topLeft->setParentAnchor(pItemTracer->position, true);
          pItemRect->topLeft->setCoords(tracerRectMarginX, tracerRectMarginY-tracerRectHeight);
          pItemRect->bottomRight->setCoords(tracerRectMarginX+tracerRectWidth, tracerRectMarginY);
          qDebug()<<"8";
    }
    qDebug()<<"Manage tracer OK!";
}

void AnalysisWindow::SetTracerPosition(QMouseEvent* event)
{
    double eventX = static_cast<double>(event->x());
    QRect plotRect;
    plotRect=pCustomPlot->axisRect()->rect();
    if(plotRect.contains(event->pos(),true)){
        if (bFirstTracerEnter==true){
           CreateTracer(pCustomPlot, pTracer, pTracerRect, pTracerText);
           bFirstTracerEnter=false;
        }
        double key;
        key=pCustomPlot->xAxis->pixelToCoord(eventX);
        qDebug()<<"Before ManageTracer OK!";
        ManageTracer(pCustomPlot, pTracer, pTracerRect, pTracerText, key);
        pCustomPlot->replot();
    }
}

void AnalysisWindow::MousePressMapper(QMouseEvent* event)
{
    switch (interactionMode){
    case imZoomLine:
        if (event->button()==Qt::LeftButton)
            BeginLineZoomRectDraw(event);
        else if (event->button()==Qt::RightButton)
            LineZoomOneStepBack();
        break;
    case imZoomSquare:
        if (event->button()==Qt::LeftButton)
            BeginSquareZoomRectDraw(event);
        else if (event->button()==Qt::RightButton)
            SquareZoomOneStepBack(qobject_cast<QCustomPlot*>(sender()));
        break;
    case imAnalysBand:
        if (event->button()==Qt::LeftButton){
            analysRectChange(event);
        }
        break;
    }
}

void AnalysisWindow::CreateZoomRect(QCPItemRect* &itemRect, int x, int y, const QRect &rect)
{
    double ratioX;
    double ratioY;
    QColor color(Qt::blue);
    itemRect = new QCPItemRect(pCustomPlot);
    itemRect->setPen(color);
    color.setAlpha(30);
    itemRect->setBrush(color);
    itemRect->setAntialiased(false);
    pCustomPlot->addItem(itemRect);
    itemRect->topLeft->setType(QCPItemPosition::ptAxisRectRatio);
    itemRect->bottomRight->setType(QCPItemPosition::ptAxisRectRatio);
    itemRect->topLeft->setAxes(pCustomPlot->xAxis,pCustomPlot->yAxis);
    itemRect->bottomRight->setAxes(pCustomPlot->xAxis,pCustomPlot->yAxis);
    ratioX=static_cast<double>(x-rect.x())/static_cast<double>(rect.width());
    ratioY=static_cast<double>(y-rect.y())/static_cast<double>(rect.height());
    if (interactionMode==imZoomLine){
        itemRect->topLeft->setCoords(ratioX,0);
        itemRect->bottomRight->setCoords(ratioX,1);
    }
    else if (interactionMode==imZoomSquare){
        itemRect->topLeft->setCoords(ratioX,ratioY);
        itemRect->bottomRight->setCoords(ratioX,ratioY);
    }
}

void AnalysisWindow::createRect(QCPItemRect* &itemRect, int x, int y, const QRect& axisRect,
                                QColor color)
{
    itemRect = new QCPItemRect(pCustomPlot);

    itemRect->setPen(color); color.setAlpha(30);
    itemRect->setBrush(color); //with alpha
    pCustomPlot->addItem(itemRect);
    itemRect->topLeft->setTypeX(QCPItemPosition::ptPlotCoords);
    itemRect->bottomRight->setTypeX(QCPItemPosition::ptPlotCoords);
    double xCoord=pCustomPlot->xAxis->pixelToCoord(x);
    if (interactionMode==imZoomLine||interactionMode==imAnalysBand){
        itemRect->topLeft->setTypeY(QCPItemPosition::ptAxisRectRatio);
        itemRect->bottomRight->setTypeY(QCPItemPosition::ptAxisRectRatio);
        itemRect->topLeft->setCoords(xCoord,0);
        itemRect->bottomRight->setCoords(xCoord,1);
    } else if (interactionMode==imZoomSquare||interactionMode==imAnalysFrame){
        itemRect->topLeft->setTypeY(QCPItemPosition::ptPlotCoords);
        itemRect->bottomRight->setTypeY(QCPItemPosition::ptPlotCoords);
        double yCoord=pCustomPlot->yAxis->pixelToCoord(y);
        itemRect->topLeft->setCoords(xCoord,yCoord);
        itemRect->bottomRight->setCoords(xCoord,yCoord);
    }
}

void AnalysisWindow::BeginLineZoomRectDraw(QMouseEvent *event)
{
    QRect rect;
    rect=pCustomPlot->axisRect()->rect();
    if (rect.contains(event->x(),event->y(),true)){
        connect(pCustomPlot,SIGNAL(mouseMove(QMouseEvent*)),SLOT(LineZoomRectDraw(QMouseEvent*)));
        connect(pCustomPlot,SIGNAL(mouseRelease(QMouseEvent*)),SLOT(EndLineZoomRectDraw(QMouseEvent*)));
        CreateZoomRect(pLineZoomRect,event->x(),event->y(),rect);
    }
}

void AnalysisWindow::LineZoomRectDraw(QMouseEvent *event)
{
    QRect rect;
    rect=pCustomPlot->axisRect()->rect();
    double ratio;
    ratio=static_cast<double>(event->x()-rect.x())/static_cast<double>(rect.width());
    if (ratio>1) ratio=1;
    if (ratio<0) ratio=0;
    pLineZoomRect->bottomRight->setCoords(ratio,1);
    pCustomPlot->replot();
}

void AnalysisWindow::SetRangeZoomLine(QCPItemRect* &itemRect)
{
    itemRect->topLeft->setType(QCPItemPosition::ptAbsolute);
    itemRect->bottomRight->setType(QCPItemPosition::ptAbsolute);
    int xL=itemRect->topLeft->key();
    int xR=itemRect->bottomRight->key();
    if (xL!=xR){
        double old_keyL;
        double old_keyR;
        old_keyL=pCustomPlot->xAxis->range().lower;
        old_keyR=pCustomPlot->xAxis->range().upper;
        ZoomPairList.append(ScalePair(old_keyL,old_keyR));
        itemRect->topLeft->setType(QCPItemPosition::ptPlotCoords);
        itemRect->bottomRight->setType(QCPItemPosition::ptPlotCoords);
        double keyL=itemRect->topLeft->key();
        double keyR=itemRect->bottomRight->key();
        if (keyL>keyR){
            keyL=keyR;
            keyR=itemRect->topLeft->key();
        }
        QCPRange range(keyL,keyR);
        pCustomPlot->xAxis->setRange(range);
        if (zoomMode==zmNoZoom)
            SetZoomMode(zmZoomLine);
    }
}

void AnalysisWindow::EndLineZoomRectDraw(QMouseEvent *event)
{
    disconnect(pCustomPlot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(LineZoomRectDraw(QMouseEvent*)));
    disconnect(pCustomPlot,SIGNAL(mouseRelease(QMouseEvent*)),this,SLOT(EndLineZoomRectDraw(QMouseEvent*)));
    SetRangeZoomLine(pLineZoomRect);
    pCustomPlot->removeItem(pLineZoomRect);
    pCustomPlot->replot();
}

void AnalysisWindow::LineZoomOneStepBack()
{
    if (!ZoomPairList.empty()){
        double keyL;
        double keyR;
        keyL=ZoomPairList.last().xL;
        keyR=ZoomPairList.last().xR;
        pCustomPlot->xAxis->setRange(QCPRange(keyL,keyR));
        pCustomPlot->replot();
        ZoomPairList.removeLast();
        if (ZoomPairList.empty()) SetZoomMode(zmNoZoom);
    }
}

void AnalysisWindow::BeginSquareZoomRectDraw(QMouseEvent* event)
{
    QRect rect;
    rect=pCustomPlot->axisRect()->rect();
    if (rect.contains(event->x(),event->y(),true)){
        connect(pCustomPlot,SIGNAL(mouseMove(QMouseEvent*)),SLOT(SquareZoomRectDraw(QMouseEvent*)));
        connect(pCustomPlot,SIGNAL(mouseRelease(QMouseEvent*)),SLOT(EndSquareZoomRectDraw(QMouseEvent*)));
        CreateZoomRect(pSquareZoomRect,event->x(),event->y(),rect);
    }
}

void AnalysisWindow::SquareZoomRectDraw(QMouseEvent* event)
{
    QRect rect;
    QCustomPlot* sender = qobject_cast<QCustomPlot*>(this->sender());
    if (sender==pCustomPlot)
        rect=pCustomPlot->axisRect()->rect();
    double ratioX;
    double ratioY;
    ratioX=static_cast<double>(event->x()-rect.x())/static_cast<double>(rect.width());
    ratioY=static_cast<double>(event->y()-rect.y())/static_cast<double>(rect.height());
    if (ratioX>1) ratioX=1;
    if (ratioX<0) ratioX=0;
    if (ratioY>1) ratioY=1;
    if (ratioY<0) ratioY=0;
    pSquareZoomRect->bottomRight->setCoords(ratioX,ratioY);
    pCustomPlot->replot();
}

void AnalysisWindow::SetRangeZoomSquare(QCustomPlot* customPlot, QCPItemRect* &itemRect)
{
    itemRect->topLeft->setType(QCPItemPosition::ptAbsolute);
    itemRect->bottomRight->setType(QCPItemPosition::ptAbsolute);
    int xL=itemRect->topLeft->key();
    int xR=itemRect->bottomRight->key();
    int yT=itemRect->topLeft->value();
    int yB=itemRect->bottomRight->value();
    if (xL!=xR && yT!=yB){
        double old_keyL=customPlot->xAxis->range().lower;
        double old_keyR=customPlot->xAxis->range().upper;
        double old_keyB=customPlot->yAxis->range().lower;
        double old_keyT=customPlot->yAxis->range().upper;
        if (ZoomSquareList.empty())
            SetZoomMode(zmZoomSquare);
        ZoomSquareList.append(ScaleSquare(old_keyL, old_keyR, old_keyB, old_keyT));
        itemRect->topLeft->setType(QCPItemPosition::ptPlotCoords);
        itemRect->bottomRight->setType(QCPItemPosition::ptPlotCoords);
        double keyL=itemRect->topLeft->key();
        double keyR=itemRect->bottomRight->key();
        double keyT=itemRect->topLeft->value();
        double keyB=itemRect->bottomRight->value();
        if (keyL>keyR){
            keyL=keyR;
            keyR=itemRect->topLeft->key();
        }
        if (keyT<keyB){
            keyT=keyB;
            keyB=itemRect->topLeft->value();
        }
        QCPRange rangeX(keyL,keyR);
        QCPRange rangeY(keyB,keyT);
        customPlot->xAxis->setRange(rangeX);
        customPlot->yAxis->setRange(rangeY);
    }
}

void AnalysisWindow::EndSquareZoomRectDraw(QMouseEvent* event)
{
    QCustomPlot* sender = qobject_cast<QCustomPlot*>(this->sender());
    if (sender==pCustomPlot){
        disconnect(pCustomPlot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(SquareZoomRectDraw(QMouseEvent*)));
        disconnect(pCustomPlot,SIGNAL(mouseRelease(QMouseEvent*)),this,SLOT(EndSquareZoomRectDraw(QMouseEvent*)));
        SetRangeZoomSquare(sender, pSquareZoomRect);
        pCustomPlot->removeItem(pSquareZoomRect);
        pCustomPlot->replot();
    }
}

void AnalysisWindow::SquareZoomOneStepBack(QCustomPlot* sender)
{
    double keyL;
    double keyR;
    double keyT;
    double keyB;
    if (sender==pCustomPlot){
        if (!ZoomSquareList.empty()){
            keyL=ZoomSquareList.last().xL;
            keyR=ZoomSquareList.last().xR;
            keyB=ZoomSquareList.last().yB;
            keyT=ZoomSquareList.last().yT;
            pCustomPlot->xAxis->setRange(QCPRange(keyL,keyR));
            pCustomPlot->yAxis->setRange(QCPRange(keyB,keyT));
            pCustomPlot->replot();
            ZoomSquareList.removeLast();
            if (ZoomSquareList.empty())
                SetZoomMode(zmNoZoom);
        }
    }
}

void AnalysisWindow::loadRecord(Record* pRecord, int insertIndex)
{
    switch (pRecord->getType()){
    case Record::rtRecordFun1:
        QString name=pRecord->getName();
        QString sourceFile=pRecord->getSourceFile();
        GraphItem* pGraphItem = new GraphItem();
        pGraphItem->setName(name);
        pGraphItem->setSourceFile(sourceFile);
        pGraphItem->setColor(QColor(Qt::red));
        pGraphItem->setLineType(Qt::SolidLine);
        pGraphItem->setLineWidth(1);
        pGraphItem->setScatter(QCPScatterStyle::ssCross);
        pGraphItem->setRecordFun1Ptr(dynamic_cast<RecordFun1*>(pRecord));

        QList<QVector<double> > data;
        pRecord->readMyData(data);
        QCPGraph* pGraph=ui->exQCustomPlot->addGraph();
        pGraph->setData(data[0],data[1]);
        pGraphItem->setGraph(pGraph);
        pGraphItem->updateAppearance();

        QList<GraphItem*> gInsertList;
        gInsertList<<pGraphItem;
    //  bool GraphListWasEmpy = GraphList.empty();
        pGraphItemModel->insertGraphItem(insertIndex, gInsertList);

        switch (zoomMode){
        case zmNoZoom:
            ui->exQCustomPlot->EXrescaleAxes();
            break;
        case zmZoomLine:
            ui->exQCustomPlot->yAxis->EXrescale();
            break;
        case zmZoomSquare:
            break;
        }
        break;
    }
    pCustomPlot->replot();
}

void  AnalysisWindow::slotReplot()
{
    pCustomPlot->replot();
}

void AnalysisWindow::slotRescaleReplot()
{
    pCustomPlot->EXrescaleAxes();
    pCustomPlot->replot();
}

AnalysisWindow::RectRegion AnalysisWindow::getBandRegion(int x, int y)
{
    QPoint topLeft = pAnalysRect->topLeft->pixelPoint().toPoint();//reletive to QCustomPlot
    QPoint bottomRight = pAnalysRect->bottomRight->pixelPoint().toPoint();
    QRect analysRect(topLeft,bottomRight);
    analysRect=analysRect.normalized();
    QRect interRect(analysRect.topLeft(),analysRect.bottomRight());
    interRect.setLeft(analysRect.left()+5); interRect.setRight(analysRect.right()-5);
    QRect exterRect(analysRect.topLeft(),analysRect.bottomRight());
    exterRect.setLeft(analysRect.left()-5); exterRect.setRight(analysRect.right()+5);
    if (x>interRect.left()&&x<interRect.right()){/*qDebug()<<"inside!";*/ return rrInside;  }
    else if (x>=exterRect.left()&&x<=interRect.left()){ /*qDebug()<<"left!";*/ return rrLeft;}
    else if (x<=exterRect.right()&&x>=interRect.right()){ /*qDebug()<<"right!";*/ return rrRight;}
    else { /*qDebug()<<"ouside!";*/ return rrOutside;}
}

AnalysisWindow::RectRegion AnalysisWindow::getFrameRegion(QMouseEvent* event)
{

}

void AnalysisWindow::analysRectChange(QMouseEvent* event)
{
    if (bAnalysRectExist==false)
    beginAnalysRectDraw(event);
    else {
        RectRegion rRegion = getBandRegion(event->x(), event->y());
        if (rRegion==rrOutside){
            deleteAnalysRect();
            beginAnalysRectDraw(event);
        }
        else if (rRegion==rrInside)
            beginAnalysRectMove(event);
        else
            beginAnalysRectResize(event, rRegion);
    }
}

void AnalysisWindow::deleteAnalysRect()
{
    pCustomPlot->removeItem(pAnalysRect);
    pAnalysRect=0;
    bAnalysRectExist=false;
    emit analysRectChanged();
    pCustomPlot->replot();
    qDebug()<<"I have been deleted";
}

void AnalysisWindow::beginAnalysRectDraw(QMouseEvent *event)
{
    QRect rect;
    rect=pCustomPlot->axisRect()->rect();
    if (rect.contains(event->x(),event->y(),true)){
        connect(pCustomPlot,SIGNAL(mouseMove(QMouseEvent*)),SLOT(analysRectDraw(QMouseEvent*)));
        connect(pCustomPlot,SIGNAL(mouseRelease(QMouseEvent*)),SLOT(endAnalysRectDraw(QMouseEvent*)));
        createRect(pAnalysRect,event->x(), event->y(),rect,QColor(Qt::green));
    }
}

void AnalysisWindow::analysRectDraw(QMouseEvent *event)
{
    double xCoord = pCustomPlot->xAxis->pixelToCoord(event->x());
    if (interactionMode==imAnalysBand){
        pAnalysRect->bottomRight->setCoords(xCoord, 1);
    } else if (interactionMode==imAnalysFrame){
        double yCoord = pCustomPlot->yAxis->pixelToCoord(event->y());
        pAnalysRect->bottomRight->setCoords(xCoord, yCoord);
    }
    pCustomPlot->replot();
}

void AnalysisWindow::endAnalysRectDraw(QMouseEvent* event)
{
    QPoint topLeft = pAnalysRect->topLeft->pixelPoint().toPoint();
    QPoint bottomRight = pAnalysRect->bottomRight->pixelPoint().toPoint();
    QRect rect(topLeft, bottomRight);
    rect=rect.normalized();
    if ((rect.right()-rect.left())<20||(rect.bottom()-rect.top())<20)
        deleteAnalysRect();
    else{
        bAnalysRectExist=true;
        emit analysRectChanged();
    }
    disconnect(pCustomPlot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(analysRectDraw(QMouseEvent *)));
    disconnect(pCustomPlot,SIGNAL(mouseRelease(QMouseEvent*)),this,SLOT(endAnalysRectDraw(QMouseEvent*)));
    pCustomPlot->replot();
}

void AnalysisWindow::beginAnalysRectMove(QMouseEvent* event)
{
    beginMoveKey=pCustomPlot->xAxis->pixelToCoord(event->x());
    beginMoveValue=pCustomPlot->xAxis->pixelToCoord(event->y());
    beginMoveTopLeftKey=pAnalysRect->topLeft->key();
    beginMoveTopLeftValue=pAnalysRect->topLeft->value();
    beginMoveBotRightKey=pAnalysRect->bottomRight->key();
    beginMoveBotRightValue=pAnalysRect->bottomRight->value();
    connect(pCustomPlot,SIGNAL(mouseMove(QMouseEvent*)),SLOT(analysRectMove(QMouseEvent*)));
    connect(pCustomPlot,SIGNAL(mouseRelease(QMouseEvent*)),SLOT(endAnalysRectMove(QMouseEvent*)));
}

void AnalysisWindow::analysRectMove(QMouseEvent* event)
{
    double eventKey = pCustomPlot->xAxis->pixelToCoord(event->x());
    double eventValue = pCustomPlot->yAxis->pixelToCoord(event->y());
    double deltaKey=eventKey-beginMoveKey;
    double deltaValue=eventValue-beginMoveValue;
    if (interactionMode==imAnalysBand){
        pAnalysRect->topLeft->setCoords(beginMoveTopLeftKey+deltaKey, 0);
        pAnalysRect->bottomRight->setCoords(beginMoveBotRightKey+deltaKey, 1);
    } else if (interactionMode==imAnalysFrame){
        //todo
    }
    pCustomPlot->replot();
}

void AnalysisWindow::endAnalysRectMove(QMouseEvent* event)
{
    disconnect(pCustomPlot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(analysRectMove(QMouseEvent*)));
    disconnect(pCustomPlot,SIGNAL(mouseRelease(QMouseEvent*)),this,SLOT(endAnalysRectMove(QMouseEvent*)));
    emit analysRectChanged();
}

void AnalysisWindow::normalizeAnalysRect(QMouseEvent* event)
{
    if (interactionMode==imAnalysBand){
        RectRegion regionEvent=getBandRegion(event->x(), event->y());
        RectRegion regionBottomRight=getBandRegion(pAnalysRect->bottomRight->pixelPoint().x(),
                                        pAnalysRect->bottomRight->pixelPoint().y());
        if (regionEvent!=regionBottomRight){
            double topLeftKey=pAnalysRect->topLeft->coords().x();
            double bottomRightKey=pAnalysRect->bottomRight->coords().x();//!!!
            pAnalysRect->topLeft->setCoords(bottomRightKey, 0);
            pAnalysRect->bottomRight->setCoords(topLeftKey, 1);
        }
    } else if (interactionMode==imAnalysFrame){
        //todo
    }
}

void AnalysisWindow::beginAnalysRectResize(QMouseEvent* event, RectRegion rRegion)
{
    normalizeAnalysRect(event);
    connect(pCustomPlot,SIGNAL(mouseMove(QMouseEvent*)),SLOT(analysRectDraw(QMouseEvent*)));
    connect(pCustomPlot,SIGNAL(mouseRelease(QMouseEvent*)),SLOT(endAnalysRectDraw(QMouseEvent*)));
}

void AnalysisWindow::analysRectResize(QMouseEvent* event, RectRegion rRegion)
{

}

void AnalysisWindow::endAnalysRectResize(QMouseEvent* event)
{

}

void AnalysisWindow::setMouseInRegion(RectRegion region)
{
    mouseInRegion=region;
}

void AnalysisWindow::cursorChange(QMouseEvent * event)
{
    switch (interactionMode){
    case imAnalysBand:
        if (bAnalysRectExist==false) return;
        RectRegion rRegion = getBandRegion(event->x(), event->y());
        if (rRegion==mouseInRegion) return;
        else{
            if (rRegion==rrInside)
                pCustomPlot->setCursor(QCursor(Qt::SizeAllCursor));
            else if (rRegion==rrLeft||rRegion==rrRight)
                pCustomPlot->setCursor(QCursor(Qt::SizeHorCursor));
            else if (rRegion==rrOutside)
                pCustomPlot->setCursor(QCursor(Qt::ArrowCursor));
            setMouseInRegion(rRegion);
        }
        break;
    }
}

void AnalysisWindow::createDigFiltWindow()
{
    pDigFiltDialog = new DigitalFiltersDialog(this);
    pDigFiltDialog->show();
}

void AnalysisWindow::createFFTWindow()
{
    pFFTDialog = new FFTDialog(this);
    pFFTDialog->show();
}
