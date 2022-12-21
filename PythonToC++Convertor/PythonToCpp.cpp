#include "PythonToCpp.h"

PythonToCpp::PythonToCpp(){
}

PythonToCpp::~PythonToCpp(){
}

bool PythonToCpp::IsConvertable(std::vector<std::string>& pythonLinesStorage)
{
	for (unsigned int i = 0; i < pythonLinesStorage.size(); i++) {
		std::vector<std::string> brokenLine;
		std::string brokenPiece;

		//breaking string by spaces
		for (unsigned int j = 0; j < pythonLinesStorage[i].size(); j++) {

		}
		std::wcout << pythonLinesStorage[i].size() << '\n';
	}


	return true;
}
