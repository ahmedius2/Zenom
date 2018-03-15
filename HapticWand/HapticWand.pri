#--------------------------------------------------------------
#
# HapticWand library is designed to control Quanser's 5DOF Haptic Wand.
# Copyright (C) 2013
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Haptic Wand License, Version 1.0
#
#--------------------------------------------------------------

HAPTIC_WAND_VER_MAJ   = 1
HAPTIC_WAND_VER_MIN   = 0
HAPTIC_WAND_VER_PAT   = 0
HAPTIC_WAND_VERSION   = $${HAPTIC_WAND_VER_MAJ}.$${HAPTIC_WAND_VER_MIN}.$${HAPTIC_WAND_VER_PAT}

#--------------------------------------------------------------
# Install paths
#--------------------------------------------------------------

HAPTIC_WAND_INSTALL_PREFIX = /usr

HAPTIC_WAND_INSTALL_HEADERS   = $${HAPTIC_WAND_INSTALL_PREFIX}/include/hapticWand
HAPTIC_WAND_INSTALL_LIBS      = $${HAPTIC_WAND_INSTALL_PREFIX}/lib64
HAPTIC_WAND_INSTALL_BINS      = $${HAPTIC_WAND_INSTALL_PREFIX}/bin

#--------------------------------------------------------------
# Xenomai path
#--------------------------------------------------------------
XENOMAI_HEADERS   = /usr/xenomai/include
XENOMAI_LIBS      = /usr/xenomai/lib

#--------------------------------------------------------------
# Zenom path
#--------------------------------------------------------------
ZENOM_HEADERS   = /usr/include/zenom
ZENOM_LIBS      = /usr/lib64


