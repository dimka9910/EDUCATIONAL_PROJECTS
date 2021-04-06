#include "recordstreeview.h"
#include "recordtreemodel.h"
#include <QMouseEvent>
#include <QDebug>

#include <QGlobalStatic>//del me!

RecordsTreeView::RecordsTreeView(QWidget *parent):QTreeView(parent)
{
    rightClickIndex=QModelIndex();
}

void RecordsTreeView::mousePressEvent(QMouseEvent* event)
{
    QTreeView::mousePressEvent(event);
    switch (event->button()){
    case Qt::LeftButton:
        break;
    case Qt::RightButton:
        rightClickIndex = indexAt(QPoint(event->x(), event->y()));
        break;
    }
}

void RecordsTreeView::mouseReleaseEvent(QMouseEvent* event)
{
    QModelIndex index = indexAt(QPoint(event->x(), event->y()));
    QTreeView::mouseReleaseEvent(event);
    switch (event->button()){
    case Qt::LeftButton:
        break;
    case Qt::RightButton:
        if (index==rightClickIndex){
            emit showContextMenu(index, QPoint(event->x(), event->y()));
        }
        break;
    }
}

//Q_GLOBAL_STATIC(QEmptyItemModel, qEmptyModel)

//void RecordsTreeView::setModel(QAbstractItemModel *model)
//{
//    QAbstractItemView::setModel(model);
////    Q_D(QAbstractItemView);

////    if (model == this->model())
////        return;
////    if (this->model() && this->model() != qEmptyModel()) {
////        disconnect(this->model(), SIGNAL(destroyed()),
////                   this, SLOT(_q_modelDestroyed()));
////        disconnect(this->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
////                   this, SLOT(dataChanged(QModelIndex,QModelIndex,QVector<int>)));
////        disconnect(this->model(), SIGNAL(headerDataChanged(Qt::Orientation,int,int)),
////                   this, SLOT(_q_headerDataChanged()));
////        disconnect(this->model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
////                   this, SLOT(rowsInserted(QModelIndex,int,int)));
////        disconnect(this->model(), SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
////                   this, SLOT(rowsAboutToBeRemoved(QModelIndex,int,int)));
////        disconnect(this->model(), SIGNAL(rowsRemoved(QModelIndex,int,int)),
////                   this, SLOT(_q_rowsRemoved(QModelIndex,int,int)));
////        disconnect(this->model(), SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)),
////                   this, SLOT(_q_rowsMoved(QModelIndex,int,int,QModelIndex,int)));
////        disconnect(this->model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
////                   this, SLOT(_q_rowsInserted(QModelIndex,int,int)));
////        disconnect(this->model(), SIGNAL(columnsAboutToBeRemoved(QModelIndex,int,int)),
////                   this, SLOT(_q_columnsAboutToBeRemoved(QModelIndex,int,int)));
////        disconnect(this->model(), SIGNAL(columnsRemoved(QModelIndex,int,int)),
////                   this, SLOT(_q_columnsRemoved(QModelIndex,int,int)));
////        disconnect(this->model(), SIGNAL(columnsInserted(QModelIndex,int,int)),
////                   this, SLOT(_q_columnsInserted(QModelIndex,int,int)));
////        disconnect(this->model(), SIGNAL(columnsMoved(QModelIndex,int,int,QModelIndex,int)),
////                   this, SLOT(_q_columnsMoved(QModelIndex,int,int,QModelIndex,int)));

////        disconnect(this->model(), SIGNAL(modelReset()), this, SLOT(reset()));
////        disconnect(this->model(), SIGNAL(layoutChanged()), this, SLOT(_q_layoutChanged()));
////    }
////    //this->model() = (model ? model : qEmptyModel());

////    // These asserts do basic sanity checking of the model
////    Q_ASSERT_X(this->model()->index(0,0) == this->model()->index(0,0),
////               "QAbstractItemView::setModel",
////               "A model should return the exact same index "
////               "(including its internal id/pointer) when asked for it twice in a row.");
////    Q_ASSERT_X(!this->model()->index(0,0).parent().isValid(),
////               "QAbstractItemView::setModel",
////               "The parent of a top level index should be invalid");

////    if (this->model() != qEmptyModel()) {
////        connect(this->model(), SIGNAL(destroyed()),
////                this, SLOT(_q_modelDestroyed()));
////        connect(this->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
////                this, SLOT(dataChanged(QModelIndex,QModelIndex,QVector<int>)));
////        connect(this->model(), SIGNAL(headerDataChanged(Qt::Orientation,int,int)),
////                this, SLOT(_q_headerDataChanged()));
////        connect(this->model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
////                this, SLOT(rowsInserted(QModelIndex,int,int)));
////        connect(this->model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
////                this, SLOT(_q_rowsInserted(QModelIndex,int,int)));
////        connect(this->model(), SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
////                this, SLOT(rowsAboutToBeRemoved(QModelIndex,int,int)));
////        connect(this->model(), SIGNAL(rowsRemoved(QModelIndex,int,int)),
////                this, SLOT(_q_rowsRemoved(QModelIndex,int,int)));
////        connect(this->model(), SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)),
////                this, SLOT(_q_rowsMoved(QModelIndex,int,int,QModelIndex,int)));
////        connect(this->model(), SIGNAL(columnsAboutToBeRemoved(QModelIndex,int,int)),
////                this, SLOT(_q_columnsAboutToBeRemoved(QModelIndex,int,int)));
////        connect(this->model(), SIGNAL(columnsRemoved(QModelIndex,int,int)),
////                this, SLOT(_q_columnsRemoved(QModelIndex,int,int)));
////        connect(this->model(), SIGNAL(columnsInserted(QModelIndex,int,int)),
////                this, SLOT(_q_columnsInserted(QModelIndex,int,int)));
////        connect(this->model(), SIGNAL(columnsMoved(QModelIndex,int,int,QModelIndex,int)),
////                this, SLOT(_q_columnsMoved(QModelIndex,int,int,QModelIndex,int)));

////        connect(this->model(), SIGNAL(modelReset()), this, SLOT(reset()));
////        connect(this->model(), SIGNAL(layoutChanged()), this, SLOT(_q_layoutChanged()));
////    }

////    QItemSelectionModel *selection_model = new QItemSelectionModel(this->model(), this);
////    connect(this->model(), SIGNAL(destroyed()), selection_model, SLOT(deleteLater()));
////    setSelectionModel(selection_model);

////    reset(); // kill editors, set new root and do layout
//}

void RecordsTreeView::newEmptyGroup()
{
    dynamic_cast<RecordTreeModel*>(model())->newEmptyGroup(rightClickIndex);
}

void RecordsTreeView::newEmptyProbeFile()
{
    dynamic_cast<RecordTreeModel*>(model())->newEmptyProbeFile();
}

void RecordsTreeView::deleteRecord()
{
    dynamic_cast<RecordTreeModel*>(model())->deleteRecord(rightClickIndex);
}

void RecordsTreeView::deleteGroup()
{
   dynamic_cast<RecordTreeModel*>(model())->deleteGroup(rightClickIndex);
}

void RecordsTreeView::deleteProbeFile()
{
    dynamic_cast<RecordTreeModel*>(model())->deleteProbeFile(rightClickIndex);
}

void RecordsTreeView::cutRecord()
{
    dynamic_cast<RecordTreeModel*>(model())->cutRecord(rightClickIndex);
}

void RecordsTreeView::copyRecord()
{
    dynamic_cast<RecordTreeModel*>(model())->copyRecord(rightClickIndex);
}

void RecordsTreeView::pasteRecord()
{
    dynamic_cast<RecordTreeModel*>(model())->pasteRecord(rightClickIndex);
}

void RecordsTreeView::copyGroup()
{
    dynamic_cast<RecordTreeModel*>(model())->copyGroup(rightClickIndex);
}

void RecordsTreeView::pasteGroup()
{
    dynamic_cast<RecordTreeModel*>(model())->pasteGroup(rightClickIndex);
}
