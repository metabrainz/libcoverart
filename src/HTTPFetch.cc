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

#include "coverart/HTTPFetch.h"

#include <stdlib.h>
#include <string.h>

#include <iostream>

#include <ne_session.h>
#include <ne_auth.h>
#include <ne_string.h>
#include <ne_request.h>
#include <ne_uri.h>

class CoverArtArchive::CHTTPFetchPrivate
{
	public:
		CHTTPFetchPrivate()
		:	m_Result(0),
			m_Status(0),
			m_ProxyPort(0)
		{
		}

		std::string m_UserAgent;
		std::vector<unsigned char> m_Data;
		int m_Result;
		int m_Status;
		std::string m_ErrorMessage;
		std::string m_UserName;
		std::string m_Password;
		std::string m_ProxyHost;
		int m_ProxyPort;
		std::string m_ProxyUserName;
		std::string m_ProxyPassword;
};

CoverArtArchive::CHTTPFetch::CHTTPFetch(const std::string& UserAgent)
:	m_d(new CHTTPFetchPrivate)
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

CoverArtArchive::CHTTPFetch::~CHTTPFetch()
{
	delete m_d;
}

void CoverArtArchive::CHTTPFetch::SetUserName(const std::string& UserName)
{
	m_d->m_UserName=UserName;
}

void CoverArtArchive::CHTTPFetch::SetPassword(const std::string& Password)
{
	m_d->m_Password=Password;
}

void CoverArtArchive::CHTTPFetch::SetProxyHost(const std::string& ProxyHost)
{
	m_d->m_ProxyHost=ProxyHost;
}

void CoverArtArchive::CHTTPFetch::SetProxyPort(int ProxyPort)
{
	m_d->m_ProxyPort=ProxyPort;
}

void CoverArtArchive::CHTTPFetch::SetProxyUserName(const std::string& ProxyUserName)
{
	m_d->m_ProxyUserName=ProxyUserName;
}

void CoverArtArchive::CHTTPFetch::SetProxyPassword(const std::string& ProxyPassword)
{
	m_d->m_ProxyPassword=ProxyPassword;
}

int CoverArtArchive::CHTTPFetch::Fetch(const std::string& URL, bool FollowRedirects)
{
	int Ret=0;
	bool Finished=false;

	std::string RequestURL=URL;

	while (!Finished)
	{
		try
		{
			Ret=DoRequest(RequestURL);
			Finished=true;
		}

		catch(CRedirect r)
		{
			if (FollowRedirects)
			{
				RequestURL=r.Location();
				Finished=false;
			}
			else
			{
				throw;
			}
		}

		catch(...)
		{
			throw;
		}
	}

	return Ret;
}

int CoverArtArchive::CHTTPFetch::DoRequest(const std::string& URL)
{
	int Ret=0;

#ifdef _COVERART_DEBUG_
	std::cerr << "Fetching '" << URL << "'" << std::endl;
#endif

	ne_uri uri;
	ne_uri_parse(URL.c_str(),&uri);
	int Port=uri.port;
	if (0==Port)
		Port=ne_uri_defaultport(uri.scheme);

	m_d->m_Data.clear();

	ne_sock_init();

	ne_session *sess=ne_session_create(uri.scheme, uri.host, Port);
	if (sess)
	{
		ne_set_useragent(sess, m_d->m_UserAgent.c_str());

		ne_set_server_auth(sess, httpAuth, this);

		// Use proxy server
		if (!m_d->m_ProxyHost.empty())
		{
			ne_session_proxy(sess, m_d->m_ProxyHost.c_str(), m_d->m_ProxyPort);
			ne_set_proxy_auth(sess, proxyAuth, this);
		}

		ne_request *req = ne_request_create(sess, "GET", uri.path);

		ne_add_response_body_reader(req, ne_accept_2xx, httpResponseReader, &m_d->m_Data);

		m_d->m_Result = ne_request_dispatch(req);
		m_d->m_Status = ne_get_status(req)->code;
		const char *Location = ne_get_response_header(req,"Location");
		std::string strLocation;
		if (0!=Location)
			strLocation=Location;

		Ret=m_d->m_Data.size();

		ne_request_destroy(req);

		m_d->m_ErrorMessage = ne_get_error(sess);

		ne_session_destroy(sess);

		switch (m_d->m_Result)
		{
			case NE_OK:
				break;

			case NE_CONNECT:
			case NE_LOOKUP:
				throw CConnectionError(m_d->m_ErrorMessage);
				break;

			case NE_TIMEOUT:
				throw CTimeoutError(m_d->m_ErrorMessage);
				break;

			case NE_AUTH:
			case NE_PROXYAUTH:
				throw CAuthenticationError(m_d->m_ErrorMessage);
				break;

			default:
				throw CFetchError(m_d->m_ErrorMessage);
				break;
		}

		switch (m_d->m_Status)
		{
			case 200:
				break;

			case 300:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 306:
			case 307:
				throw CRedirect(strLocation);
				break;

			case 400:
				throw CRequestError(m_d->m_ErrorMessage);
				break;

			case 401:
				throw CAuthenticationError(m_d->m_ErrorMessage);
				break;

			case 404:
				throw CResourceNotFoundError(m_d->m_ErrorMessage);
				break;

			default:
				throw CFetchError(m_d->m_ErrorMessage);
				break;
		}
	}

	ne_sock_exit();

	return Ret;
}

int CoverArtArchive::CHTTPFetch::httpAuth(void *userdata, const char *realm, int attempts,
					 char *username, char *password)
{
	realm=realm;

	CoverArtArchive::CHTTPFetch *Fetch = (CoverArtArchive::CHTTPFetch *)userdata;
	strncpy(username, Fetch->m_d->m_UserName.c_str(), NE_ABUFSIZ);
	strncpy(password, Fetch->m_d->m_Password.c_str(), NE_ABUFSIZ);
	return attempts;
}

int CoverArtArchive::CHTTPFetch::proxyAuth(void *userdata, const char *realm, int attempts,
					 char *username, char *password)
{
	realm=realm;

	CoverArtArchive::CHTTPFetch *Fetch = (CoverArtArchive::CHTTPFetch *)userdata;
	strncpy(username, Fetch->m_d->m_ProxyUserName.c_str(), NE_ABUFSIZ);
	strncpy(password, Fetch->m_d->m_ProxyPassword.c_str(), NE_ABUFSIZ);
	return attempts;
}

int CoverArtArchive::CHTTPFetch::httpResponseReader(void *userdata, const char *buf, size_t len)
{
	std::vector<unsigned char> *buffer = reinterpret_cast<std::vector<unsigned char> *>(userdata);

	buffer->insert(buffer->end(),buf,buf+len);

	return 0;
}

std::vector<unsigned char> CoverArtArchive::CHTTPFetch::Data() const
{
	return m_d->m_Data;
}

int CoverArtArchive::CHTTPFetch::Result() const
{
	return m_d->m_Result;
}

int CoverArtArchive::CHTTPFetch::Status() const
{
	return m_d->m_Status;
}

std::string CoverArtArchive::CHTTPFetch::ErrorMessage() const
{
	return m_d->m_ErrorMessage;
}
