/* --------------------------------------------------------------------------

   libcoverart - Client library to access CoverArtArchive

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libcoverart.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libcoverart is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _COVERARTARCHIVE_IMAGES_
#define _COVERARTARCHIVE_IMAGES_

#include <iostream>
#include <vector>

#include <jansson.h>

namespace CoverArtArchive
{
	class CImagesPrivate;
	class CImage;

	class CImages
	{
		public:
			CImages(json_t *Root=0);
			CImages(const CImages& Other);
			CImages& operator =(const CImages& Other);
			virtual ~CImages();

			int NumItems() const;
			CImage *Item(int Item) const;

		private:
			CImagesPrivate * const m_d;

			void Cleanup();
	};
}

std::ostream& operator << (std::ostream& os, const CoverArtArchive::CImages& Images);

#endif
