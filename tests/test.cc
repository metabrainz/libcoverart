#include <iostream>

#include "coverart/HTTPFetch.h"
#include "coverart/CoverArt.h"

int main(int /*argc*/, const char */*argv*/[])
{
	try
	{
		CoverArtArchive::CCoverArt Art("test");
		CoverArtArchive::CReleaseInfo ReleaseInfo=Art.ReleaseInfo("189d7863-a23c-49d9-ae7e-031b413b2805");
		std::cout << ReleaseInfo << std::endl;

		std::vector<unsigned char> Image=Art.FetchFront("189d7863-a23c-49d9-ae7e-031b413b2805");
		std::cout << "Front has size " << Image.size() << std::endl;

		Image=Art.FetchBack("189d7863-a23c-49d9-ae7e-031b413b2805");
		std::cout << "Back has size " << Image.size() << std::endl;

		Image=Art.FetchImage("189d7863-a23c-49d9-ae7e-031b413b2805","832154846");
		std::cout << "Image has size " << Image.size() << std::endl;

		Image=Art.FetchImage("189d7863-a23c-49d9-ae7e-031b413b2805","832154846",CoverArtArchive::CCoverArt::eSize_250);
		std::cout << "Image has size " << Image.size() << std::endl;

		Image=Art.FetchImage("189d7863-a23c-49d9-ae7e-031b413b2805","832154846",CoverArtArchive::CCoverArt::eSize_500);
		std::cout << "Image has size " << Image.size() << std::endl;
	}

	catch (const CoverArtArchive::CExceptionBase& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

  return 0;
}
