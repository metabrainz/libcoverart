/* --------------------------------------------------------------------------

   libcoverart - Client library to access CoverArtArchive

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libcoverart.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libcoverart is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _COVERARTARCHIVE_NEON_WRAPPERS_
#define _COVERARTARCHIVE_NEON_WRAPPERS_

#include <ne_socket.h>
#include <ne_session.h>
#include <ne_request.h>

class CNESockWrapper
{
	public:
		CNESockWrapper()
		{
			ne_sock_init();
		}

		~CNESockWrapper()
		{
			ne_sock_exit();
		}
};

class CNESessionWrapper
{
	public:
		CNESessionWrapper(const std::string& Scheme, const std::string& Host, int Port)
		:	m_Session(ne_session_create(Scheme.c_str(), Host.c_str(), Port))
		{
		}

		~CNESessionWrapper()
		{
			ne_session_destroy(m_Session);
		}

		operator ne_session *()
		{
			return m_Session;
		}

		operator bool()
		{
			return 0!=m_Session;
		}

	private:
		ne_session *m_Session;
};

class CNERequestWrapper
{
	public:
		CNERequestWrapper(CNESessionWrapper &SessionWrapper, const std::string& Method, const std::string& Path)
		:	m_Request(ne_request_create(SessionWrapper, Method.c_str(), Path.c_str()))
		{
		}

		~CNERequestWrapper()
		{
			ne_request_destroy(m_Request);
		}

		operator ne_request *()
		{
			return m_Request;
		}

		operator bool()
		{
			return 0!=m_Request;
		}

	private:
		ne_request *m_Request;
};

class CNEURIWrapper
{
	public:
		CNEURIWrapper(const std::string& URL)
		{
			m_Success=(0==ne_uri_parse(URL.c_str(),&m_URI));
		}

		~CNEURIWrapper()
		{
			ne_uri_free(&m_URI);
		}

		operator bool() const
		{
			return m_Success;
		}

		char *Scheme()
		{
			return m_URI.scheme;
		}

		char *Host()
		{
			return m_URI.host;
		}

		char *UserInfo()
		{
			return m_URI.userinfo;
		}

		unsigned int Port()
		{
			return m_URI.port;
		}

		char *Path()
		{
			return m_URI.path;
		}
		char *Query()
		{
			return m_URI.query;
		}
		char *Fragment()
		{
			return m_URI.fragment;
		}

	private:
		bool m_Success;
		ne_uri m_URI;
};

#endif
