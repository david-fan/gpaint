/*
 * This source file is part of EasyPaint.
 *
 * Copyright (c) 2012 EasyPaint <https://github.com/Gr1N/EasyPaint>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "datasingleton.h"

#include <QtCore/QSettings>

DataSingleton* DataSingleton::m_pInstance = 0;

DataSingleton::DataSingleton()
{
    mPrimaryColor = Qt::black;
    mSecondaryColor = Qt::white;
    mPenSize = 1;
    mTextFont = QFont("Times", 12);
    mCurrentInstrument = NONE_INSTRUMENT;
    mPreviousInstrument = NONE_INSTRUMENT;
    mIsInitialized = false;
    readSetting();
    readState();
}

DataSingleton* DataSingleton::Instance()
{
    if(!m_pInstance)
        m_pInstance = new DataSingleton;

    return m_pInstance;
}

void DataSingleton::readSetting()
{
    QSettings settings;
    mBaseSize = settings.value("/Settings/BaseSize", QSize(800, 600)).toSize();
    mIsAutoSave = settings.value("/Settings/IsAutoSave", false).toBool();
    mAutoSaveInterval = settings.value("/Settings/AutoSaveInterval", 300).toInt();
    mHistoryDepth = settings.value("/Settings/HistoryDepth", 40).toInt();
    mAppLanguage = settings.value("/Settings/AppLanguage", "system").toString();
    mIsRestoreWindowSize = settings.value("/Settings/IsRestoreWindowSize", true).toBool();
    mIsAskCanvasSize = settings.value("/Settings/IsAskCanvasSize", true).toBool();
}

void DataSingleton::writeSettings()
{
    QSettings settings;
    settings.setValue("/Settings/BaseSize", mBaseSize);
    settings.setValue("/Settings/IsAutoSave", mIsAutoSave);
    settings.setValue("/Settings/AutoSaveInterval", mAutoSaveInterval);
    settings.setValue("/Settings/HistoryDepth", mHistoryDepth);
    settings.setValue("/Settings/AppLanguage", mAppLanguage);
    settings.setValue("/Settings/IsRestoreWindowSize", mIsRestoreWindowSize);
    settings.setValue("/Settings/IsAskCanvasSize", mIsAskCanvasSize);
}

void DataSingleton::readState()
{
    QSettings settings;
    mWindowSize = settings.value("/State/WindowSize", QSize()).toSize();
}

void DataSingleton::writeState()
{
    QSettings settings;
    if (mWindowSize.isValid()) {
        settings.setValue("/State/WindowSize", mWindowSize);
    }
}
