/********************************************************************
 KWin - the KDE window manager
 This file is part of the KDE project.

Copyright (C) 2018 Vlad Zagorodniy <vladzzag@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/

#ifndef KWIN_GLRENDERBUFFER_H
#define KWIN_GLRENDERBUFFER_H

#include <kwinglutils_export.h>

#include <QExplicitlySharedDataPointer>
#include <QSize>

#include <epoxy/gl.h>


namespace KWin
{

class KWINGLUTILS_EXPORT GLRenderbuffer
{
public:
    GLRenderbuffer(int width, int height, int samples = 0,
                   GLenum format = GL_RGBA8,
                   GLenum target = GL_RENDERBUFFER);
    GLRenderbuffer(const QSize &size, int samples = 0,
                   GLenum format = GL_RGBA8,
                   GLenum target = GL_RENDERBUFFER);
    ~GLRenderbuffer();

    void bind();
    void unbind();

    GLuint renderbuffer() const;
    GLenum target() const;
    GLenum internalFormat() const;
    int samples() const;

    int width() const;
    int height() const;
    QSize size() const;

    void resize(int width, int height);
    void resize(const QSize &size);

private:
    class Private;

private:
    QExplicitlySharedDataPointer<Private> d;
};

} // namespace KWin

#endif // KWIN_GLRENDERBUFFER_H
