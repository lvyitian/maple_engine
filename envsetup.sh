#!/bin/echo This script should be sourced in a shell. Execute command: source
#
# Copyright (C) [2020] Futurewei Technologies, Inc. All rights reverved.
#
# Licensed under the Mulan Permissive Software License v2.
# You can use this software according to the terms and conditions of the MulanPSL - 2.0.
# You may obtain a copy of MulanPSL - 2.0 at:
#
#   https://opensource.org/licenses/MulanPSL-2.0
#
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
# FIT FOR A PARTICULAR PURPOSE.
# See the MulanPSL - 2.0 for more details.
#

if [ "${BASH_SOURCE[0]}" -ef "$0" ]; then
    echo "This script should be sourced in a bash shell, not executed directly"
    exit 1
fi

export MAPLE_ROOT=$(realpath $(dirname ${BASH_SOURCE[0]}))
export MAPLE_COMPILER_ROOT="$MAPLE_ROOT/../mapleall"
export MAPLE_ENGINE_ROOT="$MAPLE_ROOT/maple_engine"
export MAPLE_RUNTIME_ROOT="$MAPLE_ROOT/maple_runtime"
export MAPLE_BUILD_ROOT="$MAPLE_ROOT/maple_build"
export MAPLE_BUILD_TOOLS="$MAPLE_BUILD_ROOT/tools"
export MAPLE_TARGET_ARCH="x86_64"
export JAVA_CORE_LIB="libcore"
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
if [ ! -d "$JAVA_HOME" ]; then
    echo "Error: directory $JAVA_HOME not found"
    echo "Please install the openjdk-8-jdk-headless package"
fi