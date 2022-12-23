#include <iostream>
#include <format>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <random>
#include<windows.h>
#include<fstream>

using namespace std;

int numberOfPeople = 100;
float bushelsOfWheat = 2800;
int numberOfAcres = 1000;
int roundNumber = 1;
int sownAcres = 0;
int bushesToEat;
int totalNumberOfPeopleDied = 0;

//Random information
int currentAcreCost;
int ammountFromAcre;
int harvest;
float destroyedByRats;
bool wasPlague;
int peopleDied;
int peopleArrived;

bool fromTheSave = false;


int getRandomNum(int minBound, int maxBound) 
{
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<std::mt19937::result_type> dist6(minBound, maxBound); // distribution in range [minBound, maxBound]
	return dist6(rng);
}

bool UpdateRandomData(){
	currentAcreCost = getRandomNum(17, 26);
	ammountFromAcre = getRandomNum(1, 6);
	harvest = ammountFromAcre * sownAcres;
	destroyedByRats = (getRandomNum(0, 7) * (harvest + bushelsOfWheat)) / 100;
	bushelsOfWheat += harvest - ceil(destroyedByRats);
	peopleDied = (bushesToEat - numberOfPeople * 20 > 0) ? 0 : numberOfPeople - floor(bushesToEat / 20);
	totalNumberOfPeopleDied += peopleDied;
	peopleArrived = ((peopleDied / 2 + (5 - ammountFromAcre) * bushelsOfWheat / 600 + 1));
	peopleArrived = clamp((int)peopleArrived, 0, 50);
	if (ceil(numberOfPeople / 100) * peopleDied >= 45)
	{
		return true;
	}
	numberOfPeople += -peopleDied + peopleArrived;
	wasPlague = getRandomNum(0, 100) < 15;
	if (wasPlague)
	{
		numberOfPeople /= 2;
	}
	return false;
}


void printReport(int peopleDied, int peopleArrived, bool wasPlague, int harvest,
			   int ammountFromAcre, int destroyedByRats)
{
	string report = "Мой повелитель, соизволь поведать тебе:\n";
	report += (roundNumber != 1) ? format("\t в году {} твоего высочайшего правления\n", roundNumber) : 
		                           format("\t это Ваш первый год высочайшего правления\n", roundNumber);
	if (roundNumber != 1) {
		report += (peopleDied > 0) ? format("\t {} человек умерли с голоду;\n ", peopleDied) : "";
		report += (peopleArrived > 0) ? format("\t {} человек прибыли в наш великий город;\n", peopleArrived) : "";
		report += (wasPlague) ? "\t Чума уничтожила половину населения;\n" : "";
	}
	report += format("\t Население города сейчас составляет {} человек;\n", numberOfPeople);
	report += (roundNumber != 1) ? format("\t Мы собрали {} бушелей пшеницы, по {} бушеля с акра;\n", harvest, ammountFromAcre) : "";
	

	report += (destroyedByRats == 0) ? "\t Cейчас в амбаре 3103 бушеля пшеницы;\n" :
			  format("\t Крысы истребили {} бушелей пшеницы, сейчас в амбаре {} бушеля пшеницы;\n", destroyedByRats, bushelsOfWheat);
	report += format("\t Город сейчас занимает {} акров;\n", numberOfAcres);
	report += format("\t 1 акр земли стоит сейчас {} бушель.\n", currentAcreCost);
	report += "Что пожелаешь, повелитель?\n";
	cout << report;
}


void SaveProgress() {
	ofstream MyFile("save.txt");
	MyFile << roundNumber << endl;
	MyFile << numberOfPeople << endl;
	MyFile << numberOfAcres << endl;
	MyFile << bushelsOfWheat << endl;

	MyFile << currentAcreCost << endl;
	MyFile << ammountFromAcre << endl;
	MyFile << harvest << endl;
	MyFile << destroyedByRats << endl;
	MyFile << wasPlague << endl;
	MyFile << peopleDied << endl;
	MyFile << peopleArrived << endl;
	MyFile << totalNumberOfPeopleDied << endl;
	
	MyFile.close();
}

void LoadData() {
	system("CLS");
	string myText;
	ifstream MyReadFile("save.txt");
	if (!MyReadFile)
	{
		cout << "There is no saves yet...\nYou will start new game." << endl;
		return;
	}
	getline(MyReadFile, myText);
	roundNumber = std::atoi(myText.c_str());

	getline(MyReadFile, myText);
	numberOfPeople = std::atoi(myText.c_str());

	getline(MyReadFile, myText);
	numberOfAcres = std::atoi(myText.c_str());

	getline(MyReadFile, myText);
	bushelsOfWheat = std::atoi(myText.c_str());



	getline(MyReadFile, myText);
	currentAcreCost = std::atoi(myText.c_str());

	getline(MyReadFile, myText);
	ammountFromAcre = std::atoi(myText.c_str());

	getline(MyReadFile, myText);
	harvest = std::atoi(myText.c_str());

	getline(MyReadFile, myText);
	destroyedByRats = std::atoi(myText.c_str());

	getline(MyReadFile, myText);
	wasPlague = std::atoi(myText.c_str());

	getline(MyReadFile, myText);
	peopleDied = std::atoi(myText.c_str());

	getline(MyReadFile, myText);
	peopleArrived = std::atoi(myText.c_str());

	getline(MyReadFile, myText);
	totalNumberOfPeopleDied = std::atoi(myText.c_str());

	fromTheSave = true;
	// Close the file
	MyReadFile.close();
}

bool playRound()
{
	bool result = false;
	if (fromTheSave)
	{
		fromTheSave = false;
		printReport(peopleDied, peopleArrived, wasPlague, harvest, ammountFromAcre, destroyedByRats);
	}
	else if (roundNumber == 1)
	{
		currentAcreCost = getRandomNum(17, 26);
		printReport(0, 0, false, 0, 0, 0);
	}
	else {
		result = UpdateRandomData();
		printReport(peopleDied, peopleArrived, wasPlague, harvest, ammountFromAcre, destroyedByRats);
		cout << "\n";
		cout << "Do you want to save progress and exit game?\n(yes/no): ";
		string response;
		cin >> response;
		if (response == "yes")
		{
			cout << "Exit...";
			SaveProgress();
			exit(0);
		}
	}
	return result;
}

bool getInput() {
	int a;
	int b;
	int c;
	cout << "Сколько акров земли повелеваешь купить? - ";
	cin >> a;
	cout << "Сколько бушелей пшеницы повелеваешь съесть? - ";
	cin >> b;
	cout << "Сколько акров земли повелеваешь засеять? - ";
	cin >> c;
	if (b + c * 0.5 + a * currentAcreCost > bushelsOfWheat || c > numberOfPeople * 10)
	{
		return false;
	}
	bushelsOfWheat -= b + c * 0.5 + a * currentAcreCost;
	numberOfAcres += a;
	bushesToEat = b;
	sownAcres = c;
	roundNumber += 1;
	system("CLS");
	return true;
}

void gameLoop()
{
	while (true) 
	{
		if (roundNumber >= 11)
		{
			int p = totalNumberOfPeopleDied / 10;
			int l = numberOfPeople / numberOfAcres;
			cout << "You finished the game!!!" << endl;
			if (p > 33 && l < 7)
			{
				cout << "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города.Теперь вы вынуждены влачить жалкое существование в изгнании" << endl;
			}
			else if (p > 10 && l < 9)
			{
				cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному.Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем" << endl;
			}
			else if (p > 3 && l < 10)
			{
				cout << "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова" << endl;
			}
			else {
				cout << "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше" << endl;
			}
			exit(0);
		}
		bool isOver = playRound();
		if (isOver) {
			cout << "Game Over!";
			break;
		}
		while (!getInput())
		{
			cout << format("О, повелитель, пощади нас! У нас только {} человек, {} бушелей пшеницы и {} акров земли!",
				numberOfPeople, bushelsOfWheat, numberOfAcres) << endl;
		}
	}
}

int getRandN(int maxB, int minB) {
	srand(time(0));
	int numberOfItterations = rand() % 10 + 1;
	int result = -1;
	for (size_t i = 0; i <= numberOfItterations; i++)
	{
		result = rand();
		Sleep(100);
	}
	return result % (maxB - minB) + minB;

}

void main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Do you want to continue with save(1) or start a new game(2)?\n ('1' or '2'): ";
	string response;
	cin >> response;
	if (response == "1") {
		LoadData();
	}
	gameLoop();
}