#pragma once

class m_IDirect3D9Ex : public IDirect3D9Ex
{
private:
	LPDIRECT3D9 ProxyInterface;
	LPDIRECT3D9EX ProxyInterfaceEx = nullptr;
	REFIID WrapperID;

	// For Create & CreateEx
	template <typename T>
	HRESULT CreateDeviceT(D3DPRESENT_PARAMETERS& d3dpp, bool& MultiSampleFlag, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, D3DDISPLAYMODEEX* pFullscreenDisplayMode, T ppReturnedDeviceInterface);
	HRESULT CreateDeviceT(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, D3DDISPLAYMODEEX*, IDirect3DDevice9** ppReturnedDeviceInterface)
	{ return ProxyInterface->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface); }
	HRESULT CreateDeviceT(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, D3DDISPLAYMODEEX* pFullscreenDisplayMode, IDirect3DDevice9Ex** ppReturnedDeviceInterface)
	{ return (ProxyInterfaceEx) ? ProxyInterfaceEx->CreateDeviceEx(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, pFullscreenDisplayMode, ppReturnedDeviceInterface) : D3DERR_INVALIDCALL; }

	// Other helper functions
	void LogAdapterNames();

public:
	m_IDirect3D9Ex(LPDIRECT3D9EX pDirect3D, REFIID DeviceID) : ProxyInterface(pDirect3D), WrapperID(DeviceID)
	{
		LOG_LIMIT(3, "Creating interface " << __FUNCTION__ << " (" << this << ")");

		if (WrapperID == IID_IDirect3D9Ex)
		{
			ProxyInterfaceEx = pDirect3D;
		}

		LogAdapterNames();
	}
	~m_IDirect3D9Ex()
	{
		LOG_LIMIT(3, __FUNCTION__ << " (" << this << ")" << " deleting interface!");

		DeviceWindow = nullptr;
		BufferWidth = 0;
		BufferHeight = 0;
	}

	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	/*** IDirect3D9 methods ***/
	STDMETHOD(RegisterSoftwareDevice)(THIS_ void* pInitializeFunction);
	STDMETHOD_(UINT, GetAdapterCount)(THIS);
	STDMETHOD(GetAdapterIdentifier)(THIS_ UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier);
	STDMETHOD_(UINT, GetAdapterModeCount)(THIS_ UINT Adapter, D3DFORMAT Format);
	STDMETHOD(EnumAdapterModes)(THIS_ UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode);
	STDMETHOD(GetAdapterDisplayMode)(THIS_ UINT Adapter, D3DDISPLAYMODE* pMode);
	STDMETHOD(CheckDeviceType)(THIS_ UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed);
	STDMETHOD(CheckDeviceFormat)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat);
	STDMETHOD(CheckDeviceMultiSampleType)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels);
	STDMETHOD(CheckDepthStencilMatch)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat);
	STDMETHOD(CheckDeviceFormatConversion)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat);
	STDMETHOD(GetDeviceCaps)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps);
	STDMETHOD_(HMONITOR, GetAdapterMonitor)(THIS_ UINT Adapter);
	STDMETHOD(CreateDevice)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface);

	/*** IDirect3D9Ex methods ***/
	STDMETHOD_(UINT, GetAdapterModeCountEx)(THIS_ UINT Adapter, CONST D3DDISPLAYMODEFILTER* pFilter);
	STDMETHOD(EnumAdapterModesEx)(THIS_ UINT Adapter, CONST D3DDISPLAYMODEFILTER* pFilter, UINT Mode, D3DDISPLAYMODEEX* pMode);
	STDMETHOD(GetAdapterDisplayModeEx)(THIS_ UINT Adapter, D3DDISPLAYMODEEX* pMode, D3DDISPLAYROTATION* pRotation);
	STDMETHOD(CreateDeviceEx)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, D3DDISPLAYMODEEX* pFullscreenDisplayMode, IDirect3DDevice9Ex** ppReturnedDeviceInterface);
	STDMETHOD(GetAdapterLUID)(THIS_ UINT Adapter, LUID * pLUID);

	// Helper functions
	bool TestResolution(UINT Adapter, DWORD BackBufferWidth, DWORD BackBufferHeight);
};
