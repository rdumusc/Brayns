/* Copyright (c) 2015-2017, EPFL/Blue Brain Project
 * All rights reserved. Do not distribute without permission.
 * Responsible Author: Cyrille Favreau <cyrille.favreau@epfl.ch>
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

#ifndef OSPRAYSCENE_H
#define OSPRAYSCENE_H

#include <brayns/common/scene/Scene.h>
#include <brayns/common/types.h>

#include <ospray.h>

namespace brayns
{
/**

   OSPRay specific scene

   This object is the OSPRay specific implementation of a scene

*/
class OSPRayScene : public Scene
{
public:
    OSPRayScene(ParametersManager& parametersManager,
                const size_t memoryManagementFlags);
    ~OSPRayScene();

    /** @copydoc Scene::commit */
    void commit() final;

    /** @copydoc Scene::commitLights */
    bool commitLights() final;

    /** @copydoc Scene::commitTransferFunctionData */
    bool commitTransferFunctionData() final;

    SharedDataVolumePtr createSharedDataVolume(const Vector3ui& dimensions,
                                               const Vector3f& spacing,
                                               const DataType type) const final;
    BrickedVolumePtr createBrickedVolume(const Vector3ui& dimensions,
                                         const Vector3f& spacing,
                                         const DataType type) const final;
    ModelPtr createModel() const final;

    OSPModel getModel() { return _rootModel; }
    OSPModel simulationModelImpl() { return _rootSimulationModel; }
    OSPData lightData() { return _ospLightData; }
    OSPData simulationData() { return _ospSimulationData; }
    OSPData transferFunctionDiffuseData()
    {
        return _ospTransferFunctionDiffuseData;
    }
    OSPData transferFunctionEmissionData()
    {
        return _ospTransferFunctionEmissionData;
    }

private:
    void _commitSimulationData();
    bool _commitVolumeData();

    OSPModel _rootModel{nullptr};
    OSPModel _rootSimulationModel{nullptr};

    std::vector<OSPLight> _ospLights;
    OSPData _ospLightData{nullptr};

    OSPData _ospSimulationData{nullptr};

    OSPTransferFunction _ospTransferFunction{nullptr};

    OSPData _ospTransferFunctionEmissionData{nullptr};
    OSPData _ospTransferFunctionDiffuseData{nullptr};

    size_t _memoryManagementFlags{0};

    ModelDescriptors _activeModels;
};
}
#endif // OSPRAYSCENE_H
