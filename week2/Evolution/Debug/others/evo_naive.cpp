#include <iostream>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

string solve(string child, int age, map<string, int>& ages, map<string, string>& relations){
  string parent;
  int year_parent;
  parent = relations.find(child)->second;
  year_parent = ages.find(parent)->second;
  while(age >= year_parent){
    //cout << age << endl;
    //cout << year_parent << endl;
    child = parent;
    //find new parent age
    parent = relations.find(child)->second;
    year_parent = ages.find(parent)->second;
  }
  return child;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int cases;
  cin >> cases;
  for (int c = 0; c < cases; c++) {
    int n, qs, age, q_age;
    string species, child, parent, q_species;
    std::cin >> n;
    std::cin >> qs;
    map<string, int> ages;
    map<string, string> relations;
    //cout << " hi"<< endl;
    // loading in species and ages
    for (int s = 0; s < n; s++) {
      std::cin >> species;
      std::cin >> age;
      ages[species] = age;
    }

    // loadin in relations
    for (int r = 0; r < n-1; r++) {
      std::cin >> child;
      std::cin >> parent;
      relations[child] = parent;
    }

    /*map<string,string>::iterator it;
    for(it = relations.begin(); it != relations.end(); it++){
      cout << "second " << it->second << endl;
    }*/

    // loading in queries
    string ans;
    for (int q = 0; q < qs; q++) {
      std::cin >> q_species;
      std::cin >> q_age;
      ans = solve(q_species, q_age, ages, relations);
      std::cout << ans << " ";
    }
    std::cout << endl;
  }
  return 0;
}
