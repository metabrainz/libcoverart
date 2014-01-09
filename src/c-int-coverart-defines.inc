/* --------------------------------------------------------------------------

   libcoverart - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libcoverart.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libcoverart is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

typedef void *CaaImageData;

/**
 * Create a new instance of #CaaCoverArt.
 *
 * @see CoverArtArchive::CCoverArt::CCoverArt
 *
 * @param UserAgent User agent to be passed to submissions
 *
 * @return The newly created #CaaCoverArt object. This object <b>must</b> be deleted once
 *				finished with.
 */

	CaaCoverArt caa_coverart_new(const char *UserAgent);

/**
 * Set the proxy server
 *
 * @see CoverArtArchive::CCoverArt::SetProxyHost
 *
 * @param CoverArt #CaaCoverArt object
 * @param ProxyHost Proxy server to use
 */
	void caa_coverart_set_proxyhost(CaaCoverArt CoverArt, const char *ProxyHost);

/**
 *	Set the port to use on the proxy server
 *
 * @see CoverArtArchive::CCoverArt::SetProxyPort
 *
 * @param CoverArt #CaaCoverArt object
 * @param ProxyPort Port to use on proxy server
 */
	void caa_coverart_set_proxyport(CaaCoverArt CoverArt, int ProxyPort);

/**
 *	Set the username to use to authenticate to the proxy server
 *
 * @see CoverArtArchive::CCoverArt::SetProxyUserName
 *
 * @param CoverArt #CaaCoverArt object
 * @param	ProxyUserName User name to use
 */
	void caa_coverart_set_proxyusername(CaaCoverArt CoverArt, const char *ProxyUserName);

/**
 * Set the password to use to authenticate to the proxy server
 *
 * @see CoverArtArchive::CCoverArt::SetProxyPassword
 *
 * @param CoverArt #CaaCoverArt object
 * @param ProxyPassword Password to use
 */
	void caa_coverart_set_proxypassword(CaaCoverArt CoverArt, const char *ProxyPassword);

/**
 * Request the front image for a release
 *
 * @see CoverArtArchive::CCoverArt::FetchFront
 *
 * @param CoverArt #CaaCoverArt object
 * @param ReleaseID The release ID
 *
 * @return The downloaded image. This object <b>must</b> be deleted once
 *				finished with.
 */
	CaaImageData caa_coverart_fetch_front(CaaCoverArt CoverArt, const char *ReleaseID);

/**
 * Request the back image for a release
 *
 * @see CoverArtArchive::CCoverArt::FetchBack
 *
 * @param CoverArt #CaaCoverArt object
 * @param ReleaseID The release ID
 *
 * @return The downloaded image. This object <b>must</b> be deleted once
 *				finished with.
 */
	CaaImageData caa_coverart_fetch_back(CaaCoverArt CoverArt, const char *ReleaseID);

	typedef enum
	{
		eSize_Full=0,
		eSize_250=250,
		eSize_500=500
	} tImageSize;

/**
 * Request a specific image for a release
 *
 * @see CoverArtArchive::CCoverArt::FetchImage
 *
 * @param CoverArt #CaaCoverArt object
 * @param ReleaseID The release ID
 * @param ImageID The image ID
 * @param ImageSize The size of image to retrieve
 *
 * @return The downloaded image. This object <b>must</b> be deleted once
 *				finished with.
 */
	CaaImageData caa_coverart_fetch_image(CaaCoverArt CoverArt, const char *ReleaseID, const char *ImageID, tImageSize ImageSize);

/**
 * Request all information about a release
 *
 * @see CoverArtArchive::CCoverArt::ReleaseInfo
 *
 * @param CoverArt #CaaCoverArt object
 * @param ReleaseID The release ID
 *
 * @return Release information. This object <b>must</b> be deleted once
 *				finished with.
 */
	CaaReleaseInfo caa_coverart_releaseinfo(CaaCoverArt CoverArt, const char *ReleaseID);

/**
 * @see CoverArtArchive::CCoverArt::tCoverArtResult
 */

	typedef enum
	{
			eCoverArt_Success=0,
			eCoverArt_ConnectionError,
			eCoverArt_Timeout,
			eCoverArt_AuthenticationError,
			eCoverArt_FetchError,
			eCoverArt_RequestError,
			eCoverArt_ResourceNotFound
	} tCoverArtResult;

/**
 * @see CoverArtArchive::CCoverArt::LastResult
 *
 * @param CoverArt #CaaCoverArt object
 *
 * @return Last CoverArt result code
 */
	tCoverArtResult caa_coverart_get_lastresult(CaaCoverArt CoverArt);

