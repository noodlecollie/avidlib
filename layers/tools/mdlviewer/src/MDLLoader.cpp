#include <iostream>
#include <stdio.h>
#include <vector>

#include "MDLLoader.h"
#include "AVIDLib_IO/GenericOperations.h"
#include "AVIDLib_IO/ReadContext.h"
#include "AVIDLib_IO/GenericOperations.h"

namespace MDLLoader
{
	static std::string Path;
	static bool HasNewPath = false;
	static ALIO_GenericContainer* Container = nullptr;

	static void DestroyContainer()
	{
		if ( Container )
		{
			ALIO_GenericContainer_Deinit(Container);
			free(Container);
			Container = nullptr;
		}
	}

	static bool LoadMDL(std::vector<ALP_Byte>& data)
	{
		FILE* inFile = fopen(Path.c_str(), "rb");

		if ( !inFile )
		{
			std::cerr << "Could not open file: " << Path << std::endl;
			return false;
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

	static bool ReadMDL(ALIO_ReadContext* context)
	{
		DestroyContainer();

		Container = (ALIO_GenericContainer*)malloc(sizeof(*Container));
		ALIO_GenericContainer_Init(Container);

		if ( ALIO_GenericRead(context, ALIO_UNIT_ID__INVALID, Container) )
		{
			std::cout << "Read " << Path << " successfully." << std::endl;
			std::cout << "Model format inferred: " << ALIO_UnitName(Container->unit) << std::endl;
			return true;
		}
		else
		{
			std::cerr
				<< "Failed to read "
				<< Path
				<< ": "
				<< ALIO_ReadContext_GetReaderErrorString(context);

			const ALP_Char* description = ALIO_ReadContext_GetErrorDetails(context);

			if ( description && *description )
			{
				std::cerr << " " << description;
			}

			std::cerr << std::endl;

			return false;
		}
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

		ReadMDL(&context);
	}

	std::string GetMDLPath()
	{
		return Path;
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

	void Cleanup()
	{
		DestroyContainer();
	}

	ALIO_GenericContainer* GetGenericIOContainer()
	{
		return Container;
	}

	ALP_Opaque* GetUnderlyingContainer(ALIO_UnitID id)
	{
		if ( Container && Container->unit == id )
		{
			return Container->container;
		}

		return nullptr;
	}
}
