#include <iostream>
#include <stdio.h>
#include <vector>

#include "MDLLoader.h"
#include "AVIDLib_IO/GenericOperations.h"
#include "AVIDLib_IO/ReadContext.h"

namespace MDLLoader
{
	static std::string Path;
	static bool HasNewPath = false;

	static bool LoadMDL(std::vector<ALP_Byte>& data)
	{
		FILE* inFile = fopen(Path.c_str(), "rb");

		if ( !inFile )
		{
			std::cerr << "Could not open file: " << Path << std::endl;
			return false
		}

		fseek(inFile, 0, SEEK_END);
		data.resize(ftell(inFile));
		fseek(inFile, 0, SEEK_SET);

		bool success = fread(data.data(), 1, data.size(), inFile) == data.size();

		if ( !success )
		{
			std::cerr << "Failed to read data from file: " << Path << std::endl;
		}

		fclose(inFile);

		return success;
	}

	static void LoadMDL()
	{
		std::vector<ALP_Byte> fileData;

		if ( !LoadMDL(fileData) )
		{
			return;
		}

		if ( fileData.empty() )
		{
			std::cerr << "No MDL file data to load." << std::endl;
			return;
		}

		ALIO_ReadContext context;
		ALIO_ReadContext_Prepare(&context, fileData.data(), fileData.size());

		ALIO_UnitID unitID = ALIO_UnitForFile(&context);
		std::cout << "Unit ID for " << Path << ": " << ALIO_UnitName(unitID) << std::endl;
	}

	void SetMDLPath(const std::string& path)
	{
		Path = path;
		HasNewPath = true;
	}

	void Poll()
	{
		if ( HasNewPath )
		{
			HasNewPath = false;
			LoadMDL();
		}
	}
}
