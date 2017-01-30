#pragma once
#include "IOManager.hh"
#include <string>
#include <fstream>
#include <ostream>
#include <XML/rapidxml_utils.hpp>


namespace IOManager {

	levelDetails loadxml(std::string difficulty) {								//loads the correct game difficulty from the xml file configuration
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

	/* Reads all scores stored in a binary file, saves them in the list
	*/
	void readScores(std::list<Score> &scoreList) {
		scoreList.clear();

		std::ifstream freading("../../res/cfg/highScores.bin", std::ios::binary);

		if (freading.good())
		{
			Score score;
			while (!freading.eof()) {
				std::getline(freading, score.name, '\0');											//read player name (ending in null character)
				if (score.name.length() >0)															//if we haven't reached the end (end of file will give 0 characters)
				{
					freading.read(reinterpret_cast<char*>(&score.points), sizeof(score.points));	//Read score (int)
					scoreList.push_front(score);
				}
			}

			scoreList.sort();
			freading.close();
		}
		else
		{
			std::cout << "Error reading file" << "\n";

		}
	}

	/* Saves all scores from the list into a binary file
	*/
	void saveScores(std::list<Score> &scoreList) {

		std::ofstream fwriting("../../res/cfg/highScores.bin", std::ios::binary);

		if (fwriting.good()) {																				//if there are no errors
			for (auto iterator = scoreList.begin(); iterator != scoreList.end(); iterator++)				//iterate scores list
			{
				fwriting.write(iterator->name.c_str(), iterator->name.size());								//Write player name in binary
				fwriting.write("\0", sizeof(char));															//Add null character (to simplify reading)
				fwriting.write(reinterpret_cast<char*>(&iterator->points), sizeof(iterator->points));		//Write score in binary
			}
			fwriting.close();
		}
		else
		{
			std::cout << "Error writing file" << "\n";
		}
		
	}
}