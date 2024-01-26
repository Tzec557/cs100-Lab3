#include "person.h"
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

Person::Person(const char *name_, Person* father_, Person* mother_){
    name = new char[strlen(name_) + 1]; // Allocate enough space for the string and the null terminator
    strcpy(name, name_);
  
    father = father_;
    mother = mother_;
    capacity = 1;
    numChildren = 0;
    children = new Person*[capacity];
}

Person::~Person(){
    delete[] name; // free the dynamically allocated memory
    delete[] children;
}

void Person::addChild(Person *newChild){
    if(numChildren == capacity) expand(&children, &capacity);
    children[numChildren++] = newChild;
}

void Person::printAncestors(){
    cout << endl << "Ancestors of " << name << endl;
    printLineage('u', 0);
}

void Person::printDecendents(){
    cout << endl << "Decendents of " << name << endl;
    printLineage('d', 0);
}

void Person::printLineage(char dir, int level){
    char *temp = compute_relation(level);

    if(dir == 'd'){
        for(int i = 0; i < numChildren; i++){
            cout << temp << "child: " << children[i]->getName() << endl;
            children[i]->printLineage(dir, level + 1);
        }
    } else {
        if(mother){
            cout << temp << "mother: " << mother->getName() << endl;
            mother->printLineage(dir, level + 1);
        }
        if(father){
            cout << temp << "father: " << father->getName() << endl;
            father->printLineage(dir, level + 1);
        }
    }
    delete[] temp;
}

/* helper function to compute the lineage
* if level = 0 then returns the empty string
* if level >= 1 then returns ("great ")^(level - 1) + "grand "
*/

char* Person::compute_relation(int level){
    if(level == 0) return strcpy(new char[1], "");

    char *temp = strcpy(new char[strlen("grand ") + 1], "grand ");

    for(int i = 2; i <= level; i++){
        char *temp2 = new char[strlen("great ") + strlen(temp) + 1];//allocating memory 
        strcat(strcpy(temp2, "great "), temp); // appends the content of temp to the end of temp2 
        delete[] temp;  // Free the memory of the previous string
        temp = temp2;
    }
    return temp;
}
// char* Person::compute_relation(int level){
//     if(level == 0) return strcpy(new char[1], "");
    
//     char *relation = new char[strlen("grand ") + 1];
//     strcpy(relation, "grand ");

//     for(int i = 2; i <= level; i++){
//         char *temp = new char[strlen("great ") + strlen(relation) + 1];
//         strcpy(temp, "great ");
//         strcpy(temp, relation);

//         delete[ ]relation;
//         relation = temp;
//     }
//     return relation;
// }


/* non-member function which doubles the size of t
 * NOTE: t's type will be a pointer to an array of pointers
 */

void expand(Person ***t, int *MAX) {
    Person **temp = new Person*[2 * *MAX];
    for (int i = 0; i < *MAX; ++i) {
        temp[i] = (*t)[i]; // Copy pointers
        (*t)[i] = nullptr; // Set old pointers to nullptr to avoid double deletion
    }
    delete[] *t; // Delete old array of pointers
    *MAX *= 2; // Update campacity
    *t = temp; // Updates the pointer to point to the new array.
}
