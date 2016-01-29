/********************************************************************
 This file is part of the KDE project.

 Copyright (C) 2012 Martin Gr‰ﬂlin <mgraesslin@kde.org>
 Copyright (C) 2016 Marco Martin <mart@kde.org>

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
/*global effect, effects, animate, animationTime, Effect*/
var morphingEffect = {
    duration: animationTime(250),
    loadConfig: function () {
        "use strict";
        morphingEffect.duration = animationTime(250);
    },
    geometryChange: function (window, oldGeometry) {
        "use strict";


        if (!window.oldGeometry) {
        //    return;
        }

        var newGeometry = window.geometry;
        //window.oldGeometry = oldGeometry;
        //window.olderGeometry = oldGeometry;

        window.maximizeAnimation1 = animate({
            window: window,
            duration: morphingEffect.duration,
            animations: [{
                type: Effect.Size,
                to: {
                    value1: newGeometry.width,
                    value2: newGeometry.height
                },
                from: {
                    value1: oldGeometry.width,
                    value2: oldGeometry.height
                }
            }, {
                type: Effect.Translation,
                to: {
                    value1: 0,
                    value2: 0
                },
                from: {
                    value1: oldGeometry.x - newGeometry.x - (newGeometry.width / 2 - oldGeometry.width / 2),
                    value2: oldGeometry.y - newGeometry.y
                }
            }]
        });
        if (1||!window.resize) {
            window.maximizeAnimation2 =animate({
                window: window,
                duration: morphingEffect.duration,
                animations: [{
                    type: Effect.CrossFadePrevious,
                    to: 1.0,
                    from: 0.0
                }]
            });
        }
    },
    init: function () {
        "use strict";
        effect.configChanged.connect(morphingEffect.loadConfig);
        effects.windowGeometryShapeChanged.connect(morphingEffect.geometryChange);
    }
};
morphingEffect.init();
