# OpenHD native IMX662 integration (Pi VC4)

The fork already contains an IMX662 camera helper and `bcm2835` tuning JSON,
but the VC4 Meson data list did not install the tuning. It is now included in
`/usr/share/libcamera/ipa/rpi/vc4/imx662.json` in the normal libcamera-openhd
package. No unrelated PISP tuning is changed.

The IMX662 helper now matches OpenHD's Linux 6.1.29 raw sensor driver: analogue
gain codes 0..100 and a four-line integration margin. Static sensor properties
provide 2900 nm pixels; no unsupported test-pattern controls are advertised.
Use native camera profile 47, not the separate VEYE GX ISP profile 64.

The existing tuning is retained. Module/lens-specific image quality, physical
clock/lane wiring, sensor capture, flips, sustained encoding and RF operation
still need hardware verification. This does not add HDR support.

For a focused host check against a matching previously built libcamera core:

```sh
bash test/run-imx662-openhd.sh /path/to/libcamera-core-build /tmp/imx662-test
```

This compiles the actual IMX662 helper, sensor metadata and Pi controller
algorithms, and checks helper registration, gain conversion/clamping, exposure
margin, sensor properties and VC4 tuning initialization. It does not require
the binary-only Pivariety SDK, but it is not a full ARM libcamera package build.
See OpenHD-KernelBuilder `additional/imx662/README.md` for kernel/overlay setup
and the physical capture checklist.
