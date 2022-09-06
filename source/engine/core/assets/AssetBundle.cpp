#include "AssetBundle.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(AssetBundle)
AssetBundle::AssetBundle()
{

}

AssetBundle::AssetBundle(const std::string& path)
	:Super(path)
{

}

const SharePtr<Asset> AssetBundle::getAsset(const std::string& name)
{
	auto it = m_assets.find(name);
	if ( it == m_assets.end())
	{
		return SharePtr<Asset>();
	}

	if (it->second == nullptr)
	{

	}
	return it->second;
}

void AssetBundle::releaseAsset(const std::string& name)
{
	auto it = m_assets.find(name);
	if (it == m_assets.end())
	{
		return;
	}
	
	m_assets.erase(it);
}

void AssetBundle::onLoad(SharePtr<Data>& data)
{

}

void AssetBundle::onUnload()
{

}

END_OGS_NAMESPACE