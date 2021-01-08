# Distributed Systems Assignment
![build-status-badge] ![license-badge] ![cpp-badge] ![cmake-badge]
<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/thiago-rezende/distributed-systems-assignment">
    <img src=".github/logo.png" alt="Logo" width="100" height="100">
  </a>

  <h3 align="center">Distributed Systems Assignment</h3>
  <p align="center">
    Solution for the assignment of Distributed Systems subject
    <br />
    <a href="https://github.com/thiago-rezende/distributed-systems-assignment/issues">Report Bug</a>
    ·
    <a href="https://github.com/thiago-rezende/distributed-systems-assignment/issues">Request Feature</a>
    .
    <a href="https://github.com/thiago-rezende/distributed-systems-assignment/actions">Continuous Integration</a>
  </p>
</div>

 - Libraries Included
    - [Spdlog][spdlog-url]

 - Project structure
 ```
    .
    ├── .github                     # Repository stuff.
    ├──  first_implementation       # First impl folder.
    |    ├── core                   # Core functionalities folder.
    |    |    ├── logger.h          # Logger utils.
    |    |    └── logger.cpp        # Logger utils implementation.
    |    ├── pch.h                  # Pre-compiled header.
    |    ├── base.hpp
    |    ├── producer.hpp
    |    ├── consumer.hpp
    |    ├── main.cpp               # First impl entrypoint.
    |    └── CMakeLists.txt         # First impl CMake build script.
    ├──  second_implementation      # Second impl folder.
    |    ├── core                   # Core functionalities folder.
    |    |    ├── logger.h          # Logger utils.
    |    |    └── logger.cpp        # Logger utils implementation.
    |    ├── pch.h                  # Pre-compiled header.
    |    ├── base.hpp
    |    ├── sempahore.hpp
    |    ├── producer.hpp
    |    ├── consumer.hpp
    |    ├── main.cpp               # Second impl entrypoint.
    |    └── CMakeLists.txt         # Second impl CMake build script.
    ├──  third_implementation       # Third impl folder.
    |    ├── core                   # Core functionalities folder.
    |    |    ├── logger.h          # Logger utils.
    |    |    └── logger.cpp        # Logger utils implementation.
    |    ├── pch.h                  # Pre-compiled header.
    |    ├── base.hpp
    |    ├── producer.hpp
    |    ├── consumer.hpp
    |    ├── main.cpp               # Third impl entrypoint.
    |    └── CMakeLists.txt         # Third impl CMake build script.
    ├── vendor                      # Third-party packages will be here.
    |    └── spdlog                 # Fast C++ logging library.
    └── CMakeLists.txt              # Main CMake build script.
```
 ## Compatibility

 | Toolset | Windows |  Linux  |   MacOS    |
 | :-----: | :-----: | :-----: | :--------: |
 |   GCC   |    ✔️    |    ✔️    |    ✔️    |
 |  Clang   |    ✔️    |    ✔️    |    ✔️    |
 |  MSVC   |    ✔️    | ------- | ---------- |

<!-- Links -->
[cmake-url]: https://cmake.org/
[spdlog-url]: https://github.com/gabime/spdlog

<!-- Badges -->
[build-status-badge]: https://github.com/thiago-rezende/distributed-systems-assignment/workflows/build/badge.svg
[license-badge]: https://img.shields.io/badge/license-MIT-blue.svg?style=flat-square
[cmake-badge]: https://img.shields.io/badge/CMake-3.16.0-blueviolet.svg?style=flat-square
[cpp-badge]: https://img.shields.io/badge/C++-17-orange.svg?style=flat-square
