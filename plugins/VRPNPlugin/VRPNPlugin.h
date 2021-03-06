/* Copyright (c) 2018, EPFL/Blue Brain Project
 * All rights reserved. Do not distribute without permission.
 *
 * This file is part of Brayns <https://github.com/BlueBrain/Brayns>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include <vrpnplugin/defines.h>

#include <brayns/common/types.h>
#include <brayns/pluginapi/ExtensionPlugin.h>

#include <vrpn_Tracker.h>

#ifdef VRPNPLUGIN_USE_LIBUV
#include <uv.h>
#endif

namespace brayns
{
class VRPNPlugin : public ExtensionPlugin
{
public:
    VRPNPlugin(PluginAPI* api, const std::string& vrpnName);
    ~VRPNPlugin();

    void preRender() final;

#ifdef VRPNPLUGIN_USE_LIBUV
    void resumeRenderingIfTrackerIsActive();
#endif

private:
    PluginAPI* _api = nullptr;
    Camera& _camera;
    vrpn_Tracker_Remote _vrpnTracker;

#ifdef VRPNPLUGIN_USE_LIBUV
    struct LibuvDeleter
    {
        void operator()(uv_timer_t* timer)
        {
            uv_timer_stop(timer);
            uv_close(reinterpret_cast<uv_handle_t*>(timer),
                     [](uv_handle_t* handle) { delete handle; });
        }
    };
    std::unique_ptr<uv_timer_t, LibuvDeleter> _idleTimer;

    void _setupIdleTimer();
#endif
};
}
