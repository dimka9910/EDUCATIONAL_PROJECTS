#ifndef RECORDSTREEVIEW_H
#define RECORDSTREEVIEW_H

#include <QTreeView>

class QEmptyItemModel : public QAbstractItemModel
{
public:
    explicit QEmptyItemModel(QObject *parent = 0) : QAbstractItemModel(parent) {}
    QModelIndex index(int, int, const QModelIndex &) const Q_DECL_OVERRIDE { return QModelIndex(); }
    QModelIndex parent(const QModelIndex &) const Q_DECL_OVERRIDE { return QModelIndex(); }
    int rowCount(const QModelIndex &) const Q_DECL_OVERRIDE { return 0; }
    int columnCount(const QModelIndex &) const Q_DECL_OVERRIDE { return 0; }
    bool hasChildren(const QModelIndex &) const Q_DECL_OVERRIDE { return false; }
    QVariant data(const QModelIndex &, int) const Q_DECL_OVERRIDE { return QVariant(); }
};

class RecordsTreeView: public QTreeView
{
    Q_OBJECT
public:
    explicit RecordsTreeView(QWidget* parent=0);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    //void setModel(QAbstractItemModel *model) Q_DECL_OVERRIDE;
public slots:
    void newEmptyGroup();
    void newEmptyProbeFile();
    void deleteRecord();
    void deleteGroup();
    void deleteProbeFile();
    void cutRecord();
    void copyRecord();
    void pasteRecord();

    void copyGroup();
    void pasteGroup();

private:
    QPersistentModelIndex rightClickIndex;
signals:
    void showContextMenu(const QModelIndex& index, QPoint point);

};

#endif // RECORDSTREEVIEW_H
