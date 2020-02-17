#include <QDebug>

#include "OperatorEditDialog.hpp"
#include "ui_OperatorEditDialog.h"

OperatorEditDialog::OperatorEditDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::OperatorEditDialog)
{
    ui->setupUi(this);
    init();

    connect(ui->mccInput, &QLineEdit::textChanged,
            this, &OperatorEditDialog::searchAndSetIcons);
    connect(ui->mncInput, &QLineEdit::textChanged,
            this, &OperatorEditDialog::searchAndSetIcons);

    searchAndSetIcons();
}

OperatorEditDialog::OperatorEditDialog(const OperatorData &data, QWidget *parent)
    : QDialog(parent), ui(new Ui::OperatorEditDialog)
{
    ui->setupUi(this);
    init();

    ui->operatorNameInput->setText(data.name);
    ui->mccInput->setText(QString::number(data.mcc));
    ui->mccInput->setReadOnly(true);
    ui->mncInput->setText(QString::number(data.mnc));
    ui->mncInput->setReadOnly(true);

    searchAndSetIcons();
}

OperatorEditDialog::~OperatorEditDialog()
{
    delete ui;
}

void OperatorEditDialog::init()
{
    connect(ui->saveButton, &QPushButton::clicked,
            this, [&]() {
        emit saveOperator(OperatorData {
            .name = ui->operatorNameInput->text(),
            .mcc = ui->mccInput->text().toUInt(),
            .mnc = ui->mncInput->text().toUInt()
        });
        close();
    });
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &OperatorEditDialog::close);
}

void OperatorEditDialog::searchAndSetIcons()
{
    const QString defaultIconPath(":/ui/icons/question.svg");
    const int countryIconSize(ui->countryIconLabel->height());
    const QString mccCode(ui->mccInput->text());
    const QString mncCode(ui->mncInput->text());

    if (!mccCode.isEmpty() && !mncCode.isEmpty()) {

    } else {
        ui->countryIconLabel->setPixmap(QPixmap(defaultIconPath)
                                        .scaled(countryIconSize, countryIconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
