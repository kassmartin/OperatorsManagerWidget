#pragma once

#include <QDialog>

namespace Ui {
class OperatorEditDialog;
}

struct OperatorData;

class OperatorEditDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \param database Database pointer for future icons operations.
     * \param parent Parent widget.
     */
    OperatorEditDialog(QWidget *parent = nullptr);
    /// Just deletes ui.
    ~OperatorEditDialog();

public slots:
    /// Default view for new operator creation.
    void show();
    /*!
     * \param data Existing data of operator.
     *
     * Shows view for existing operator editting.
     */
    void show(OperatorData *data);
    /// Accepts country icon path. Check if it exists. Sets to default icon if false.
    void setCountryIconPath(const QString &path);

signals:
    /// Emits when "Save" button clicked.
    void saveOperator(const OperatorData &data);
    /// Signal to parent widget for icon search.
    void requestCountryIconPath(int mcc);

private:
    /// Override consists inputs clearing. Calls QDialog::closeEvent.
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    /// Searches and set window icon. Also requests country icon.
    void manageIcons();
    /// Generates new data package and emits saveOperator signal.
    void onSaveButtonClicked();

private:
    const QString pDefaultIconPath = ":/ui/icons/question.svg";
    Ui::OperatorEditDialog *ui;

};

