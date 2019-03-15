# Libsodium directory for Windows

Since Windows doesn't have proper package management,
to build on Windows you need to manually put the libsodium lib here.

Expected structure is simple, copy the `include` file from libsodium release verbatim
in this folder, and copy the relevant library objects.

E.g.:
- include/sodium.h
- include/sodium/...
- libsodium.dll / libsodium.a