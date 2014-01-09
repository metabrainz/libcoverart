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

/**
* Delete a #CaaImageData object
*
* @param ImageData Object to delete
*/
  void caa_imagedata_delete(CaaImageData ImageData);

/**
* Clone a #CaaImageData object
*
* @param ImageData Object to clone
*
* @return Cloned object. This object <b>must</b> be deleted once
*				finished with.
*/
  CaaImageData caa_imagedata_clone(CaaImageData ImageData);

/**
 * Return the number of bytes in a #CaaImageData object
 *
 * @param ImageData #CaaImageData object
 *
 * @return The number of bytes in the object
 */
	int caa_imagedata_size(CaaImageData ImageData);

/**
 * Return the data in a #CaaImageData object
 *
 * @param ImageData #CaaImageData object
 *
 * @return The data in the object. This data <b>must not</b> be deleted.
 */
	unsigned char *caa_imagedata_data(CaaImageData ImageData);

