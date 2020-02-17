#include "OperatorsManagerWidget.hpp"
#include "ui_OperatorsManagerWidget.h"

OperatorsManagerWidget::OperatorsManagerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OperatorsManagerWidget)
{
    ui->setupUi(this);
}

OperatorsManagerWidget::~OperatorsManagerWidget()
{
    delete ui;
}

