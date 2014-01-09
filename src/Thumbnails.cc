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

#include "config.h"
#include "coverart/defines.h"

#include <iostream>
#include <string>

#include <jansson.h>

#include "coverart/Thumbnails.h"

class CoverArtArchive::CThumbnailsPrivate
{
	public:
		CThumbnailsPrivate()
		{
		};

		std::string m_Large;
		std::string m_Small;
};

CoverArtArchive::CThumbnails::CThumbnails(json_t *Root)
:	m_d(new CThumbnailsPrivate)
{
	if (Root && json_is_object(Root))
	{
		json_t *Large=json_object_get(Root,"large");
		if (json_is_string(Large))
		{
			const char *str=json_string_value(Large);
			if (str)
				m_d->m_Large=str;
		}

		json_t *Small=json_object_get(Root,"small");
		if (json_is_string(Small))
		{
			const char *str=json_string_value(Small);
			if (str)
				m_d->m_Small=str;
		}
	}
}

CoverArtArchive::CThumbnails::CThumbnails(const CThumbnails& Other)
:	m_d(new CThumbnailsPrivate)
{
	*this=Other;
}

CoverArtArchive::CThumbnails& CoverArtArchive::CThumbnails::operator =(const CThumbnails& Other)
{
	if (this!=&Other)
	{
		m_d->m_Large=Other.m_d->m_Large;
		m_d->m_Small=Other.m_d->m_Small;
	}

	return *this;
}

CoverArtArchive::CThumbnails::~CThumbnails()
{
	delete m_d;
}

std::string CoverArtArchive::CThumbnails::Large() const
{
	return m_d->m_Large;
}

std::string CoverArtArchive::CThumbnails::Small() const
{
	return m_d->m_Small;
}

std::ostream& operator << (std::ostream& os, const CoverArtArchive::CThumbnails& Thumbnails)
{
	os << "      Thumbnails:" << std::endl;
	os << "        Large: '" << Thumbnails.Large() << "'" << std::endl;
	os << "        Small: '" << Thumbnails.Small() << "'" << std::endl;

	return os;
}

