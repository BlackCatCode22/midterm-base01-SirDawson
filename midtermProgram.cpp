/*
sD 10/25/24
midtermProgram.cpp
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;
using std::cout;

string removeUnnecessarySpaces(const string& str)
{
    size_t start = 0;
    while(start < str.length() && std::isspace(str[start]))
    {
        start++;
    }

    size_t end = str.length() - 1;
    while(end > start && std::isspace(str[end]))
    {
        end--;
    }

    return str.substr(start, end - start + 1);
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
    string gender;
    int age;
    string birthSeason;
    string color;
    int weight;
    string origin;
    string id;

    public:
    Animal(string species, string gender, int age, string birthSeason, string color, int weight, string origin, string id) :
    species(species), gender(gender), age(age), birthSeason(birthSeason), color(color), weight(weight), origin(origin), id(id) {}
    string getSpecies() const {return species;}
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
        else if (origin.find("Zanibar") != string::npos || origin.find("KopeLion") != string::npos)
        {
            return "Lion";
        }
        else if (origin.find("Dhaka") != string::npos || origin.find("Bardia") != string::npos)
        {
            return "Tiger";
        }
        else if (origin.find("Alaska Zoo") != string::npos || origin.find("Woodland park Zoo") != string::npos)
        {
            return "Bear";
        }

        return "Unknown";
    }
};

class ZooReport
{
    private:
    vector<Animal> animals;

    public:
    void readAnimalFile(const string& fileName)
    {
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

        animals.emplace_back(species, gender, age, birthSeason, color, weight, origin, id);
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