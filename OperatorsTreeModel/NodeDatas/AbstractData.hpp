#pragma once

#include <QString>
/*!
 * \brief The AbstractData struct
 *
 * Represents base data structure.
 * Contains common fields:
 *  name - in CountryData name of country;
 *         in OperatorData name of operator;
 *  mcc - MCC code of country.
 */
struct AbstractData
{
    AbstractData(const QString &name, int mcc)
        : name(name), mcc(mcc) {}
    virtual ~AbstractData() {}

    QString name;
    unsigned mcc;
};
