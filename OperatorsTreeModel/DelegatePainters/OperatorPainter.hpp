#pragma once

#include "AbstractPainter.hpp"

struct OperatorPainter : AbstractPainter
{
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const TreeNode* node) const override;

private:
    const QString pIconPathTemplate = "Icons/Operators/%1_%2.png";
};

