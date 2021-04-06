#include "graphitemmodel.h"

//GraphItem
GraphItem::GraphItem()
{

}

GraphItem::~GraphItem()
{
    pGraph->parentPlot()->removeGraph(pGraph);
}

void GraphItem::updateAppearance() const
{
    QPen pen;
    pen.setColor(color);
    pen.setStyle(lineType);
    pen.setWidth(lineWidth);
    pGraph->setPen(pen);
}

// CustomLookComboBox
CustomLookComboBox::CustomLookComboBox(QWidget *parent, const QColor &backcolor):QComboBox(parent)
{
    BackColor=backcolor;
    layoutTop = new QHBoxLayout();
    layoutTop->setMargin(0);
    layoutTop->setSpacing(0);
    setLayout(layoutTop);
    frame = new QFrame();
    frame->setFrameStyle(QFrame::StyledPanel);
    layoutTop->addWidget(frame,1);
    button=new QPushButton(QString(QChar(0x25bc)));//code of an "arrow" character
    button->setMaximumHeight(1000);//Ugly!
    button->setMaximumWidth(20);
    QFont font("Times",6);
    button->setFont(font);
    layoutIn = new QHBoxLayout();
    layoutIn->setMargin(0);
    layoutIn->setSpacing(0);
    layoutTop->addLayout(layoutIn,0);
    layoutIn->addWidget(button);
    connect(button,SIGNAL(clicked()),SLOT(PopUp()));
}

// LineStyleComboBox
void LineStyleComboBox::paintEvent(QPaintEvent *e)
{
    QPainter* painter = new QPainter(this);
    QRect r=this->frame->rect();
    QBrush brush(BackColor);
    QPen pen(BackColor);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRect(e->rect());
    pen.setColor(Qt::black);
    pen.setWidthF(1.0);
    pen.setStyle(static_cast<Qt::PenStyle>(itemData(currentIndex(),Qt::DisplayRole).toInt()));
    painter->setPen(pen);
    const qreal x1=r.x()+r.width()*0.1;
    const qreal y1=r.y()+r.height()/2;
    const qreal x2=x1+r.width()*0.8;
    const qreal y2=y1;
    painter->drawLine(QPointF(x1,y1),QPointF(x2,y2));
    qDebug()<<"Paint! "<<itemData(currentIndex(),Qt::DisplayRole).toInt();
}
// ColorComboBox
ColorComboBox::ColorComboBox(QWidget* parent, const QColor& backcolor):
    CustomLookComboBox(parent, backcolor)
{
    inFrameLayout = new QHBoxLayout();
    inFrameLayout->setMargin(0);
    inFrameLayout->setSpacing(0);
    frame->setLayout(inFrameLayout);
    pixmap = new QLabel();
    pixmap->setMaximumHeight(30);
    pixmap->setMinimumWidth(25);
    QPixmap pic(25,27);
    pixmap->setPixmap(pic);
    Text = new QLabel(currentData(Qt::DisplayRole).toString());
    Text->setMinimumWidth(20);
    QFont font("Segoe UI",9);
    Text->setFont(font);
    inFrameLayout->addWidget(pixmap,0);
    inFrameLayout->addWidget(Text,1);
}

void ColorComboBox::paintEvent(QPaintEvent *e)
{
    QPainter* painter = new QPainter(this);
    QRect r=frame->rect();
    QBrush brush(BackColor);
    QPen pen(BackColor);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRect(e->rect());
    painter->end();
    QColor color(currentData(Qt::DecorationRole).value<QColor>());
    pen.setColor(color);
    brush.setColor(color);
    QPixmap* pic = const_cast<QPixmap*>(pixmap->pixmap());
    pic->fill(BackColor);
    painter->begin(pic);
    painter->setPen(pen);
    painter->setBrush(brush);
    int x1=3;
    int y1=5;
    int w=15;
    int h=15;
    painter->drawRect(x1,y1,w,h);
    painter->end();
    QFontMetrics metrics(Text->font());
    QString elideText = metrics.elidedText(currentData(Qt::DisplayRole).toString(),
                                           Qt::ElideRight, Text->width());
    Text->setText(elideText);
}

// LineWidthComboBox
void LineWidthComboBox::paintEvent(QPaintEvent *e)
{
    QPainter* painter = new QPainter(this);
    QRect r=this->frame->rect();
    QBrush brush(BackColor);
    QPen pen(BackColor);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRect(e->rect());
    pen.setColor(Qt::black);
    pen.setWidthF(itemData(currentIndex(),Qt::DisplayRole).toInt());
    painter->setPen(pen);
    const qreal x1=r.x()+r.width()*0.1;
    const qreal y1=r.y()+r.height()/2;
    const qreal x2=x1+r.width()*0.8;
    const qreal y2=y1;
    painter->drawLine(QPointF(x1,y1),QPointF(x2,y2));
    qDebug()<<"Paint! "<<itemData(currentIndex(),Qt::DisplayRole).toInt();
}

// ScatterComboBox
void ScatterComboBox::paintEvent(QPaintEvent *e)
{
    QCPPainter* painter = new QCPPainter(this);
    QRect r=this->frame->rect();
    QBrush brush(BackColor);
    QPen pen(BackColor);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRect(e->rect());
    pen.setColor(Qt::black);
    painter->setPen(pen);
    double x=frame->rect().x()+static_cast<double>(frame->rect().width())/2;
    double y=frame->rect().y()+static_cast<double>(frame->rect().height())/2;
    QCPScatterStyle ScatterStyle(
                static_cast<QCPScatterStyle::ScatterShape>(itemData(currentIndex(),Qt::DisplayRole).toInt()), 10);
    ScatterStyle.drawShape(painter,x,y);
}
// CommonGraphDataDelegate
CommonGraphDataDelegate::CommonGraphDataDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

void CommonGraphDataDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    if (option.state & QStyle::State_Selected)
    {
        if (option.state & QStyle::State_Active)
        {
            QBrush brush(option.palette.highlight());
            QColor color(brush.color());
            color.setAlpha(127);
            brush.setColor(color);
            painter->fillRect(option.rect,brush);
        }
        else
        painter->fillRect(option.rect,option.palette.button());
    }
    if (option.state & QStyle::State_HasFocus)
    {
        QStyleOptionFocusRect o;
        o.QStyleOption::operator=(option);
        o.rect = QApplication::style()->subElementRect(QStyle::SE_ItemViewItemFocusRect, &option);
        o.state |= QStyle::State_KeyboardFocusChange;
        o.state |= QStyle::State_Item;
        QPalette::ColorGroup cg = (option.state & QStyle::State_Enabled)
                      ? QPalette::Normal : QPalette::Disabled;
        o.backgroundColor = option.palette.color(cg, (option.state & QStyle::State_Selected)
                                     ? QPalette::Highlight : QPalette::Window);
        QApplication::style()->drawPrimitive(QStyle::PE_FrameFocusRect,
                                             &o, painter);
    }
}
// NameDelegate
void NameDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    QStyleOptionViewItem& opt = const_cast<QStyleOptionViewItem&>(option);
    QColor color(option.palette.highlight().color());
    if (option.state & QStyle::State_Active)
    {
        color.setAlpha(127);
        opt.palette.setColor(QPalette::Highlight,color);
        opt.palette.setColor(QPalette::HighlightedText, Qt::black);
    }
    QStyledItemDelegate::paint(painter,opt,index);
}
//SourceDelegate
void SourceDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    QStyleOptionViewItem& opt = const_cast<QStyleOptionViewItem&>(option);
    QColor color(option.palette.highlight().color());
    if (option.state & QStyle::State_Active)
    {
        color.setAlpha(127);
        opt.palette.setColor(QPalette::Highlight,color);
        opt.palette.setColor(QPalette::HighlightedText, Qt::black);
    }
    QStyledItemDelegate::paint(painter,opt,index);
}
// LineStyleDelegate
LineStyleDelegate::LineStyleDelegate(QObject *parent):CommonGraphDataDelegate(parent)
{

}

void LineStyleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    painter->save();

    CommonGraphDataDelegate::paint(painter, option, index);
    QPen pen(QBrush(Qt::black),1.0,static_cast<Qt::PenStyle>(index.data(Qt::DisplayRole).toInt()));
    painter->setPen(pen);
    const qreal x1=option.rect.x()+option.rect.width()*0.1;
    const qreal y1=option.rect.y()+option.rect.height()/2;
    const qreal x2=x1+option.rect.width()*0.8;
    const qreal y2=y1;
    painter->drawLine(QPointF(x1,y1),QPointF(x2,y2));


    painter->restore();
}

QWidget* LineStyleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    LineStyleComboBox* editor = new LineStyleComboBox(parent);
    for (int i=0;i<5;++i)
        editor->addItem(QString::number(i+1));
    editor->setItemDelegate(const_cast<LineStyleDelegate*>(this));//TODO
    return editor;
}

void LineStyleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    LineStyleComboBox* LineStyleEditor = qobject_cast<LineStyleComboBox*>(editor);
    LineStyleEditor->setCurrentIndex(index.data().toInt()-1);
}

void LineStyleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    LineStyleComboBox* LineStyleEditor = qobject_cast<LineStyleComboBox*>(editor);
    int style = LineStyleEditor->currentData(Qt::DisplayRole).toInt();
    model->setData(index,style);
}

QSize LineStyleDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    int height=qobject_cast<QTableView*>(this->parent())->sizeHintForRow(index.row());
    QSize size(0,/*height*/30);//TODO!!!
    return size;
}

// ColorDelegate
ColorDelegate::ColorDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

void ColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    QStyleOptionViewItem& opt = const_cast<QStyleOptionViewItem&>(option);
    QColor color(option.palette.highlight().color());
    if (option.state & QStyle::State_Active)
    {
        color.setAlpha(127);
        opt.palette.setColor(QPalette::Highlight,color);
        opt.palette.setColor(QPalette::HighlightedText, Qt::black);
    }
    QStyledItemDelegate::paint(painter,opt,index);
}

QWidget* ColorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    GraphItemModel* p_graphdatamodel;
    p_graphdatamodel=const_cast<GraphItemModel*>(qobject_cast<const GraphItemModel*>(index.model()));
    ChangeRetDecoration(p_graphdatamodel);
    SetColorEditPIndex(p_graphdatamodel,index);
    ColorComboBox* editor = new ColorComboBox(parent);
    ColorDelegateForList* delegate = new ColorDelegateForList(editor);
    editor->setItemDelegate(delegate);
    const GraphItemModel* gdmodel =  qobject_cast<const GraphItemModel*>(index.model());
    int maxcolor = gdmodel->getCOLOR_NUMBER();
    for (int i=0;i<maxcolor;++i)
    {
        editor->insertItem(i, gdmodel->getColorMapString(i));
        editor->setItemData(i, gdmodel->getColorMapColor(i),Qt::DecorationRole);
    }
    return editor;
}

void ColorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    ColorComboBox* ColorEditor = qobject_cast<ColorComboBox*>(editor);
    const GraphItemModel* graphdatamodel = qobject_cast<const GraphItemModel*>(index.model());
    int maxcolor = graphdatamodel->getCOLOR_NUMBER();
    for (int i=0;i<maxcolor;++i)
    {
        if (index.data().toString()==graphdatamodel->getColorMapString(i))
        {
            ColorEditor->setCurrentIndex(i);
            return;
        }
    }
}

void ColorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    GraphItemModel* p_graphdatamodel;
    p_graphdatamodel=const_cast<GraphItemModel*>(qobject_cast<const GraphItemModel*>(index.model()));
    ChangeRetDecoration(p_graphdatamodel);
    SetColorEditPIndex(p_graphdatamodel,index);
    ColorComboBox* ColorEditor = qobject_cast<ColorComboBox*>(editor);
    QColor color(ColorEditor->currentData(Qt::DecorationRole).value<QColor>());
    qobject_cast<GraphItemModel*>(model)->setData(index,color);
}

QSize ColorDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void ColorDelegate::ChangeRetDecoration(GraphItemModel* gdm) const
{
    (gdm->bRetDecorate=!(gdm->bRetDecorate));
}

void ColorDelegate::SetColorEditPIndex(GraphItemModel *gdm, QPersistentModelIndex index) const
{
    gdm->ColorEditPIndex=index;
}
// ColorDelegateForList
QSize ColorDelegateForList::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size(0,/*height*/20);//TODO!!!
    return size;
}
// LineWidthDelegate
LineWidthDelegate::LineWidthDelegate(QObject *parent):CommonGraphDataDelegate(parent)
{

}

void LineWidthDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    painter->save();
    CommonGraphDataDelegate::paint(painter, option, index);
    QPen pen(QBrush(Qt::black),index.data(Qt::DisplayRole).toInt());
    painter->setPen(pen);
    const qreal x1=option.rect.x()+option.rect.width()*0.1;
    const qreal y1=option.rect.y()+option.rect.height()/2;
    const qreal x2=x1+option.rect.width()*0.8;
    const qreal y2=y1;
    painter->drawLine(QPointF(x1,y1),QPointF(x2,y2));
    painter->restore();
}

QWidget* LineWidthDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    LineWidthComboBox* editor = new LineWidthComboBox(parent);
    for (int i=0;i<5;++i)
        editor->addItem(QString::number(i+1));
    editor->setItemDelegate(const_cast<LineWidthDelegate*>(this));//TODO
    return editor;
}

void LineWidthDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    LineWidthComboBox* LineWidthEditor = qobject_cast<LineWidthComboBox*>(editor);
    LineWidthEditor->setCurrentIndex(index.data().toInt()-1);
}

void LineWidthDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    LineWidthComboBox* LineWidthEditor = qobject_cast<LineWidthComboBox*>(editor);
    int width = LineWidthEditor->currentData(Qt::DisplayRole).toInt();
    model->setData(index,width);
}

QSize LineWidthDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    int height=qobject_cast<QTableView*>(this->parent())->sizeHintForRow(index.row());
    QSize size(0,/*height*/30);//TODO!!!
    return size;
}
// ScatterDelegate
ScatterDelegate::ScatterDelegate(QObject *parent):CommonGraphDataDelegate(parent)
{

}

void ScatterDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    painter->save();
    CommonGraphDataDelegate::paint(painter, option, index);
    double x=option.rect.x()+static_cast<double>(option.rect.width())/2;
    double y=option.rect.y()+static_cast<double>(option.rect.height())/2;
    painter->setPen(QPen(QBrush(Qt::black),1.0));
    painter->setRenderHint(QPainter::Antialiasing,false);
    double mSize = 10;
    double w = mSize/2;
    QCPScatterStyle::ScatterShape mShape =
            static_cast<QCPScatterStyle::ScatterShape>(index.data(Qt::DisplayRole).toInt());
    switch (mShape)
    {
      case QCPScatterStyle::ssCross:
      {
        painter->drawLine(QLineF(x-w, y-w, x+w, y+w));
        painter->drawLine(QLineF(x-w, y+w, x+w, y-w));
        break;
      }
      case QCPScatterStyle::ssPlus:
      {
        painter->drawLine(QLineF(x-w,   y, x+w,   y));
        painter->drawLine(QLineF(  x, y+w,   x, y-w));
        break;
      }
      case QCPScatterStyle::ssCircle:
      {
        painter->drawEllipse(QPointF(x , y), w, w);
        break;
      }
      case QCPScatterStyle::ssDisc:
      {
        QBrush b = painter->brush();
        painter->setBrush(painter->pen().color());
        painter->drawEllipse(QPointF(x , y), w, w);
        painter->setBrush(b);
        break;
      }
      case QCPScatterStyle::ssSquare:
      {
        painter->drawRect(QRectF(x-w, y-w, mSize, mSize));
        break;
      }
      case QCPScatterStyle::ssDiamond:
      {
        painter->drawLine(QLineF(x-w,   y,   x, y-w));
        painter->drawLine(QLineF(  x, y-w, x+w,   y));
        painter->drawLine(QLineF(x+w,   y,   x, y+w));
        painter->drawLine(QLineF(  x, y+w, x-w,   y));
        break;
      }
    }
    painter->restore();
}

QWidget* ScatterDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    ScatterComboBox* editor = new ScatterComboBox(parent);
    const GraphItemModel* p_gdmodel = qobject_cast<const GraphItemModel*>(index.model());
    QCPScatterStyle::ScatterShape scatter;
    for (int i=0;i<5;++i)
    {
        scatter=p_gdmodel->getScatter(i);
        editor->addItem(QString::number(scatter));
    }
    editor->setItemDelegate(const_cast<ScatterDelegate*>(this));//TODO
    return editor;
}

void ScatterDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    ScatterComboBox* ScatterEditor = qobject_cast<ScatterComboBox*>(editor);
    const GraphItemModel* p_gdmodel = qobject_cast<const GraphItemModel*>(index.model());
    int cur_index = p_gdmodel->getNumberByScatter(
                static_cast<QCPScatterStyle::ScatterShape>(index.data().toInt())).toInt();

    ScatterEditor->setCurrentIndex(cur_index);
}

void ScatterDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    ScatterComboBox* ScatterEditor = qobject_cast<ScatterComboBox*>(editor);
    GraphItemModel* p_gdmodel = qobject_cast<GraphItemModel*>(model);
    QCPScatterStyle::ScatterShape scatter = p_gdmodel->getScatter(ScatterEditor->currentIndex());
    model->setData(index, static_cast<int>(scatter));
}

QSize ScatterDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size(0,/*height*/30);//TODO!!!
    return size;
}

// GraphDataTableView
GraphDataTableView::GraphDataTableView(QWidget *parent):QTableView(parent)
{

}

void GraphDataTableView::keyPressEvent(QKeyEvent *event)
{
    QTableView::keyPressEvent(event);
    switch (event->key()){
    case Qt::Key_Delete:
        GraphItemModel* pGraphItemModel = qobject_cast<GraphItemModel*>(model());
        int rows=model()->rowCount();
        int i =0;
        while (i!=rows){
            if (selectionModel()->isRowSelected(i,QModelIndex())==true){
                pGraphItemModel->deleteGraphItem(i);
                rows-=1;
            }
            else i++;
        }
    emit pGraphItemModel->needRescaleReplot();
    break;
    }
}

// GraphItemModel
const GraphItemModel::ColorMapItem GraphItemModel::ColorMap[GraphItemModel::COLOR_NUMBER]=
{
    {Qt::red,tr("Red")},
    {Qt::darkGreen, tr("Green")},
    {Qt::blue, tr("Blue")},
    {Qt::magenta,tr("Magenta")},
    {QColor(255,69,0),tr("Orange")},
    {QColor(124,255,0),tr("Lawn Green")},
    {Qt::darkBlue,tr("Dark Blue")},
    {Qt::darkMagenta,tr("Dark Magenta")}
};

const QCPScatterStyle::ScatterShape GraphItemModel::ScatterMap[GraphItemModel::SCATTER_NUMBER]=
{
    QCPScatterStyle::ssCross,
    QCPScatterStyle::ssPlus ,
    QCPScatterStyle::ssCircle,
    QCPScatterStyle::ssDisc,
    QCPScatterStyle::ssSquare
};

GraphItemModel::GraphItemModel(QList<GraphItem>* pgraphlist, QCustomPlot *pcustomplot, QObject *parent):
    QAbstractTableModel(parent)
{
    bRetDecorate=true;
    pGraphList=pgraphlist;
    pCustomPlot=pcustomplot;
}

GraphItemModel::~GraphItemModel()
{

}

int GraphItemModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid()? 0 : COLUMNS_NUMBER;
}

bool GraphItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()||index.row()<0)
    return false;
    GraphItem &graphItem = (*pGraphList)[index.row()];

    if (role==Qt::EditRole){
        switch(index.column()){
//          case Name:
//          graphItem.name=value.toString(); break;
//          case SourceFile:
//          graphItem.SourceFile=value.toString(); break;
        case cColor:
            graphItem.setColor(value.value<QColor>());
            break;
        case cLineType:
            graphItem.setLineType(static_cast<Qt::PenStyle>(value.toInt()));
            break;
        case cLineWidth:
            graphItem.setLineWidth(value.toInt());
            break;
        case cScatter:
            graphItem.setScatter(static_cast<QCPScatterStyle::ScatterShape>(value.toInt()));
            break;
        }
        emit dataChanged(index,index);
        graphItem.updateAppearance();
        emit needReplot();
        return true;
    }
    return false;
}

bool GraphItemModel::insertGraphItem(int row, const QList<GraphItem *> &data)
{
    int count=data.count();
    beginInsertRows(QModelIndex(),row, row+count-1);
    for (int i=0;i<count;++i){
        pGraphList->insert(row+i,*(data.at(i)));
    }
    endInsertRows();
    return true;
}

bool GraphItemModel::deleteGraphItem(int row)
{
    int count=1;
    beginRemoveRows(QModelIndex(),row,row+count-1);
    pGraphList->removeAt(row);
    endRemoveRows();
    return true;
}

QVariant GraphItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()||index.row()<0)
    return QVariant();
    const GraphItem& graphItem = pGraphList->at(index.row());

    if (role==Qt::DisplayRole){
        switch (index.column()){
        case cName:
            return graphItem.getName();
        case cSourceFile:
            return graphItem.getSourceFile();
        case cColor:
        for (int i=0;i<COLOR_NUMBER;++i){
            if (ColorMap[i].color==graphItem.getColor())
            return ColorMap[i].string;
        }
        case cLineType:
            return static_cast<int>(graphItem.getLineType());
        case cLineWidth:
            return graphItem.getLineWidth();
        case cScatter:
            return static_cast<int>(graphItem.getScatter());
        }
    }
    else if (role==Qt::DecorationRole){
         switch (index.column()){
         case cName:
             //TODO:
             break;
         case cColor:
             if ((bRetDecorate==true)||(index!=ColorEditPIndex))
             return graphItem.getColor();
         }
    }
    else if (role==Qt::EditRole)
    {
        switch (index.column()){
//            case Name: return graphdata.name;
//            case Color://TODO
//            case LineType: return static_cast<int>(graphdata.LineType);
            case cLineWidth:
                return graphItem.getLineWidth();
//            case Marker: return static_cast<int>(graphdata.Marker);
        }
    }
    return QVariant();
}

QVariant GraphItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role!=Qt::DisplayRole)
        return QVariant();
    if (orientation==Qt::Horizontal){
        switch (section){
        case cName:
            return tr("Name");
        case cSourceFile:
            return tr("Source File");
        case cColor:
            return tr("Color");
        case cLineType:
            return tr("Line Style");
        case cLineWidth:
            return tr("Line Width");
        case cScatter:
            return tr("Scatter");
        }
    }
    if (orientation==Qt::Vertical)
        return section+1;
}

int GraphItemModel::rowCount(const QModelIndex &index) const
{
    return index.isValid()? 0 :pGraphList->count();
}

QVariant GraphItemModel::getColorByName(const QString& colorname) const
{
    for (int i=0;i<COLOR_NUMBER;++i)
    if (ColorMap[i].string==colorname) return ColorMap[i].color;
    return QVariant();
}

QVariant GraphItemModel::getNumberByScatter(QCPScatterStyle::ScatterShape scattershape) const
{
    for (int i=0;i<SCATTER_NUMBER;++i)
    if (ScatterMap[i]==scattershape) return i;
    return QVariant();
}

Qt::ItemFlags GraphItemModel::flags(const QModelIndex &index) const
{
    if (index.column()==0) return QAbstractTableModel::flags(index)|Qt::ItemIsUserCheckable;
    else if (index.column()==1) return QAbstractTableModel::flags(index);
    else return QAbstractTableModel::flags(index)|Qt::ItemIsEditable;
}

