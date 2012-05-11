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

#ifndef _COVERARTARCHIVE_TYPE_
#define _COVERARTARCHIVE_TYPE_

#include <iostream>

namespace CoverArtArchive
{
	class CTypePrivate;

	class CType
	{
		public:
			CType(const std::string& Type);
			CType(const CType& Other);
			CType& operator =(const CType& Other);
			virtual ~CType();

			std::string Type() const;

		private:
			CTypePrivate * const m_d;
	};
}

std::ostream& operator << (std::ostream& os, const CoverArtArchive::CType& Type);

#endif
