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

#include "coverart/ReleaseInfo.h"
#include "coverart/ImageList.h"

class CoverArtArchive::CReleaseInfoPrivate
{
	public:
		CReleaseInfoPrivate():
			m_ImageList(0)
		{
		};

		std::string m_Release;
		CoverArtArchive::CImageList *m_ImageList;
};

CoverArtArchive::CReleaseInfo::CReleaseInfo(const std::string& JSON)
:	m_d(new CReleaseInfoPrivate)
{
	json_error_t error;
	json_t *Root=json_loads(JSON.c_str(),0,&error);
	if (Root && json_is_object(Root))
	{
		json_t *Release=json_object_get(Root,"release");
		if (Release && json_is_string(Release))
			m_d->m_Release=json_string_value(Release);

		json_t *Images=json_object_get(Root,"images");
		if (Images && json_is_array(Images))
			m_d->m_ImageList=new CImageList(Images);
	}

	json_decref(Root);
}

CoverArtArchive::CReleaseInfo::CReleaseInfo(const CReleaseInfo& Other)
:	m_d(new CReleaseInfoPrivate)
{
	*this=Other;
}

CoverArtArchive::CReleaseInfo& CoverArtArchive::CReleaseInfo::operator =(const CReleaseInfo& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_Release=Other.m_d->m_Release;
		m_d->m_ImageList=new CImageList(*Other.m_d->m_ImageList);
	}

	return *this;
}

CoverArtArchive::CReleaseInfo::~CReleaseInfo()
{
	Cleanup();

	delete m_d;
}

void CoverArtArchive::CReleaseInfo::Cleanup()
{
	delete m_d->m_ImageList;
	m_d->m_ImageList=0;
}

std::string CoverArtArchive::CReleaseInfo::Release() const
{
	return m_d->m_Release;
}

CoverArtArchive::CImageList *CoverArtArchive::CReleaseInfo::ImageList() const
{
	return m_d->m_ImageList;
}

std::ostream& operator << (std::ostream& os, const CoverArtArchive::CReleaseInfo& ReleaseInfo)
{
	os << "Release: " << ReleaseInfo.Release() << std::endl;

	if (ReleaseInfo.ImageList())
		os << *ReleaseInfo.ImageList() << std::endl;

	return os;
}

