#pragma once

#include <QStyleOptionViewItem>

class QPainter;
class TreeNode;
/*!
 * \brief The AbstractPainter struct
 *
 * Base painter struct for different paint implementations.
 */
struct AbstractPainter
{
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
               TreeNode* node) const = 0;
    virtual ~AbstractPainter() {};

protected:
    const int pElementsOffset = 4;
};

