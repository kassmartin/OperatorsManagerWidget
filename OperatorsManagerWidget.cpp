#include <QPushButton>
#include <QResizeEvent>

#include <QDebug>

#include "OperatorsManagerWidget.hpp"
#include "ui_OperatorsManagerWidget.h"
#include "OperatorsTreeModel/OperatorsTreeModel.hpp"
#include "OperatorsTreeModel/LabelViewDelegate.hpp"

OperatorsManagerWidget::OperatorsManagerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::OperatorsManagerWidget), pDBManager("system.db", this),
      pAddButton(nullptr), pOperatorEditDialog(new OperatorEditDialog(&pDBManager, this))
{
    ui->setupUi(this);
    // OperatorEditDialog connections
    connect(pOperatorEditDialog, &OperatorEditDialog::saveOperator,
            this, &OperatorsManagerWidget::saveOperator);

    initFloatingAddOperatorButton();
    setViewModel();
}

OperatorsManagerWidget::~OperatorsManagerWidget()
{
    delete ui;
}

void OperatorsManagerWidget::onTreeItemDoubleClicked(const QModelIndex &index)
{
    auto node = static_cast<TreeNode*>(index.internalPointer());
    if (node->type() == TreeNode::Operator) {
        auto data = dynamic_cast<OperatorData*>(node->dataPtr());
        if (data != nullptr) {
            pOperatorEditDialog->show(data);
        }
    }
}

void OperatorsManagerWidget::saveOperator(const OperatorData &data)
{
    auto model = qobject_cast<OperatorsTreeModel*>(ui->operatorsTreeView->model());
    if (model != nullptr) {
        model->setOperator(data);
        ui->operatorsTreeView->update(); // TODO: Fix update
    }
    pDBManager.setOperator(data);
}

void OperatorsManagerWidget::initFloatingAddOperatorButton()
{
    const QSize buttonSize(36, 36);
    const QString iconPath(":/ui/icons/plus.svg");

    if (pAddButton == nullptr) {
        pAddButton = new QPushButton(ui->operatorsTreeView);
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
    auto model = new OperatorsTreeModel(pDBManager.getOperatorsList(), ui->operatorsTreeView);

    ui->operatorsTreeView->setItemDelegate(new LabelViewDelegate(ui->operatorsTreeView));
    ui->operatorsTreeView->setModel(model);

    connect(ui->operatorsTreeView, &QTreeView::doubleClicked,
            this, &OperatorsManagerWidget::onTreeItemDoubleClicked);
}

void OperatorsManagerWidget::resizeEvent(QResizeEvent *event)
{
    const int buttonWidgetSizeOffset = 16;
    const QSize windowSize = ui->operatorsTreeView->size();

    pAddButton->move(windowSize.width() - (pAddButton->width() + buttonWidgetSizeOffset),
                     windowSize.height() - (pAddButton->height() + buttonWidgetSizeOffset));

    QWidget::resizeEvent(event);
}
