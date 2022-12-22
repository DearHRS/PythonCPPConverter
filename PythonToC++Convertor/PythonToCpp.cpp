#include "PythonToCpp.h"

PythonToCpp::PythonToCpp(){
}

PythonToCpp::~PythonToCpp(){
}

bool PythonToCpp::IsConvertable(std::vector<std::vector<std::string>>& pythonLinesStorage){
	for (unsigned int i = 0; i < pythonLinesStorage.size(); i++) {

		//need logic here to mark down what line is what
	}


	return true;
}

std::string PythonToCpp::EnumToString(PythonKeyWords pythonKeyWord){
	switch (pythonKeyWord)
	{
	case PythonToCpp::imports:
		return "imports";
	case PythonToCpp::comments:
		return "comments";
	case PythonToCpp::documentedStrings:
		return "documented strings";
	case PythonToCpp::variables:
		return "variables";
	case PythonToCpp::lists:
		return "lists";
	case PythonToCpp::dictionaries:
		return "dictionaries";
	case PythonToCpp::functions:
		return "functions";
	case PythonToCpp::statements:
		return "statements";
	case PythonToCpp::classes:
		return "classes";
	default:
		return "unidentified Keyword";
	}
}

PythonToCpp::PythonKeyWords PythonToCpp::whatKeyWordIsThis(const std::vector<std::string>& pythonLinePieces){


	return PythonKeyWords::unidentifiedKeyword;
}

bool PythonToCpp::IsImport(std::string testString) {
	if (testString == "from" || testString == "import") {
		return true;
	}

	return false;
}

bool PythonToCpp::IsComment(std::string testString)
{
	if (testString == "#" || testString[0] == '#') {
		return true;
	}

	return false;
}

bool PythonToCpp::IsDocumentedString(std::string testString)
{
	if (testString == "'''" || (testString[0] == '\'' && testString[1] == '\'' && testString[2] == '\'')) {
		return true;
	}

	return false;
}

bool PythonToCpp::IsVariable(std::vector<std::string> givenVector)
{

	you were here
	return false;
}

bool PythonToCpp::IsList(std::vector<std::string> givenVector)
{
	return false;
}

bool PythonToCpp::IsDictionary(std::vector<std::string> givenVector)
{
	return false;
}

bool PythonToCpp::IsFunction(std::string testString)
{
	if (testString == "def") {
		return true;
	}

	return false;
}

bool PythonToCpp::IsStatement(std::string testString)
{
	if ((testString == "if" || testString == "if(") || (testString == "elif" || testString == "elif(") || (testString == "else" || testString == "else:") || 
		(testString == "while" || testString == "while(") || testString == "for" ||
		(testString[0] == 'p' && testString[1] == 'r' && testString[2] == 'i' && testString[3] == 'n' && testString[4] == 't' && testString[5] == '(')) {
		return true;
	}

	return false;
}

bool PythonToCpp::IsClass(std::string testString)
{
	if (testString == "class") {
		return true;
	}

	return false;
}
