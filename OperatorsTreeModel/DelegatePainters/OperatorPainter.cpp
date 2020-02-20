#include <QApplication>
#include <QPainter>

#include "OperatorPainter.hpp"
#include "../TreeNode.hpp"
#include "IconDealer.hpp"

void OperatorPainter::paint(QPainter *painter, const QStyleOptionViewItem &option,
                            TreeNode *node) const
{
    auto operatorData = dynamic_cast<OperatorData*>(node->dataPtr());
    if (operatorData == nullptr) { return; }

    QString labelText = pLabelTemplate.arg(operatorData->name,
                                           QString::number(operatorData->mcc),
                                           QString::number(operatorData->mnc));
    QPixmap icon(node->getIcon());
    QRect textRect = QApplication::style()->subElementRect(QStyle::SE_ItemViewItemText, &option);
    QRect iconRect = textRect;
    QFontMetrics fontMetrics(painter->font());
    QSize nodeViewSize;

    iconRect.setWidth(iconRect.height());
    textRect.setX(textRect.x() + iconRect.width() + pElementsOffset);
    textRect.setWidth(fontMetrics.horizontalAdvance(labelText));

    nodeViewSize.setWidth(textRect.x() + textRect.width());
    nodeViewSize.setHeight(textRect.height());

    if (option.state & QStyle::State_MouseOver) {
        QPixmap plusIcon = IconDealer::getPlusIcon(iconRect.width());
        QRect plusIconRect = iconRect;
        plusIconRect.setX(textRect.x() + textRect.width() + pElementsOffset);
        painter->drawPixmap(plusIconRect, plusIcon);
        nodeViewSize.setWidth(plusIconRect.x() + plusIcon.width());
    }
    node->setSize(nodeViewSize);

    if (icon.isNull()) {
        icon = IconDealer::getDefaultUnknownIcon();
    }
    icon = icon.scaled(iconRect.width(), iconRect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(iconRect, icon);

    painter->drawText(textRect, option.displayAlignment, labelText);
}
