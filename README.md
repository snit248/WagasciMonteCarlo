# GEANT4 simulation code for WAGASCI+BabyMIND at J-PARC (v0.2.0)

This is the GEANT4 Monte Carlo simulation code for the WAGASCI project
at J-PARC. All its sub-detectors, WAGASCI, Proton Module, Side MRD and
Baby-MIND, are included in the simulation.

## External dependencies

### GEANT4

[GEANT4](http://geant4.cern.ch/) is a toolkit for the simulation of
the passage of particles through matter developed by CERN. Geant4
v10.5.0+ is recommended.

### ROOT

[ROOT](https://root.cern.ch/) is an object-oriented program and
library developed by CERN. ROOT 6.20+ is recommended.

### BOOST

[BOOST](https://www.boost.org/) is a set of libraries for the C++
programming language that provides support for tasks and structures
such as linear algebra, pseudorandom number generation,
multithreading, image processing, regular expressions, and unit
testing. Boost 1.53+ is recommended.

## Installation

Only the following operative systems are tested and supported:
 - Ubuntu 18.04/20.04 64bit
 - CentOS 7 (KEKCC)

To install the software with all its dependencies I have written a
bash shell script called `install.bash`. Basically you just have to
launch it and the script will install everything automatically. **Only
bash shell is supported.**

However, the script makes a couple of assumptions behind the hood:

 - If the OS is CentOS 7, it is assumed that the user is installing
 the software in a KEKCC account so there is no super user access.
 - If the OS is Ubuntu, it is assumed that the user has complete
 access to the system and it is possible to run commands as super
 user.

**Note:** The script assumes a vanilla install of Ubuntu or a clean
environment of KEKCC.  In KEKCC, if you already have customized your
environment, I strongly recommend to backup your `.bashrc` file and
restore the original one, before running the script. Then run the
script and when the script has finished, compare the new `.bashrc`
with the old one and merge them as you see fit.

**Note:** I recommend using the WAGASCI MC software only with the
ROOT, Geant4 and BOOST versions compiled by the installation
script. If you want to use different versions of those libraries, I
can provide (limited) support but you are essentially on your own.

**Note:** the script takes quite long (a couple of hours depending on
your hardware) to complete because it has to compile a lot of code. In
Ubuntu you need occasionally to input your sudo password, so keep an
eye on the shell.

To run the script, first make sure that you have git installed (in
Ubuntu `sudo apt install git`). Git is already installed on the KEKCC
server.  Then issue the following commands in a bash shell:

```shell script
cd
git clone https://git.t2k.org/wagasci_babymind/wagasci-babymind-monte-carlo.git WagasciMC
cd WagasciMC/tools/scripts
chmod a+x install.bash
./install.bash
```

After the installation is concluded, it is better to exit from the ssh
session and login again (KEKCC) or reboot the system (Ubuntu) to make
sure that the environment is correctly set up (the `.bashrc` file is
automatically sourced only during login).  If you want to start using
the software rightaway, manually source the `.bashrc` file: ```shell
script . ~/.bashrc ```

Beware that the Geant4 visualization is disabled by default. That is
because in order to visualize the detectors some approximations on the
detector geometry has to be done, thus affecting the Physics output of
the simulation.  To enable the visualization use the CMake
`-DWITH_G4VIS=ON` option. Remember to recompile switching off the
visualization when you do Physics analysis on the output.

### KEKCC

For further info about how to create an account and use the KEKCC
cloud computing servers, refer to the [WAGASCI
wiki](https://www-he.scphys.kyoto-u.ac.jp/research/Neutrino/WAGASCI/wiki/dokuwiki/doku.php?id=components:kekcc).

To recompile the package on KEKCC, move to the `build` folder and type:
```shell script
CC=$(command -v gcc) CXX=$(command -v g++) \
  BOOST_ROOT=<path/to/your/boost/installation> \
  cmake3 -DCMAKE_INSTALL_PREFIX=${HOME}/Programs/WagasciMC ..
```
where you have to specify the path to your own BOOST installation.

## Configuration

The first time you run the software, a default configuration file is
created and filled with default values in this location:
`~/.wagasci/B2MC_conf.ini`. If you wish to use a different location
for the configuration file, you need to specify it in the
`--configuration-file-path` option of the command line arguments.  If
you do not specify it, the program will always fall back to the
default location.

The options in the configuration file are the very same as the command
line options. If an option is specified both in the command line and
configuration file, the command line value is used.

## Usage

Open a terminal and type:

```shell script
B2MC -h
```
to get a detailed description of all the options. If you see the error:
```shell script
B2MC: command not found
```

it means that you need to add the folder where B2MC is installed to
your `PATH`.  For UBUNTU the default installation folder is
`/usr/local`. For KEKCC is `~/Programs/WagasciMC`.

## Input NEUT files

There are some sample neut files in the `data/sample_neut_files`
directory for testing purposes.  NEUT files can come both in hbook and
ROOT format, however, from version v0.0.2, the only accepted format is
ROOT. To convert from hbook format to root format use the `h2root`
utility bundles with ROOT. If you do not have h2root you need to
recompile ROOT with the `-Dfortran=ON` flag.

## Documentation

A detailed description of the output format is included in the doxygen
documentation.  To generate the documentation, go into the docs
directory and type:

``` shell script
doxygen doxygen.conf
```

The documentation can then be read using any web browser by opening
the file `/docs/html/index.html`

## Normalization of MC
All MC events must be weighted by the following factor:

Number of events / 10<sup>21</sup> POT = (Number of simulated events) x (Weight factor)

Weight factor = (Normalization) x (Total cross-section) x (Avogadro constant) x (Density of matter) x (Thickness of matter)

- Normalization: JNUBEAM normalization factor = (the number of neutrinos to detector) / (10<sup>21</sup> POT) / (the number of entries in a JNUBEAM file)
- Total cross-section: (NEUT normalization factor) x 10<sup>-38</sup> cm<sup>2</sup> mol g<sup>-1</sup>
- Avogadro constant: 6.02x10<sup>23</sup> mol<sup>-1</sup>
- Density of matter:
  - Plastic scintillator = 1.03 g/cm<sup>3</sup>
  - Water = 0.997 g/cm<sup>3</sup>
  - Iron = 7.87 g/cm<sup>3</sup>
  - Wall = 2.2 g/cm<sup>3</sup>    
- Thickness of matter:
  - WAGASCI = 50 cm : water box dimension along Z
  - Proton module = 46.2 cm : thickness in the Z direction of (INGRID-scintillators region + VETO planes - air gaps)
  - Side-MRD = 161 cm : inner iron plate dimension along Z
  - Baby-MIND = 99 cm : 33 iron planes x 3 cm (plane thickness along Z)
- 1 NEUT file corresponds to 10<sup>21</sup> POT after weighting

### Dimensional analysis of weight factor

 - [L] = length
 - [N] = amount of substance
 - [M] = mass

 - `n` = JNUBEAM normalization = (the number of neutrinos to detector) / (10<sup>21</sup> POT) / (the number of entries in a JNUBEAM file) = dimensionless
 - `S = s / m` = NEUT total cross-section per single nucleon = cross-section / molar mass (cm<sup>2</sup> mol g<sup>-1</sup>) = [L<sup>2</sup> N M<sup>-1</sup>]
 - `A` = Avogadro constant (mol<sup>-1</sup>) = [N<sup>-1</sup>]
 - `d` = density of matter (g/cm<sup>3</sup>) = [M L<sup>-3</sup>]
 - `t` = thickness of matter (cm) = [L]

mass of target per square cm

`j = d x t` ⟶ [M L<sup>-2</sup>]

number of nucleons per square cm

`k = A x j / m` ⟶ [M N<sup>-1</sup> L<sup>-2</sup> M<sup>-1</sup> N] = [L<sup>-2</sup>]

number of interacting neutrinos / number of incoming neutrinos

`s x k` ⟶ [L<sup>2</sup> L<sup>-2</sup>] = dimensionless

Weight factor = number of interacting neutrinos / 10<sup>21</sup> POT

`W = n x s x k =  n x S x A x d x t` ⟶ [L<sup>2</sup> N<sup>-1</sup> M L<sup>-3</sup> L M<sup>-1</sup> N] = dimensionless