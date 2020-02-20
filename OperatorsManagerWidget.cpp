#include <QPushButton>
#include <QResizeEvent>

#include <QDebug>

#include "OperatorsManagerWidget.hpp"
#include "ui_OperatorsManagerWidget.h"
#include "OperatorsTreeModel/OperatorsTreeModel.hpp"
#include "OperatorsTreeModel/LabelViewDelegate.hpp"

OperatorsManagerWidget::OperatorsManagerWidget(QWidget *parent)
    : QTreeView(parent), pDBManager("system.db", this),
      pAddButton(nullptr), pOperatorEditDialog(new OperatorEditDialog(&pDBManager, this))
{
    // OperatorEditDialog connections
    connect(pOperatorEditDialog, &OperatorEditDialog::saveOperator,
            this, &OperatorsManagerWidget::saveOperator);

    initFloatingAddOperatorButton();
    setViewModel();
    setHeaderHidden(true);
}

void OperatorsManagerWidget::onItemDoubleClicked(const QModelIndex &index)
{
    auto node = static_cast<TreeNode*>(index.internalPointer());
    if (node == nullptr) { return; }

    if (node->type() == TreeNode::Operator) {
        auto data = dynamic_cast<OperatorData*>(node->dataPtr());
        if (data != nullptr) {
            pOperatorEditDialog->show(data);
        }
    }
}

void OperatorsManagerWidget::saveOperator(const OperatorData &data)
{
    auto operatorsModel = qobject_cast<OperatorsTreeModel*>(model());
    if (operatorsModel != nullptr) {
        operatorsModel->setOperator(data);
    }
    pDBManager.setOperator(data);
}

void OperatorsManagerWidget::initFloatingAddOperatorButton()
{
    const QSize buttonSize(36, 36);
    const QString iconPath(":/ui/icons/plus.svg");

    if (pAddButton == nullptr) {
        pAddButton = new QPushButton(this);
    }
    pAddButton->setFlat(true);
    pAddButton->setIcon(QIcon(iconPath));
    pAddButton->setIconSize(buttonSize);
    pAddButton->resize(buttonSize);

    connect(pAddButton, SIGNAL(clicked()),
            pOperatorEditDialog, SLOT(show()));
}

void OperatorsManagerWidget::setViewModel()
{
    auto model = new OperatorsTreeModel(pDBManager.getOperatorsList(), this);

    setItemDelegate(new LabelViewDelegate(this));
    setModel(model);

    connect(this, &QTreeView::clicked,
            this, &OperatorsManagerWidget::onItemClicked);
    connect(this, &QTreeView::doubleClicked,
            this, &OperatorsManagerWidget::onItemDoubleClicked);
}

void OperatorsManagerWidget::resizeEvent(QResizeEvent *event)
{
    const int buttonWidgetSizeOffset = 16;

    pAddButton->move(size().width() - (pAddButton->width() + buttonWidgetSizeOffset),
                     size().height() - (pAddButton->height() + buttonWidgetSizeOffset));

    QWidget::resizeEvent(event);
}
