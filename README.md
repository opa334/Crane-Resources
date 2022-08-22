# Crane-Resources

This repo contains the localization files of Crane and the libCrane.h header to use it's functionality from other tweaks (Not supported on Crane Lite!).

## libCrane usage notes

Some APIs use XPC to communicate with cranehelperd so if you are trying to use libCrane from a sandboxed process, you will have to use libSandy to gain access to the `com.opa334.cranehelperd.xpc` mach service.