#pragma once

#include <QStyledItemDelegate>
/*!
 * \brief The LabelViewDelegate class
 *
 * Represents different paint types system for treeview labels.
 */
class LabelViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    LabelViewDelegate(QObject* parent = nullptr);
    /// Draws needed stuff according to index inner pointer data type.
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
    /// Returns size that entry takes on view.
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

