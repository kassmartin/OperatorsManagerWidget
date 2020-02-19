#include <QApplication>
#include <QPainter>

#include "OperatorPainter.hpp"
#include "../TreeNode.hpp"

void OperatorPainter::paint(QPainter *painter, const QStyleOptionViewItem &option,
                            const TreeNode* node) const
{
    auto operatorData = dynamic_cast<OperatorData*>(node->dataPtr());
    if (operatorData == nullptr) { return; }

    QPixmap icon(pIconPathTemplate.arg(QString::number(operatorData->mcc),
                                       QString::number(operatorData->mnc)));
    QRect textRect = QApplication::style()->subElementRect(QStyle::SE_ItemViewItemText, &option);
    QRect iconRect = textRect;

    textRect.setX(textRect.x() + textRect.height() + pElementsOffset);
    iconRect.setWidth(iconRect.height());

    if (icon.isNull()) {
        icon = QPixmap(":/ui/icons/question.svg");
    }
    icon = icon.scaled(iconRect.width(), iconRect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    painter->drawPixmap(iconRect, icon);

    QString labelText = pLabelTemplate.arg(operatorData->name,
                                           QString::number(operatorData->mcc),
                                           QString::number(operatorData->mnc));
    painter->drawText(textRect, option.displayAlignment, labelText);
}
