#include <QDebug>
#include <QFileInfo>

#include "OperatorEditDialog.hpp"
#include "ui_OperatorEditDialog.h"
#include "OperatorsTreeModel/NodeDatas/OperatorData.hpp"
#include "IconDealer.hpp"

OperatorEditDialog::OperatorEditDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::OperatorEditDialog)
{
    ui->setupUi(this);

    // Buttons connections
    connect(ui->saveButton, &QPushButton::clicked,
            this, &OperatorEditDialog::onSaveButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &OperatorEditDialog::close);
    // Inputs connections
    connect(ui->mccInput, &QLineEdit::textChanged,
            this, &OperatorEditDialog::manageIcons);
    connect(ui->mncInput, &QLineEdit::textChanged,
            this, &OperatorEditDialog::manageIcons);
}

OperatorEditDialog::~OperatorEditDialog()
{
    delete ui;
}

void OperatorEditDialog::show()
{
    int countryIconSize = ui->countryIconLabel->height();

    setWindowIcon(QIcon(IconDealer::getDefaultUnknownIcon()));
    ui->countryIconLabel->setPixmap(IconDealer::getDefaultUnknownIcon(countryIconSize));
    ui->mccInput->setReadOnly(false);
    ui->mncInput->setReadOnly(false);

    this->exec();
}

void OperatorEditDialog::show(OperatorData *data)
{
    ui->operatorNameInput->setText(data->name);
    ui->mccInput->setText(QString::number(data->mcc));
    ui->mccInput->setReadOnly(true);
    ui->mncInput->setText(QString::number(data->mnc));
    ui->mncInput->setReadOnly(true);
    this->exec();
}

void OperatorEditDialog::setCountryIcon(const QPixmap &icon)
{
    ui->countryIconLabel->setPixmap(icon);
}

void OperatorEditDialog::closeEvent(QCloseEvent *event)
{
    ui->operatorNameInput->clear();
    ui->mccInput->clear();
    ui->mncInput->clear();

    QDialog::closeEvent(event);
}

void OperatorEditDialog::manageIcons()
{
    QString mcc = ui->mccInput->text();
    QString mnc = ui->mncInput->text();
    if (!mcc.isEmpty()) {
        int iconSize = ui->countryIconLabel->height();
        emit requestCountryIconPath(mcc.toInt(), iconSize);

        if (!mnc.isEmpty()) {
            setWindowIcon(IconDealer::getOperatorIcon(mcc.toInt(), mnc.toInt()));
        }
    }
}

void OperatorEditDialog::onSaveButtonClicked()
{
    emit saveOperator(OperatorData (
        ui->operatorNameInput->text(),
        ui->mccInput->text().toInt(),
        ui->mncInput->text().toInt()));
    close();
}
