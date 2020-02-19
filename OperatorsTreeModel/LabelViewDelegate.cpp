#include <QApplication>
#include <QPainter>
#include <QPixmap>
#include <QIcon>

#include "LabelViewDelegate.hpp"
#include "TreeNode.hpp"
#include "DelegatePainters/DelegatePainters"

LabelViewDelegate::LabelViewDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void LabelViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    auto element = static_cast<TreeNode*>(index.internalPointer());
    if (element != nullptr) {
        std::unique_ptr<AbstractPainter> elementPainter;
        switch (element->type()) {
        case TreeNode::Country:
            elementPainter = std::make_unique<CountryPainter>();
            break;
        case TreeNode::Operator:
            elementPainter = std::make_unique<OperatorPainter>();
            break;
        default:
            QStyledItemDelegate::paint(painter, option, index);
            return;
        }
        elementPainter->paint(painter, option, element);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
