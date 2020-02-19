#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPair>

struct OperatorData;

class DBManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * \param dbPath Relative path to database file.
     * \param parent Parent object.
     *
     * Connects to database.
     */
    explicit DBManager(const QString &dbPath, QObject *parent = nullptr);

    /*!
     * Executes "select" query and constructs database keys.
     * \return Pair of QSqlQuery and Keys Map.
     * QSqlQuery object - return table from database.
     * Map contains human-readable keys in assosiations with numeric columns positions in
     *  return table.
     */
    QPair<QSqlQuery, QMap<QString, unsigned>> getOperatorsList() const;
    /*!
     * \param mcc Operator mcc for search.
     * \return Returns operator code string. If not exists - empty string returns.
     */
    QString getCountryCode(const QString &mcc) const;
    /*!
     * \param data New operator data object.
     *
     * Checks if operator exists: if true - updates row; false - inserts new operator row.
     */
    void setOperator(const OperatorData &data);

private:
    QSqlDatabase pConnection;
};

