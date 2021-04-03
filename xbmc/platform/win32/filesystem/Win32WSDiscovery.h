/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "threads/Event.h"

#include <wsdapi.h>
#pragma comment(lib, "wsdapi.lib")

#include <vector>


class CClientNotificationSink;
HRESULT CreateClientNotificationSink(CClientNotificationSink** sink);


class CClientNotificationSink : public IWSDiscoveryProviderNotify
{
public:
  CClientNotificationSink();
  ~CClientNotificationSink();

  HRESULT STDMETHODCALLTYPE Add(IWSDiscoveredService* service);
  HRESULT STDMETHODCALLTYPE Remove(IWSDiscoveredService* service);
  HRESULT STDMETHODCALLTYPE SearchFailed(HRESULT hr, LPCWSTR tag);
  HRESULT STDMETHODCALLTYPE SearchComplete(LPCWSTR tag);
  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** object);
  ULONG STDMETHODCALLTYPE AddRef();
  ULONG STDMETHODCALLTYPE Release();

  void AttachEvent(CEvent* pEvent) { m_pEvent = pEvent; };
  std::vector<std::wstring> GetServersIps() { return m_serversIps; }

private:
  std::vector<std::wstring> m_serversIps;
  CEvent* m_pEvent = nullptr;
  ULONG m_cRef;
};
