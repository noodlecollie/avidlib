# AVIDlib
Library for interacting with assets from Valve and iD Tech games.

![CI Status](https://github.com/x6herbius/avidlib/actions/workflows/continuous-integration.yml/badge.svg)

This repo doesn't currently have anything substantial in it, but while the overall design goals are still in my head, I'm writing them down here. I'm hoping I can add bits and pieces to this project as time goes on, when I have the need for them in my own projects.

## What is AVID?

**AVID** is a library (or rather, collection of libraries) for reading, writing and using **a**ssets from **V**alve and **iD** Tech games. The primary purpose of AVID is to provide portable support for Half Life MDL files (because that's what I need primarily), but anything from the Quake-tech games (various versions of the BSP and MDL file formats, plus other oddities like SPZ sprites) is included in the overall scope.

## What will AVID be used for?

AVID is intended to be used by programs which wish to read, write, or otherwise make use of any of the asset formats it supports. Examples include:

* Loading models for use in modern game engines
* Viewing models or maps in modder utilities
* Decompiling assets to their component sources
* Compiling assets into formats compatible with existing games like Half Life or Quake

## What language will AVID be written in?

AVID will be written in C. C is widely supported by a variety of compilers and platforms, and so pretty much any application should be able to interface with the AVID libraries. C++-based engines will be able to use AVID's libraries directly, and other popular languages like C# and Python have existing methods of utilising native platform libraries.

AVID will be C99-compliant. I believe that C99 strikes a good balance between compatibility with older software or compilers, and convenient modern language features. This is in contrast to the previous C89, upon which it adds significantly more flexibility, and the later C11, where `static_assert` is the only extra that I see as being particularly useful to this project.

AVID will use CMake as its build system. CMake is also widely supported on many different platforms, and its configuration files should be relatively easy to port to other build systems if CMake cannot be used.

## How will AVID be architectured?

AVID will be designed so that a developer can build libraries for only the asset formats that they need to support, in static or shared configuration. For example, a developer can link against `avid_mdlv10.lib` if they need support for Half Life MDL files, without needing to pull in knowledge about any other formats that they don't need.

AVID will follow a layered architecture, described below. The most basic layers are at the top of the table, and a layer only has knowledge about other layers that have come before it.

| Layer | Provides | Produces | Users |
|-------|----------|----------|-------|
| **Core**  | Mathematical entities (vectors, matrices, etc.) and common utility functions | Single library of mathematical types | AVID asset containers; applications that use AVID libraries |
| **Asset Containers** | Structures for individual asset formats, for const and non-const access | One library per supported asset format | AVID I/O and tools; applications that use AVID libraries  |
| **Asset I/O** | Routines for reading and writing different asset formats | One library per supported asset format | AVID tools; applications that use AVID libraries |
| **Asset Tools** | Utilities for compiling, decompiling and viewing assets | Applications which can support manipulations of multiple asset formats, depending on libraries available at runtime | AVID end-user developers |

## Anything else?

AVID will support trans rights because it can, and because transgender developers and content creators contribute a significant amount to the game modding communities I'm a part of. In this rough old world we call meatspace, they deserve to be recognised.
