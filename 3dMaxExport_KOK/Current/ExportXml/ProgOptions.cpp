#include "ProgOptions.h"
#include <iostream>
#include <string.h>

DEFINE_SET_GET_FUNC(ProgOptions,std::string,inFileFullPath);

ProgOptions::ProgOptions()
{
	m_inFileFullPath = "E:\\aaaa.xml";
}

void ProgOptions::parseParam(int argc, char *argv[])
{
	if (argc == 1)
	{
		std::cout << "-infile input file";
		return;
	}

	int idx = 1;
	for (; idx < argc; ++idx)
	{
		if (strcmp("-infile", argv[idx]) == 0)
		{
			if (idx + 1 < argc)
			{
				m_inFileFullPath = argv[idx + 1];
				++idx;
			}
		}
	}
}