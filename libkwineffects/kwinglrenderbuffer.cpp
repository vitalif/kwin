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

#include "kwinglrenderbuffer.h"

#include <QSharedData>


namespace KWin
{

class Q_DECL_HIDDEN GLRenderbuffer::Private : public QSharedData
{
public:
    Private();
    ~Private();

    GLuint renderbuffer = 0;
    GLenum target = GL_RENDERBUFFER;
    GLenum internalFormat = GL_RGBA8;
    int width = 0;
    int height = 0;
    int samples = 0;

private:
    Q_DISABLE_COPY(Private)
};

GLRenderbuffer::Private::Private()
{
}

GLRenderbuffer::Private::~Private()
{
    if (renderbuffer != 0) {
        glDeleteRenderbuffers(1, &renderbuffer);
    }
}

GLRenderbuffer::GLRenderbuffer(int width, int height, int samples,
                               GLenum format, GLenum target)
    : d(new GLRenderbuffer::Private)
{
    d->target = target;
    d->internalFormat = format;
    d->width = width;
    d->height = height;
    d->samples = samples;

    glGenRenderbuffers(1, &d->renderbuffer);

    bind();
    if (samples > 0) {
        glRenderbufferStorageMultisample(target, samples, format, width, height);
    } else {
        glRenderbufferStorage(target, format, width, height);
    }
    unbind();
}

GLRenderbuffer::GLRenderbuffer(const QSize &size, int samples, GLenum format, GLenum target)
    : GLRenderbuffer(size.width(), size.height(), samples, format, target)
{
}

GLRenderbuffer::~GLRenderbuffer()
{
}

void GLRenderbuffer::bind()
{
    glBindRenderbuffer(d->target, d->renderbuffer);
}

void GLRenderbuffer::unbind()
{
    glBindRenderbuffer(d->target, 0);
}

GLuint GLRenderbuffer::renderbuffer() const
{
    return d->renderbuffer;
}

GLenum GLRenderbuffer::target() const
{
    return d->target;
}

GLenum GLRenderbuffer::internalFormat() const
{
    return d->internalFormat;
}

int GLRenderbuffer::samples() const
{
    return d->samples;
}

int GLRenderbuffer::width() const
{
    return d->width;
}

int GLRenderbuffer::height() const
{
    return d->height;
}

QSize GLRenderbuffer::size() const
{
    return QSize(d->width, d->height);
}

void GLRenderbuffer::resize(int width, int height)
{
    if (d->width == width && d->height == height) {
        return;
    }

    if (d->renderbuffer != 0) {
        glDeleteRenderbuffers(1, &d->renderbuffer);
    }

    glGenRenderbuffers(1, &d->renderbuffer);

    bind();
    if (d->samples > 0) {
        glRenderbufferStorageMultisample(
            d->target, d->samples, d->internalFormat, d->width, d->height);
    } else {
        glRenderbufferStorage(d->target, d->internalFormat, d->width, d->height);
    }
    unbind();

    d->width = width;
    d->height = height;
}

void GLRenderbuffer::resize(const QSize &size)
{
    resize(size.width(), size.height());
}

}
