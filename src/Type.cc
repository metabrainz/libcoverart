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

#include <iostream>
#include <string>

#include "coverart/Type.h"

class CoverArtArchive::CTypePrivate
{
	public:
		CTypePrivate()
		{
		};

		std::string m_Type;
};

CoverArtArchive::CType::CType(const std::string& Type)
:	m_d(new CTypePrivate)
{
	m_d->m_Type=Type;
}

CoverArtArchive::CType::CType(const CType& Other)
:	m_d(new CTypePrivate)
{
	*this=Other;
}

CoverArtArchive::CType& CoverArtArchive::CType::operator =(const CType& Other)
{
	if (this!=&Other)
	{
		m_d->m_Type=Other.m_d->m_Type;
	}

	return *this;
}

CoverArtArchive::CType::~CType()
{
	delete m_d;
}

std::string CoverArtArchive::CType::Type() const
{
	return m_d->m_Type;
}

std::ostream& operator << (std::ostream& os, const CoverArtArchive::CType& Type)
{
	os << "Type: " << Type.Type() << std::endl;

	return os;
}

