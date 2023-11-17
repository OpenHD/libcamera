/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2021, Raspberry Pi Ltd
 *
 * cam_helper_ov64a40.cpp - camera information for ov64a40 sensor
 */

#include <assert.h>

#include "cam_helper.h"

using namespace RPiController;

class CamHelperOv64a40 : public CamHelper
{
public:
	CamHelperOv64a40();
	uint32_t gainCode(double gain) const override;
	double gain(uint32_t gainCode) const override;
	void getDelays(int &exposureDelay, int &gainDelay,
		       int &vblankDelay, int &hblankDelay) const override;
	double getModeSensitivity(const CameraMode &mode) const override;

private:
	/*
	 * Smallest difference between the frame length and integration time,
	 * in units of lines.
	 */
	static constexpr int frameIntegrationDiff = 4;
};

CamHelperOv64a40::CamHelperOv64a40()
	: CamHelper({}, frameIntegrationDiff)
{
}

uint32_t CamHelperOv64a40::gainCode(double gain) const
{
	return static_cast<uint32_t>(gain * 128.0);
}

double CamHelperOv64a40::gain(uint32_t gainCode) const
{
	return static_cast<double>(gainCode) / 128.0;
}

void CamHelperOv64a40::getDelays(int &exposureDelay, int &gainDelay,
				 int &vblankDelay, int &hblankDelay) const
{
	/* The driver appears to behave as follows: */
	exposureDelay = 2;
	gainDelay = 2;
	vblankDelay = 2;
	hblankDelay = 2;
}

double CamHelperOv64a40::getModeSensitivity(const CameraMode &mode) const
{
	if (mode.binX >= 2 && mode.scaleX >= 4) {
        return 4.0;
	} else if (mode.binX >= 2 && mode.scaleX >= 2) {
		return 2.0;
	} else {
		return 1.0;
	}
}

static CamHelper *create()
{
	return new CamHelperOv64a40();
}

static RegisterCamHelper reg("ov64a40", &create);