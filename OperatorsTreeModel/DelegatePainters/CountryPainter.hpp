#pragma once

#include <QString>

#include "AbstractPainter.hpp"
/*!
 * \brief The CountryPainter struct
 *
 * Represents how country label will be drawn.
 */
struct CountryPainter : AbstractPainter
{
    /// Paints operator icon and label.
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               TreeNode *node) const override;
};

