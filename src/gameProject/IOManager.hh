
#pragma once
#include "ID.hh"
#include <fstream>
#include <sstream>
#include <iterator>
#include "Logger.hh"
#include "Assert.hh"
#include "Resource.hh"
#include <XML/rapidxml_utils.hpp>
using namespace Logger;

namespace IOManager {

	// Base test function for XML purposes (TODO)
	/*void TestXML(std::string &&filename) {
	rapidxml::file<> xmlFile(RESOURCE_FILE(filename));
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	rapidxml::xml_node<> *root_node = doc.first_node("document");
	for (rapidxml::xml_node<> * node = root_node->first_node("node"); node; node = node->next_sibling()) {
	Println("Node: ",
	node->first_attribute("att1")->value(),
	" - ",
	node->first_attribute("att2")->value());
	}
	}*/

	struct xmlParameters
	{
		int cells;
		int timeToComplete;
		int snakeVel;
		int initFood;
		int foodIncrease;
	};

	xmlParameters loadxml(std::string difficulty) {
		//loads the correct game difficulty configuration
		xmlParameters parameters;
		
		rapidxml::file<> xmlFile("../../res/cfg/levelcfg.xml");
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *root_node = doc.first_node("levels");
		rapidxml::xml_node<> * difNode = root_node->first_node("difficulty");
		for (int i = 0; i < 3; i++)												//find the right difficulty (only 3 available)
		{
			if (difNode->first_attribute("mode")->value() == difficulty) {
				rapidxml::xml_node<> *multNode = difNode->first_node();
				for (int i = 0; i < 5; i++)										//get the 5 parameters
				{
					switch (i)
					{
					case 0: parameters.cells = atoi(multNode->value());				//atoi -> parse char to int
						break;
					case 1: parameters.timeToComplete = atoi(multNode->value());
						break;
					case 2: parameters.snakeVel = atoi(multNode->value());
						break;
					case 3: parameters.initFood= atoi(multNode->value());
						break;
					case 4: parameters.foodIncrease = atoi(multNode->value());
						break;
					}
					multNode = multNode->next_sibling();
				}
				break;															//no need to check the rest
			}
			difNode = difNode->next_sibling();
		}

		return parameters;
	}








	// Loader function that takes level info for a grid -- per esborrar
	std::vector<std::vector<ObjectID>> LoadLevel(std::string &&filename, int &rows, int &cols) {
		std::ifstream fileData(RESOURCE_FILE(filename));
		ASSERT(fileData.good());
		std::vector<std::vector<ObjectID>> lvlData;
		std::string line;
		while (std::getline(fileData, line)) {
			std::istringstream strData(std::move(line));
			lvlData.emplace_back(std::istream_iterator<ObjectID>(std::move(strData)), std::istream_iterator<ObjectID>());
		}
		rows = int(lvlData.size()); cols = int(lvlData[0].size());
		fileData.close();
#pragma region DEBUG_DATA
		Println("Level: ", filename);
		for (auto &r : lvlData) {
			for (auto &c : r) Print(c, ' ');
			Endln();
		}
#pragma endregion
		return std::move(lvlData);
	}

}