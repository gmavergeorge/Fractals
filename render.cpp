#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

ifstream fin("mandeloutput.ppm");
ofstream fout("obj.gpl");

string null;
int width;
int height;
int depth;

void getHeader(std::ifstream& i){
	i >> null;
	i >> width;
	i >> height;
	i >> depth;
}

string getColor(std::ifstream& i){
	string line;
	fin >> line;
	fin >> line;
	fin >> line;
	return line;
}

int main(){
	getHeader(fin);
	cout << "Color Depth: "<< depth << endl;
	cout << "Width: "<< width << endl;
	cout << "Height: "<< height << endl;
	for(int w=1; w<=width; w++){
		for(int h=1;h<=height; h++){
			fout << w << " " << h << " " << stoi(getColor(fin)) << endl;
		}
	}
	return 0;
}