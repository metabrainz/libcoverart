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

#include "config.h"
#include "coverart/defines.h"

#include <iostream>
#include <string>

#include <jansson.h>

#include "coverart/Image.h"
#include "coverart/Thumbnails.h"
#include "coverart/TypeList.h"

class CoverArtArchive::CImagePrivate
{
	public:
		CImagePrivate()
		:	m_Approved(false),
			m_Back(false),
			m_Edit(0),
			m_Front(false),
			m_Thumbnails(0),
			m_TypeList(0)
		{
		};

		bool m_Approved;
		bool m_Back;
		std::string m_Comment;
		int m_Edit;
		bool m_Front;
		std::string m_ID;
		std::string m_Image;
		CThumbnails *m_Thumbnails;
		CTypeList *m_TypeList;
};

CoverArtArchive::CImage::CImage(json_t *Root)
:	m_d(new CImagePrivate)
{
	if (Root && json_is_object(Root))
	{
		json_t *Approved=json_object_get(Root,"approved");
		if (json_is_boolean(Approved))
			m_d->m_Approved=json_is_true(Approved);

		json_t *Back=json_object_get(Root,"back");
		if (json_is_boolean(Back))
			m_d->m_Back=json_is_true(Back);

		json_t *Comment=json_object_get(Root,"comment");
		if (json_is_string(Comment))
		{
			const char *str=json_string_value(Comment);
			if (str)
				m_d->m_Comment=str;
		}

		json_t *Edit=json_object_get(Root,"edit");
		if (json_is_integer(Edit))
			m_d->m_Edit=json_integer_value(Edit);

		json_t *Front=json_object_get(Root,"front");
		if (json_is_boolean(Front))
			m_d->m_Front=json_is_true(Front);

		json_t *ID=json_object_get(Root,"id");
		if (json_is_string(ID))
		{
			const char *str=json_string_value(ID);
			if (str)
				m_d->m_ID=str;
		}

		json_t *Image=json_object_get(Root,"image");
		if (json_is_string(Image))
		{
			const char *str=json_string_value(Image);
			if (str)
				m_d->m_Image=str;
		}

		json_t *Thumbnails=json_object_get(Root,"thumbnails");
		if (json_is_object(Thumbnails))
			m_d->m_Thumbnails=new CThumbnails(Thumbnails);

		json_t *Types=json_object_get(Root,"types");
		if (json_is_array(Types))
			m_d->m_TypeList=new CTypeList(Types);
	}
}

CoverArtArchive::CImage::CImage(const CImage& Other)
:	m_d(new CImagePrivate)
{
	*this=Other;
}

CoverArtArchive::CImage& CoverArtArchive::CImage::operator =(const CImage& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_Approved=Other.m_d->m_Approved;
		m_d->m_Back=Other.m_d->m_Back;
		m_d->m_Comment=Other.m_d->m_Comment;
		m_d->m_Edit=Other.m_d->m_Edit;
		m_d->m_Front=Other.m_d->m_Front;
		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Image=Other.m_d->m_Image;

		if (Other.m_d->m_Thumbnails)
			m_d->m_Thumbnails=new CThumbnails(*Other.m_d->m_Thumbnails);

		if (Other.m_d->m_TypeList)
			m_d->m_TypeList=new CTypeList(*Other.m_d->m_TypeList);
	}

	return *this;
}

CoverArtArchive::CImage::~CImage()
{
	Cleanup();

	delete m_d;
}

void CoverArtArchive::CImage::Cleanup()
{
	delete m_d->m_Thumbnails;
	m_d->m_Thumbnails=0;

	delete m_d->m_TypeList;
	m_d->m_TypeList=0;
}

bool CoverArtArchive::CImage::Approved() const
{
	return m_d->m_Approved;
}

bool CoverArtArchive::CImage::Back() const
{
	return m_d->m_Back;
}

std::string CoverArtArchive::CImage::Comment() const
{
	return m_d->m_Comment;
}

int CoverArtArchive::CImage::Edit() const
{
	return m_d->m_Edit;
}

bool CoverArtArchive::CImage::Front() const
{
	return m_d->m_Front;
}

std::string CoverArtArchive::CImage::ID() const
{
	return m_d->m_ID;
}

std::string CoverArtArchive::CImage::Image() const
{
	return m_d->m_Image;
}

CoverArtArchive::CThumbnails *CoverArtArchive::CImage::Thumbnails() const
{
	return m_d->m_Thumbnails;
}

CoverArtArchive::CTypeList *CoverArtArchive::CImage::TypeList() const
{
	return m_d->m_TypeList;
}

std::ostream& operator << (std::ostream& os, const CoverArtArchive::CImage& Image)
{
	os << "  Image:" << std::endl;

	os << "    Approved: " << Image.Approved() << std::endl;
	os << "    Back: " << Image.Back() << std::endl;
	os << "    Comment: " << Image.Comment() << std::endl;
	os << "    Edit: " << Image.Edit() << std::endl;
	os << "    Front: " << Image.Front() << std::endl;
	os << "    ID: " << Image.ID() << std::endl;
	os << "    Image: " << Image.Image() << std::endl;

	if (Image.Thumbnails())
		os << *Image.Thumbnails() << std::endl;

	if (Image.TypeList())
		os << *Image.TypeList() << std::endl;

	return os;
}

