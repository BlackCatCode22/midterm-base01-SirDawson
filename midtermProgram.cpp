/*
sD 10/28/24
midtermProgram.cpp
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;
using std::cout;
using std::map;

string removeUnnecessarySpaces(const string& str)
{
    size_t start = 0;
    while(start < str.length() && std::isspace(static_cast<unsigned char>(str[start])))
    {
        start++;
    }

    size_t end = str.length();
    while(end > start && std::isspace(static_cast<unsigned char>(str[end - 1])))
    {
        end--;
    }

    return str.substr(start, end - start);
}

string getRidOfFromWithAspaceInFrontOfIt(const string& origin)
{
    const string fromStr = "from ";
    if(origin.find(fromStr) == 0)
    {
        return origin.substr(fromStr.length());
    }
    
    return origin;
}

class Animal
{
    private:
    string species;
    string name;
    string gender;
    int age;
    string birthSeason;
    string color;
    int weight;
    string origin;
    string id;

    public:
    Animal(string species, string name, string gender, int age, string birthSeason, string color, int weight, string origin, string id) :
    species(species), name(name), gender(gender), age(age), birthSeason(birthSeason), color(color), weight(weight), origin(origin), id(id) {}

    string getSpecies() const {return species;}
    string getName() const {return name;}
    string getGender() const {return gender;}
    int getAge() const {return age;}
    string getBirthSeason() const {return birthSeason;}
    string getColor() const {return color;}
    int getWeight() const {return weight;}
    string getOrigin() const {return origin;}
    string getId() const {return id;}

    static string determineSpecies(const string& origin)
    {
        if(origin.find("Friguia Park") != string::npos)
        {
            return "Hyena";
        }
        else if(origin.find("Zanzibar") != string::npos || origin.find("KopeLion") != string::npos)
        {
            return "Lion";
        }
        else if(origin.find("Dhaka") != string::npos || origin.find("Bardia") != string::npos)
        {
            return "Tiger";
        }
        else if(origin.find("Alaska Zoo") != string::npos || origin.find("Woodland park Zoo") != string::npos)
        {
            return "Bear";
        }

        return "Unknown";
    }
};

class AnimalNames
{
    private:
    map<string, vector<string>> namesMap;
    map<string, size_t> nameIndices;

    public:
    AnimalNames()
    {
        nameIndices["Hyena"] = 0;
        nameIndices["Lion"] = 0;
        nameIndices["Bear"] = 0;
        nameIndices["Tiger"] = 0;
    }

    void readNamesFile(const string& fileName)
    {
        ifstream file(fileName);
        if(!file)
        {
            cout << "There was an error opening the file called: " << fileName << '\n';
            return;
        }

        string line;
        string currentSpecies;
        while(getline(file, line))
        {
            line = removeUnnecessarySpaces(line);
            if(line.empty())
                continue;
            string lowerLine = line;
            std::transform(lowerLine.begin(), lowerLine.end(), lowerLine.begin(),
                           [](unsigned char c){ return std::tolower(c); });

            if(lowerLine.find("names:") != string::npos)
            {
                size_t pos = lowerLine.find("names:");
                currentSpecies = line.substr(0, pos);
                currentSpecies = removeUnnecessarySpaces(currentSpecies);
                continue;
            }

            stringstream ss(line);
            string name;
            while(getline(ss, name, ','))
            {
                name = removeUnnecessarySpaces(name);
                if(!name.empty())
                {
                    namesMap[currentSpecies].push_back(name);
                }
            }
        }

        file.close();
    }

    string getNextName(const string& species)
    {
        if(namesMap.find(species) != namesMap.end())
        {
            auto& namesList = namesMap[species];
            auto& index = nameIndices[species];

            if(index < namesList.size())
            {
                return namesList[index++];
            }
            else
            {
                index = 0;
                return namesList[index++];
            }
        }
        else
        {
            return "Unnamed";
        }
    }
};

class ZooReport
{
    private:
    vector<Animal> animals;
    AnimalNames namesRepo;

    public:
    void readAnimalFile(const string& fileName)
    {
        // Read names first
        namesRepo.readNamesFile("C:/Users/savxl/OneDrive/Documents/animalNames.txt");

        ifstream file(fileName);
        if(!file)
        {
            cout << "There was an error opening the file called: " << fileName << '\n';
            return;
        }

        string line;
        int idCounter = 1;
        while(getline(file, line))
        {
            stringstream ss(line);
            string species, gender, birthSeason, color, origin, temp;
            int age = 0, weight = 0;

            ss >> age >> temp >> temp >> gender;
            getline(ss, temp, ',');
            getline(ss, birthSeason, ',');
            getline(ss, color, ',');
            ss >> weight >> temp;
            getline(ss, origin);

            gender = removeUnnecessarySpaces(gender);
            birthSeason = removeUnnecessarySpaces(birthSeason);
            color = removeUnnecessarySpaces(color);
            origin = removeUnnecessarySpaces(origin);

            origin = getRidOfFromWithAspaceInFrontOfIt(origin);

            species = Animal::determineSpecies(origin);

            string id = species.substr(0, 2) + std::to_string(idCounter);
            idCounter++;

            // Get the next name for the species
            string name = namesRepo.getNextName(species);

            animals.emplace_back(species, name, gender, age, birthSeason, color, weight, origin, id);
        }

        file.close();
    }

    void writeReport(const string& fileName)
    {
        ofstream file(fileName);
        if(!file)
        {
            cout << "There was an error opening the file called: " << fileName << '\n';
            return;
        }

        for(const auto& animal : animals)
        {
            file << animal.getSpecies() << " Habitat:\n";
            file << animal.getId() << "; ";
            file << "Name: " << animal.getName() << "; ";
            file << animal.getAge() << " years old; ";
            file << "birth season " << animal.getBirthSeason() << "; ";
            file << animal.getColor() << "; ";
            file << animal.getGender() << "; ";
            file << animal.getWeight() << " pounds;\n";
            file << "from " << animal.getOrigin() << "\n\n";
        }

        file.close();
    }
};

int main()
{
    ZooReport report;

    report.readAnimalFile("C:/Users/savxl/OneDrive/Documents/arrivingAnimals.txt");

    report.writeReport("C:/Users/savxl/OneDrive/Documents/zooPopulation.txt");

    cout << "A report has been generated. Saved locally at 'C:/Users/savxl/OneDrive/Documents/zooPopulation.txt'.\n";

    return 0;
}

// I'm so glad this finally works!! :D
