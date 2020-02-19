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
    /*!
     * \param[in] index Index of double clicked item.
     *
     * Calls OperatorEditDialog instance with item from index.
     */
    void onTreeItemDoubleClicked(const QModelIndex &index);
    /*!
     * \param[in] data New data object.
     *
     * Notifies model and database to update instance with new data.
     */
    void saveOperator(const OperatorData &data);

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
