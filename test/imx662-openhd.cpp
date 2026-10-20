/* SPDX-License-Identifier: BSD-2-Clause */
// Standalone validation against an already-built matching libcamera core.
#include <cmath>
#include <iostream>
#include <memory>
#include "libcamera/base/log.h"
#include "libcamera/internal/camera_sensor_properties.h"
#include "src/ipa/rpi/cam_helper/cam_helper.h"
#include "src/ipa/rpi/controller/controller.h"
namespace libcamera { LOG_DEFINE_CATEGORY(IPARPI) }

int main(int argc, char **argv)
{
    if (argc != 2)
        return 2;
    std::unique_ptr<RPiController::CamHelper> helper(RPiController::CamHelper::create("imx662"));
    if (!helper || helper->gainCode(1.0) != 0 || helper->gainCode(1000) != 100)
        return 1;
    for (unsigned int code = 0; code <= 100; ++code) {
        if (std::abs(int(helper->gainCode(helper->gain(code))) - int(code)) > 1)
            return 1;
    }
    int exposure, gain, vblank, hblank;
    helper->getDelays(exposure, gain, vblank, hblank);
    if (exposure != 2 || gain != 2 || vblank != 2 || hblank != 2)
        return 1;
    CameraMode mode{};
    mode.width = 1936; mode.height = 1100;
    mode.pixelRate = 148500000;
    mode.minLineLength = mode.maxLineLength = std::chrono::microseconds(20);
    mode.minFrameLength = 1250; mode.maxFrameLength = 0xfffff;
    helper->setCameraMode(mode);
    libcamera::utils::Duration requestedExposure = std::chrono::microseconds(25000);
    auto blanking = helper->getBlanking(requestedExposure,
                                      std::chrono::microseconds(25000),
                                      std::chrono::microseconds(25000));
    if (helper->exposureLines(requestedExposure, mode.minLineLength) >
        mode.height + blanking.first - 4)
        return 1;
    auto *properties = libcamera::CameraSensorProperties::get("imx662");
    if (!properties || properties->unitCellSize.width != 2900 ||
        properties->unitCellSize.height != 2900)
        return 1;
    RPiController::Controller controller;
    if (controller.read(argv[1]) || controller.getTarget() != "bcm2835")
        return 1;
    controller.initialise();
    for (auto name : {"rpi.agc", "rpi.awb", "rpi.alsc", "rpi.black_level", "rpi.ccm"})
        if (!controller.getAlgorithm(name))
            return 1;
    std::cout << "IMX662 helper, gain/blanking limits, sensor properties and VC4 tuning passed\n";
}
