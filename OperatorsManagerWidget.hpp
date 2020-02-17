#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class OperatorsManagerWidget; }
QT_END_NAMESPACE

class OperatorsManagerWidget : public QWidget
{
    Q_OBJECT

public:
    OperatorsManagerWidget(QWidget *parent = nullptr);
    ~OperatorsManagerWidget();

private:
    Ui::OperatorsManagerWidget *ui;
};
