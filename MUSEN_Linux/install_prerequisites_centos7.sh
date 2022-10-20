#!/bin/bash

#######################################################################################
# Installs all packages and compiles libraries needed to build MUSEN.
# Requires common_config.sh in the same directory to run.
# Run it as 
# $ chmod +x ./install_prerequisites_centos7.sh
# $ sudo ./install_prerequisites_centos7.sh
#######################################################################################

# check for running as root
if [[ ${EUID} -ne 0 ]]; then
   echo "Please run this script as root or using sudo!" 
   exit 1
fi

# make the config file visible regardless of calling location and load it
PATH_PREFIX="${BASH_SOURCE%/*}" 
if [[ ! -d "${PATH_PREFIX}" ]]; then PATH_PREFIX="${PWD}"; fi
. "${PATH_PREFIX}/common_config.sh"

# if working directory does not exist yet
if [ ! -d "${MUSEN_WORK_PATH}" ]; then
	# create working directory
	mkdir -p ${MUSEN_WORK_PATH}
	# set proper permissions for current user
	chown ${SUDO_USER}.${SUDO_USER} ${MUSEN_WORK_PATH}
fi
	
# change permissions of files 
chmod +x ./install_gcc_centos7.sh
chmod +x ./install_cmake_centos7.sh
chmod +x ./install_zlib_centos7.sh
chmod +x ./install_protobuf_centos7.sh
chmod +x ./install_qt_centos7.sh
chmod +x ./install_cuda_centos7.sh
chmod +x ./compile_on_centos7.sh
chmod +x ./make_musen_centos7.sh
chmod +x ./copy_source_files.sh
chmod +x ./generate_hash_header.sh
chmod +x ./generate_time_header.sh
chmod +x ./assemble_gui.sh
chmod +x ./musen.sh

# gcc
./install_gcc_centos7.sh

# cmake  
./install_cmake_centos7.sh
		 
# zlib   
./install_zlib_centos7.sh

# protobuf
./install_protobuf_centos7.sh

# qt
./install_qt_centos7.sh

# cuda
./install_cuda_centos7.sh

# check installed versions
source /opt/rh/devtoolset-${GCC_VER}/enable
gcc --version | head -n1
g++ --version | head -n1
cmake3 --version | head -n1
${MUSEN_EXTERNAL_LIBS_PATH}/protobuf/bin/protoc --version | head -n1
${MUSEN_EXTERNAL_LIBS_PATH}/qt/${QT_VER}/gcc_64/bin/qmake --version | tail -n1
/usr/local/cuda-${CUDA_VER}/bin/nvcc --version | head -n4 | tail -1
