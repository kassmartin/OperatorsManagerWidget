#include "OperatorsTreeModel.hpp"

OperatorsTreeModel::OperatorsTreeModel(const DBManager &database, QObject *parent)
    : QAbstractItemModel(parent), pRootItem(new TreeNode)
{
    modelFromDatabase(database);
}

QModelIndex OperatorsTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeNode *parentItem;

    if (!parent.isValid())
        parentItem = pRootItem.get();
    else
        parentItem = static_cast<TreeNode*>(parent.internalPointer());

    TreeNode *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex OperatorsTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    auto *childItem = static_cast<TreeNode*>(child.internalPointer());
    TreeNode *parentItem = childItem->parentNode();

    if (parentItem == pRootItem.get())
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int OperatorsTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeNode *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = pRootItem.get();
    else
        parentItem = static_cast<TreeNode*>(parent.internalPointer());

    return parentItem->childCount();
}

int OperatorsTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant OperatorsTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    auto *item = static_cast<TreeNode*>(index.internalPointer());

    return item->data();
}

void OperatorsTreeModel::modelFromDatabase(const DBManager &database)
{
    QSqlQuery query = database.getOperatorsList();
    TreeNode *currentCountry = nullptr;

    while (query.next()) {
        QString country = query.value(0).toString();
        if (currentCountry == nullptr ||
            country != currentCountry->data(0)) {
            currentCountry = new TreeNode(TreeNode::Country, {
                country,
                query.value(2).toString(),
                query.value(1).toInt()
            }, pRootItem.get());
            pRootItem->appendChild(currentCountry);
        }
        auto newOperator = new TreeNode(TreeNode::Operator, {
            query.value(5).toString(),
            query.value(1).toInt(),
            query.value(4).toInt(),
            query.value(3).toInt()
        }, currentCountry);
        currentCountry->appendChild(newOperator);
    }
}
