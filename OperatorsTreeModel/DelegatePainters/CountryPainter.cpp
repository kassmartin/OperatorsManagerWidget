#include <QApplication>
#include <QPainter>

#include "CountryPainter.hpp"
#include "../TreeNode.hpp"
#include "IconDealer.hpp"

void CountryPainter::paint(QPainter *painter, const QStyleOptionViewItem &option,
                           TreeNode* node) const
{
    auto countryData = dynamic_cast<CountryData*>(node->dataPtr());
    if (countryData == nullptr) { return; }

    QPixmap icon(node->getIcon());
    QRect textRect = QApplication::style()->subElementRect(QStyle::SE_ItemViewItemText, &option);
    QRect iconRect = textRect;
    QFontMetrics fontMetrics(painter->font());
    QSize nodeViewSize;

    iconRect.setWidth(iconRect.height());
    textRect.setX(textRect.x() + iconRect.width() + pElementsOffset);
    textRect.setWidth(fontMetrics.horizontalAdvance(countryData->name));

    nodeViewSize.setWidth(iconRect.width() + pElementsOffset + textRect.width());
    nodeViewSize.setHeight(textRect.height());
    node->setSize(nodeViewSize);

    if (icon.isNull()) {
        icon = IconDealer::getDefaultUnknownIcon();
    }
    icon = icon.scaled(iconRect.width(), iconRect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    painter->drawPixmap(iconRect, icon);

    painter->drawText(textRect, option.displayAlignment, countryData->name);
}
