# ShadingZen C++ - A set of tools for 2D/3D Engine development

ShadingZen C++ is an optimized library for computer graphics applications. It is meant to replace some internal code in [ShadingZen
Engine](https://github.com/TraxNet/ShadingZen). Target is to have it running 
with optimized code for ARM Neon and Intel/AMD SSE instruction sets.


## Current status

This library is currently in its infant state, there are many areas to develop and it currently lacks ARM Neon support. 
Current target is to have set of 2D/3D computational classes ready (vectors, matrices, bounding boxes, quaternions) to perform basic math operations.
After that, some raytracing queries (for example for occlusion discarding) will be implemented. 

As of May 2013, the source compiles against Boost 1.53 on (ShadingZenCpp requires a semi-compliant C++11 compiler):
- Linux GCC 4.7.20121109 (probably works with 4.6)
- MacOSX Clang 3.2 (using libc++)
- MSVC 2012

Supported SIMD instruction sets: 
- SSE3: No
- SSE4.1: Yes
- NEON ARM: No
- AVX: No


NOTE: ShadingZenCpp is still not ready to be used in any project.


## License

Copyright (c) 2013 Oscar Blasco Maestro and Contributors.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
