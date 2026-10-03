# IMX415 on the OpenHD VC4 stack

The IMX415 camera helper and VC4 tuning are backported from Raspberry Pi
libcamera `v0.7.1+rpt20260609`, commit
`06c385619acb10bbfb33f52f3abeb8f8c095f42b`. Source paths:

- `src/ipa/rpi/cam_helper/cam_helper_imx415.cpp`
- `src/ipa/rpi/vc4/data/imx415.json`

The JSON uses the existing version-2 tuning format and bcm2835 target. Meson
ships it with the VC4 tuning files in the normal libcamera-openhd package.
This is the upstream Arducam B0569 calibration; other module lenses and colour
filters require image-quality validation and potentially recalibration.

The helper uses logarithmic 0.3 dB gain codes, an eight-line integration margin
and no embedded metadata. Its maximum gain code is adapted to 100, matching
OpenHD's 6.1.29 IMX415 kernel backport. Pixel properties specify 1.45 um cells.

Validation compiled the helper against this fork's libcamera core and compiled
the existing Pi controller/algorithms. Helper registration and gain roundtrips
passed; the controller loaded and initialized every algorithm in imx415.json.
This host test does not establish capture on Pi hardware or a complete armhf
package build. No PISP tuning or Pi 5 integration is included.

OpenHD's kernel backport adds default two-lane H/V 2/2 binning at 60 fps,
using RAW12 output, a 1782 Mbps lane rate and a 27 or 37.125 MHz input clock.
The binned readout includes margins (1944x1097); OpenHD defaults to 1080p60.
The driver expresses blanking/exposure in output lines, accounting for two XHS
periods per line. The helper retains its conservative eight-output-line shutter
margin, also suitable for the retained all-pixel modes. This mode uses the
OpenIPC 1080p binning register reference with Sony's two-lane timing. Actual
frame rate, RAW12 levels, AE/AWB and lens calibration still need camera testing.
