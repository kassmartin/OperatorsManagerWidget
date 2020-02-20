#pragma once

#include <QStyleOptionViewItem>

class QPainter;
class TreeNode;

struct AbstractPainter
{
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
               TreeNode* node) const = 0;

protected:
    const int pElementsOffset = 4;
};

