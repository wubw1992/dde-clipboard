/*
 * Copyright (C) 2019 ~ 2022 Uniontech Technology Co., Ltd.
 *
 * Author:     fanpengcheng <fanpengcheng@uniontech.com>
 *
 * Maintainer: fanpengcheng <fanpengcheng@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <QApplication>
#include <QDBusConnection>
#include <QDebug>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QMetaClassInfo>

#include <DLog>

#include "dbus_manager.h"

DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("deepin");
    a.setApplicationName("dde-clipboard-daemon");
    DLogManager::registerConsoleAppender();
    DLogManager::registerFileAppender();

    DBusManager *manager = DBusManager::instance();
    const QString &interface = "com.deepin.daemon.Clipboard";
    const QString &path = "/com/deepin/daemon/Clipboard";

    if (!QDBusConnection::sessionBus().registerService(interface)) {
        qDebug() << "DBus register failed, error message:" << QDBusConnection::sessionBus().lastError().message();
        exit(-1);
    }
    QDBusConnection::sessionBus().registerObject(path, manager, QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals);
    manager->LoadAllPlugins();
    qDebug() << "Everything is ok!";
    return a.exec();
}
