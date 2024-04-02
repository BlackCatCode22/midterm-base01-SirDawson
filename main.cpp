#include <iostream>
#include <sstream>
#include <chrono>
#include <vector>

// This is a small, learning program, and these make the code more readable.
using namespace std;
using namespace std::chrono;

// A function that returns the current date
string getCurrentDateISO() {
    // Get the current time_point
    auto now = system_clock::now();

    // Convert the time_point to days
    auto nowInDays = floor<days>(now);

    // Convert to year_month_day
    year_month_day currentDate = year_month_day{nowInDays};

    // Use ostringstream to convert year_month_day to string
    // ostringstream is handy when using mixed data types
    ostringstream oss;
    // This outputs in ISO 8601 format
    oss << currentDate;

    return oss.str();
}

// A function that finds the animal birthdate.
year_month_day calcAnimalBirthday(int age, int birthMonth, int birthDay) {
    // Get the current system time
    auto now = system_clock::now();

    // Convert to a time_point with day precision
    auto nowInDays = floor<days>(now);

    // Convert to year_month_day for easy calendar date manipulation
    year_month_day today = year_month_day{nowInDays};

    // Construct the birthday for this year
    year_month_day thisYearBirthday{today.year(), month{birthMonth}, day{birthDay}};

    // Subtract the age to find the birth year
    year_month_day birthYearBirthday = thisYearBirthday - years{age};

    return birthYearBirthday;
}

class Animal {
  public:
    // The constructor is called when a new object of the class is created.
    // It must be public, the same name as the class and end in ().
    // Here the only thing this constructor will do is increment the numOfAnimals and
    // display that number.
    Animal() {
        numOfAnimals++;
        cout << "\n A new animal was created and there are now " << numOfAnimals << " animals in the zoo!\n";
    }


    // These fields are available to any other class (because they are public).
    string name;
    year_month_day birthDate;
    int weight;
    string color;
    string id;
    string origin;
    year_month_day arrivalDate;

private:
    // Declare this important variable as static - that means it belongs to the class
    // (not to object created from the class)
    static int numOfAnimals;
};

// Create a subclass named Hyena.
class Hyena : public Animal {
public:
    string favoriteFood;

};

int Animal::numOfAnimals = 0;

int main() {
    cout << "\nWelcome to ZKC Base 01\n";
    cout << "This project uses C++ 20 and was created in Clion for CIT-66 Spr '24\n";
    cout << "\nThe current date is: " << getCurrentDateISO() << "\n";

    // Create a dynamic array (vector) that acts as a list of animals.
    vector<Animal> listOfAnimals;


    // Create a new animal on the stack.
    Animal myStackAnimal;
    myStackAnimal.name = "Leo";

    // Add the animal to the vector.
    listOfAnimals.push_back(myStackAnimal);

    // Assume your incoming report says your animal is 7 years old and was born in
    // the fall (Sept 21), create a birthday for your new animal.
    auto animalBirthday = calcAnimalBirthday(7, 9, 21);
    cout << "\nAnimal's Birthday: " << animalBirthday << "\n";

    // Give your new animal its birthdate.
    myStackAnimal.birthDate = animalBirthday;

    // Create a new animal on the heap.
    Animal* myHeapAnimal = new Animal;
    myHeapAnimal->name = "Simba";
    // Add the animal to the vector list.
    // Note how myHeapAnimal is a pointer, so it must be dereferenced before adding to the vector.
    listOfAnimals.push_back(*myHeapAnimal);

    // Delete myHeapAnimal (watch out for those memory leaks) after it is saved to the vector.
    delete myHeapAnimal;

    // Create a couple hyenas named Ed and Zig.
    // Do you want to create them on the stack or on the heap?
    // Let's do stack.
    Hyena hyenaOne;
    Hyena hyenaTwo;

    hyenaOne.name = "Ed";
    hyenaTwo.name = "Zig";

    // Let's add them to our list of animals.
    listOfAnimals.push_back(hyenaOne);
    listOfAnimals.push_back(hyenaTwo);

    // Output the list
    cout << "\n List of animals:";
    for (const auto& animal : listOfAnimals) {
        cout << "\nAnimal's name: " << animal.name << "\n";
    }

    return 0;
}
