QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    OperatorEditDialog.cpp \
    OperatorsTreeModel/DelegatePainters/CountryPainter.cpp \
    OperatorsTreeModel/DelegatePainters/OperatorPainter.cpp \
    OperatorsTreeModel/LabelViewDelegate.cpp \
    OperatorsTreeModel/OperatorsTreeModel.cpp \
    OperatorsTreeModel/TreeNode.cpp \
    main.cpp \
    OperatorsManagerWidget.cpp \
    DBManager.cpp

HEADERS += \
    OperatorEditDialog.hpp \
    OperatorsManagerWidget.hpp \
    DBManager.hpp \
    OperatorsTreeModel/DelegatePainters/AbstractPainter.hpp \
    OperatorsTreeModel/DelegatePainters/CountryPainter.hpp \
    OperatorsTreeModel/DelegatePainters/DelegatePainters \
    OperatorsTreeModel/DelegatePainters/OperatorPainter.hpp \
    OperatorsTreeModel/LabelViewDelegate.hpp \
    OperatorsTreeModel/NodeDatas/AbstractData.hpp \
    OperatorsTreeModel/NodeDatas/CountryData.hpp \
    OperatorsTreeModel/NodeDatas/NodeDatas \
    OperatorsTreeModel/NodeDatas/OperatorData.hpp \
    OperatorsTreeModel/OperatorsTreeModel.hpp \
    OperatorsTreeModel/TreeNode.hpp

FORMS += \
    OperatorEditDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
