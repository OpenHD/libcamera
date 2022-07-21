/* SPDX-License-Identifier: LGPL-2.1-or-later */
/*
 * Copyright (C) 2021-2022, Ideas On Board
 *
 * ipa_context.cpp - RkISP1 IPA Context
 */

#include "ipa_context.h"

/**
 * \file ipa_context.h
 * \brief Context and state information shared between the algorithms
 */

namespace libcamera::ipa::rkisp1 {

/**
 * \struct IPASessionConfiguration
 * \brief Session configuration for the IPA module
 *
 * The session configuration contains all IPA configuration parameters that
 * remain constant during the capture session, from IPA module start to stop.
 * It is typically set during the configure() operation of the IPA module, but
 * may also be updated in the start() operation.
 */

/**
 * \var IPASessionConfiguration::agc
 * \brief AGC parameters configuration of the IPA
 *
 * \var IPASessionConfiguration::agc.minShutterSpeed
 * \brief Minimum shutter speed supported with the configured sensor
 *
 * \var IPASessionConfiguration::agc.maxShutterSpeed
 * \brief Maximum shutter speed supported with the configured sensor
 *
 * \var IPASessionConfiguration::agc.minAnalogueGain
 * \brief Minimum analogue gain supported with the configured sensor
 *
 * \var IPASessionConfiguration::agc.maxAnalogueGain
 * \brief Maximum analogue gain supported with the configured sensor
 *
 * \var IPASessionConfiguration::agc.measureWindow
 * \brief AGC measure window
 *
 * \var IPASessionConfiguration::hw
 * \brief RkISP1-specific hardware information
 *
 * \var IPASessionConfiguration::hw.revision
 * \brief Hardware revision of the ISP
 */

/**
 * \var IPASessionConfiguration::awb
 * \brief AWB parameters configuration of the IPA
 *
 * \var IPASessionConfiguration::awb.measureWindow
 * \brief AWB measure window
 *
 * \var IPASessionConfiguration::awb.enabled
 * \brief Indicates if the AWB hardware is enabled and applies colour gains
 *
 * The AWB module of the ISP applies colour gains and computes statistics. It is
 * enabled when the AWB algorithm is loaded, regardless of whether the algorithm
 * operates in manual or automatic mode.
 */

/**
 * \var IPASessionConfiguration::lsc
 * \brief Lens Shading Correction configuration of the IPA
 *
 * \var IPASessionConfiguration::lsc.enabled
 * \brief Indicates if the LSC hardware is enabled
 */

/**
 * \var IPASessionConfiguration::sensor
 * \brief Sensor-specific configuration of the IPA
 *
 * \var IPASessionConfiguration::sensor.lineDuration
 * \brief Line duration in microseconds
 *
 * \var IPASessionConfiguration::sensor.size
 * \brief Sensor output resolution
 */

/**
 * \struct IPAActiveState
 * \brief Active state for algorithms
 *
 * The active state stores algorithm-specific data that needs to be shared
 * between multiple algorithms and the IPA module. It is accessible through the
 * IPAContext structure.
 *
 * \todo Split the data contained in this structure between the active state
 * and the frame contexts.
 *
 * Each of the fields in the active state belongs to either a specific
 * algorithm, or to the top-level IPA module. A field may be read by any
 * algorithm, but should only be written by its owner.
 */

/**
 * \var IPAActiveState::agc
 * \brief State for the Automatic Gain Control algorithm
 *
 * The exposure and gain determined are expected to be applied to the sensor
 * at the earliest opportunity.
 *
 * \var IPAActiveState::agc.exposure
 * \brief Exposure time expressed as a number of lines
 *
 * \var IPAActiveState::agc.gain
 * \brief Analogue gain multiplier
 *
 * The gain should be adapted to the sensor specific gain code before applying.
 */

/**
 * \var IPAActiveState::awb
 * \brief State for the Automatic White Balance algorithm
 *
 * \struct IPAActiveState::awb.gains
 * \brief White balance gains
 *
 * \var IPAActiveState::awb.gains.red
 * \brief White balance gain for R channel
 *
 * \var IPAActiveState::awb.gains.green
 * \brief White balance gain for G channel
 *
 * \var IPAActiveState::awb.gains.blue
 * \brief White balance gain for B channel
 *
 * \var IPAActiveState::awb.temperatureK
 * \brief Estimated color temperature
 *
 * \var IPAActiveState::awb.autoEnabled
 * \brief Whether the Auto White Balance algorithm is enabled
 */

/**
 * \var IPAActiveState::cproc
 * \brief State for the Color Processing algorithm
 *
 * \struct IPAActiveState::cproc.brightness
 * \brief Brightness level
 *
 * \var IPAActiveState::cproc.contrast
 * \brief Contrast level
 *
 * \var IPAActiveState::cproc.saturation
 * \brief Saturation level
 *
 * \var IPAActiveState::cproc.updateParams
 * \brief Indicates if ISP parameters need to be updated
 */

/**
 * \var IPAActiveState::dpf
 * \brief State for the Denoise Pre-Filter algorithm
 *
 * \var IPAActiveState::dpf.denoise
 * \brief Indicates if denoise is activated
 *
 * \var IPAActiveState::dpf.updateParams
 * \brief Indicates if ISP parameters need to be updated
 */

/**
 * \var IPAActiveState::filter
 * \brief State for the Filter algorithm
 *
 * \struct IPAActiveState::filter.denoise
 * \brief Denoising level
 *
 * \var IPAActiveState::filter.sharpness
 * \brief Sharpness level
 *
 * \var IPAActiveState::filter.updateParams
 * \brief Indicates if ISP parameters need to be updated
 */

/**
 * \var IPAActiveState::sensor
 * \brief Effective sensor values
 *
 * \var IPAActiveState::sensor.exposure
 * \brief Exposure time expressed as a number of lines
 *
 * \var IPAActiveState::sensor.gain
 * \brief Analogue gain multiplier
 */

/**
 * \var IPAActiveState::frameCount
 * \brief Counter of requests queued to the IPA module
 *
 * The counter is reset to 0 when the IPA module is configured, and is
 * incremented for each request being queued, after calling the
 * Algorithm::prepare() function of all algorithms.
 */

/**
 * \struct IPAFrameContext
 * \brief Per-frame context for algorithms
 *
 * This structure is currently unused and will be replaced by a real per-frame
 * context.
 */

/**
 * \struct IPAContext
 * \brief Global IPA context data shared between all algorithms
 *
 * \var IPAContext::configuration
 * \brief The IPA session configuration, immutable during the session
 *
 * \var IPAContext::activeState
 * \brief The IPA active state, storing the latest state for all algorithms
 *
 * \todo Introduce per-frame contexts
 */

} /* namespace libcamera::ipa::rkisp1 */
