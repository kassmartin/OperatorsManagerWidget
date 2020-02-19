#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class DBManager : public QObject
{
    Q_OBJECT
public:
    /// Constructor connects to DB and initializes query object.
    explicit DBManager(const QString &dbPath, QObject *parent = nullptr);

    QSqlQuery getOperatorsList() const;

private:

private:
    QSqlDatabase pConnection;
};

