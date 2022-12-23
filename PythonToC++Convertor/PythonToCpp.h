#pragma once
#include <string>
#include <vector>
#include <iostream>


class PythonToCpp{
public:
	//enums used to mark to what type a particular line or lines associate to
	enum PythonKeyWords {
		imports, comments, documentedStrings, variables, lists, dictionaries, functions, statements, classes, unidentifiedKeyword
	};

	//struct for vectors that mark out postions with PythonKeyWords enum
	struct Markings{
		unsigned int begin;					//used to store first line of desination
		unsigned int end;					//used to store last line of desination
		PythonKeyWords designation;			//used to store to what keyword are these line designated to

		Markings(unsigned int begin, unsigned int end, PythonKeyWords designation);
	};

	/*
	constructors and destructors
	*/
	PythonToCpp();
	~PythonToCpp();

	/*
	function that goes over python lines vector and marks the beginning and ending lines
	where it met imports, comments, docummented strings, variables, lists, tuples,
	dictionaries, functions, statements and classes

	returns true if it marked everything that this convertor can convert
	returns false if met something it doesn't know
	*/
	bool IsConvertable(std::vector<std::vector<std::string>>& pythonLinesStorage, std::string& conversionError);

	/*
	function that goes over codeStructure vector and attempts to convert it to cpp
	returns true if conversion was successful
	return false if failed and why
	*/
	bool WasConversionSuccessful(std::vector<std::string>& cppLinesStorage, std::string& conversionError);


private:
	/*vector to store which line correspond to imports, comments, documented strings,
	variables, lists, tuples, dictionaries, functions, statements and classes.*/
	std::vector<Markings> codeStructure;


	//returns enum as string from PythonKeyWords
	std::string PythonKeyWordsEnumToString(PythonKeyWords pythonKeyWord);

	//returns PythonKeyWords enum
	PythonKeyWords WhatKeyWordIsThis(const std::vector<std::string>& pythonLinePieces);

	bool IsImport(std::string testString);
	bool IsComment(std::string testString);
	bool IsDocumentedString(std::string testString);
	bool IsVariable(const std::vector<std::string> givenVector);
	bool IsList(const std::vector<std::string> givenVector);
	bool IsDictionary(const std::vector<std::string> givenVector);
	bool IsFunction(std::string testString);
	bool IsStatement(std::string testString);
	bool IsClass(std::string testString);

	/*
	function called by IsVariable, IsList, IsDictionary to check whether 
	variable can be assigned with that call
	*/
	bool IsValidNamingConvention(std::string name);

	/*
	function that is called by IsValidNamingConvention to check whether
	given char is numeric
	*/
	bool IsNumeric(char test);
};