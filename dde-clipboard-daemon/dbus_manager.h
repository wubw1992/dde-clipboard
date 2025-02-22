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
#ifndef DBUSMANAGER_H
#define DBUSMANAGER_H

#include <QObject>
#include <QMap>
#include <QDBusContext>

class QLibrary;
class DBusManager : public QObject, public QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.deepin.dde.Clipboard")
    Q_CLASSINFO("D-Bus Path", "/com/deepin/dde/Clipboard")

public:
    static DBusManager *instance( QObject *parent = nullptr);

public Q_SLOTS:
    void Load(const QString &fileName);
    void UnLoad(const QString &name);
    bool IsRunning(const QString &name);
    QStringList PluginList();
    void LoadAllPlugins();

Q_SIGNALS:
    void PluginLoaded(const QString &name);
    void PluginUnLoaded(const QString &name);

private:
    DBusManager( QObject *parent = nullptr);
    ~ DBusManager();
    struct PluginInfo{
        QString name;
        QString version;
        QString service;
        bool enabled = true;
    };

    const QString getPluginPath();
    void resolveInfo(QByteArray data, PluginInfo &info);

private:
    static DBusManager *m_instance;
    QMap<QString /*name*/, QPair<QString/*fileName*/, QLibrary * /*lib*/>> m_map;
};

#endif // DBUSMANAGER_H
