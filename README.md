# aaHash README

## Overview

This repository contains the source code for aaHash, a fast hashing algorithm designed specifically for amino acid sequences. Included are the tests referenced in our publication and comprehensive usage documentation.

## Table of Contents

* [Directory Structure](#directory-structure)
* [Dependencies](#dependencies)
* [Installation](#installation)
* [How to Use aaHash](#how-to-use-aahash)
* [Running the aaHash Test used in the Manuscript](#running-the-aahash-test-used-in-the-manuscript)

## Directory Structure

- **aahash_seed_gen/**: Source code to generate the aaHash hash values for each amino acid.
- **aahash_test/**: Source code of the tests used to generate aaHash test results.
- **bin/**: Scripts to run aahash_test.
- **include/btllib/**: C++ header files for aaHash.
- **src/btllib/**: C++ src files for aaHash.

### Dependencies
 * [GCC 7+](https://gcc.gnu.org/)
 * [meson](https://mesonbuild.com/Getting-meson.html)
 * [ninja](https://github.com/ninja-build/ninja/)

## Installation

# Installing the newest version of aaHash via conda (highly recommended)

   ```
   conda install -c bioconda -c conda-forge btllib python=3.9
   conda install -c conda-forge -c bioconda compilers meson ninja // for building the tests
   ```

# Installing the version of aaHash  used in the manucsript via conda

   ```
   conda install -c bioconda -c conda-forge btllib=1.6.0 python=3.9
   conda install -c conda-forge -c bioconda compilers meson ninja // for building the tests
   ```

# Installing aaHash from this repo (not recommended)
1. Clone the repository:
   ```
   git clone https://github.com/bcgsc/aahash_paper.git
   ```

2. Navigate to the directory:
   ```
   cd aaHash_paper
   ```

3. Compile and install the code:
   ```
   meson --prefix=/path/to/install build
   cd build
   ninja
   ninja install
   ```

4. Export install directory if you use a build system like meson, CMake, autoconf
   ```
   export CPPFLAGS="-isystem /path/to/btllib/install/include $CPPFLAGS"
   export LDFLAGS="-L/path/to/btllib/install/lib -lbtllib $LDFLAGS"
   # you will also have to link the library. Check build system documentation
   # meson code example in meson.build
   link_args = [ '-lbtllib' ]
   executable('some_executable',
    link_args : link_args
  )
   ```

## How to Use aaHash

# AAHashing with btllib

## Setup

```cpp
#include "btllib/aahash.hpp"
```

## Level 1 Hashing

Level 1 hashing provides hashing for amino acid sequences where each amino acid maps to a different hash value.

```cpp
const std::string seq = "RITMLYTIRITMLYTI";
const unsigned k = 8 /*k-mer size*/, h = 3 /*number of hash*/;
btllib::AAHash aahash(seq, h, k, 1); 
while (aahash.roll())// initiate and roll the hash
{ 
   std::vector<uint64_t> hashes = aahash.hashes(); // return the hashes of the current kmer
}
```

## Level 2 Hashing

Level 2 hashing considers certain amino acids as equivalent based on their properties.

```cpp
btllib::AAHash aahash(seq, h, k, 2);
```

## Level 3 Hashing

Level 3 hashing uses another level of equivalence for amino acids.

```cpp
btllib::AAHash aahash(seq, h, k, 3);
```

## Multi-level Hashing with Seeds

Here, we demonstrate how to hash with multiple levels using seeds.

```cpp
std::string amino_alphabet = "ACDEFGHIKLMNPQRSTVWYCGASNEKIFHPCGTDKIFHP";
std::string string_seed1 = "1111111111111111111122222222222333333333";
std::string string_seed2 = "2222222222211111111111111111111333333333";
std::string string_seed3 = "3333333331111111111111111111122222222222";
std::vector<std::string> seeds  = { string_seed1, string_seed2, string_seed3 };
std::vector<btllib::SpacedSeed> parsed_seeds = btllib::aa_parse_seeds(seeds3);
btllib::SeedAAHash seed_aahash(amino_alphabet, parsed_seeds, 3, amino_alphabet.size());
```

## Compile without build system
```
g++ -isystem /path/to/btllib/install/include -L/path/to/btllib/install/lib -lbtllib foo.cpp
```


## Running the aaHash Test used in the Manuscript

### Building and Running

1. To build the tests:
   ```
   meson --prefix=/path/to/install build
   cd build
   ninja
   ninja install
   ```

2. Export tests to path:
   ```
   export PATH=/path/to/install/bin:$PATH
   ```

3. Execute the test script:
   ```
   bash aahash_manuscript_test.sh
   ```

## License
aaHash Copyright (c) 2023 British Columbia Cancer Agency Branch. All rights reserved.

aaHash is released under the GNU General Public License v3

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.

For commercial licensing options, please contact Patrick Rebstein (prebstein@bccancer.bc.ca).