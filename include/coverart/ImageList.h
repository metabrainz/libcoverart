/* --------------------------------------------------------------------------

   libcoverart - Client library to access CoverArtArchive

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libcoverart.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libcoverart is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _COVERARTARCHIVE_IMAGELIST_
#define _COVERARTARCHIVE_IMAGELIST_

#include <iostream>
#include <vector>

#include <jansson.h>

namespace CoverArtArchive
{
	class CImageListPrivate;
	class CImage;

	class CImageList
	{
		public:
			CImageList(json_t *Root=0);
			CImageList(const CImageList& Other);
			CImageList& operator =(const CImageList& Other);
			virtual ~CImageList();

			int NumItems() const;
			CImage *Item(int Item) const;

		private:
			CImageListPrivate * const m_d;

			void Cleanup();
	};
}

std::ostream& operator << (std::ostream& os, const CoverArtArchive::CImageList& Images);

#endif
