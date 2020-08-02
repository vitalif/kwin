/********************************************************************
KWin - the KDE window manager
This file is part of the KDE project.

SPDX-FileCopyrightText: 2016 Martin Gräßlin <mgraesslin@kde.org>

SPDX-License-Identifier: GPL-2.0-or-later
*********************************************************************/
#include <QClipboard>
#include <QGuiApplication>
#include <QPainter>
#include <QRasterWindow>
#include <QTimer>

class Window : public QRasterWindow
{
    Q_OBJECT
public:
    explicit Window();
    ~Window() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
};

Window::Window()
    : QRasterWindow()
{
}

Window::~Window() = default;

void Window::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::red);
}

void Window::focusInEvent(QFocusEvent *event)
{
    QRasterWindow::focusInEvent(event);
    // TODO: make it work without singleshot
    QTimer::singleShot(100,[] {
        qApp->clipboard()->setText(QStringLiteral("test"));
    });
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QScopedPointer<Window> w(new Window);
    w->setGeometry(QRect(0, 0, 100, 200));
    w->show();

    return app.exec();
}

#include "copy.moc"
