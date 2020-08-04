#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <sstream>
using namespace std;

vector<vector<char>> openfile()
{
	vector<vector<char>>empty;
	string filename;
	ifstream input;
	string line;
	bool loop = true;
	int rows=0,columns=0;

	while(loop)
	{
		cout << "Please enter file name: ";
		cin >> filename;
		input.open(filename);

		if(!input.fail())
		{
			loop = false;

			while(!input.eof())
			{
				getline ( input,line);
				stringstream ss(line);
				char ch;
				empty.resize(rows+1);
				while(ss>>ch)
				{
					empty[rows].push_back(ch);
					if (!(ch == 'x'|| ch== 'o'))
					{
						cout<< filename << " includes invalid char(s)"<< endl;
						empty[0][0]='n';
					}
				}
				columns=empty[0].size();
				if(columns!=empty[rows].size())
				{
					cout<< filename << " is invalid matrix, does not contain same amount of char each row!" << endl;
					empty[0][0]='n';

				}
				rows++;

			}
		}

		if(input.fail())
		{
			empty.resize(1);
			cout<< "Cannot find a file named matrix"<< endl;


		}


	}
	return empty;
}

bool isValid(int a, int b, vector<vector<char>> & mat){
	if ((a < mat.size()  && a >= 0) && (b < mat[0].size()  && b >= 0))
		return true;
	return false;
}

bool isVisited(int x, int y, vector<int> & coordinates){
	int size = coordinates.size();
	for (int i = 0; i < size - 1; i+=2)
	{
		if(coordinates[i] == x && coordinates[i + 1] == y) {
			return true;
		}
	}
	return false;
}

bool isEnclosed(vector<vector<char>> & mat, int x, int y,  vector<int> & coordinates){
	bool lastElement = false;
	if(isValid(x, y + 1, mat)&& !isVisited(x, y + 1, coordinates)  && mat[x][y + 1] == 'x' ){
		return false;
	}

	if(isValid(x, y + 1, mat)&& !isVisited(x, y + 1, coordinates)  && mat[x][y + 1] == 'o' ){
		lastElement = true;
	}

	if(isValid(x + 1, y, mat)  && !isVisited(x + 1, y, coordinates) && mat[x + 1][y] == 'x'){
		return false;
	}

	if(isValid(x + 1, y, mat)  && !isVisited(x + 1, y, coordinates) && mat[x + 1][y] == 'o'){
		lastElement = true;
	}

	if(isValid(x, y - 1, mat)&& !isVisited(x, y - 1, coordinates)  && mat[x][y - 1] == 'x' ){
		return false;

	}

	if(isValid(x, y - 1, mat)&& !isVisited(x, y - 1, coordinates)  && mat[x][y - 1] == 'o' ){
		lastElement = true;

	}

	if(isValid(x - 1, y, mat) && !isVisited(x-1, y, coordinates) && mat[x - 1][y] == 'x'){
		return false;
	}

	if(isValid(x - 1, y, mat) && !isVisited(x-1, y, coordinates) && mat[x - 1][y] == 'o'){
		lastElement = true;
	}

	return lastElement;

}

void findTheArea(vector<vector<char>> & mat, const int & x, const int & y,  vector<int> & coordinates, bool & found){


	if(isValid(x, y + 1, mat)&& !isVisited(x, y + 1, coordinates)  && mat[x][y + 1] == 'x' && !found){
		coordinates.push_back(x);
		coordinates.push_back(y + 1);
		found = isEnclosed(mat, x, y+1, coordinates);
		findTheArea(mat, x, y + 1, coordinates, found); 
	}

	if(isValid(x + 1, y, mat)  && !isVisited(x + 1, y, coordinates) && mat[x + 1][y] == 'x' && !found ){
		coordinates.push_back(x+1);
		coordinates.push_back(y);
		found = isEnclosed(mat, x + 1, y, coordinates);

		findTheArea(mat, x + 1, y, coordinates, found); 
	}

	if(isValid(x, y - 1, mat)&& !isVisited(x, y - 1, coordinates)  && mat[x][y - 1] == 'x'  &&  !found){
		coordinates.push_back(x);
		coordinates.push_back(y - 1);
		found = isEnclosed(mat, x, y - 1, coordinates);

		findTheArea(mat, x , y - 1, coordinates, found); 


	}

	if(isValid(x - 1, y, mat) && !isVisited(x-1, y, coordinates) && mat[x - 1][y] == 'x' && !found){
		coordinates.push_back(x-1);
		coordinates.push_back(y);
		found = isEnclosed(mat, x - 1, y, coordinates);

		findTheArea(mat, x - 1, y, coordinates, found); 
	}
}

void printVector(vector<int> & a){
	for (int i = 0; i < a.size() - 1; i+=2)
	{
		cout << a[i] << "	" << a[i + 1] << endl;
	}
}


int main()
{
	vector<int> coords;
	vector<vector<char>>matrices;
	matrices=openfile();
	cout<<endl;

	if(matrices[0][0]=='n')
	{
		cin.ignore();
		cin.get();
		return 0;

	}
	cout<< "Input Matrix:"<< endl<<endl;
	for (int j=0; j < matrices.size(); j++)
	{   

		for (int k=0; k < matrices[j].size(); k++)
		{   
			cout << matrices[j][k]<< " ";
		}
		cout << endl;
	} 
	int X, Y;
	int x,y;
	bool coord =false;

	cout << "Please enter starting coordinates, first row X then column Y: ";
	cin>> X>> Y;
	while(X != -1 && Y != -1)
	{


		if(!(cin.fail()))
		{
			if(!((int)X>matrices.size()-1||(int)Y>matrices[0].size()-1))
			{
				if(!((int)X<0||(int)Y<0))
				{
					coords.push_back(X);
					coords.push_back(Y);
					findTheArea(matrices, X, Y, coords, coord);
					if(coords.size() == 2)
						cout << "The cell is not occupied." << endl;
					else if(coord){
						cout << "Found an enclosed area. The coordinates of the followed path: " << endl;
						printVector(coords);
					}
					else if(!coord){
						cout << "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path: " << endl;
						printVector(coords);
					}
					coords.clear();
					cout << "Please enter starting coordinates, first row X then column Y: ";
					cin>> X>> Y;
				}
				else{
					cout<<endl<< "Invalid Coordinates" << endl;
					cout << "Please enter starting coordinates, first row X then column Y: ";
					cin>> X>> Y;
				}
			}
			else{
				cout<<endl<< "Invalid Coordinates" << endl;
				cout << "Please enter starting coordinates, first row X then column Y: ";
				cin>> X>> Y;
			}
		}
		else{
			cout<<endl<< "Invalid Coordinates" << endl;
			cout << "Please enter starting coordinates, first row X then column Y: ";
			cin>> X>> Y;
		}
		cin.clear();
		cin.ignore(256,'\n');
	}  
	
	cin.ignore();
	cin.get();




	return 0;
}