#include <iostream>

#include "coverart/HTTPFetch.h"

int main(int /*argc*/, const char */*argv*/[])
{
	try
	{
		CoverArtArchive::CHTTPFetch Fetch("test");
		Fetch.Fetch("http://coverartarchive.org/release/189d7863-a23c-49d9-ae7e-031b413b2805");
		std::vector<unsigned char> Data=Fetch.Data();
		std::string strData(Data.begin(),Data.end());
		std::cout << "Response: '" << strData << "'" << std::endl;
	}

	catch (CoverArtArchive::CExceptionBase e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

  return 0;
}
