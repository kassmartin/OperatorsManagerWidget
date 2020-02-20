#pragma once

#include <QAbstractItemModel>
#include <QList>
#include <QSqlQuery>

#include <memory>

#include "TreeNode.hpp"

using DatabaseData = QPair<QSqlQuery, QMap<QString, unsigned>>;
/*!
 * \brief The OperatorsTreeModel class
 *
 * Represents tree-structured model.
 */
class OperatorsTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    /// Calls modelFromDatabaseData method to build inner tree-structure.
    OperatorsTreeModel(const DatabaseData &data, QObject *parent = nullptr);
    /// Checks id operator instance exists. If true - updates entry with new data.
    /// Otherwise adds new operator instance to corresponding country.
    void setOperator(const OperatorData &data);
    /// Constracts index instance.
    QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
    /// Returns parent index if parent exists. Otherwise invalid index.
    QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    /// Returns child count for spcified index.
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    /// Always 1.
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    /// Returns data by role. Not implemented as usual.
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

private:
    /// Parses database data table to tree structure.
    /// Database table must be sorted by country name.
    void modelFromDatabaseData(const DatabaseData &data);

private:
    std::unique_ptr<TreeNode> pRootItem;
};

