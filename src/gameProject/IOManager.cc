#pragma once
#include "IOManager.hh"
#include <fstream>
#include <ostream>
#include <XML/rapidxml_utils.hpp>


namespace IOManager {

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


	void readScores(std::list<Score> &scoreList) {
		scoreList.clear();

		std::ifstream freading("../../res/cfg/highScores.dat", std::ios::binary);

		if (freading.good())
		{
			while (!freading.eof()) {
				Score score;
				std::getline(freading, score.name, '\0');
				freading.read(reinterpret_cast<char *>(&score.points), sizeof(score.points));
				//score.name.pop_back();
				std::cout << score.name << "\n";
				std::cout << score.name.length() << "\n";
				std::cout << score.points << "\n";
				if (score.name.length() != 0)
				{
					scoreList.push_front(score);
				}
			}

			//Score scor1;
			//scor1.name = "adriaaaaaa";
			//scor1.points = 50;
			//Score scor2;
			//scor2.name = "sergi";
			//scor2.points = 40;
			////std::cout << "cert? " << (scor2 < scor1) << std::endl;
			//Score scor3;
			//scor3.name = "lopes";
			//scor3.points = 200;
			//Score scor4;
			//scor4.name = "b";
			//scor4.points = 400;
			//scoreList.push_front(scor1);
			//scoreList.push_front(scor3);
			//scoreList.push_front(scor2);
			//scoreList.push_front(scor4);

			scoreList.sort();
			freading.close();
		}
		else
		{
			std::cout << "Error reading file" << freading.bad() << "\n";

		}
	}

	void saveScores(std::list<Score> &scoreList) {

		std::ofstream fwriting("../../res/cfg/highScores.dat", std::ios::binary);
		std::cout << "ESCRIBINT\n";

		if (fwriting.good()) {
			for (auto iterator = scoreList.begin(); iterator != scoreList.end(); iterator++)
			{
				std::cout << "una score\n";
				fwriting.write(iterator->name.c_str(), sizeof(iterator->name.c_str()));							//write player name				fwriting.write("\0", sizeof(char));
				int ponts = 500;
				fwriting.write(reinterpret_cast<char *>(&ponts), sizeof(ponts));	//write score
				//fwriting.write(reinterpret_cast<char *>(&(iterator->points)), sizeof(iterator->points));	//write score

			}
			fwriting.close();
		}
		else
		{
			std::cout << "Error writing file" << fwriting.bad() << "\n";
		}
		
	}

}