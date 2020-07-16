# Cet – Container Environment Test

[![Build Status](https://travis-ci.com/offa/cet.svg?branch=master)](https://travis-ci.com/offa/cet)
[![GitHub release](https://img.shields.io/github/release/offa/cet.svg)](https://github.com/offa/cet/releases)
[![License](https://img.shields.io/badge/license-GPLv3-yellow.svg)](LICENSE)
[![C++](https://img.shields.io/badge/c++-17-green.svg)]()

Simple test execution, mostly for container environments.

The tests are executed *within* the environment under tests.


### Configuration

Existence of files or directories is configured by `cet.yml`:

###### Example

```yml
files:
  - /bin/gcc
  - /bin/g++
  - /tmp/example/file1.conf

directories:
  - /usr/lib/gcc
  - /usr/lib/clang
  - /tmp/dir/example
```
