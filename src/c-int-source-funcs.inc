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

#include "coverart/defines.h"

#include "coverart/caa_c.h"

#include <string.h>
#include <vector>

#include "coverart/CoverArt.h"
#include "coverart/HTTPFetch.h"
#include "coverart/Image.h"
#include "coverart/ImageList.h"
#include "coverart/ReleaseInfo.h"
#include "coverart/Thumbnails.h"
#include "coverart/Type.h"
#include "coverart/TypeList.h"

#define CAA_C_DELETE(TYPE1, TYPE2) \
	void \
	caa_##TYPE2##_delete(Caa##TYPE1 o) \
	{ \
		delete (CoverArtArchive::C##TYPE1 *)o; \
	}

#define CAA_C_CLONE(TYPE1, TYPE2) \
	Caa##TYPE1 \
	caa_##TYPE2##_clone(Caa##TYPE1 o) \
	{ \
		if (o) \
			return (Caa##TYPE1)new CoverArtArchive::C##TYPE1(*(CoverArtArchive::C##TYPE1 *)o); \
		return 0;\
	}

#define CAA_C_STR_SETTER(TYPE1, TYPE2, PROP1, PROP2) \
	void \
	caa_##TYPE2##_set_##PROP2(Caa##TYPE1 o, const char *str) \
	{ \
		if (o) \
		{ \
			try { \
				((CoverArtArchive::C##TYPE1 *)o)->Set##PROP1(str); \
			} \
			catch (...) { \
			} \
		} \
	}

#define CAA_C_INT_SETTER(TYPE1, TYPE2, PROP1, PROP2) \
	void \
	caa_##TYPE2##_set_##PROP2(Caa##TYPE1 o, int i) \
	{ \
		if (o) \
		{ \
			try { \
				((CoverArtArchive::C##TYPE1 *)o)->Set##PROP1(i); \
			} \
			catch (...) { \
			} \
		} \
	}

#define CAA_C_STR_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	int \
	caa_##TYPE2##_get_##PROP2(Caa##TYPE1 o, char *str, int len) \
	{ \
		int ret=0; \
		if (str) \
			*str=0; \
		if (o) \
		{ \
			try { \
				ret=((CoverArtArchive::C##TYPE1 *)o)->PROP1().length(); \
				if (str && len) \
				{ \
					strncpy(str, ((CoverArtArchive::C##TYPE1 *)o)->PROP1().c_str(), len); \
					str[len-1]='\0'; \
				} \
			} \
			catch (...) { \
				str[0] = '\0'; \
			} \
		} \
		return ret; \
	}

#define CAA_C_INT_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	int \
	caa_##TYPE2##_get_##PROP2(Caa##TYPE1 o) \
	{ \
		if (o) \
		{ \
			try { \
				return ((CoverArtArchive::C##TYPE1 *)o)->PROP1(); \
			} \
			catch (...) { \
			} \
		} \
		return 0; \
	}

#define CAA_C_DOUBLE_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	double \
	caa_##TYPE2##_get_##PROP2(Caa##TYPE1 o) \
	{ \
		if (o) \
		{ \
			try { \
				return ((CoverArtArchive::C##TYPE1 *)o)->PROP1(); \
			} \
			catch (...) { \
			} \
		} \
		return 0; \
	}

#define CAA_C_BOOL_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	unsigned char \
	caa_##TYPE2##_get_##PROP2(Mb##TYPE1 o) \
	{ \
		if (o) \
		{ \
			try { \
				return ((TYPE1 *)o)->PROP1() ? 1 : 0; \
			} \
			catch (...) { \
				return 0; \
			} \
		} \
	}

#define CAA_C_OBJ_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	Caa##PROP1 \
	caa_##TYPE2##_get_##PROP2(Caa##TYPE1 o) \
	{ \
		if (o) \
		{ \
			try { \
				return (Caa##PROP1)((CoverArtArchive::C##TYPE1 *)o)->PROP1(); \
			} \
			catch (...) { \
			} \
		} \
		return (Caa##PROP1)0; \
	}

#define CAA_C_LIST_GETTER(TYPE1, TYPE2) \
	void \
	caa_##TYPE2##_list_delete(Caa##TYPE1 o) \
	{ \
		delete (CoverArtArchive::C##TYPE1##List *)o; \
	} \
	int \
	caa_##TYPE2##_list_size(Caa##TYPE1##List List) \
	{ \
		if (List) \
		{ \
			try { \
				return ((CoverArtArchive::C##TYPE1##List *)List)->NumItems(); \
			} \
			catch (...) { \
				return 0; \
			} \
		} \
		return 0; \
	} \
 \
	Caa##TYPE1 \
	caa_##TYPE2##_list_item(Caa##TYPE1##List List, int Item) \
	{ \
		if (List) \
		{ \
			try { \
				return ((CoverArtArchive::C##TYPE1##List *)List)->Item(Item); \
			} \
			catch (...) { \
				return (Caa##TYPE1)0; \
			} \
		} \
		return (Caa##TYPE1)0; \
	} \

