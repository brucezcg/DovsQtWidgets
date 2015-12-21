//======================================================================
//  TreeVisibility.h - 
//
//  Dov Grobgeld <dov.grobgeld@gmail.com>
//  Thu Dec 17 22:09:36 2015
//----------------------------------------------------------------------
#ifndef TREEVISIBILITY_H
#define TREEVISIBILITY_H

#include <QApplication>
#include <QStandardItem>
#include <QTreeView>

class TreeVisibility : public QTreeView {
  Q_OBJECT;

public:
    TreeVisibility(QWidget *parent=nullptr);
    ~TreeVisibility();
    void addItem(const QString& path);
    bool visible(QString path);
    void clear();

    // Debug routine that dumps the visibility of the entire tree
    void dumpVisibility();

signals:
    // A signal that something has changed. Currently don't give more specifics.
    void visibilityChanged(void);

private:
    class Priv;
    Priv * d;

    QStandardItem * NewCheckableItem(QString label);

    // recursively build up a list of all child widgets
    void buildItemList(QStandardItem *item, QList<QStandardItem*>& acc);

private slots:
  void onItemChanged(QStandardItem*);
};


#endif /* TREEVISABILITY */
