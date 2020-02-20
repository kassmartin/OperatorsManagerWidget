#include <QDebug>
#include <QSqlResult>

#include "DBManager.hpp"
#include "OperatorsTreeModel/NodeDatas/OperatorData.hpp"

DBManager::DBManager(const QString &dbPath, QObject *parent)
    : QObject(parent), pConnection(QSqlDatabase::addDatabase("QSQLITE"))
{
    pConnection.setDatabaseName(dbPath);
    if (!pConnection.open()) {
        qWarning() << "Open database error!";
    }
}

QPair<QSqlQuery, QMap<QString, unsigned>> DBManager::getOperatorsList() const
{
    const QMap<QString, unsigned> databaseKeys {
        { "country",    0 },
        { "code",       1 },
        { "mcc",        2 },
        { "mnc_length", 3 },
        { "mnc",        4 },
        { "name",       5 }
    };
    const QString queryString(
        "select countries.name, countries.code, countries.mcc, countries.mnc_length, "
        "operators.mnc, operators.name "
        "from countries, operators "
        "where countries.mcc == operators.mcc "
        "order by countries.name");

    return { QSqlQuery (queryString, pConnection), databaseKeys };
}

QString DBManager::getCountryCode(int mcc) const
{
    const QString queryStringTemplate(
        "select countries.code "
        "from countries "
        "where countries.mcc == '%1'");
    QSqlQuery query(queryStringTemplate.arg(QString::number(mcc)), pConnection);

    if (query.next()) {
        return query.value(0).toString();
    } 
    return {};
}

void DBManager::setOperator(const OperatorData &data)
{
    const QString existsQueryString("select * from operators "
                                    "where operators.mcc='%1' and operators.mnc='%2'");
    QSqlQuery query(existsQueryString.arg(QString::number(data.mcc),
                                          QString::number(data.mnc)), pConnection);
    if (query.next()) {
        const QString updateQueryString("update operators set name='%1' "
                                        "where mcc='%2' and mnc='%3'");
        query.exec(updateQueryString.arg(data.name,
                                         QString::number(data.mcc),
                                         QString::number(data.mnc)));
    } else {
        const QString insertQueryString("insert into operators(mcc, mnc, name) "
                                        "values('%1','%2','%3');");
        query.exec(insertQueryString.arg(QString::number(data.mcc),
                                         QString::number(data.mnc),
                                         data.name));
    }
}
