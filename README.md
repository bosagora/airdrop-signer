# BOSAgora Airdrop Signer
Desktop application for signing your airdrop address
에어드롭 주소에 서명하기 위한 데스크탑 애플리케이션

# Usage
Simply download a release / pre-built binary and input your BOS secret seed and ethereum address.
Your BOS address will be displayed when you enter your secret seed,
and a signature will appear when you enter your secret seed and ethereum address.

# Is it safe to enter my seed ?
This application does not perform any network communication. We cannot see your seed.
If you want, you can run this disconnected from the Internet.

# Compilation

First, you need to install the Qt toolsuite to compile this software.
We recommend Qt 5.12.1, which we used for development.
Open the project using Qt creator and follow the instructions according to your platform.

## Windows

You need to download [libsodium](https://libsodium.gitbook.io/doc/installation#pre-built-libraries)
and install it under `res/sodium/.

First, copy the `include` folder to `res/sodium/include/`.
Second, install the dynamically built library.
If you downloaded `libsodium-1.0.17-msvc` for example, copy everything under `x64/Release/vXXX/dynamic/`
to `res/sodium/`. `vXXX` is defined by your MSVC version.

## Mac OS

Run `brew install pkg-config libsodium`.

## Linux

Make sure you have `pkg-config` and `libsodium` (or `libsodium-dev`) installed.
