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

#ifndef _COVERARTARCHIVE_COVER_ART_
#define _COVERARTARCHIVE_COVER_ART_

#include <string>
#include <vector>

#include "coverart/ReleaseInfo.h"

/**
 * @mainpage libcoverart
 *
 * This is the documentation for libcoverart, a library for retrieving coverart
 * from the <a target="_blank" href="http://coverartarchive.org">Covert Art Archive</a>.
 *
 * The main entry point to the library is the CoverArtArchive::CCoverArt object.
 *
 * For details of the C interface, see the documentation for the file caa_c.h.
 *
 * Please report any issues with this library at
 * <a target="_blank" href="http://tickets.musicbrainz.org/">http://tickets.musicbrainz.org/</a>.
 *
 * @par Compiling and Linking
 *
 * This package provides a pkg-config script that returns the necessary compiler
 * and linker flags, as well as the version number.  To build a small sample
 * program one would use:
 *
 * @par
 *     <tt>g++ -o test_app test_app.cpp `pkg-config libcoverart --cflags --libs`</tt>
 *
 * If you don't want/can't use pkg-config and you are using the C API, make sure
 * you link in the C++ standard library:
 *
 * @par
 *     <tt>gcc -o test_app test_app.c -lcoverart -lm -lstdc++</tt>
 *
 * @par Compiling and Linking
 *
 * @par
 *
 * A brief example showing how to retrieve the 'front' artwork for a release
@code
CoverArtArchive::CCoverArt CoverArt("example-1.0");

try
{
	std::vector<unsigned char> ImageData=CoverArt.FetchFront(ReleaseID);
	if (ImageData.size())
	{
		std::stringstream FileName;
		FileName << ReleaseID << "-front.jpg";
		std::cout << "Saving front to '" << FileName.str() << "'" << std::endl;

		std::ofstream Front(FileName.str().c_str());
		Front.write((const char *)&ImageData[0],ImageData.size());
		Front.close();
	}
}

catch (CoverArtArchive::CConnectionError& Error)
{
	std::cout << "Connection Exception: '" << Error.what() << "'" << std::endl;
	std::cout << "LastResult: " << CoverArt.LastResult() << std::endl;
	std::cout << "LastHTTPCode: " << CoverArt.LastHTTPCode() << std::endl;
	std::cout << "LastErrorMessage: " << CoverArt.LastErrorMessage() << std::endl;
}

catch (CoverArtArchive::CTimeoutError& Error)
{
	std::cout << "Timeout Exception: '" << Error.what() << "'" << std::endl;
	std::cout << "LastResult: " << CoverArt.LastResult() << std::endl;
	std::cout << "LastHTTPCode: " << CoverArt.LastHTTPCode() << std::endl;
	std::cout << "LastErrorMessage: " << CoverArt.LastErrorMessage() << std::endl;
}

catch (CoverArtArchive::CAuthenticationError& Error)
{
	std::cout << "Authentication Exception: '" << Error.what() << "'" << std::endl;
	std::cout << "LastResult: " << CoverArt.LastResult() << std::endl;
	std::cout << "LastHTTPCode: " << CoverArt.LastHTTPCode() << std::endl;
	std::cout << "LastErrorMessage: " << CoverArt.LastErrorMessage() << std::endl;
}

catch (CoverArtArchive::CFetchError& Error)
{
	std::cout << "Fetch Exception: '" << Error.what() << "'" << std::endl;
	std::cout << "LastResult: " << CoverArt.LastResult() << std::endl;
	std::cout << "LastHTTPCode: " << CoverArt.LastHTTPCode() << std::endl;
	std::cout << "LastErrorMessage: " << CoverArt.LastErrorMessage() << std::endl;
}

catch (CoverArtArchive::CRequestError& Error)
{
	std::cout << "Request Exception: '" << Error.what() << "'" << std::endl;
	std::cout << "LastResult: " << CoverArt.LastResult() << std::endl;
	std::cout << "LastHTTPCode: " << CoverArt.LastHTTPCode() << std::endl;
	std::cout << "LastErrorMessage: " << CoverArt.LastErrorMessage() << std::endl;
}

catch (CoverArtArchive::CResourceNotFoundError& Error)
{
	std::cout << "ResourceNotFound Exception: '" << Error.what() << "'" << std::endl;
	std::cout << "LastResult: " << CoverArt.LastResult() << std::endl;
	std::cout << "LastHTTPCode: " << CoverArt.LastHTTPCode() << std::endl;
	std::cout << "LastErrorMessage: " << CoverArt.LastErrorMessage() << std::endl;
}
@endcode
 */

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
		/**
		 * @brief Enumerated type for image size
		 *
		 * Enumerated type for image size
		 */
		enum tImageSize
		{
			eSize_Full=0,
			eSize_250=250,
			eSize_500=500
		};

		/**
		 * @brief Enumerated type for query status
		 *
		 * Enumerated type for query status
		 */
		enum tCoverArtResult
		{
			eCoverArt_Success=0,
			eCoverArt_ConnectionError,
			eCoverArt_Timeout,
			eCoverArt_AuthenticationError,
			eCoverArt_FetchError,
			eCoverArt_RequestError,
			eCoverArt_ResourceNotFound
		};

		/**
		 * @brief Constructor
		 *
		 * Constructor
		 *
     * @param UserAgent User agent to use in any queries and submissions. The format
     *              is @c "application-version", where application is your application's name
     *              and version is a version number which may not contain a '-' character.
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
		 * Request a specific image for a release
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

		/**
		 * @brief Return release information for a release
		 *
		 * Return release information for a release
		 *
		 * @param ReleaseID The release ID
		 *
		 * @return Release information
		 *
		 * @throw CConnectionError An error occurred connecting to the web server
		 * @throw CTimeoutError A timeout occurred when connecting to the web server
		 * @throw CAuthenticationError An authentication error occurred
		 * @throw CFetchError An error occurred fetching data
		 * @throw CRequestError The request was invalid
		 * @throw CResourceNotFoundError The requested resource was not found
		 */

		CReleaseInfo ReleaseInfo(const std::string& ReleaseID) const;

		/**
		 * @brief Return result of the last query
		 *
		 * Return the result of the last query
		 *
		 * @return Result of last query
		 */

		tCoverArtResult LastResult() const;

		/**
		 * @brief Return HTTP code of the last query
		 *
		 * Return the HTTP code of the last query
		 *
		 * @return HTTP code of last query
		 */
		int LastHTTPCode() const;

		/**
		 * @brief Return error message from the last query
		 *
		 * Return the error message from the last query
		 *
		 * @return Error message from last query
		 */
		std::string LastErrorMessage() const;

		/**
		 * @brief Return the library version
		 *
		 * Return the library version
		 *
		 * @return Library version
		 */
		std::string Version() const;

	private:
		CCoverArtPrivate * const m_d;

		std::vector<unsigned char> MakeRequest(const std::string& URL) const;
	};
}

#endif
