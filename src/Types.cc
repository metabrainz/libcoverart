/* --------------------------------------------------------------------------

   libcoverart - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

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

#include "config.h"
#include "coverart/defines.h"

#include <string>
#include <vector>

#include <jansson.h>

#include "coverart/Types.h"
#include "coverart/Image.h"

class CoverArtArchive::CTypesPrivate
{
	public:
		CTypesPrivate()
		{
		};

		std::vector<std::string> m_Types;
};

CoverArtArchive::CTypes::CTypes(json_t *Root)
:	m_d(new CTypesPrivate)
{
	if (Root && json_is_array(Root))
	{
		for (size_t count=0;count<json_array_size(Root);count++)
		{
			json_t *Type=json_array_get(Root,count);
			if (json_is_string(Type))
			{
				const char *str=json_string_value(Type);
				if (str)
					m_d->m_Types.push_back(str);
			}
		}
	}
}

CoverArtArchive::CTypes::CTypes(const CTypes& Other)
:	m_d(new CTypesPrivate)
{
	*this=Other;
}

CoverArtArchive::CTypes& CoverArtArchive::CTypes::operator =(const CTypes& Other)
{
	if (this!=&Other)
	{
		m_d->m_Types=Other.m_d->m_Types;
	}

	return *this;
}

CoverArtArchive::CTypes::~CTypes()
{
	delete m_d;
}

std::vector<std::string> CoverArtArchive::CTypes::Types() const
{
	return m_d->m_Types;
}

std::ostream& operator << (std::ostream& os, const CoverArtArchive::CTypes& Types)
{
	std::vector<std::string> TypesList=Types.Types();

	os << "          Types: " << std::endl;
	for(std::vector<std::string>::const_iterator ThisType=TypesList.begin();ThisType!=TypesList.end();++ThisType)
		os << "            " << (*ThisType) << std::endl;

	return os;
}
