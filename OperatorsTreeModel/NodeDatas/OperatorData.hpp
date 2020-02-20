#pragma once

#include "AbstractData.hpp"
/*!
 * \brief The OperatorData struct
 *
 * mnc - operator MNC code number.
 */
struct OperatorData : AbstractData
{
    OperatorData(const QString &name, int mcc, int mnc)
        : AbstractData(name, mcc), mnc(mnc) {}

    unsigned mnc;
};
