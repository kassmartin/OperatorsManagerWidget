#include <QPushButton>
#include <QResizeEvent>

#include "OperatorsManagerWidget.hpp"
#include "ui_OperatorsManagerWidget.h"
#include "OperatorEditDialog.hpp"

OperatorsManagerWidget::OperatorsManagerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::OperatorsManagerWidget), pAddButtonPtr(nullptr)
{
    ui->setupUi(this);
    createFloatingAddOperatorButton();
}

OperatorsManagerWidget::~OperatorsManagerWidget()
{
    delete ui;
}

void OperatorsManagerWidget::onAddOperatorButtonClicked()
{
    // TODO: Fill OperatorData
    OperatorData data {
        .name = "Oper",
        .mcc = 2,
        .mnc = 2
    };

    auto dialog = std::make_unique<OperatorEditDialog>(new OperatorEditDialog(data, this));
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

void OperatorsManagerWidget::resizeEvent(QResizeEvent *event)
{
    const int buttonWidgetSizeOffset = 24;
    const QSize windowSize = event->size();

    pAddButtonPtr->move(windowSize.width() - (pAddButtonPtr->width() + buttonWidgetSizeOffset),
                        windowSize.height() - (pAddButtonPtr->height() + buttonWidgetSizeOffset));

    QWidget::resizeEvent(event);
}
