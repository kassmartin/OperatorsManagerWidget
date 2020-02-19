#include "OperatorsTreeModel.hpp"

OperatorsTreeModel::OperatorsTreeModel(const DatabaseData &data, QObject *parent)
    : QAbstractItemModel(parent), pRootItem(new TreeNode)
{
    modelFromDatabase(data);
}

void OperatorsTreeModel::setOperator(const OperatorData &data)
{
    for (int i = 0, count = pRootItem->childCount(); i < count; ++i) {
        auto countryNode = pRootItem->child(i);
        if (countryNode->dataPtr()->mcc == data.mcc) {
            for (int j = 0, operatorsCount = countryNode->childCount(); j < operatorsCount; ++j) {
                auto operatorNode = countryNode->child(j);
                auto operatorData = dynamic_cast<OperatorData*>(operatorNode->dataPtr());
                if (operatorData->mnc == data.mnc) {
                    operatorData->name = data.name;
                    return;
                }
            }
            countryNode->appendChild(new TreeNode(TreeNode::Operator,
                                                  new OperatorData(data),
                                                  countryNode));
        }
    }
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

void OperatorsTreeModel::modelFromDatabase(const DatabaseData &data)
{
    auto[query, dbKeys] = data;
    TreeNode *currentCountry = nullptr;

    while (query.next()) {
        QString country = query.value(dbKeys["country"]).toString();
        if (currentCountry == nullptr ||                // Firstly checks nullptr - no falls expected
            country != currentCountry->data())
        {
            auto countryData = new CountryData(
                country,
                query.value(dbKeys["mcc"]).toInt(),
                query.value(dbKeys["code"]).toString()
            );
            currentCountry = new TreeNode(TreeNode::Country, countryData, pRootItem.get());
            pRootItem->appendChild(currentCountry);
        }

        auto operatorData = new OperatorData(
            query.value(dbKeys["name"]).toString(),
            query.value(dbKeys["mcc"]).toInt(),
            query.value(dbKeys["mnc"]).toInt()
        );
        auto newOperator = new TreeNode(TreeNode::Operator, operatorData, currentCountry);
        currentCountry->appendChild(newOperator);
    }
}
