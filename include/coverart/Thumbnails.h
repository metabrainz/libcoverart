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

#ifndef _COVERARTARCHIVE_THUMBNAILS_
#define _COVERARTARCHIVE_THUMBNAILS_

#include <iostream>

#include <jansson.h>

namespace CoverArtArchive
{
	class CThumbnailsPrivate;

	class CThumbnails
	{
		public:
			CThumbnails(json_t *Root=0);
			CThumbnails(const CThumbnails& Other);
			CThumbnails& operator =(const CThumbnails& Other);
			virtual ~CThumbnails();

			std::string Large() const;
			std::string Small() const;

		private:
			CThumbnailsPrivate * const m_d;
	};
}

std::ostream& operator << (std::ostream& os, const CoverArtArchive::CThumbnails& Thumbnails);

#endif
