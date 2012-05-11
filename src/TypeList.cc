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

#include "coverart/TypeList.h"
#include "coverart/Type.h"

class CoverArtArchive::CTypeListPrivate
{
	public:
		CTypeListPrivate()
		{
		};

		std::vector<CType *> m_Types;
};

CoverArtArchive::CTypeList::CTypeList(json_t *Root)
:	m_d(new CTypeListPrivate)
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
					m_d->m_Types.push_back(new CType(str));
			}
		}
	}
}

CoverArtArchive::CTypeList::CTypeList(const CTypeList& Other)
:	m_d(new CTypeListPrivate)
{
	*this=Other;
}

CoverArtArchive::CTypeList& CoverArtArchive::CTypeList::operator =(const CTypeList& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		std::vector<CType *>::const_iterator ThisType=Other.m_d->m_Types.begin();
		while (ThisType!=Other.m_d->m_Types.end())
		{
			CType *Type=(*ThisType);
			m_d->m_Types.push_back(new CType(*Type));
			++ThisType;
		}
	}

	return *this;
}

CoverArtArchive::CTypeList::~CTypeList()
{
	Cleanup();

	delete m_d;
}

void CoverArtArchive::CTypeList::Cleanup()
{
	while (!m_d->m_Types.empty())
	{
		delete m_d->m_Types.back();
		m_d->m_Types.pop_back();
	}
}

int CoverArtArchive::CTypeList::NumItems() const
{
	return m_d->m_Types.size();
}

CoverArtArchive::CType *CoverArtArchive::CTypeList::Item(int Item) const
{
	return m_d->m_Types[Item];
}

std::ostream& operator << (std::ostream& os, const CoverArtArchive::CTypeList& TypeList)
{
	os << "          TypeList: " << std::endl;
	for (int count=0;count<TypeList.NumItems();count++)
		os << "            " << *TypeList.Item(count) << std::endl;

	return os;
}
