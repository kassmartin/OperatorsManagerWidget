#pragma once

#include <QString>

#include "AbstractPainter.hpp"

struct CountryPainter : AbstractPainter
{
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               TreeNode *node) const override;

private:
    const QString pIconPathTemplate = "Icons/Countries/%1.png";
};

