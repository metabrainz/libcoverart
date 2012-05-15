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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coverart/caa_c.h"

int main(int argc, const char *argv[])
{
	int Tmp=argc;
	const char **Tmp2=argv;
	CaaCoverArt CoverArt=0;

	Tmp=Tmp;
	Tmp2=Tmp2;

	CoverArt=caa_coverart_new("test-1.0");
	if (CoverArt)
	{
		char Version[256];

		caa_coverart_get_version(CoverArt,Version,sizeof(Version));
		printf("Version: '%s'\n",Version);

		caa_coverart_delete(CoverArt);
	}

	return 0;
}

void CompileTest()
{
	CaaCoverArt CoverArt=0;
	CaaImage Image=0;
	CaaImageData ImageData=0;
	CaaImageList ImageList=0;
	CaaReleaseInfo ReleaseInfo=0;
	CaaThumbnails Thumbnails=0;
	CaaType Type=0;
	CaaTypeList TypeList=0;
	char Str[256];
	int Size=sizeof(Str);
	int DummyInt=0;
	double DummyDouble=0;
	unsigned char *DummyData=0;
	unsigned char DummyBool=0;
	tCoverArtResult DummyResult=eCoverArt_Success;

	CoverArt=caa_coverart_new("test");
	caa_coverart_set_proxyhost(CoverArt,"");
	caa_coverart_set_proxyport(CoverArt,0);
	caa_coverart_set_proxyusername(CoverArt,"");
	caa_coverart_set_proxypassword(CoverArt,"");
	ImageData=caa_coverart_fetch_front(CoverArt,"");
	ImageData=caa_coverart_fetch_back(CoverArt,"");
	ImageData=caa_coverart_fetch_image(CoverArt,"","",eSize_500);
	DummyResult=caa_coverart_get_lastresult(CoverArt);
	DummyInt=caa_coverart_get_lasthttpcode(CoverArt);
	caa_coverart_get_lasterrormessage(CoverArt,Str,Size);
	caa_coverart_get_version(CoverArt,Str,Size);
	CoverArt=caa_coverart_clone(CoverArt);
	caa_coverart_delete(CoverArt);

	DummyBool=caa_image_get_approved(Image);
	DummyBool=caa_image_get_back(Image);
	caa_image_get_comment(Image,Str,Size);
	DummyInt=caa_image_get_edit(Image);
	DummyBool=caa_image_get_front(Image);
	caa_image_get_id(Image,Str,Size);
	caa_image_get_image(Image,Str,Size);
	Thumbnails=caa_image_get_thumbnails(Image);
	TypeList=caa_image_get_typelist(Image);
	DummyBool=caa_image_get_approved(Image);
	DummyBool=caa_image_get_approved(Image);
	Image=caa_image_clone(Image);
	caa_image_delete(Image);

	DummyInt=caa_imagedata_size(ImageData);
	DummyData=caa_imagedata_data(ImageData);
	ImageData=caa_imagedata_clone(ImageData);
	caa_imagedata_delete(ImageData);

	caa_releaseinfo_get_release(ReleaseInfo,Str,Size);
	ImageList=caa_releaseinfo_get_imagelist(ReleaseInfo);
	ReleaseInfo=caa_releaseinfo_clone(ReleaseInfo);
	caa_releaseinfo_delete(ReleaseInfo);

	caa_thumbnails_get_large(Thumbnails,Str,Size);
	caa_thumbnails_get_small(Thumbnails,Str,Size);
	Thumbnails=caa_thumbnails_clone(Thumbnails);
	caa_thumbnails_delete(Thumbnails);

	caa_type_get_type(Type,Str,Size);
	Type=caa_type_clone(Type);
	caa_type_delete(Type);

	DummyInt=caa_image_list_size(ImageList);
	Image=caa_image_list_item(ImageList,0);
	ImageList=caa_image_list_clone(ImageList);
	caa_image_list_delete(ImageList);

	DummyInt=caa_type_list_size(TypeList);
	Type=caa_type_list_item(TypeList,0);
	TypeList=caa_type_list_clone(TypeList);
	caa_type_list_delete(TypeList);

	DummyInt=DummyInt;
	DummyDouble=DummyDouble;
	DummyBool=DummyBool;
}
