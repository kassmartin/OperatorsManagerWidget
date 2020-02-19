#pragma once

#include "AbstractData.hpp"

struct OperatorData : AbstractData
{
    OperatorData(const QString &name, int mcc, int mnc)
        : AbstractData(name, mcc), mnc(mnc) {}

    unsigned mnc;
};
