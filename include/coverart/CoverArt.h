/* --------------------------------------------------------------------------

   libcoverart - Client library to access CoverArtArchive

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libcoverart.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libcoverart is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _COVERARTARCHIVE_COVER_ART_
#define _COVERARTARCHIVE_COVER_ART_

#include <string>
#include <vector>

#include "coverart/ReleaseInfo.h"

namespace CoverArtArchive
{
	class CCoverArtPrivate;

	/**
	 * @brief Object for making cover art requests
	 *
	 * Object to be used to make cover art requests
	 *
	 */
	class CCoverArt
	{
	public:
		typedef enum
		{
			eSize_Full,
			eSize_250,
			eSize_500
		} tImageSize;

		/**
		 * @brief Constructor
		 *
		 * Constructor
		 *
		 * @param UserAgent User agent string to send
		 */


		CCoverArt(const std::string& UserAgent);
		~CCoverArt();

		/**
		 * @brief Set the proxy server to use
		 *
		 * Set the proxy server to use when connecting with the web server
		 *
		 * @param ProxyHost Proxy server to use
		 */

		void SetProxyHost(const std::string& ProxyHost);

		/**
		 * @brief Set the proxy port to use
		 *
		 * Set the proxy server port to use when connecting to the web server
		 *
		 * @param ProxyPort Proxy server port to use
		 */

		void SetProxyPort(int ProxyPort);

		/**
		 * @brief Set the proxy user name to use
		 *
		 * Set the user name to use when authenticating with the proxy server
		 *
		 * @param ProxyUserName Proxy user name to use
		 */

		void SetProxyUserName(const std::string& ProxyUserName);

		/**
		 * @brief Set the proxy password to use
		 *
		 * Set the password to use when authenticating with the proxy server
		 *
		 * @param ProxyPassword Proxy server password to use
		 */

		void SetProxyPassword(const std::string& ProxyPassword);

		/**
		 * @brief Request the front image for a release
		 *
		 * Request the front image for a release
		 *
		 * @param ReleaseID The release ID
		 *
		 * @return The downloaded image
		 *
		 * @throw CConnectionError An error occurred connecting to the web server
		 * @throw CTimeoutError A timeout occurred when connecting to the web server
		 * @throw CAuthenticationError An authentication error occurred
		 * @throw CFetchError An error occurred fetching data
		 * @throw CRequestError The request was invalid
		 * @throw CResourceNotFoundError The requested resource was not found
		 */

		std::vector<unsigned char> FetchFront(const std::string& ReleaseID) const;

		/**
		 * @brief Request the back image for a release
		 *
		 * Request the back image for a release
		 *
		 * @param ReleaseID The release ID
		 *
		 * @return The downloaded image
		 *
		 * @throw CConnectionError An error occurred connecting to the web server
		 * @throw CTimeoutError A timeout occurred when connecting to the web server
		 * @throw CAuthenticationError An authentication error occurred
		 * @throw CFetchError An error occurred fetching data
		 * @throw CRequestError The request was invalid
		 * @throw CResourceNotFoundError The requested resource was not found
		 */

		std::vector<unsigned char> FetchBack(const std::string& ReleaseID) const;

		/**
		 * @brief Fetch a specific image for a release
		 *
		 *
		 *
		 * @param ReleaseID The release ID
		 * @param ImageID The image ID
		 * @param ImageSize The image size
		 *
		 * @return The downloaded image
		 *
		 * @throw CConnectionError An error occurred connecting to the web server
		 * @throw CTimeoutError A timeout occurred when connecting to the web server
		 * @throw CAuthenticationError An authentication error occurred
		 * @throw CFetchError An error occurred fetching data
		 * @throw CRequestError The request was invalid
		 * @throw CResourceNotFoundError The requested resource was not found
		 */

		std::vector<unsigned char> FetchImage(const std::string& ReleaseID, const std::string& ImageID, tImageSize ImageSize=eSize_Full) const;

		CReleaseInfo ReleaseInfo(const std::string& ReleaseID) const;
	private:
		CCoverArtPrivate * const m_d;

		std::vector<unsigned char> MakeRequest(const std::string& URL) const;
	};
}

#endif
