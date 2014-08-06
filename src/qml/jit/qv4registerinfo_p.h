/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtQml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QV4REGISTERINFO_P_H
#define QV4REGISTERINFO_P_H

#include <QtCore/QString>

QT_BEGIN_NAMESPACE

namespace QV4 {
namespace JIT {

class RegisterInfo
{
public:
    enum { InvalidRegister = (1 << 29) - 1 };
    enum SavedBy { CallerSaved, CalleeSaved };
    enum RegisterType { RegularRegister, FloatingPointRegister };
    enum Usage { Predefined, RegAlloc };

public:
    RegisterInfo()
        : _savedBy(CallerSaved)
        , _usage(Predefined)
        , _type(RegularRegister)
        , _reg(InvalidRegister)
    {}

    RegisterInfo(int reg, const QString &prettyName, RegisterType type, SavedBy savedBy, Usage usage)
        : _prettyName(prettyName)
        , _savedBy(savedBy)
        , _usage(usage)
        , _type(type)
        , _reg(reg)
    {}

    bool operator==(const RegisterInfo &other) const
    { return _type == other._type && _reg == other._reg; }

    bool isValid() const { return _reg != InvalidRegister; }
    template <typename T> T reg() const { return static_cast<T>(_reg); }
    QString prettyName() const { return _prettyName; }
    bool isCallerSaved() const { return _savedBy == CallerSaved; }
    bool isCalleeSaved() const { return _savedBy == CalleeSaved; }
    bool isFloatingPoint() const { return _type == FloatingPointRegister; }
    bool isRegularRegister() const { return _type == RegularRegister; }
    bool useForRegAlloc() const { return _usage == RegAlloc; }
    bool isPredefined() const { return _usage == Predefined; }

private:
    QString _prettyName;
    unsigned _savedBy : 1;
    unsigned _usage   : 1;
    unsigned _type    : 1;
    unsigned _reg     : 29;
};
typedef QVector<RegisterInfo> RegisterInformation;

} // JIT namespace
} // QV4 namespace

QT_END_NAMESPACE

#endif // QV4REGISTERINFO_P_H