#ifndef GRAPHITEMMODEL_H
#define GRAPHITEMMODEL_H

#include <QString>
#include <QColor>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include "exqcustomplot.h"

//FRGraphItem
class RecordFun1;
class GraphItem
{

    static bool isScatter;
public:
     GraphItem();
    ~GraphItem();
//getters
    const QString& getName() const {return name;}
    const QString& getSourceFile() const {return sourceFile;}
    const QColor& getColor() const {return color;}
    Qt::PenStyle getLineType() const {return lineType;}
    int getLineWidth() const {return lineWidth;}
    QCPScatterStyle::ScatterShape getScatter() const {return scatter;}
    QCPGraph* getGraph() const {return pGraph;}
    RecordFun1* getRecordFun1Ptr() const {return pRecordFun1;}
//setters
    void setName (const QString& name) {this->name=name;}
    void setSourceFile  (const QString& sourceFile) {this->sourceFile=sourceFile;}
    void setColor(const QColor& color){this->color=color;}
    void setLineType(Qt::PenStyle penStyle){this->lineType=penStyle;}
    void setLineWidth(int lineWidth){this->lineWidth=lineWidth;}
    void setScatter(QCPScatterStyle::ScatterShape scatter){this->scatter=scatter;}
    void setGraph(QCPGraph* pGraph){this->pGraph=pGraph; }
    void setRecordFun1Ptr(RecordFun1* pRecordFun1){this->pRecordFun1 = pRecordFun1;}
//other
    void updateAppearance() const;
private:
    QString name;
    QString sourceFile;
    // all these properties stored in the graph object in fact FIX?
    QColor color;
    Qt::PenStyle lineType;
    int lineWidth;
    QCPScatterStyle::ScatterShape scatter;

    QCPGraph* pGraph;
    RecordFun1* pRecordFun1;
};

// Custom Combo Boxes
class CustomLookComboBox: public QComboBox
{
    Q_OBJECT
public:
    CustomLookComboBox(QWidget* parent=0, const QColor& backcolor=Qt::white);
public slots:
    void PopUp() {showPopup();}
protected:
    virtual void paintEvent(QPaintEvent* e)=0;
    QHBoxLayout* layoutTop;
    QHBoxLayout* layoutIn;
    QPushButton* button;
    QFrame* frame;
    QColor BackColor;
};

class LineStyleComboBox: public CustomLookComboBox
{
    Q_OBJECT
public:
    LineStyleComboBox(QWidget* parent=0, const QColor& backcolor=Qt::white):
        CustomLookComboBox(parent, backcolor){}
private:
    void paintEvent(QPaintEvent *e);
};

class ColorComboBox: public CustomLookComboBox
{
    Q_OBJECT
public:
    ColorComboBox(QWidget* parent=0, const QColor& backcolor=Qt::white);
private:
    void paintEvent(QPaintEvent *e);
    QHBoxLayout* inFrameLayout;
    QLabel* pixmap;
    QLabel* Text;
};

class LineWidthComboBox: public CustomLookComboBox
{
    Q_OBJECT
public:
    LineWidthComboBox(QWidget* parent=0, const QColor& backcolor=Qt::white):
        CustomLookComboBox(parent, backcolor){}
private:
    void paintEvent(QPaintEvent *e);
};

class ScatterComboBox: public CustomLookComboBox
{
    Q_OBJECT
public:
    ScatterComboBox(QWidget* parent=0, const QColor& backcolor=Qt::white):
        CustomLookComboBox(parent, backcolor){}
private:
    void paintEvent(QPaintEvent *e);
};
//Delegates
class CommonGraphDataDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CommonGraphDataDelegate(QObject *parent=0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class NameDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit NameDelegate(QObject *parent=0):QStyledItemDelegate(parent){}
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class SourceDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SourceDelegate(QObject *parent=0):QStyledItemDelegate(parent){}
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class LineStyleDelegate: public CommonGraphDataDelegate
{
    Q_OBJECT
public:
    explicit LineStyleDelegate(QObject *parent=0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
};

class GraphItemModel; //forward declaration
class ColorDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ColorDelegate(/*const QList<QString> &colorlist,*/ QObject *parent=0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
    QHBoxLayout* inFrameLayout;
    QLabel* pixmap;
    QLabel* Text;
public: //does friend function must be public?
    void ChangeRetDecoration(GraphItemModel* gdm) const;
    void SetColorEditPIndex(GraphItemModel* gdm, QPersistentModelIndex index) const;
};

class ColorDelegateForList: public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ColorDelegateForList(QObject *parent=0):QStyledItemDelegate(parent){}
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

class LineWidthDelegate: public CommonGraphDataDelegate
{
    Q_OBJECT
public:
    explicit LineWidthDelegate(QObject *parent=0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
};

class ScatterDelegate: public CommonGraphDataDelegate
{
    Q_OBJECT
public:
    explicit ScatterDelegate(QObject *parent=0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
};
//GraphDataTableView
class GraphDataTableView: public QTableView
{
public:
    explicit GraphDataTableView(QWidget *parent = 0);
protected:
    void keyPressEvent(QKeyEvent* event);
};

//GraphItemModel
class GraphItemModel: public QAbstractTableModel
{
    Q_OBJECT
    enum Column {
        cName,
        cSourceFile,
        cColor,
        cLineType,
        cLineWidth,
        cScatter
    };

    const static int COLUMNS_NUMBER=6;
    const static int COLOR_NUMBER=8;
    const static int SCATTER_NUMBER=5;
    struct ColorMapItem
    {
        QColor color;
        QString string;
    };
    const static ColorMapItem ColorMap[COLOR_NUMBER];
    const static QCPScatterStyle::ScatterShape ScatterMap[SCATTER_NUMBER];
public:
    GraphItemModel(QList<GraphItem>* pgraphlist, QCustomPlot* pcutomplot, QObject *parent = 0);
    ~GraphItemModel();

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &index = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool insertGraphItem(int row, const QList<GraphItem*>& data);
    bool deleteGraphItem(int row);
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) Q_DECL_OVERRIDE;
    int getCOLOR_NUMBER() const {return COLOR_NUMBER;}
    QColor getColorMapColor(int i) const {return ColorMap[i].color;}//think about &
    QString getColorMapString(int i) const {return ColorMap[i].string;}
    QVariant getColorByName(const QString& colorname) const;
    QCPScatterStyle::ScatterShape getScatter(int i) const {return ScatterMap[i];}
    QVariant getNumberByScatter(QCPScatterStyle::ScatterShape scattershape) const;
private:
    QList<GraphItem>* pGraphList;
    QCustomPlot* pCustomPlot; //pointer to related QCutsomPlot (actually EXQCustomPlot)
    bool bRetDecorate;
    QPersistentModelIndex ColorEditPIndex;
    friend void ColorDelegate::ChangeRetDecoration(GraphItemModel* gdm) const;
    friend void ColorDelegate::SetColorEditPIndex(GraphItemModel* gdm, QPersistentModelIndex index) const;
    //void replotPlots() const {pCustomPlot->replot();}
signals:
    void needReplot();
    void needRescaleReplot();
};

#endif // GRAPHITEMMODEL_H
