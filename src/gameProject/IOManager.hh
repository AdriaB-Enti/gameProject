
#pragma once
#include "ID.hh"
#include <fstream>
#include <sstream>
#include <iterator>
#include "Logger.hh"
#include "Assert.hh"
#include "Resource.hh"
#include <XML/rapidxml_utils.hpp>
#include "LevelDetails.hh"
using namespace Logger;

namespace IOManager {
	
	struct xmlParameters	//BORRAR
	{
		int cells;
		int timeToComplete;
		int snakeVel;
		int initFood;
		int foodIncrease;
	};

	levelDetails loadxml(std::string difficulty) {
		//loads the correct game difficulty configuration
		levelDetails details = levelDetails();
		
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
					details.setInitValues(i, atoi(multNode->value()));
					multNode = multNode->next_sibling();
				}
				break;															//no need to check the rest
			}
			difNode = difNode->next_sibling();
		}

		return details;
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