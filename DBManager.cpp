#include <QDebug>

#include "DBManager.hpp"

DBManager::DBManager(const QString &dbPath, QObject *parent)
    : QObject(parent), pConnection(QSqlDatabase::addDatabase("QSQLITE"))
{
    pConnection.setDatabaseName(dbPath);
    if (!pConnection.open()) {
        qWarning() << "Open database error!";
    }
}

QSqlQuery DBManager::getOperatorsList() const
{
    const QString queryString(
        "select countries.name, countries.mcc, countries.code, countries.mnc_length, "
        "operators.mnc, operators.name "
        "from countries, operators "
        "where countries.mcc == operators.mcc "
        "order by countries.name");
    return QSqlQuery (queryString, pConnection);
}
