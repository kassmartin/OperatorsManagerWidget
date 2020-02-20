#include <QDebug>
#include <QFileInfo>

#include "OperatorEditDialog.hpp"
#include "ui_OperatorEditDialog.h"
#include "OperatorsTreeModel/NodeDatas/OperatorData.hpp"
#include "DBManager.hpp"

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

    setWindowIcon(QIcon(pDefaultIconPath));
    ui->countryIconLabel->setPixmap(
        QPixmap(pDefaultIconPath).scaled(countryIconSize, countryIconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

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

void OperatorEditDialog::setCountryIconPath(const QString &path)
{
    const int countryIconSize = ui->countryIconLabel->height();
    QPixmap countryIcon;

    if (QFileInfo::exists(path)) {
        countryIcon = QPixmap(path);
    } else {
        countryIcon = QPixmap(pDefaultIconPath);
    }

    countryIcon = countryIcon.scaled(countryIconSize, countryIconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->countryIconLabel->setPixmap(countryIcon);
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
    const QString operatorIconsPathTemplate = "Icons/Operators/%1_%2.png";
    QIcon operatorIcon;

    QString mcc = ui->mccInput->text();
    QString mnc = ui->mncInput->text();
    if (!mcc.isEmpty()) {
        emit requestCountryIconPath(mcc.toInt());

        if (!mnc.isEmpty()) {
            QString tempIconPath = operatorIconsPathTemplate.arg(mcc, mnc);
            if (QFileInfo::exists(tempIconPath)) {
                operatorIcon = QIcon(tempIconPath);
            } else {
                operatorIcon = QIcon(pDefaultIconPath);
            }
            setWindowIcon(operatorIcon);
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
