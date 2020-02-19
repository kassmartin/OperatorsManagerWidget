#include <QPushButton>
#include <QResizeEvent>

#include "OperatorsManagerWidget.hpp"
#include "ui_OperatorsManagerWidget.h"
#include "OperatorEditDialog.hpp"
#include "OperatorsTreeModel/OperatorsTreeModel.hpp"
#include "OperatorsTreeModel/LabelViewDelegate.hpp"

OperatorsManagerWidget::OperatorsManagerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::OperatorsManagerWidget), pAddButtonPtr(nullptr)
    , pDBManager("system.db", this)
{
    ui->setupUi(this);
    createFloatingAddOperatorButton();
    setViewModel();
}

OperatorsManagerWidget::~OperatorsManagerWidget()
{
    delete ui;
}

void OperatorsManagerWidget::onAddOperatorButtonClicked()
{
    auto dialog = std::make_unique<OperatorEditDialog>(new OperatorEditDialog(this));
    dialog->exec();
}

void OperatorsManagerWidget::createFloatingAddOperatorButton()
{
    const QSize buttonSize(36, 36);
    const QString iconPath(":/ui/icons/plus.svg");

    pAddButtonPtr = new QPushButton(this);
    pAddButtonPtr->setFlat(true);
    pAddButtonPtr->setIcon(QIcon(iconPath));
    pAddButtonPtr->setIconSize(buttonSize);
    pAddButtonPtr->resize(buttonSize);

    connect(pAddButtonPtr, &QPushButton::clicked,
            this, &OperatorsManagerWidget::onAddOperatorButtonClicked);
}

void OperatorsManagerWidget::setViewModel()
{
    auto model = new OperatorsTreeModel(pDBManager, ui->operatorsTreeView);

    ui->operatorsTreeView->setItemDelegate(new LabelViewDelegate(ui->operatorsTreeView));
    ui->operatorsTreeView->setModel(model);
}

void OperatorsManagerWidget::resizeEvent(QResizeEvent *event)
{
    const int buttonWidgetSizeOffset = 8;
    const QSize windowSize = ui->operatorsTreeView->size();

    pAddButtonPtr->move(windowSize.width() - (pAddButtonPtr->width() + buttonWidgetSizeOffset),
                        windowSize.height() - (pAddButtonPtr->height() + buttonWidgetSizeOffset));

    QWidget::resizeEvent(event);
}
