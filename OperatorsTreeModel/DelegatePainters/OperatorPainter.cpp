#include <QApplication>
#include <QPainter>

#include "OperatorPainter.hpp"
#include "../TreeNode.hpp"

void OperatorPainter::paint(QPainter *painter, const QStyleOptionViewItem &option,
                            TreeNode *node) const
{
    auto operatorData = dynamic_cast<OperatorData*>(node->dataPtr());
    if (operatorData == nullptr) { return; }

    QString labelText = pLabelTemplate.arg(operatorData->name,
                                           QString::number(operatorData->mcc),
                                           QString::number(operatorData->mnc));
    QPixmap icon(pIconPathTemplate.arg(QString::number(operatorData->mcc),
                                       QString::number(operatorData->mnc)));
    QRect textRect = QApplication::style()->subElementRect(QStyle::SE_ItemViewItemText, &option);
    QRect iconRect = textRect;
    QFontMetrics fontMetrics(painter->font());

    textRect.setX(textRect.x() + textRect.height() + pElementsOffset);
    textRect.setWidth(fontMetrics.horizontalAdvance(labelText));
    iconRect.setWidth(iconRect.height());

    if (option.state & QStyle::State_Selected ||
        option.state & QStyle::State_MouseOver) {
        QPixmap plusIcon(":/ui/icons/plus.svg");
        QRect plusIconRect = iconRect;
        plusIcon = plusIcon.scaled(iconRect.width(), iconRect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        plusIconRect.setX(textRect.x() + textRect.width() + pElementsOffset);
        painter->drawPixmap(plusIconRect, plusIcon);
    }

    if (icon.isNull()) {
        icon = QPixmap(":/ui/icons/question.svg");
    }
    icon = icon.scaled(iconRect.width(), iconRect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(iconRect, icon);

    painter->drawText(textRect, option.displayAlignment, labelText);
}
