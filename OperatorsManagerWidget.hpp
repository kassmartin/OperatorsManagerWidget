#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class OperatorsManagerWidget; }
QT_END_NAMESPACE

class QPushButton;

class OperatorsManagerWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \param[in] parent Parent widget pointer.
     *
     * Includes creating of floating button for adding operators.
     */
    OperatorsManagerWidget(QWidget *parent = nullptr);
    ~OperatorsManagerWidget();

private slots:
    /// Creates operator adding dialog.
    void onAddOperatorButtonClicked();

private:
    /// Initializes floating button for operators adding.
    void createFloatingAddOperatorButton();

protected:
    /// Resize event override includes floating button movement.
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::OperatorsManagerWidget *ui;
    QPushButton *pAddButtonPtr;

};
