#pragma once

#include <QTreeView>

#include "DBManager.hpp"
#include "OperatorEditDialog.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class OperatorsManagerWidget; }
QT_END_NAMESPACE

class QPushButton;

class OperatorsManagerWidget : public QTreeView
{
    Q_OBJECT

public:
    /*!
     * \param[in] parent Parent widget pointer.
     *
     * Includes creating of floating button for adding operators.
     */
    OperatorsManagerWidget(QWidget *parent = nullptr);

private slots:
    /// Just empty slot that write to debug console.
    void emptySlot(int mcc, int mnc);
    /*!
     * \brief onItemClicked
     * \param index
     */
    void onItemClicked(const QModelIndex &index);
    /*!
     * \param[in] index Index of double clicked item.
     *
     * Calls OperatorEditDialog instance with item from index.
     */
    void onItemDoubleClicked(const QModelIndex &index);
    /*!
     * \param[in] data New data object.
     *
     * Notifies model and database to update instance with new data.
     */
    void saveOperator(const OperatorData &data);
    /*!
     * \param mcc MCC of country for database search
     *
     * Searches and constructs icon path. Calls setIconPath method of OperatorEditDialog instance.
     */
    void onCountryIconRequest(int mcc);

private:
    /// Initializes floating button for operators adding.
    void initFloatingAddOperatorButton();
    /// Initializes model and delegate for ui tree view.
    void setViewModel();

protected:
    /// Resize event override includes floating button positioning.
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    DBManager pDBManager;
    QPushButton *pAddButton;
    OperatorEditDialog *pOperatorEditDialog;
};
