#pragma once

#include <QAbstractItemModel>
#include <QList>

#include <memory>

#include "../DBManager.hpp"
#include "TreeNode.hpp"

class OperatorsTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    OperatorsTreeModel(const DBManager &database, QObject *parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

private:
    void modelFromDatabase(const DBManager &database);

private:
    std::unique_ptr<TreeNode> pRootItem;
};

