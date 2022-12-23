#include "PythonToCpp.h"

PythonToCpp::PythonToCpp(){
}

PythonToCpp::~PythonToCpp(){
}


//struct for vectors that mark out postions with PythonKeyWords enum
PythonToCpp::Markings::Markings(unsigned int begin, unsigned int end, PythonKeyWords designation) {
		this->begin = begin;
		this->end = end;
		this->designation = designation;
}

/*
function that checks if given python lines can even be converted by current algorithm
if it can be converted then it mark downs what line corresponds to what keyword
*/
bool PythonToCpp::IsConvertable(std::vector<std::vector<std::string>>& pythonLinesStorage, std::string& conversionError){
	unsigned int multiLineKeyWordBeginningIndex;			//require for all keywords that need to be mark multiple lines
	bool ignoreAlgorithmTerminatingCheck = false;			//used to ignore checks that would cause algorithm to stop execution

	//going over all the lines in given python source code
	for (unsigned int i = 0; i < pythonLinesStorage.size(); i++) {
		//classifying current line to particular keyword
		PythonKeyWords currentLineMarking = WhatKeyWordIsThis(pythonLinesStorage[i]);

		//for all PythonKeyWords that are multi lined
		if (ignoreAlgorithmTerminatingCheck) {
			if (currentLineMarking == PythonKeyWords::documentedStrings && ignoreAlgorithmTerminatingCheck) {
				ignoreAlgorithmTerminatingCheck = false;
				codeStructure.push_back(PythonToCpp::Markings(multiLineKeyWordBeginningIndex, i, currentLineMarking));
			}
		}
		//for all PythonKeyWords that are single lined
		else{
			//checking if current line corresponds to keyword that is not yet supported
			if (currentLineMarking == PythonKeyWords::classes || currentLineMarking == PythonKeyWords::functions ||
				currentLineMarking == PythonKeyWords::statements || currentLineMarking == PythonKeyWords::imports ||
				currentLineMarking == PythonKeyWords::unidentifiedKeyword || currentLineMarking == PythonKeyWords::dictionaries) {

				//returning what caused error and where
				conversionError = PythonKeyWordsEnumToString(currentLineMarking) + ", on line " + std::to_string(i + 1);
				return false;
			}
			//if at beginning of documented strings
			if (currentLineMarking == PythonKeyWords::documentedStrings && !ignoreAlgorithmTerminatingCheck) {
				ignoreAlgorithmTerminatingCheck = true;
				multiLineKeyWordBeginningIndex = i;
			}
			//marking out all keywords that take only 1 line
			else if (currentLineMarking == PythonKeyWords::comments || currentLineMarking == PythonKeyWords::variables || 
					currentLineMarking == PythonKeyWords::lists || currentLineMarking == PythonKeyWords::dictionaries) {
				
				codeStructure.push_back(PythonToCpp::Markings(i, i, currentLineMarking));
			}
		}
	}

	return true;
}

/*
function that converts python code to c++ code,
if everthing went successfully return true
else false and what caused it
*/
bool PythonToCpp::WasConversionSuccessful(std::vector<std::string>& cppLinesStorage, std::string& conversionError){
	return false;

	add code to convert already
}

/*
function that returns PythonKeyWords enum for given line
*/
PythonToCpp::PythonKeyWords PythonToCpp::WhatKeyWordIsThis(const std::vector<std::string>& pythonLinePieces){
	if (IsImport(pythonLinePieces[0])) {
		return PythonKeyWords::imports;
	}
	else if (IsFunction(pythonLinePieces[0])) {
		return PythonKeyWords::functions;
	}
	else if (IsClass(pythonLinePieces[0])) {
		return PythonKeyWords::classes;
	}
	else if (IsStatement(pythonLinePieces[0])) {
		return PythonKeyWords::statements;
	}
	else if (IsComment(pythonLinePieces[0])) {
		return PythonKeyWords::comments;
	}
	else if (IsDocumentedString(pythonLinePieces[0])) {
		return PythonKeyWords::documentedStrings;
	}
	else if (IsList(pythonLinePieces)) {
		return PythonKeyWords::lists;
	}
	else if (IsDictionary(pythonLinePieces)) {
		return PythonKeyWords::dictionaries;
	}
	else if (IsVariable(pythonLinePieces)) {
		return PythonKeyWords::variables;
	}
	else {
		return PythonKeyWords::unidentifiedKeyword;
	}	
}

/*
this function is called on the first element of line
that first element is checked whether to be "from" or "import"
*/
bool PythonToCpp::IsImport(std::string testString) {
	if (testString == "from" || testString == "import") {
		return true;
	}
	return false;
}

/*
this function is called on the first element of line
that first element is checked whether its first char is '#'
*/
bool PythonToCpp::IsComment(std::string testString)
{
	if (testString[0] == '#') {
		return true;
	}

	return false;
}

/*
this function is called on the first element of line
that first element is checked whether it is atleast
of size 3 and its first three char are '\''
*/
bool PythonToCpp::IsDocumentedString(std::string testString)
{
	if (testString.size() > 2 && testString[0] == '\'' && testString[1] == '\'' && testString[2] == '\'') {
		return true;
	}

	return false;
}

/*
this function checks if current line has at least 3 elements
and checks if first element passes is IsValiNamingConvention()
and checks if second element is "="

by design of this function it must be called after IsList and IsDictionary
*/
bool PythonToCpp::IsVariable(const std::vector<std::string> givenVector)
{
	if (givenVector.size() > 2 && IsValidNamingConvention(givenVector[0]) && givenVector[1] == "=") {
		return true;
	}
	return false;
}

/*
this function checks if current line is valid to be variable 
and checks if first char of third element begins with char '['
*/
bool PythonToCpp::IsList(const std::vector<std::string> givenVector)
{
	if (IsVariable(givenVector) && givenVector[2][0] == '[') {
		return true;
	}
	return false;
}

/*
this function checks if current line is valid to be variable
and checks if first char of third element begins with char '{'
*/
bool PythonToCpp::IsDictionary(const std::vector<std::string> givenVector)
{
	if (IsVariable(givenVector) && givenVector[2][0] == '{') {
		return true;
	}
	return false;
}

/*
this function is called on the first element and check if it is "def"
*/
bool PythonToCpp::IsFunction(std::string testString)
{
	if (testString == "def") {
		return true;
	}

	return false;
}

/*
this function is called on the first element and 
checks if it is "if" or "if(" or
checks if it is "elif" or "elif(" or
checks if it is "else" or "else:" or
checks if it is "while" or "while(" or
checks if it is "for"
checks if it is "elif" or "elif(" or
check if first 5 chars spell out "print("
*/
bool PythonToCpp::IsStatement(std::string testString)
{
	if ((testString == "if" || testString == "if(") || (testString == "elif" || testString == "elif(") || (testString == "else" || testString == "else:") || 
		(testString == "while" || testString == "while(") || testString == "for" ||
		(testString[0] == 'p' && testString[1] == 'r' && testString[2] == 'i' && testString[3] == 'n' && testString[4] == 't' && testString[5] == '(')) {
		return true;
	}

	return false;
}

/*
this function is called on the first element and check if it is "class"
*/
bool PythonToCpp::IsClass(std::string testString)
{
	if (testString == "class") {
		return true;
	}

	return false;
}

/*
this function is called at the first element of line and it checks
if first element is 0 or space or char '\'' or char '"' or char '.' or char ',' or beings with number
and returns false if true
*/
bool PythonToCpp::IsValidNamingConvention(std::string name)
{
	if (name.size() == 0 || name[0] == ' ' || name[0] == '\'' || name[0] == '"' || name[0] == '.' || name[0] == ',' || IsNumeric(name[0])) {
		return false;
	}
	return true;
}

/*
this function checks if given char is numeric
*/
bool PythonToCpp::IsNumeric(char test)
{
	switch (test)
	{
	case ('0'):
	case ('1'):
	case ('2'):
	case ('3'):
	case ('4'):
	case ('5'):
	case ('6'):
	case ('7'):
	case ('8'):
	case ('9'):
		return true;
	default:
		return false;
	}
}

/*
return strings for enum PythonKeywords
*/
std::string PythonToCpp::PythonKeyWordsEnumToString(PythonKeyWords pythonKeyWord) {
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
