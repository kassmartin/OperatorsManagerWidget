#pragma once

#include <QString>

struct AbstractData
{
    AbstractData(const QString &name, int mcc)
        : name(name), mcc(mcc) {}
    virtual ~AbstractData() {}

    QString name;
    unsigned mcc;
};
