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

#include <vector>

#include <jansson.h>

#include "coverart/Images.h"
#include "coverart/Image.h"

class CoverArtArchive::CImagesPrivate
{
	public:
		CImagesPrivate()
		{
		};

		std::vector<CoverArtArchive::CImage *> m_Images;
};

CoverArtArchive::CImages::CImages(json_t *Root)
:	m_d(new CImagesPrivate)
{
	if (Root && json_is_array(Root))
	{
		for (size_t count=0;count<json_array_size(Root);count++)
		{
			json_t *Image=json_array_get(Root,count);
			m_d->m_Images.push_back(new CImage(Image));
		}
	}
}

CoverArtArchive::CImages::CImages(const CImages& Other)
:	m_d(new CImagesPrivate)
{
	*this=Other;
}

CoverArtArchive::CImages& CoverArtArchive::CImages::operator =(const CImages& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		std::vector<CImage *>::const_iterator ThisImage=Other.m_d->m_Images.begin();
		while (ThisImage!=Other.m_d->m_Images.end())
		{
			CImage *Image=(*ThisImage);
			m_d->m_Images.push_back(new CImage(*Image));
			++ThisImage;
		}
	}

	return *this;
}

CoverArtArchive::CImages::~CImages()
{
	delete m_d;
}

void CoverArtArchive::CImages::Cleanup()
{
	while (!m_d->m_Images.empty())
	{
		delete m_d->m_Images.back();
		m_d->m_Images.pop_back();
	}
}

std::vector<CoverArtArchive::CImage *> CoverArtArchive::CImages::Images() const
{
	return m_d->m_Images;
}

std::ostream& operator << (std::ostream& os, const CoverArtArchive::CImages& Images)
{
	std::vector<CoverArtArchive::CImage *> ImageList=Images.Images();

	for (std::vector<CoverArtArchive::CImage *>::const_iterator ThisImage=ImageList.begin();ThisImage!=ImageList.end();++ThisImage)
		os << **ThisImage << std::endl;

	return os;
}


