/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Win32WSDiscovery.h"


HRESULT CreateClientNotificationSink(CClientNotificationSink** sink)
{
  CClientNotificationSink* tempSink = nullptr;

  if (!sink)
    return E_POINTER;

  tempSink = new CClientNotificationSink();

  if (!tempSink)
    return E_OUTOFMEMORY;

  *sink = tempSink;
  tempSink = nullptr;

  return S_OK;
}

CClientNotificationSink::CClientNotificationSink() : m_cRef(1)
{
}

CClientNotificationSink::~CClientNotificationSink()
{
}

HRESULT STDMETHODCALLTYPE CClientNotificationSink::Add(IWSDiscoveredService* service)
{

  if (!service)
    return E_INVALIDARG;

  WSD_NAME_LIST* list = nullptr;
  service->GetTypes(&list);

  LPCWSTR address = nullptr;
  service->GetRemoteTransportAddress(&address);

  if (list && address)
  {
    std::wstring name(list->Next->Element->LocalName);

    if (name == L"Computer")
    {
      std::wstring addr(address);
      m_serversIps.push_back(addr.substr(0, addr.find(L":", 0)));
    }
  }

  return S_OK;
}

HRESULT STDMETHODCALLTYPE CClientNotificationSink::Remove(IWSDiscoveredService* service)
{
  return S_OK;
}

HRESULT STDMETHODCALLTYPE CClientNotificationSink::SearchFailed(HRESULT hr, LPCWSTR tag)
{
  if (m_pEvent)
    m_pEvent->Set();

  return S_OK;
}

HRESULT STDMETHODCALLTYPE CClientNotificationSink::SearchComplete(LPCWSTR tag)
{
  if (m_pEvent)
    m_pEvent->Set();

  return S_OK;
}

HRESULT STDMETHODCALLTYPE CClientNotificationSink::QueryInterface(REFIID riid, void** object)
{
  if (!object)
    return E_POINTER;

  *object = nullptr;

  if (__uuidof(IWSDiscoveryProviderNotify) == riid)
    *object = static_cast<IWSDiscoveryProviderNotify*>(this);
  else if (__uuidof(IUnknown) == riid)
    *object = static_cast<IUnknown*>(this);
  else
    return E_NOINTERFACE;

  ((LPUNKNOWN)*object)->AddRef();

  return S_OK;
}

ULONG STDMETHODCALLTYPE CClientNotificationSink::AddRef()
{
  ULONG newRefCount = InterlockedIncrement(&m_cRef);

  return newRefCount;
}

ULONG STDMETHODCALLTYPE CClientNotificationSink::Release()
{
  ULONG newRefCount = InterlockedDecrement(&m_cRef);

  if (!newRefCount)
    delete this;

  return newRefCount;
}
