# Crane-Resources

This repo contains the localization files of Crane and the libCrane.h header to use it's functionality from other tweaks (Not supported on Crane Lite!).

## How to use libCrane

Run `install_libcrane.sh` in the `libCrane` directory to install the libcrane tbd's into theos.
Afterwards you can add libcrane to your makefile as follows:
`<YOUR_PROJECT>_LIBRARIES += crane`
Then copy libCrane.h into your project and include it, read the header to see what methods are available.

## Usage notes

Some APIs use XPC to communicate with cranehelperd so if you are trying to use libCrane from a sandboxed process, you will have to use libSandy to gain access to the `com.opa334.cranehelperd.xpc` mach service.