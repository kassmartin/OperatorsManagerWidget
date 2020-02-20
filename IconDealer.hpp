#pragma once

#include <QPixmap>
#include <QString>
#include <QFileInfo>

struct IconDealer
{
    static QPixmap getCountryIcon(const QString &code, int size = 16) {
        const QString pathTemplate("Icons/Countries/%1.png");
        return getIcon(pathTemplate.arg(code), size);
    }

    static QPixmap getOperatorIcon(int mcc, int mnc, int size = 16) {
        const QString pathTemplate("Icons/Operators/%1_%2.png");
        return getIcon(pathTemplate.arg(QString::number(mcc),
                                         QString::number(mnc)),
                       size);
    }

    static QPixmap getDefaultUnknownIcon(int size = 16) {
        const QString iconPath(":/ui/icons/question.svg");
        return getIcon(iconPath, size);
    }

    static QPixmap getPlusIcon(int size = 16) {
        const QString iconPath(":/ui/icons/plus.svg");
        return getIcon(iconPath, size);
    }

    static QPixmap getIcon(const QString &path, int size = 16) {
        if (QFileInfo::exists(path)) {
            QPixmap icon(path);
            return icon.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        return getDefaultUnknownIcon(size);
    }
};
