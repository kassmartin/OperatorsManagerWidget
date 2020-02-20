#pragma once

#include "AbstractData.hpp"
/*!
 * \brief The CountryData struct
 *
 * code - country short code string.
 */
struct CountryData : AbstractData
{
    CountryData(const QString &name, int mcc, const QString &code)
        : AbstractData(name, mcc), code(code) {}

    QString code;
};

