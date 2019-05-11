// dllmain.h : Declaration of module class.

class CmsRDPdvcPluginModule : public ATL::CAtlDllModuleT< CmsRDPdvcPluginModule >
{
public :
	DECLARE_LIBID(LIBID_msRDPdvcPluginLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MSRDPDVCPLUGIN, "{1e300d6b-9787-4bf6-a5eb-57c443a5bf8c}")
};

extern class CmsRDPdvcPluginModule _AtlModule;
