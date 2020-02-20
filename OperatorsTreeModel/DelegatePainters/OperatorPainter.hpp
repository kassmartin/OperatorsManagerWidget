#pragma once

#include "AbstractPainter.hpp"
/*!
 * \brief The OperatorPainter struct
 *
 * Represents how operator label will be drawn.
 */
struct OperatorPainter : AbstractPainter
{
    /// Paints operator icon, label and button icon.
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               TreeNode *node) const override;

private:
    const QString pIconPathTemplate = "Icons/Operators/%1_%2.png";
    const QString pLabelTemplate = "%1 (%2, %3)";
};

