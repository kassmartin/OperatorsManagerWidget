#pragma once

#include "AbstractData.hpp"

struct CountryData : AbstractData
{
    CountryData(const QString &name, int mcc, const QString &code)
        : AbstractData(name, mcc), code(code) {}

    QString code;
};

