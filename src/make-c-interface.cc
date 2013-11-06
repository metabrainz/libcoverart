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

#include "config.h"
#include "coverart/defines.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>

#include "xmlParser.h"

void ProcessBoilerplate(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include, const std::string& Path);
void ProcessHeader(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include);
void ProcessClass(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include);
void ProcessList(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include);
void ProcessDeclare(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include);

int main(int argc, const char *argv[])
{
	for (int count=0;count<argc;count++)
		std::cout << argv[count] << " ";

	std::cout << std::endl;

	if (argc==6)
	{
		std::string XMLFile=std::string(argv[1])+"/"+argv[2];
		XMLResults Results;
		memset(&Results, 0, sizeof(Results));
		XMLNode *TopNode=XMLRootNode::parseFile(XMLFile.c_str(),&Results);
		if (!TopNode->isEmpty())
		{
			std::cout << "Generating '" << argv[3] << "/" << argv[4] << "' and '" << argv[3] << "/" << argv[5] << "'" << std::endl;

			std::string IncludeName=std::string(argv[3])+"/"+argv[5];
			std::ofstream Include(IncludeName.c_str());

			std::string SourceName=std::string(argv[3])+"/" + argv[4];
			std::ofstream Source(SourceName.c_str());

			if (!Include.is_open())
			{
				std::cerr << "Error opening '" << IncludeName << "'" << std::endl;
				return 1;
			}

			if (!Source.is_open())
			{
				std::cerr << "Error opening '" << SourceName << "'" << std::endl;
				return 1;
			}

			for (XMLNode Node = TopNode->getChildNode();
			     !Node.isEmpty();
			     Node = Node.next())
			{
				std::string Name=Node.getName();

				if ("boilerplate"==Name)
					ProcessBoilerplate(Node,Source,Include,argv[1]);
				else if ("header"==Name)
					ProcessHeader(Node,Source,Include);
				else if ("declare"==Name)
					ProcessDeclare(*TopNode,Source,Include);
				else if ("class"==Name)
					ProcessClass(Node,Source,Include);
				else if ("list"==Name)
					ProcessList(Node,Source,Include);
				else
				{
					std::cerr << "Unrecognised item " << Name << std::endl;
					return 1;
				}
			}
		}
		else
		{
			std::cerr << "Error reading XML: " << Results.message << " at line " << Results.line << std::endl;
			return 1;
		}
                if (TopNode != NULL)
                    delete TopNode;
	}

	return 0;
}

std::ofstream *GetFile(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include)
{
	std::ofstream *File=&Source;

	if (Node.isAttributeSet("target"))
	{
		std::string Target=Node.getAttribute("target").value();
		if ("source"==Target)
			File=&Source;
		else if ("include"==Target)
			File=&Include;
	}

	return File;
}

void ProcessHeader(const XMLNode& /*Node*/, std::ofstream& Source, std::ofstream& Include)
{
	std::stringstream os;
	os << "/* --------------------------------------------------------------------------" << std::endl;
	os << std::endl;
	os << "   libcoverart - Client library to access MusicBrainz" << std::endl;
	os << std::endl;
	os << "   Copyright (C) 2012 Andrew Hawkins" << std::endl;
	os << std::endl;
	os << "   This file is part of libcoverart." << std::endl;
	os << std::endl;
	os << "   This library is free software; you can redistribute it and/or" << std::endl;
	os << "   modify it under the terms of v2 of the GNU Lesser General Public" << std::endl;
	os << "   License as published by the Free Software Foundation." << std::endl;
	os << std::endl;
	os << "   libcoverart is distributed in the hope that it will be useful," << std::endl;
	os << "   but WITHOUT ANY WARRANTY; without even the implied warranty of" << std::endl;
	os << "   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU" << std::endl;
	os << "   Lesser General Public License for more details." << std::endl;
	os << std::endl;
	os << "   You should have received a copy of the GNU General Public License" << std::endl;
	os << "   along with this library.  If not, see <http://www.gnu.org/licenses/>." << std::endl;
	os << std::endl;
	os << "   THIS FILE IS AUTOMATICALLY GENERATED - DO NOT EDIT IT!" << std::endl;
	os << std::endl;
	os << "----------------------------------------------------------------------------*/" << std::endl;
	os << std::endl;

	Source << os.str() << std::endl;
	Include << os.str() << std::endl;
}

void ProcessBoilerplate(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include, const std::string& Path)
{
	std::ofstream *File=GetFile(Node,Source,Include);

	if (Node.isAttributeSet("file"))
	{
		std::string FileName=Path+"/"+Node.getAttribute("file").value();
		std::ifstream InFile(FileName.c_str());
		if (InFile.is_open())
			*File << InFile.rdbuf() << std::endl;
		else
		{
			std::cerr << "Error opening include file '" << FileName << "'" << std::endl;
			exit(1);
		}
	}
	else if (Node.getText())
	{
		*File << Node.getText() << std::endl;
	}

	*File << std::endl;
}

void ProcessClass(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include)
{
	if (Node.isAttributeSet("name"))
	{
		std::string LowerName=Node.getAttribute("name").value();

		std::string UpperName=LowerName;
		if (Node.isAttributeSet("uppername"))
			UpperName=Node.getAttribute("uppername").value();
		else
			UpperName[0]=toupper(UpperName[0]);

		Include << "/**" << std::endl;
		Include << "* Delete a #Caa" << UpperName << " object" << std::endl;
		Include << "*" << std::endl;
		Include << "* @param " << UpperName << " Object to delete" << std::endl;
		Include << "*/" << std::endl;
		Include << "  void caa_" << LowerName << "_delete(Caa" << UpperName << " " << UpperName << ");" << std::endl;
		Include << std::endl;

		Source << "  CAA_C_DELETE(" << UpperName << "," << LowerName << ")" << std::endl;

		Include << "/**" << std::endl;
		Include << "* Clone a #Caa" << UpperName << " object" << std::endl;
		Include << "*" << std::endl;
		Include << "* @param " << UpperName << " Object to clone" << std::endl;
		Include << "*" << std::endl;
		Include << "* @return Cloned object. This object <b>must</b> be deleted once" << std::endl;
		Include << "*				finished with." << std::endl;
		Include << "*/" << std::endl;
		Include << "  Caa" << UpperName << " caa_" << LowerName << "_clone(Caa" << UpperName << " " << UpperName << ");" << std::endl;
		Include << std::endl;

		Source << "  CAA_C_CLONE(" << UpperName << "," << LowerName << ")" << std::endl;

		for (XMLNode ChildNode = Node.getChildNode();
		     !ChildNode.isEmpty();
		     ChildNode = ChildNode.next())
		{
			std::string Name=ChildNode.getName();

			if ("property"==Name)
			{
				if (ChildNode.isAttributeSet("name") && ChildNode.isAttributeSet("type"))
				{
					std::string PropertyLowerName=ChildNode.getAttribute("name").value();

					std::string PropertyUpperName=PropertyLowerName;
					if (ChildNode.isAttributeSet("uppername"))
						PropertyUpperName=ChildNode.getAttribute("uppername").value();
					else
						PropertyUpperName[0]=toupper(PropertyUpperName[0]);

					std::string PropertyType=ChildNode.getAttribute("type").value();

					if ("string"==PropertyType)
					{
						bool Deprecated=false;
						std::string Replacement;

						if (ChildNode.isAttributeSet("deprecated"))
						{
							std::string StrDeprecated=ChildNode.getAttribute("deprecated").value();

							if (StrDeprecated=="true")
								Deprecated=true;

							if (ChildNode.isAttributeSet("replacement"))
								Replacement=ChildNode.getAttribute("replacement").value();
						}

						Include << "/**" << std::endl;
						Include << " * ";
						if (Deprecated)
							Include << "@deprecated ";

						Include << "@see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;

						if (Deprecated)
						{
 							Include << " * <b>This method is deprecated, please use #" << Replacement << "</b>" << std::endl;
 							Include << " *" << std::endl;
 						}

						Include << " * @param " << UpperName << " #Caa" << UpperName << " object" << std::endl;
						Include << " * @param str Returned string" << std::endl;
						Include << " * @param len Number of characters available in return string" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
						Include << " */" << std::endl;
						Include << "  ";

						if (Deprecated)
							Include << "LIBCOVERART_DEPRECATED(" << Replacement << ") ";

						Include << "int caa_" << LowerName << "_get_" << PropertyLowerName << "(Caa" << UpperName << " " << UpperName << ", char *str, int len);" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_STR_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("integer"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Caa" << UpperName << " object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return Returned value" << std::endl;
						Include << " */" << std::endl;
						Include << "  int caa_" << LowerName << "_get_" << PropertyLowerName << "(Caa" << UpperName << " " << UpperName << ");" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_INT_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("double"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Caa" << UpperName << " object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return Returned value" << std::endl;
						Include << " */" << std::endl;
						Include << "  double caa_" << LowerName << "_get_" << PropertyLowerName << "(Caa" << UpperName << " " << UpperName << ");" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_DOUBLE_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("object"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Caa" << UpperName << " object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return #Caa" << PropertyUpperName << " object" << std::endl;
						Include << " */" << std::endl;
						Include << "  Caa" << PropertyUpperName << " caa_" << LowerName << "_get_" << PropertyLowerName << "(Caa" << UpperName << " " << UpperName << ");" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_OBJ_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("relationlist"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @deprecated @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * <b>This method is deprecated, please use #caa_" << LowerName << "_get_" << PropertyLowerName << "list</b>" << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Caa" << UpperName << " object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return #Caa" << PropertyUpperName << " object" << std::endl;
						Include << " */" << std::endl;
						Include << " LIBCOVERART_DEPRECATED(caa_" << LowerName << "_get_" << PropertyLowerName << "list) Caa" << PropertyUpperName << " caa_" << LowerName << "_get_" << PropertyLowerName << "(Caa" << UpperName << " " << UpperName << ");" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_OBJ_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;

						Include << "/**" << std::endl;
						Include << " * @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << "List" << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Caa" << UpperName << "List object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return #Caa" << PropertyUpperName << "List object" << std::endl;
						Include << " */" << std::endl;
						Include << "  Caa" << PropertyUpperName << "List caa_" << LowerName << "_get_" << PropertyLowerName << "list(Caa" << UpperName << " " << UpperName << ");" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_OBJ_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "List," << PropertyLowerName << "list)" << std::endl;
					}
					else if ("iswc"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @deprecated @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * <b>This method is deprecated, please use #caa_" << LowerName << "_get_" << PropertyLowerName << "list</b>" << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Caa" << UpperName << " object" << std::endl;
						Include << " * @param str Returned string" << std::endl;
						Include << " * @param len Number of characters available in return string" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
						Include << " */" << std::endl;
						Include << "  LIBCOVERART_DEPRECATED(caa_" << LowerName << "_get_" << PropertyLowerName << "list) int caa_" << LowerName << "_get_" << PropertyLowerName << "(Caa" << UpperName << " " << UpperName << ", char *str, int len);" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_STR_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;

						Include << "/**" << std::endl;
						Include << " * @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << "List" << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Caa" << UpperName << "List object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return #Caa" << PropertyUpperName << "List object" << std::endl;
						Include << " */" << std::endl;
						Include << "  Caa" << PropertyUpperName << "List caa_" << LowerName << "_get_" << PropertyLowerName << "list(Caa" << UpperName << " " << UpperName << ");" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_OBJ_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "List," << PropertyLowerName << "list)" << std::endl;
					}
					else if ("ipi"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @deprecated @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * <b>This method is deprecated, please use #caa_" << LowerName << "_get_" << PropertyLowerName << "list</b>" << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Caa" << UpperName << " object" << std::endl;
						Include << " * @param str Returned string" << std::endl;
						Include << " * @param len Number of characters available in return string" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
						Include << " */" << std::endl;
						Include << "  LIBCOVERART_DEPRECATED(caa_" << LowerName << "_get_" << PropertyLowerName << "list) int caa_" << LowerName << "_get_" << PropertyLowerName << "(Caa" << UpperName << " " << UpperName << ", char *str, int len);" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_STR_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;

						Include << "/**" << std::endl;
						Include << " * @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << "List" << std::endl;
						Include << " *" << std::endl;
						Include << " * @param " << UpperName << " #Caa" << UpperName << "List object" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return #Caa" << PropertyUpperName << "List object" << std::endl;
						Include << " */" << std::endl;
						Include << "  Caa" << PropertyUpperName << "List caa_" << LowerName << "_get_" << PropertyLowerName << "list(Caa" << UpperName << " " << UpperName << ");" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_OBJ_GETTER(" << UpperName << "," << LowerName << "," << PropertyUpperName << "List," << PropertyLowerName << "list)" << std::endl;
					}
					else
					{
						std::cerr << "Unexpected property type: '" << PropertyType << "'" << std::endl;
						exit(1);
					}
				}
				else
				{
					std::cerr << "Class " << LowerName << " property specified with no name or type" << std::endl;
					exit(1);
				}
			}
		}

		Source << std::endl;
	}
	else
	{
		std::cerr << "Class specified with no name" << std::endl;
		exit(1);
	}
}

void ProcessList(const XMLNode& Node, std::ofstream& Source, std::ofstream& Include)
{
	if (Node.isAttributeSet("name"))
	{
		std::string LowerName=Node.getAttribute("name").value();

		std::string UpperName=LowerName;
		if (Node.isAttributeSet("uppername"))
			UpperName=Node.getAttribute("uppername").value();
		else
			UpperName[0]=toupper(UpperName[0]);

		Include << "/**" << std::endl;
		Include << " * Delete a #Caa" << UpperName << "List" << std::endl;
		Include << " *" << std::endl;
		Include << " * @param List List to delete" << std::endl;
		Include << " */" << std::endl;
		Include << "  void caa_" << LowerName << "_list_delete(Caa" << UpperName << "List List);" << std::endl;
		Include << std::endl;
		Include << "/**" << std::endl;
		Include << " * Return the number of entries in a #Caa" << UpperName << "List" << std::endl;
		Include << " *" << std::endl;
		Include << " * @param	List List to use" << std::endl;
		Include << " */" << std::endl;
		Include << "  int caa_" << LowerName << "_list_size(Caa" << UpperName << "List List);" << std::endl;
		Include << std::endl;
		Include << "/**" << std::endl;
		Include << " * Returns an entry from a #Caa" << UpperName << "List" << std::endl;
		Include << " *" << std::endl;
		Include << " * @param List List to use" << std::endl;
		Include << " * @param Item Item number to return" << std::endl;
		Include << " *" << std::endl;
		Include << " * @return A #Caa" << UpperName << " object." << std::endl;
		Include << " */" << std::endl;
		Include << "  Caa" << UpperName << " caa_" << LowerName << "_list_item(Caa" << UpperName << "List List, int Item);" << std::endl;
		Include << std::endl;
		Include << "/**" << std::endl;
		Include << " *	Return the count of entries in an #Caa" << UpperName << "List" << std::endl;
		Include << " *" << std::endl;
		Include << " * @param	List List to use" << std::endl;
		Include << " */" << std::endl;
		Include << "	int caa_" << LowerName << "_list_get_count(Caa" << UpperName << "List List);" << std::endl;
		Include << std::endl;
		Include << "/**" << std::endl;
		Include << " *	Return the offset of entries in an #Caa" << UpperName << "List" << std::endl;
		Include << " *" << std::endl;
		Include << " * @param	List List to use" << std::endl;
		Include << " */" << std::endl;
		Include << "	int caa_" << LowerName << "_list_get_offset(Caa" << UpperName << "List List);" << std::endl;
		Include << std::endl;

		Source << "  CAA_C_LIST_GETTER(" << UpperName << "," << LowerName << ")" << std::endl;

		Include << "/**" << std::endl;
		Include << "* Clone an #Caa" << UpperName << "List object" << std::endl;
		Include << "*" << std::endl;
		Include << "* @param " << UpperName << "List Object to clone" << std::endl;
		Include << "*" << std::endl;
		Include << "* @return Cloned list. This list <b>must</b> be deleted once" << std::endl;
		Include << "*				finished with." << std::endl;
		Include << "*/" << std::endl;
		Include << "  Caa" << UpperName << "List caa_" << LowerName << "_list_clone(Caa" << UpperName << "List " << UpperName << "List" << ");" << std::endl;
		Include << std::endl;

		Source << "  CAA_C_CLONE(" << UpperName << "List," << LowerName << "_list)" << std::endl;

		for (XMLNode ChildNode = Node.getChildNode();
		     !ChildNode.isEmpty();
		     ChildNode = ChildNode.next())
		{
			std::string Name=ChildNode.getName();

			if ("property"==Name)
			{
				if (ChildNode.isAttributeSet("name") && ChildNode.isAttributeSet("type"))
				{
					std::string PropertyLowerName=ChildNode.getAttribute("name").value();

					std::string PropertyUpperName=PropertyLowerName;
					if (ChildNode.isAttributeSet("uppername"))
						PropertyUpperName=ChildNode.getAttribute("uppername").value();
					else
						PropertyUpperName[0]=toupper(PropertyUpperName[0]);

					std::string PropertyType=ChildNode.getAttribute("type").value();

					if ("string"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param List List to use" << std::endl;
						Include << " * @param str Returned string" << std::endl;
						Include << " * @param len Number of characters available in return string" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return The number of characters in the string to copy (not including terminating NULL)" << std::endl;
						Include << " */" << std::endl;
						Include << "  int caa_" << LowerName << "_list_get_" << PropertyLowerName << "(Caa" << UpperName << "List List, char *str, int len);" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_STR_GETTER(" << UpperName << "List," << LowerName << "_list," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("integer"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param List List to use" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return Returned value" << std::endl;
						Include << " */" << std::endl;
						Include << "  int caa_" << LowerName << "_list_get_" << PropertyLowerName << "(Caa" << UpperName << "List List);" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_INT_GETTER(" << UpperName << "List," << LowerName << "_list," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("double"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param List List to use" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return Returned value" << std::endl;
						Include << " */" << std::endl;
						Include << "  double caa_" << LowerName << "_list_get_" << PropertyLowerName << "(Caa" << UpperName << "List List);" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_DOUBLE_GETTER(" << UpperName << "List," << LowerName << "_list," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else if ("object"==PropertyType)
					{
						Include << "/**" << std::endl;
						Include << " * @see CoverArtArchive::C" << UpperName << "::" << PropertyUpperName << std::endl;
						Include << " *" << std::endl;
						Include << " * @param List List to use" << std::endl;
						Include << " *" << std::endl;
						Include << " * @return #Caa" << PropertyUpperName << " object" << std::endl;
						Include << " */" << std::endl;
						Include << "  int caa_" << LowerName << "_list_get_" << PropertyLowerName << "(Caa" << UpperName << "List List);" << std::endl;
						Include << std::endl;

						Source << "  CAA_C_OBJ_GETTER(" << UpperName << "List," << LowerName << "_list," << PropertyUpperName << "," << PropertyLowerName << ")" << std::endl;
					}
					else
					{
						std::cerr << "Unexpected property type: '" << PropertyType << "'" << std::endl;
						exit(1);
					}
				}
				else
				{
					std::cerr << "List " << LowerName << " property specified with no name or type" << std::endl;
					exit(1);
				}
			}
		}

		Source << std::endl;
	}
	else
	{
		std::cerr << "List specified with no name" << std::endl;
		exit(1);
	}
}

void ProcessDeclare(const XMLNode& Node, std::ofstream& /*Source*/, std::ofstream& Include)
{
	std::vector<std::string> Classes;

	for (XMLNode ChildNode = Node.getChildNode();
	     !ChildNode.isEmpty();
	     ChildNode = ChildNode.next())
	{
		std::string Name=ChildNode.getName();

		if ("class"==Name || "list"==Name)
		{
			if (ChildNode.isAttributeSet("name"))
			{
				std::string UpperName=ChildNode.getAttribute("name").value();
				if (ChildNode.isAttributeSet("uppername"))
					UpperName=ChildNode.getAttribute("uppername").value();
				else
					UpperName[0]=toupper(UpperName[0]);

				if ("list"==Name)
					UpperName+="List";

				Classes.push_back(UpperName);
			}
			else
			{
				std::cerr << "Class or List specified with no name" << std::endl;
				exit(1);
			}
		}
	}

	for (std::vector<std::string>::const_iterator Class=Classes.begin();Class!=Classes.end();Class++)
	{
		Include << "  typedef void *Caa" << *Class << ";" << std::endl;
	}

	Include << std::endl;

}
