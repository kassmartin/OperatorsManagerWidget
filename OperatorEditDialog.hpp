#pragma once

#include <QDialog>

namespace Ui {
class OperatorEditDialog;
}

struct OperatorData;
class DBManager;

class OperatorEditDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \param database Database pointer for future icons operations.
     * \param parent Parent widget.
     */
    OperatorEditDialog(DBManager *database = nullptr, QWidget *parent = nullptr);
    ~OperatorEditDialog();

public slots:
    /// Default view for new operator creation.
    void show();
    /// View for operator editing.
    void show(OperatorData *data);

signals:
    /// Emits when "Save" button clicked.
    void saveOperator(const OperatorData &data);

private:
    /// Override consists inputs clearing. Calls QDialog::closeEvent.
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    /// Searches and sets icons.
    void manageIcons();
    /// Generates new data package and emits saveOperator signal.
    void onSaveButtonClicked();

private:
    Ui::OperatorEditDialog *ui;
    DBManager *pDatabase;
};

