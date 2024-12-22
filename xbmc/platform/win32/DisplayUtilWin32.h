/*
 *  Copyright (C) 2024 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "HDRStatus.h"

#include <Windows.h>

#include <optional>
#include <string>
#include <vector>

// @todo: Remove this and "SDK_26100.h" when Windows SDK updated to 10.0.26100.0 in builders
#ifndef NTDDI_WIN11_GE // Windows SDK 10.0.26100.0 or newer
#include "SDK_26100.h"
#endif

struct DisplayConfigId
{
  LUID adapterId;
  UINT32 id;
};

class CDisplayUtilWin32
{
public:
  CDisplayUtilWin32() = default;
  ~CDisplayUtilWin32() = default;

  static std::wstring GetCurrentDisplayName();
  static std::vector<DISPLAYCONFIG_PATH_INFO> GetDisplayConfigPaths();
  static std::optional<DisplayConfigId> GetCurrentDisplayTargetId();
  static std::optional<DisplayConfigId> GetDisplayTargetId(const std::wstring& gdiDeviceName);
  static HDR_STATUS GetDisplayHDRStatus(const DisplayConfigId& identifier);
  static HDR_STATUS SetDisplayHDRStatus(const DisplayConfigId& identifier, bool enable);
};
