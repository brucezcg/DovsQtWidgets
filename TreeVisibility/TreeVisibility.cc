#include <QApplication>
#include <QPushButton>
#include <QTreeView>
#include <memory>
#include <QStandardItemModel>
#include <QList>
#include <iostream>
#include <map>

using namespace std;

#include "TreeVisibility.h"

class TreeVisibility::Priv {
public:
    QStandardItemModel* model { nullptr };
    map<QString, QStandardItem*> items;
};

// Constructor
TreeVisibility::TreeVisibility(QWidget *parent)
    : QTreeView(parent)
{
    d = new Priv;
    d->model = new QStandardItemModel;
    setModel(d->model);
    QObject::connect(d->model,
                     SIGNAL(itemChanged(QStandardItem*)),
                     this,
                     SLOT(onItemChanged(QStandardItem*)));
}

TreeVisibility::~TreeVisibility()
{
    delete d->model;
}

// Create a checkable item row.
QStandardItem *TreeVisibility::NewCheckableItem(QString label)
{
    const Qt::ItemFlags Flags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
    auto item = new QStandardItem(label);
    item->setCheckState(Qt::CheckState(2));
    item->setFlags(Flags);
    return item;
}

void TreeVisibility::addItem(const QString& path)
{
    auto pathList = path.split("/", QString::SkipEmptyParts);
    int n = pathList.length();
    QString subPath = "";
    QStandardItem *parent = nullptr;
    for (int i=0; i<n; i++) {
        subPath += QString("/") + pathList[i];
        auto it = d->items.find(subPath);
        if (it== d->items.end()) {
            QStandardItem *item = NewCheckableItem(pathList[i]);
            d->items[subPath] = item;
            if (i==0)
                d->model->appendRow(item);
            else
                parent->appendRow(item);
            parent = item;
        }
        else
            parent = it->second;
    }

    // Expand all - TBDov - only expand the added item!
    QModelIndexList indexes = d->model->match(d->model->index(0,0),
                                              Qt::DisplayRole,
                                              "*", -1, Qt::MatchWildcard|Qt::MatchRecursive);
    for (auto& index : indexes)
	expand(index);
}

bool TreeVisibility::visible(const QString& path)
{
    auto it = d->items.find(path);
    if (it == d->items.end())
        return false; // False by default, or should we throw an exception?
    return it->second->checkState() == 2;
}

// Debug routine to dump the visibility of all the nodes
void TreeVisibility::dumpVisibility()
{
    for (const auto& it : d->items)
        printf("%s -> %d\n",
               it.first.toUtf8().data(),
               visible(it.first));
}

// Used for recursively creating a flat list of all items in a model.
void TreeVisibility::buildItemList(QStandardItem *item, QList<QStandardItem*>& acc)
{
    acc.append(item);
    int childrenNum = item->rowCount();
    for (int i=0; i<childrenNum; i++) 
        buildItemList(item->child(i), acc);
}

void TreeVisibility::onItemChanged(QStandardItem*item)
{
    printf("Item %s has changed!\n", item->text().toUtf8().data());
    auto checkState = item->checkState();

    // Make all children the same, but don't emit signals for them
    QList<QStandardItem*> children;
    buildItemList(item, children);
    for (auto child : children) {
        bool oldState = this->blockSignals(true);
        child->setCheckState(checkState);
        this->blockSignals(oldState);
    }

    emit visibilityChanged();
}
