/* --------------------------------------------------------------------------

   libcoverart - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libcoverart.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libcoverart is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

CaaCoverArt caa_coverart_new(const char *UserAgent)
{
	return new CoverArtArchive::CCoverArt(UserAgent);
}

CAA_C_STR_SETTER(CoverArt,coverart,ProxyHost,proxyhost)
CAA_C_INT_SETTER(CoverArt,coverart,ProxyPort,proxyport)
CAA_C_STR_SETTER(CoverArt,coverart,ProxyUserName,proxyusername)
CAA_C_STR_SETTER(CoverArt,coverart,ProxyPassword,proxypassword)

CaaImageData caa_coverart_fetch_front(CaaCoverArt CoverArt, const char *ReleaseID)
{
	if (CoverArt)
	{
		try
		{
			CoverArtArchive::CCoverArt *TheCoverArt=reinterpret_cast<CoverArtArchive::CCoverArt *>(CoverArt);
			if (TheCoverArt)
				return new std::vector<unsigned char>(TheCoverArt->FetchFront(ReleaseID));
		}

		catch(...)
		{
		}
	}

	return 0;
}

CaaImageData caa_coverart_fetch_back(CaaCoverArt CoverArt, const char *ReleaseID)
{
	if (CoverArt)
	{
		try
		{
			CoverArtArchive::CCoverArt *TheCoverArt=reinterpret_cast<CoverArtArchive::CCoverArt *>(CoverArt);
			if (TheCoverArt)
				return new std::vector<unsigned char>(TheCoverArt->FetchBack(ReleaseID));
		}

		catch(...)
		{
		}
	}

	return 0;
}

CaaImageData caa_coverart_fetch_image(CaaCoverArt CoverArt, const char *ReleaseID, const char *ImageID, tImageSize ImageSize)
{
	if (CoverArt)
	{
		try
		{
			CoverArtArchive::CCoverArt *TheCoverArt=reinterpret_cast<CoverArtArchive::CCoverArt *>(CoverArt);
			if (TheCoverArt)
				return new std::vector<unsigned char>(TheCoverArt->FetchImage(ReleaseID,ImageID,static_cast<CoverArtArchive::CCoverArt::tImageSize>(ImageSize)));
		}

		catch(...)
		{
		}
	}

	return 0;
}

CaaReleaseInfo caa_coverart_releaseinfo(CaaCoverArt CoverArt, const char *ReleaseID)
{
	if (CoverArt)
	{
		try
		{
			CoverArtArchive::CCoverArt *TheCoverArt=reinterpret_cast<CoverArtArchive::CCoverArt *>(CoverArt);
			if (TheCoverArt)
				return new CoverArtArchive::CReleaseInfo(TheCoverArt->ReleaseInfo(ReleaseID));
		}

		catch(...)
		{
		}
	}

	return 0;
}

tCoverArtResult caa_coverart_get_lastresult(CaaCoverArt o)
{
	if (o)
	{
		try
		{
			return (tCoverArtResult)((CoverArtArchive::CCoverArt *)o)->LastResult();
		}

		catch (...)
		{
		}
	}

	return eCoverArt_FetchError;
}

