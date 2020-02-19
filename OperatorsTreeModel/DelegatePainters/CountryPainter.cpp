#include <QApplication>
#include <QPainter>

#include "CountryPainter.hpp"
#include "../TreeNode.hpp"

void CountryPainter::paint(QPainter *painter, const QStyleOptionViewItem &option,
                           const TreeNode* node) const
{
    auto countryData = dynamic_cast<CountryData*>(node->dataPtr());
    if (countryData == nullptr) { return; }

    QPixmap icon(pIconPathTemplate.arg(countryData->code));
    QRect textRect = QApplication::style()->subElementRect(QStyle::SE_ItemViewItemText, &option);
    QRect iconRect = textRect;

    textRect.setX(textRect.x() + textRect.height() + pElementsOffset);
    iconRect.setWidth(iconRect.height());

    if (icon.isNull()) {
        icon = QPixmap(":/ui/icons/question.svg");
    }
    icon = icon.scaled(iconRect.width(), iconRect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    painter->drawPixmap(iconRect, icon);

    painter->drawText(textRect, option.displayAlignment, countryData->name);
}
