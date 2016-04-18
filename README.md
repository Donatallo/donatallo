# Donatallo

[![Build Status](https://travis-ci.org/Donatallo/donatallo.svg?branch=master)](https://travis-ci.org/Donatallo/donatallo)

Donatallo project aims to make donations to FLOSS projects easier.
We maintain [database](https://github.com/Donatallo/donatallo-database)
of FLOSS projects accepting donations, and the application (this
repository) which determines which projects are relevant to you and
allows to donate in an easy way.

Note that Donatallo **does not** accept or process any funds itself.
We only point you to upstream donation options.

## Frontends

For now only proof of concept command line application is provided,
```donatallo-cli```.

Run ```donatallo-cli -a``` to list all projects available in the
donatallo database, or ```donatallo-cli``` to list only projects
detected on your system.

## OS support

Support for different OS, distros and packaging systems is in
development, for now we support:

* FreeBSD (pkg)
* Ubuntu/Debian (dpkg)

## Building

Dependencies:

* [CMake](http://www.cmake.org/)
* [yaml-cpp](https://github.com/jbeder/yaml-cpp) 0.5.3 or later

To build the project, run:

```
cmake . && make
```

## Author

* [Dmitry Marakasov](https://github.com/AMDmi3) <amdmi3@amdmi3.ru>

## License

* GPLv3 or later, see [COPYING](COPYING).
