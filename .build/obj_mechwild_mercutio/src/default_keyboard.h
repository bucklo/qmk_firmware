// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*******************************************************************************
  88888888888 888      d8b                .d888 d8b 888               d8b
      888     888      Y8P               d88P"  Y8P 888               Y8P
      888     888                        888        888
      888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
      888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
      888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
      888     888  888 888      X88      888    888 888 Y8b.          888      X88
      888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
                                                        888                 888
                                                        888                 888
                                                        888                 888
     .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
    d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
    888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
    Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
     "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
         888
    Y8b d88P
     "Y88P"
*******************************************************************************/

#pragma once
#include "quantum.h"

// Layout content

#define LAYOUT_all(k4C, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k4G, k4F, k4E, k4D, k5C, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k5G, k5F, k5E, k4B, k5D, k2A, k2B, k6B, k2D, k2E, k2F, k2G, k6G, k6F, k6E, k6D, k6C, k3A, k5B, k3B, k3E, k3F, k3G, k3D, k3C, k2C) { \
	 {k0A, k0B, k0C, k0D, k0E, k0F, k0G}, \
	 {k1A, k1B, k1C, k1D, k1E, k1F, k1G}, \
	 {k2A, k2B, k2C, k2D, k2E, k2F, k2G}, \
	 {k3A, k3B, k3C, k3D, k3E, k3F, k3G}, \
	 {KC_NO, k4B, k4C, k4D, k4E, k4F, k4G}, \
	 {KC_NO, k5B, k5C, k5D, k5E, k5F, k5G}, \
	 {KC_NO, k6B, k6C, k6D, k6E, k6F, k6G} \
}

#define LAYOUT_625u_space(k4C, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k4G, k4F, k4E, k4D, k5C, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k5G, k5F, k5E, k4B, k5D, k2A, k2B, k6B, k2D, k2E, k2F, k2G, k6G, k6F, k6E, k6D, k6C, k3A, k5B, k3B, k3F, k3D, k3C, k2C) { \
	 {k0A, k0B, k0C, k0D, k0E, k0F, k0G}, \
	 {k1A, k1B, k1C, k1D, k1E, k1F, k1G}, \
	 {k2A, k2B, k2C, k2D, k2E, k2F, k2G}, \
	 {k3A, k3B, k3C, k3D, KC_NO, k3F, KC_NO}, \
	 {KC_NO, k4B, k4C, k4D, k4E, k4F, k4G}, \
	 {KC_NO, k5B, k5C, k5D, k5E, k5F, k5G}, \
	 {KC_NO, k6B, k6C, k6D, k6E, k6F, k6G} \
}

// Keycode content
