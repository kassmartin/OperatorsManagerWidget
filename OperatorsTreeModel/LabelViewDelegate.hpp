#pragma once

#include <QStyledItemDelegate>

class LabelViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    LabelViewDelegate(QObject* parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
};

