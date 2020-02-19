#pragma once

#include <QAbstractItemModel>
#include <QList>
#include <QSqlQuery>

#include <memory>

#include "TreeNode.hpp"

using DatabaseData = QPair<QSqlQuery, QMap<QString, unsigned>>;

class OperatorsTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    OperatorsTreeModel(const DatabaseData &data, QObject *parent = nullptr);

    void setOperator(const OperatorData &data);

    QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

private:
    void modelFromDatabase(const DatabaseData &data);

private:
    std::unique_ptr<TreeNode> pRootItem;
};

