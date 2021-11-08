# AVIDLib
Library for interacting with assets from Valve and iD Tech games.

![CI Status](https://github.com/noodlecollie/avidlib/actions/workflows/continuous-integration.yml/badge.svg)
![Test Status](https://github.com/noodlecollie/avidlib/actions/workflows/tests.yml/badge.svg)

## What is AVID?

**AVID** is a library (or rather, collection of libraries) for reading, writing and using **a**ssets from **V**alve and **iD** Tech games. The primary purpose of AVID is to provide portable support for Half Life MDL files (because that's what I need primarily), but anything from the Quake-tech games (various versions of the BSP and MDL file formats, plus other oddities like SPZ sprites) is included in the overall scope.

## What is AVID used for?

AVID is intended to be used by programs which wish to read, write, or otherwise make use of any of the asset formats it supports. Examples include:

* Loading models for use in modern game engines
* Viewing models or maps in modder utilities
* Decompiling assets to their component sources
* Compiling assets into formats compatible with existing games like Half Life or Quake

## What language is AVID written in?

The main proportion of AVID is written in C, with the example tools in C++ (primarily because of the external libraries they rely on). C is widely supported by a variety of compilers and platforms, and so pretty much any application should be able to interface with the AVID libraries. C++-based engines will be able to use AVID's libraries directly, and other popular languages like C# and Python have existing methods of utilising native platform libraries.

AVID is C99-compliant. I believe that C99 strikes a good balance between compatibility with older software or compilers, and convenient modern language features. This is in contrast to the previous C89, upon which it adds significantly more flexibility, and the later C11, where `static_assert` is the only extra that I see as being particularly useful to this project.

AVID uses CMake as its build system. CMake is also widely supported on many different platforms, and its configuration files should be relatively easy to port to other build systems if CMake cannot be used.

## How is AVID architectured?

AVID is designed so that a developer can build libraries for only the asset formats that they need to support, in static or shared configuration. Extraneous libraries, such as for I/O and for tools, can be selectively enabled or disabled depending on a developer's requirements.

For example, a developer could choose to enable MDLv10 support for Half Life models, and would then be able to compile container and I/O libraries containing only code for this format of model.

AVID will follow a layered architecture, described below. The most basic layers are at the top of the table, and a layer only has knowledge about other layers that have come before it.

| Layer | Provides | Produces | Users |
|-------|----------|----------|-------|
| **Core**  | Mathematical entities (vectors, matrices, etc.), platform abstractions, and common utility functions | Libraries of mathematical types and platform abstractions | AVID asset containers; applications that use AVID libraries |
| **Asset Containers** | Structures for individual asset formats, for const and non-const access | One library containing required functions for chosen model formats | AVID I/O and tools; applications that use AVID libraries  |
| **Asset I/O** | Routines for reading and writing different asset formats | One library containing required functions for chosen model formats | AVID tools; applications that use AVID libraries |
| **Asset Tools** | Utilities for compiling, decompiling and viewing assets | Applications which can support manipulations of multiple asset formats, depending on libraries available at runtime | AVID end-user developers |

## Anything else?

AVID will support trans rights because it can, and because transgender developers and content creators contribute a significant amount to the game modding communities I'm a part of. In this rough old world we call meatspace, they deserve to be recognised.

## Dependencies

When building tools on Linux, the following dependencies will need to be installed (the example command below is for Ubuntu):

``` bash
# X11 libraries and OpenGL
$ sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev mesa-common-dev
```

## Documentation

Documentation is generated using [Natural Docs](https://www.naturaldocs.org). To build the documentation:

* On Windows, install NaturalDocs and make sure it is visible on the system path, then run `NaturalDocs.exe <path to repo>\docs`.
* On Linux, copy the NaturalDocs binaries to a `.naturaldocs` directory in the root of the repo, and then run `docs/makedocs.sh`.
  * Note that [Mono must be installed](http://www.mono-project.com/download) for NaturalDocs to run on Linux.
