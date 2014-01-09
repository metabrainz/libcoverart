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

void caa_imagedata_delete(CaaImageData ImageData)
{
	delete (std::vector<unsigned char> *)ImageData;
}

CaaImageData caa_imagedata_clone(CaaImageData ImageData)
{
	if (ImageData)
		return (CaaImageData)new std::vector<unsigned char>(*(std::vector<unsigned char> *)ImageData);

	return 0;
}

int caa_imagedata_size(CaaImageData ImageData)
{
	if (ImageData)
	{
		try
		{
			std::vector<unsigned char> *TheImageData=reinterpret_cast<std::vector<unsigned char> *>(ImageData);
			if (TheImageData)
				return TheImageData->size();
		}

		catch(...)
		{
		}
	}

	return 0;
}

unsigned char *caa_imagedata_data(CaaImageData ImageData)
{
	if (ImageData)
	{
		try
		{
			std::vector<unsigned char> *TheImageData=reinterpret_cast<std::vector<unsigned char> *>(ImageData);
			if (TheImageData)
				return &(*TheImageData)[0];
		}

		catch(...)
		{
		}
	}

	return 0;
}

