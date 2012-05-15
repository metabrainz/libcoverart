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
#include <limits.h>
#include <string.h>

#include "coverart/caa_c.h"

int main(int argc, const char *argv[])
{
	if (argc==2)
	{
		const char *ReleaseID=argv[1];
		CaaCoverArt CoverArt=caa_coverart_new("c-example-1.0");
		if (CoverArt)
		{
			CaaReleaseInfo ReleaseInfo;

			CaaImageData ImageData=caa_coverart_fetch_front(CoverArt,ReleaseID);
			if (ImageData)
			{
				if (0!=caa_imagedata_size(ImageData))
				{
					char FileName[PATH_MAX];
					FILE *fptr;

					sprintf(FileName,"%s-front.jpg",ReleaseID);

					printf("Saving front to '%s'\n",FileName);
					fptr=fopen(FileName,"wb");
					if (fptr)
					{
						fwrite(caa_imagedata_data(ImageData),caa_imagedata_size(ImageData),1,fptr);
						fclose(fptr);
						printf("Saved front to '%s'\n",FileName);
					}
				}
				else
				{
					printf("No front image found\n");
				}

				caa_imagedata_delete(ImageData);
			}

			ImageData=caa_coverart_fetch_back(CoverArt,ReleaseID);
			if (ImageData)
			{
				if (0!=caa_imagedata_size(ImageData))
				{
					char FileName[PATH_MAX];
					FILE *fptr;

					sprintf(FileName,"%s-back.jpg",ReleaseID);

					printf("Saving back to '%s'\n",FileName);
					fptr=fopen(FileName,"wb");
					if (fptr)
					{
						fwrite(caa_imagedata_data(ImageData),caa_imagedata_size(ImageData),1,fptr);
						fclose(fptr);
						printf("Saved back to '%s'\n",FileName);
					}
				}
				else
				{
					printf("No back image found\n");
				}

				caa_imagedata_delete(ImageData);
			}

			ReleaseInfo=caa_coverart_releaseinfo(CoverArt,ReleaseID);
			if (ReleaseInfo)
			{
				CaaImageList ImageList=caa_releaseinfo_get_imagelist(ReleaseInfo);

				if (ImageList)
				{
					int ImageNum;

					printf("Found %d images\n",caa_image_list_size(ImageList));

					for (ImageNum=0;ImageNum<caa_image_list_size(ImageList);ImageNum++)
					{
						CaaImage Image=caa_image_list_item(ImageList,ImageNum);
						if (Image)
						{
							char ID[PATH_MAX];
							char Comment[PATH_MAX];
							char URL[PATH_MAX];
							CaaThumbnails Thumbnails=caa_image_get_thumbnails(Image);

							caa_image_get_id(Image,ID,sizeof(ID));
							caa_image_get_comment(Image,Comment,sizeof(Comment));
							caa_image_get_image(Image,URL,sizeof(URL));

							printf("\nApproved: %d\n",caa_image_get_approved(Image));
							printf("Back: %d\n",caa_image_get_back(Image));
							printf("Comment: %s\n",Comment);
							printf("Edit: %d\n",caa_image_get_edit(Image));
							printf("Front: %d\n",caa_image_get_front(Image));
							printf("ID: %s\n",ID);
							printf("Image: %s\n\n",URL);

							ImageData=caa_coverart_fetch_image(CoverArt,ReleaseID,ID,eSize_Full);
							if (ImageData)
							{
								if (0!=caa_imagedata_size(ImageData))
								{
									char FileName[PATH_MAX];
									FILE *fptr;

									sprintf(FileName,"%s-%s-full.jpg",ReleaseID,ID);

									printf("Saving full for '%s' to '%s'\n",ID,FileName);
									fptr=fopen(FileName,"wb");
									if (fptr)
									{
										fwrite(caa_imagedata_data(ImageData),caa_imagedata_size(ImageData),1,fptr);
										fclose(fptr);
										printf("Saved full to '%s'\n",FileName);
									}
								}

								caa_imagedata_delete(ImageData);
							}

							if (Thumbnails)
							{
								if (0!=caa_thumbnails_get_large(Thumbnails,0,0))
								{
									ImageData=caa_coverart_fetch_image(CoverArt,ReleaseID,ID,eSize_500);
									if (ImageData)
									{
										if (0!=caa_imagedata_size(ImageData))
										{
											char FileName[PATH_MAX];
											FILE *fptr;

											sprintf(FileName,"%s-%s-500.jpg",ReleaseID,ID);

											printf("Saving 500 for '%s' to '%s'\n",ID,FileName);
											fptr=fopen(FileName,"wb");
											if (fptr)
											{
												fwrite(caa_imagedata_data(ImageData),caa_imagedata_size(ImageData),1,fptr);
												fclose(fptr);
												printf("Saved 500 to '%s'\n",FileName);
											}
										}

										caa_imagedata_delete(ImageData);
									}

									if (0!=caa_thumbnails_get_small(Thumbnails,0,0))
									{
										ImageData=caa_coverart_fetch_image(CoverArt,ReleaseID,ID,eSize_250);
										if (ImageData)
										{
											if (0!=caa_imagedata_size(ImageData))
											{
												char FileName[PATH_MAX];
												FILE *fptr;

												sprintf(FileName,"%s-%s-250.jpg",ReleaseID,ID);

												printf("Saving 250 for '%s' to '%s'\n",ID,FileName);
												fptr=fopen(FileName,"wb");
												if (fptr)
												{
													fwrite(caa_imagedata_data(ImageData),caa_imagedata_size(ImageData),1,fptr);
													fclose(fptr);
													printf("Saved 250 to '%s'\n",FileName);
												}
											}

											caa_imagedata_delete(ImageData);
										}
									}
								}
							}
						}
					}
				}

				caa_releaseinfo_delete(ReleaseInfo);
			}

			caa_coverart_delete(CoverArt);
		}
	}
	else
	{
		fprintf(stderr,"Usage: %s releaseid",argv[0]);
	}

	return 0;
}
