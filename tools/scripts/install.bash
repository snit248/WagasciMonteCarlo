#!/bin/bash

# install.bash
# Copyright (C) 2018 by Pintaudi Giorgio <giorgio-pintaudi-kx@ynu.jp>
# Released under the GPLv3 license
#
#     Pintaudi Giorgio (PhD Student)
#     Yokohama National University
#     giorgio-pintaudi-kx@ynu.jp
#
# This is a bash script that installs the WAGASCI-BabyMIND-MC software
# along with all its dependencies for the Ubuntu and Scientific Linux OS.

UBUNTU="n"
UBUNTU1804="n"
UBUNTU2004="n"
CENTOS7="n"
ROOTVERS="6-22-06"
GEANTVERS="10.6.2"
BOOSTVERS="1_73_0"

# Define a function that checks if a package is installed

function isinstalled() {
  if [ $CENTOS7 == "y" ]; then
    if yum list installed "$@" >/dev/null 2>&1; then
      true
    else
      false
    fi
  elif [ $UBUNTU == "y" ]; then
    if dpkg -s "$1" &>/dev/null; then
      true
    else
      false
    fi
  fi
}

# Get script path
SOURCE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)/../.."

# Check the Ubuntu and Scientific Linux releases

if [ ! -f "/usr/bin/lsb_release" ] && [ ! -f "/etc/redhat-release" ]; then
  echo ""
  echo "This installer is for Ubuntu 18.04/20.04 and CentOS 7 only!"
  echo "You may get this script to run on other Linux distro too,"
  echo "but in that case you are on your own."
  echo ""
  exit 1
fi

if [ -f "/usr/bin/lsb_release" ] && [[ "$(lsb_release -rs)" == "18.04" || "$(lsb_release -rs)" == "20.04" ]]; then
  UBUNTU="y"
  CMAKE=cmake
  if [[ "$(lsb_release -rs)" == "18.04" ]]; then
    UBUNTU1804="y"
  else
    UBUNTU2004="y"
  fi
elif [ -f "/etc/redhat-release" ] && [[ "$(cat /etc/redhat-release)" == "CentOS Linux release 7.7.1908 (Core)" ]]; then
  CENTOS7="y"
  CMAKE=cmake3
  # Stop if there is some error
  set -e
else
  echo "There is something wrong about OS detection."
  echo "UBUNTU 18.04 = $UBUNTU1804"
  echo "UBUNTU 20.04 = $UBUNTU2004"
  echo "CENTOS7 = $CENTOS7"
  echo ""
  exit 1
fi

#check if sudo has been used

if [ "$(whoami)" == "root" ]; then
  echo ""
  echo "This installer is not intended be run as root or with sudo"
  echo "You will need to insert the user password AFTER the script has started."
  echo ""
  exit 1
fi

#############################################################################
#                                                                           #
#                                 CENTOS 7                                  #
#                                                                           #
#############################################################################

if [ $CENTOS7 == "y" ]; then

  #############################################################################
  #                                                                           #
  #                            GCC COMPILER (CENTOS7)                         #
  #                                                                           #
  #############################################################################

  echo ""
  echo "Loading GCC 9.3.0 environment"
  module load gcc/930
  if grep -Fxq "module load gcc/930" "${HOME}/.bashrc"; then
    echo "gcc/930 module already present in the .bashrc file"
  else
    cat >>"${HOME}/.bashrc" <<EOF

# load GCC 9.3.0 environment
module load gcc/930
EOF
  fi

  #############################################################################
  #                                                                           #
  #                                GIT (CENTOS7)                              #
  #                                                                           #
  #############################################################################

  echo ""
  echo "Loading git 2.26.0 environment"
  module load git/2260
  if grep -Fxq "module load git/2260" "${HOME}/.bashrc"; then
    echo "git/2260 module already present in the .bashrc file"
  else
    cat >>"${HOME}/.bashrc" <<EOF

# load git 2.26.0 environment
module load git/2260
EOF
  fi

  #############################################################################
  #                                                                           #
  #                               GEANT 4 (CENTOS7)                           #
  #                                                                           #
  #############################################################################

  ### Install Geant4 ###
  cd
  mkdir -p "${HOME}/Programs"
  git clone https://github.com/Geant4/geant4.git "${HOME}/Programs/geant4-sources"
  cd "${HOME}/Programs/geant4-sources"
  git checkout v${GEANTVERS}
  cd "${HOME}/Programs"
  mkdir -p "${HOME}/Programs/geant4-${GEANTVERS}-build"
  mkdir -p "${HOME}/Programs/geant4-${GEANTVERS}"
  cd "${HOME}/Programs/geant4-${GEANTVERS}-build"
  CC="$(command -v gcc)" CXX="$(command -v g++)" \
    ${CMAKE} \
    -DCMAKE_INSTALL_PREFIX="${HOME}/Programs/geant4-${GEANTVERS}" \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DGEANT4_USE_GDML=ON \
    -DGEANT4_INSTALL_DATA=ON \
    -DGEANT4_BUILD_MULTITHREADED=ON \
    -DGEANT4_USE_OPENGL_X11=ON \
    -DGEANT4_USE_QT=ON \
    -DGEANT4_USE_XM=ON \
    -DGEANT4_USE_SYSTEM_EXPAT=ON \
    -DGEANT4_USE_SYSTEM_ZLIB=ON \
    ../geant4-sources
  make -j"$(nproc)"
  make install
  rm -rf "${HOME}/Programs/geant4-${GEANTVERS}-build" "${HOME}/Programs/geant4-sources"

  source "${HOME}/Programs/geant4-${GEANTVERS}/bin/geant4.sh"

  if grep -Fxq "# set Geant4 environment" "${HOME}/.bashrc"; then
    echo "Geant 4 source command already present in the .bashrc file"
  else
    cat >>"${HOME}/.bashrc" <<EOF

# set Geant4 environment
if [ -f "${HOME}/Programs/geant4-${GEANTVERS}/bin/geant4.sh" ] ; then
    . "${HOME}/Programs/geant4-${GEANTVERS}/bin/geant4.sh"
fi
EOF
  fi

  #############################################################################
  #                                                                           #
  #                               ROOT (CENTOS7)                              #
  #                                                                           #
  #############################################################################

  # Download and install ROOT
  ROOTDIR="${HOME}/Programs/ROOT"
  mkdir -p "${ROOTDIR}"/{sources,${ROOTVERS},${ROOTVERS}-build}
  cd "${ROOTDIR}"
  git clone http://github.com/root-project/root.git sources
  cd "${ROOTDIR}/sources"
  git checkout -b v${ROOTVERS} v${ROOTVERS}
  cd "${ROOTDIR}/${ROOTVERS}-build"
  CC="$(command -v gcc)" CXX="$(command -v g++)" \
    ${CMAKE} \
    -DCMAKE_INSTALL_PREFIX="${ROOTDIR}/${ROOTVERS}" \
    -Dminuit2=ON \
    -Dfortran=ON \
    ../sources
  ${CMAKE} \
    --build . --target install -- -j"$(nproc)"
  cd
  rm -rf "${ROOTDIR}/${ROOTVERS}-build"
  source "${ROOTDIR}/${ROOTVERS}/bin/thisroot.sh"
  if grep -Fxq "# set ROOT environment" "${HOME}/.bashrc"; then
    echo "ROOT environment settings already present in the .bashrc file"
  else
    cat >>"${HOME}/.bashrc" <<EOF

# set ROOT environment
if [ -f "${ROOTDIR}/${ROOTVERS}/bin/thisroot.sh" ] ; then
   source ${ROOTDIR}/${ROOTVERS}/bin/thisroot.sh
fi
EOF
  fi

  #############################################################################
  #                                                                           #
  #                              BOOST (CENTOS7)                              #
  #                                                                           #
  #############################################################################

  # Download and install BOOST
  BOOSTDIR="${HOME}/Programs/BOOST"
  mkdir -p "${BOOSTDIR}"
  cd "${BOOSTDIR}"
  wget https://dl.bintray.com/boostorg/release/${BOOSTVERS//_/.}/source/boost_${BOOSTVERS}.tar.bz2
  tar --bzip2 -xf boost_${BOOSTVERS}.tar.bz2
  mv "${BOOSTDIR}/boost_${BOOSTVERS}" "${BOOSTDIR}/boost_${BOOSTVERS}_sources"
  cd "${BOOSTDIR}/boost_${BOOSTVERS}_sources"
  CC="$(command -v gcc)" CXX="$(command -v g++)" \
    ./bootstrap.sh --prefix="${BOOSTDIR}/boost_${BOOSTVERS}"
  CC="$(command -v gcc)" CXX="$(command -v g++)" \
    ./b2 install

  #############################################################################
  #                                                                           #
  #                      WAGASCI-BabyMIND MC (CENTOS7)                        #
  #                                                                           #
  #############################################################################

  echo ""
  echo "-------------------"
  echo "WAGASCI-BabyMIND MC INSTALLATION"
  echo "-------------------"

  # ROOT detection
  if [ -z "${ROOTSYS}" ]; then
    echo "Couldn't detect ROOT installation."
    echo "Perhaps you forgot to source the thisroot.sh script."
    exit
  else
    # shellcheck disable=SC1090
    source "${ROOTSYS}/bin/thisroot.sh"
  fi

  cd "${SOURCE_DIR}"
  mkdir build
  cd build
  BOOST_ROOT="${BOOSTDIR}/boost_${BOOSTVERS}" CC="$(command -v gcc)" CXX="$(command -v g++)" \
    ${CMAKE} ..-DCMAKE_INSTALL_PREFIX="${HOME}/Programs/WagasciMC" -DCMAKE_BUILD_TYPE=Release
  make -j"$(nproc)"
  make install

#############################################################################
#                                                                           #
#                                   UBUNTU                                  #
#                                                                           #
#############################################################################

elif [ $UBUNTU == "y" ]; then

  sudo apt-get update
  sudo apt-get -y upgrade

  #############################################################################
  #                                                                           #
  #                                BOOST (UBUNTU)                             #
  #                                                                           #
  #############################################################################

  sudo apt-get -y install libboost-all-dev

  #############################################################################
  #                                                                           #
  #                               GEANT 4 (UBUNTU)                            #
  #                                                                           #
  #############################################################################

  if [ ! -d "/opt/geant4" ]; then
    echo ""
    echo "-------------------"
    echo "Geant4 INSTALLATION"
    echo "-------------------"

    cd
    sudo apt-get install -y git build-essential libexpat1-dev libxmu-dev libxerces-c-dev cmake \
      cmake-curses-gui qt5-default qtbase5-dev zlib1g-dev libmotif-dev
    if [ ! -d "./geant4-sources" ]; then
      git clone https://github.com/Geant4/geant4.git geant4-sources
    fi
    cd geant4-sources
    git checkout v${GEANTVERS}
    cd ..
    mkdir -p geant4-${GEANTVERS}-build
    cd geant4-${GEANTVERS}-build
    ${CMAKE} -DCMAKE_INSTALL_PREFIX=/opt/geant4 \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DGEANT4_USE_GDML=ON \
      -DGEANT4_INSTALL_DATA=ON \
      -DGEANT4_BUILD_MULTITHREADED=ON \
      -DGEANT4_USE_OPENGL_X11=ON \
      -DGEANT4_USE_QT=ON \
      -DGEANT4_USE_XM=ON \
      -DGEANT4_USE_SYSTEM_EXPAT=ON \
      -DGEANT4_USE_SYSTEM_ZLIB=ON \
      ../geant4-sources
    make -j"$(nproc)"
    sudo make install
    cd && rm -rf geant4-${GEANTVERS}-build

    source "/opt/geant4/bin/geant4.sh"

    if grep -Fxq "# set Geant4 environment" "${HOME}/.profile"; then
      echo "Geant 4 source command already present in the .profile file"
    else
      cat >>"${HOME}/.profile" <<EOF

# set Geant4 environment
if [ -f "/opt/geant4/bin/geant4.sh" ] ; then
    . "/opt/geant4/bin/geant4.sh"
fi
EOF
    fi
  fi

  #############################################################################
  #                                                                           #
  #                                 ROOT (UBUNTU)                             #
  #                                                                           #
  #############################################################################

  #install root if necessary
  if [ -z "${ROOTSYS}" ]; then
    echo ""
    echo "-----------------"
    echo "ROOT INSTALLATION"
    echo "-----------------"

    ROOTDIR="${HOME}/ROOT"
    sudo apt-get update
    sudo apt-get install -y build-essential git dpkg-dev cmake xutils-dev \
      binutils libx11-dev libxpm-dev libxft-dev libxext-dev \
      libssl-dev libpcre3-dev libglu1-mesa-dev libglew-dev \
      libmysqlclient-dev libfftw3-dev libcfitsio-dev libgraphviz-dev \
      libavahi-compat-libdnssd-dev libldap2-dev python-dev libxml2-dev \
      libkrb5-dev libgsl-dev qtdeclarative5-dev libmotif-dev libmotif-common \
      libblas-dev liblapack-dev xfstt xfsprogs t1-xfree86-nonfree \
      ttf-xfree86-nonfree ttf-xfree86-nonfree-syriac xfonts-75dpi \
      xfonts-100dpi libgif-dev libtiff-dev libjpeg-dev liblz4-dev \
      liblzma-dev lzma lzma-dev libgl2ps-dev libpostgresql-ocaml-dev libsqlite3-dev \
      libpythia8-dev davix-dev srm-ifce-dev libtbb-dev libafterimage-dev \
      python3-numpy python-numpy python3 python3-dev zstd libzstd-dev

    if [ $UBUNTU1804 == "y" ]; then
      sudo apt-get install -y python python-dev
    elif [ $UBUNTU2004 == "y" ]; then
      sudo apt-get install -y python2 python2-dev xxhash libxxhash-dev
    fi

    cd
    # Download and install ROOT
    mkdir -p "${ROOTDIR}"/{${ROOTVERS},${ROOTVERS}-build}
    cd "${ROOTDIR}"
    if [ ! -d "./sources" ]; then
      git clone http://github.com/root-project/root.git sources
    fi
    cd sources
    git checkout -b v${ROOTVERS} v${ROOTVERS}
    cd ../${ROOTVERS}-build
    ${CMAKE} -DCMAKE_INSTALL_PREFIX="${ROOTDIR}/${ROOTVERS}" -Dfortran=ON -Dminuit2=ON ../sources
    ${CMAKE} --build . --target install -- -j"$(nproc)"
    cd
    # shellcheck disable=SC1090
    source "${ROOTDIR}/${ROOTVERS}/bin/thisroot.sh"
    if grep -Fxq "# set ROOT environment" "${HOME}/.profile"; then
      echo "ROOT environment settings already present in the .profile file"
    else
      cat >>"${HOME}/.profile" <<EOF

# set ROOT environment
if [ -f "${ROOTDIR}/${ROOTVERS}/bin/thisroot.sh" ] ; then
   source ${ROOTDIR}/${ROOTVERS}/bin/thisroot.sh
fi
EOF
    fi
    rm -rf "${ROOTDIR}"/${ROOTVERS}-build
  fi

  #############################################################################
  #                                                                           #
  #                       WAGASCI-BabyMIND MC (UBUNTU)                        #
  #                                                                           #
  #############################################################################

  echo ""
  echo "--------------------------------"
  echo "WAGASCI-BabyMIND MC Installation"
  echo "--------------------------------"

  # ROOT detection
  if [ -z "${ROOTSYS}" ]; then
    echo "Couldn't detect ROOT installation."
    echo "Perhaps you forgot to source the thisroot.sh script."
    exit
  else
    # shellcheck disable=SC1090
    source "${ROOTSYS}/bin/thisroot.sh"
  fi

  # GEANT4 detection
  if [ ! -d "/opt/geant4" ]; then
    echo "Couldn't detect Geant4 installation."
    exit
  else
    source "/opt/geant4/bin/geant4.sh"
  fi

  sudo apt-get install -y libxi-dev
  cd "${SOURCE_DIR}"
  mkdir build
  cd build
  ${CMAKE} -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release ..
  make -j"$(nproc)"
  sudo make install
fi

echo ""
echo "Installation successfully completed!"
echo "Please reboot the system."
echo "For any questions about this script please contact:"
echo "Pintaudi Giorgio (PhD Student)"
echo "Yokohama National University"
echo "giorgio-pintaudi-kx@ynu.jp"
echo ""

exit 0

# install.bash
#
# Copyright (C) 2018 by Pintaudi Giorgio <giorgio-pintaudi-kx@ynu.jp>
# Released under the GPLv3 license
#
#     Pintaudi Giorgio (PhD Student)
#     Yokohama National University
#     giorgio-pintaudi-kx@ynu.jp
