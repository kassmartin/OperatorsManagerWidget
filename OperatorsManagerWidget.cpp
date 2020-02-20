#include <QPushButton>
#include <QResizeEvent>

#include <QDebug>

#include "OperatorsManagerWidget.hpp"
#include "ui_OperatorsManagerWidget.h"
#include "OperatorsTreeModel/OperatorsTreeModel.hpp"
#include "OperatorsTreeModel/LabelViewDelegate.hpp"

OperatorsManagerWidget::OperatorsManagerWidget(QWidget *parent)
    : QTreeView(parent), pDBManager("system.db", this),
      pAddButton(nullptr), pOperatorEditDialog(new OperatorEditDialog(this))
{
    // OperatorEditDialog connections
    connect(pOperatorEditDialog, &OperatorEditDialog::saveOperator,
            this, &OperatorsManagerWidget::saveOperator);
    connect(pOperatorEditDialog, &OperatorEditDialog::requestCountryIconPath,
            this, &OperatorsManagerWidget::onCountryIconRequest);

    initFloatingAddOperatorButton();
    setViewModel();

    setHeaderHidden(true);
    setAttribute(Qt::WA_MouseTracking, true);
}

void OperatorsManagerWidget::emptySlot(int mcc, int mnc)
{
    qDebug() << "Empty slot with mcc: " << mcc << ", mnc: " << mnc;
}

void OperatorsManagerWidget::onItemClicked(const QModelIndex &index)
{
    auto node = static_cast<TreeNode*>(index.internalPointer());
    if (node != nullptr && node->type() == TreeNode::Operator) {    // Firstly checks nullptr
        QSize elementSize = node->getSize();
        int buttonWidth = elementSize.height();
        int minButtonPos = elementSize.width() - buttonWidth;
        int mousePointerXPos = mapFromGlobal(QCursor::pos()).x();

        if (mousePointerXPos >= minButtonPos &&
            mousePointerXPos <= elementSize.width())
        {
            auto data = dynamic_cast<OperatorData*>(node->dataPtr());
            if (data != nullptr) { emptySlot(data->mcc, data->mnc); }
        }
    }
}

void OperatorsManagerWidget::onItemDoubleClicked(const QModelIndex &index)
{
    auto node = static_cast<TreeNode*>(index.internalPointer());
    if (node != nullptr && node->type() == TreeNode::Operator) {    // Firstly checks nullptr
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

void OperatorsManagerWidget::onCountryIconRequest(int mcc)
{
    const QString pathTemplate = "Icons/Countries/%1.png";
    QString code = pDBManager.getCountryCode(mcc);
    pOperatorEditDialog->setCountryIconPath(pathTemplate.arg(code));
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

    QTreeView::resizeEvent(event);
}
