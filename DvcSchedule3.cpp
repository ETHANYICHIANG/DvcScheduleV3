//Programmer: Ethan Chiang
//Programmer ID: 1538719

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

#include <cstring>

#include "AssociativeArray.h"

AssociativeArray<int, string> toKeys(const queue<string>&);

int main()
{
  cout << "Programmer: Ethan Yi Chiang\n"
       << "Programmer ID: 1538719\n"
       << "File: " << __FILE__ << endl;

  char* token;
  char buf[1000];
  const char* const tab = "\t";

  AssociativeArray<string, AssociativeArray<string, bool> > seen;
  AssociativeArray<string, AssociativeArray<string, int> > count;

  int dup = 0;
  int num = 0;

  ifstream fin;
  fin.open("dvc-schedule.txt");
  if(!fin.good()) throw "I/O error";
  
  while(fin.good())
  {
    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue; // skip blank lines

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if(course.find('-') == string::npos) continue; // invalid line: no dash in course name
    const string subjectCode(course.begin(), course.begin() + course.find('-'));
    
    if(seen[term][section])
      dup++;
    else 
    {
      seen[term][section] = true;
      count[subjectCode][course]++;
    }

    num++;
    if(num % 7000 == 0)
    {
      cout << ". ";
      cout.flush();
    }
  }
  
  cout << endl;
  fin.close();

  cout << "Duplication: : " << dup << endl;

  AssociativeArray<int, string> subjectKey = toKeys(count.Keys());
  for(int i = 0; i < subjectKey.size(); i++)
    for(int j = i + 1; j < subjectKey.size(); j++)
      if(subjectKey[i] > subjectKey[j])
        swap(subjectKey[i], subjectKey[j]);

  for(int i = 0; i < count.size(); i++)
  {
    cout << subjectKey[i] << ", " << count[subjectKey[i]].size() << " course(s)\n";

    AssociativeArray<int, string> couresKey = toKeys(count[subjectKey[i]].Keys());
    for(int a = 0; a < count[subjectKey[i]].size(); a++)
      for(int b = a + 1; b < count[subjectKey[i]].size(); b++)
        if(couresKey[a] > couresKey[b])
          swap(couresKey[a], couresKey[b]);
    for(int j = 0; j < couresKey.size(); j++)
      cout << "  " << couresKey[j] << ", " << count[subjectKey[i]][couresKey[j]] << " section(s)\n";
  }

  return 0;
}

AssociativeArray<int, string> toKeys(const queue<string>& original)
{
  AssociativeArray<int, string> keys;
  queue<string> qKeys = original;
  
  for(int i = 0; !qKeys.empty(); i++)
  {
    keys[i] = qKeys.front();
    qKeys.pop();
  }

  return keys;
}