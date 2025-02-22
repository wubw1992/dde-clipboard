/*
 * Copyright (C) 2018 ~ 2025 Deepin Technology Co., Ltd.
 *
 * Author:     fanpengcheng <fanpengcheng_cm@deepin.com>
 *
 * Maintainer: fanpengcheng <fanpengcheng_cm@deepin.com>
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
#ifndef LISTDELEGATE_H
#define LISTDELEGATE_H

#include <QStyledItemDelegate>

/*!
 * \~chinese \class ItemDelegate
 * \~chinese \brief 继承于QStyledItemDelegate,QAbstractItemDelegate 是model/view架构中的用于delegate的抽象基类。
 * \~chinese 缺省的delegate实现在QItemDelegate类中提供.它可以用于Qt标准views的缺省 delegate.通过重写以下方法paint,
 * \~chinese createEditor,sizeHint,updateEditorGeometry,eventFilter提供一个自定义的委托样式
 */
class ItemDelegate : public QStyledItemDelegate
{
public:
    explicit ItemDelegate(QObject *parent = nullptr);

    /*!
     * \~chinese \name paint
     * \~chinese \brief 重写paint函数消除Qt默认提供的背景颜色,如果不重写此函数,剪切块显示时会提供一个默认的背景色
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    /*!
     * \~chinese \name createEditor
     * \~chinese \brief 重写父类的createEditor函数,创建一个自定义的编辑器
     */
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    /*!
     * \~chinese \name sizeHint
     * \~chinese \brief 返回一个推荐的窗口大小
     */
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    /*!
     * \~chinese \name updateEditorGeometry
     * \~chinese \brief 根据参数中数据项的信息设置编辑器的位置和大小
     */
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    /*!
     * \~chinese \name eventFilter
     * \~chinese \brief 过滤Qt::Key_Tab,Qt::Key_Backtab事件,将其转变为特殊按键事件，表示切换内部‘焦点’
     */
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // LISTDELEGATE_H
