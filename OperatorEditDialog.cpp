#include <QDebug>
#include <QFileInfo>

#include "OperatorEditDialog.hpp"
#include "ui_OperatorEditDialog.h"
#include "OperatorsTreeModel/NodeDatas/OperatorData.hpp"
#include "DBManager.hpp"

OperatorEditDialog::OperatorEditDialog(DBManager *database, QWidget *parent)
    : QDialog(parent), ui(new Ui::OperatorEditDialog), pDatabase(database)
{
    ui->setupUi(this);
    manageIcons();
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

void OperatorEditDialog::closeEvent(QCloseEvent *event)
{
    ui->operatorNameInput->clear();
    ui->mccInput->clear();
    ui->mncInput->clear();

    QDialog::closeEvent(event);
}

void OperatorEditDialog::manageIcons()
{
    const QString countryIconsPathTemplate = "Icons/Countries/%1.png";
    const QString operatorIconsPathTemplate = "Icons/Operators/%1_%2.png";
    const QString defaultIconPath = ":/ui/icons/question.svg";
    const int countryIconSize = ui->countryIconLabel->height();
    QString countryIconPath = defaultIconPath;
    QString operatorIconPath = defaultIconPath;

    QString mcc = ui->mccInput->text();
    QString mnc = ui->mncInput->text();
    if (!mcc.isEmpty()) {
        QString countryCode = pDatabase->getCountryCode(mcc);
        if (!countryCode.isEmpty()) {
            countryIconPath = countryIconsPathTemplate.arg(countryCode);
        }

        if (!mnc.isEmpty()) {
            QString tempIconPath = operatorIconsPathTemplate.arg(mcc, mnc);
            if (QFileInfo::exists(tempIconPath)) {
                operatorIconPath = tempIconPath;
            }
        }
    }

    QPixmap countryIcon(countryIconPath);
    countryIcon = countryIcon.scaled(countryIconSize, countryIconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->countryIconLabel->setPixmap(countryIcon);

    setWindowIcon(QIcon(operatorIconPath));
}

void OperatorEditDialog::onSaveButtonClicked()
{
    emit saveOperator(OperatorData (
        ui->operatorNameInput->text(),
        ui->mccInput->text().toUInt(),
        ui->mncInput->text().toUInt()));
    close();
}
