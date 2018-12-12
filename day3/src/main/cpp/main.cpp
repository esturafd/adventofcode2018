#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

void push_vector(vector<string> &vec, string &str) {
   if (!str.empty()) {
      vec.push_back(str);
   }
}

vector<string> string_split(string str, string dlm) {
   size_t pos = str.find(dlm);
   vector<string> foo;
   string token;
   while (pos != string::npos) {
      token = str.substr(0, pos);
      push_vector(foo, token);
      str.erase(0, pos + dlm.length());
      pos = str.find(dlm);
   }
   push_vector(foo, str);
   return foo;
}

void initialize_matix(int (&matrix)[1000][1000], int value) {
   int i, j;
   for (i = 0; i < 1000; i++) {
      for (j = 0; j < 1000; j++) {
         matrix[i][j] = value;
      }
   }
}

int total_square_inches(int (&data)[1000][1000]) {
   int i, j, foo;
   foo = 0;
   for (j = 0; j < 1000; j++) {
      for (i = 0; i < 1000; i++) {
         if (data[i][j] > 1) {
            foo++;
         }
      }
   }
   return foo;
}

int analyze_data(ifstream& file, int (&data)[1000][1000], bool rereading) {
   string line;
   int i, j, foo = 0;
   if (file.is_open()) {
      while (getline(file, line)) {
         bool one_use = true;
         vector<string> args_line = string_split(line, " ");
         vector<string> coordinates = string_split(args_line[2], ",");
         vector<string> size = string_split(args_line[3], "x");
         coordinates[1].erase(coordinates[1].find(":"));
         for (i = stoi(coordinates[0]) +1; i <= stoi(coordinates[0]) + stoi(size[0]); i++) {
            for (j = stoi(coordinates[1]) +1; j <= stoi(coordinates[1]) + stoi(size[1]); j++) {
               if (rereading && data[i][j] > 1) {
                  one_use = false;
               } else if (!rereading) {
                  data[i][j]++;
               }
            }
         }
         if (one_use) {
            foo = stoi(args_line[0].erase(0, 1));
         }
      }
   }
   return foo;
}

void first_puzzle(ifstream &file) {
   int chimney_squeeze[1000][1000];
   initialize_matix(chimney_squeeze, 0);
   analyze_data(file, chimney_squeeze, false);
   int square_inches = total_square_inches(chimney_squeeze);
   printf("Square inches reused is: %d\n", square_inches);
}

void second_puzzle(ifstream &file) {
   int chimney_squeeze[1000][1000];
   initialize_matix(chimney_squeeze, 0);
   analyze_data(file, chimney_squeeze, false);
   file.clear();
   file.seekg(0, file.beg);
   int req = analyze_data(file, chimney_squeeze, true);
   printf("The claim that does not repeat space is: %d\n", req);
}

int main(int argc, char** argv) {
   ifstream file("input.txt");
   string option(argv[1]);
   if (option == "1") {
      first_puzzle(file);
   } else if (option == "2") {
      second_puzzle(file);
   }
   file.close();
   return 0;
}
