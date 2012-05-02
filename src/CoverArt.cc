/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "config.h"
#include "coverart/defines.h"

#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <sstream>

#include <ne_uri.h>

#include "coverart/CoverArt.h"
#include "coverart/HTTPFetch.h"

class CoverArtArchive::CCoverArtPrivate
{
	public:
		CCoverArtPrivate()
		:	m_ProxyPort(0)
		{
		}

		std::string m_UserAgent;
		std::string m_ProxyHost;
		int m_ProxyPort;
		std::string m_ProxyUserName;
		std::string m_ProxyPassword;
};

CoverArtArchive::CCoverArt::CCoverArt(const std::string& UserAgent)
:	m_d(new CCoverArtPrivate)
{
	m_d->m_UserAgent=UserAgent;

	for (std::string::size_type Pos=0;Pos<m_d->m_UserAgent.length();Pos++)
		if (m_d->m_UserAgent[Pos]=='-')
			m_d->m_UserAgent[Pos]='/';

	// Parse http_proxy environmnent variable
	const char *http_proxy = getenv("http_proxy");
	if (http_proxy)
	{
		ne_uri uri;
		if (!ne_uri_parse(http_proxy, &uri))
		{
			if (uri.host)
				m_d->m_ProxyHost = uri.host;
			if (uri.port)
				m_d->m_ProxyPort = uri.port;

			if (uri.userinfo)
			{
				char *pos = strchr(uri.userinfo, ':');
				if (pos)
				{
					*pos = '\0';
					m_d->m_ProxyUserName = uri.userinfo;
					m_d->m_ProxyPassword = pos + 1;
				}
				else
				{
					m_d->m_ProxyUserName = uri.userinfo;
				}
			}
		}

		ne_uri_free(&uri);
	}
}

CoverArtArchive::CCoverArt::~CCoverArt()
{
	delete m_d;
}

void CoverArtArchive::CCoverArt::SetProxyHost(const std::string& ProxyHost)
{
	m_d->m_ProxyHost=ProxyHost;
}

void CoverArtArchive::CCoverArt::SetProxyPort(int ProxyPort)
{
	m_d->m_ProxyPort=ProxyPort;
}

void CoverArtArchive::CCoverArt::SetProxyUserName(const std::string& ProxyUserName)
{
	m_d->m_ProxyUserName=ProxyUserName;
}

void CoverArtArchive::CCoverArt::SetProxyPassword(const std::string& ProxyPassword)
{
	m_d->m_ProxyPassword=ProxyPassword;
}

std::vector<unsigned char> CoverArtArchive::CCoverArt::FetchFront(const std::string& ReleaseID) const
{
	std::stringstream URL;
	URL << "http://coverartarchive.org/release/" << ReleaseID << "/front";

	return MakeRequest(URL.str());
}

std::vector<unsigned char> CoverArtArchive::CCoverArt::FetchBack(const std::string& ReleaseID) const
{
	std::stringstream URL;
	URL << "http://coverartarchive.org/release/" << ReleaseID << "/back";

	return MakeRequest(URL.str());
}

std::vector<unsigned char> CoverArtArchive::CCoverArt::FetchImage(const std::string& ReleaseID, const std::string& ID, tImageSize Size) const
{
	std::stringstream URL;
	URL << "http://coverartarchive.org/release/" << ReleaseID << "/" << ID;

	switch (Size)
	{
		case eSize_Full:
			break;

		case eSize_250:
			URL << "-250";
			break;

		case eSize_500:
			URL << "-500";
			break;
	}

	URL << ".jpg";

	return MakeRequest(URL.str());
}

std::vector<unsigned char> CoverArtArchive::CCoverArt::MakeRequest(const std::string& URL) const
{
	CHTTPFetch Fetch(m_d->m_UserAgent);

	Fetch.SetProxyHost(m_d->m_ProxyHost);
	Fetch.SetProxyPort(m_d->m_ProxyPort);
	Fetch.SetProxyUserName(m_d->m_ProxyUserName);
	Fetch.SetProxyPassword(m_d->m_ProxyPassword);

	Fetch.Fetch(URL);
	return Fetch.Data();
}

CoverArtArchive::CReleaseInfo CoverArtArchive::CCoverArt::ReleaseInfo(const std::string& ReleaseID) const
{
	CReleaseInfo ReleaseInfo;

	std::stringstream URL;
	URL << "http://coverartarchive.org/release/" << ReleaseID;

	std::vector<unsigned char> JSON=MakeRequest(URL.str());
	std::string strJSON(JSON.begin(),JSON.end());

	if (strJSON.size()!=0)
	{
		ReleaseInfo=CReleaseInfo(strJSON);
	}

	return ReleaseInfo;
}
