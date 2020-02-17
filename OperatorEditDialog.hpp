#pragma once

#include <QDialog>

namespace Ui {
class OperatorEditDialog;
}

struct OperatorData
{
    QString name;
    unsigned mcc;
    unsigned mnc;
};

class OperatorEditDialog : public QDialog
{
    Q_OBJECT

public:
    /// Default init for new operator adding.
    OperatorEditDialog(QWidget *parent = nullptr);

    /*!
     * \param[in] data Operator information.
     *
     * Constructor for operator editting.
     */
    OperatorEditDialog(const OperatorData &data, QWidget *parent = nullptr);

    ~OperatorEditDialog();

signals:
    /// Emits when "Save" button clicked.
    void saveOperator(const OperatorData data);

private:
    /// Sets connections for ui.
    void init();

private slots:
    /// Searches and sets dialog and country icons.
    void searchAndSetIcons();

private:
    Ui::OperatorEditDialog *ui;
};

