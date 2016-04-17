# Donatallo

[![Build Status](https://travis-ci.org/Donatallo/donatallo.svg?branch=master)](https://travis-ci.org/Donatallo/donatallo)

Donatallo project aims to make donations to FLOSS projects easier.
We maintain [database](https://github.com/Donatallo/donatallo-database)
of FLOSS projects accepting donations, and the application (this
repository) which determines which projects are relevant to you and
allows to donate in an easy way.

**NOTE** that Donatallo **does not** accept or process any funds
itself. We only point you to upstream donation metods.

## OS support

Support for different OS, distros and packaging systems is in
development, for now we support:

* FreeBSD (pkg)

## Building

Dependencies:

* [yaml-cpp](https://github.com/jbeder/yaml-cpp) 0.5.3 or later
* [CMake](http://www.cmake.org/)

To build the project, run:

```
cmake . && make
```

## Author

* [Dmitry Marakasov](https://github.com/AMDmi3) <amdmi3@amdmi3.ru>

## License

* GPLv3 or later, see [COPYING](COPYING).
