#pragma once
#include <string>
#include <vector>
#include <iostream>

//struct for vectors that mark out postions
struct Position
{
	unsigned int begin;
	unsigned int end;

	Position(unsigned int begin, unsigned int end) {
		this->begin = begin;
		this->end = end;
	}
};


class PythonToCpp{
private:
	//bunch of vectors to store line positions of where python keywords begin and end
	std::vector <Position> vectorCommentsandDocumentedStrings;
	std::vector <Position> vectorVariables;
	std::vector <Position> vectorLists;
	std::vector <Position> vectorStatements;
	std::vector <Position> vectorFunctions;

	//to save time these vectors are not going to be implemented
	std::vector <Position> vectorDictionaries;
	std::vector <Position> vectorTuples;
	std::vector <Position> vectorImports;
	std::vector <Position> vectorClasses;

public:
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
	bool IsConvertable(std::vector<std::string>& pythonLinesStorage);
	

};