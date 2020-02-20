#pragma once

#include "AbstractPainter.hpp"

struct OperatorPainter : AbstractPainter
{
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               TreeNode *node) const override;

private:
    const QString pIconPathTemplate = "Icons/Operators/%1_%2.png";
    const QString pLabelTemplate = "%1 (%2, %3)";
};

