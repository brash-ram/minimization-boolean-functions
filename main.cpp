#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector< vector<int> > Matrix;
typedef vector<int> Array;

void dec2bin(int num, int length, Array& result)
{
	int k = 1, b = 0;
	Array bin;

	while (num)
	{
		b += (num % 2) * k;
		k *= 10;
		num /= 2;
	}

	while(b)
    {
        bin.push_back(b % 10);
        b = b / 10;
    }

	while (bin.size() < length){
		bin.push_back(0);
	}

	for (int i = bin.size()-1; i>=0; i--){
		result.push_back(bin[i]);
	}
}

void print(const Matrix& mat){
	for (int i = 0; i<mat.size(); i++){
		cout << "[" << i << "] = ";
		for (int j = 0; j<mat[i].size(); j++)
			cout << mat[i][j] << " ";

		cout << endl;
	}
	cout << endl;
}

bool areShrinking(const Array& array1, const Array& array2){
	bool oneDifference = false;
	if (array1.size() == array2.size()){
		for (int i = 0; i<array1.size(); i++){
			if (oneDifference == false){
				if (array1[i] != array2[i]) oneDifference = true;
			}
			else{
				if (array1[i] != array2[i]) return false;
			}
				
		}
	}
	return oneDifference;
	
}

Array getShrink(const Array& array1, const Array& array2){
	Array result;
	for (int i = 0; i<array1.size(); i++){
		if (array1[i] == array2[i])
			result.push_back(array1[i]);	
	}
	return result;
}

bool inArray(const Array& array, int el){
	for (int i = 0; i<array.size(); i++)
		if (array[i] == el) return true;
}

Matrix getMinFunc(const Matrix& mat){
	Matrix newMat;
	Array visitingIndex;
	int i=0, j=0;
	while (i < mat.size())
	{
		j = i + 1;
		while (j < mat.size())
		{	
			if ((!inArray(visitingIndex, i)) && (!inArray(visitingIndex, j)))
				if (areShrinking(mat[i], mat[j])){
					visitingIndex.push_back(i);
					visitingIndex.push_back(j);
					newMat.push_back(getShrink(mat[i], mat[j]));
				}
			j++;
		}
		i++;
		
	}
	for ( i=0; i<mat.size(); i++){
		if (!inArray(visitingIndex, i)) newMat.push_back(mat[i]);
	}
	if (visitingIndex.size() == 0)
		return mat;
	else return getMinFunc(newMat);
}

int main(){
	while (true){
		int action, length;
		cout << "On what interval to define the function?" << endl;
		cout << "[0] - exit" << endl;
		cout << "[1] - 0-7" << endl;
		cout << "[2] - 0-15" << endl;
		cin >> action;
		if (action == 0) break;

		length = 3+action-1;
		
		int size;
		cout << "Enter size:" << endl;
		cin >> size;

		Matrix matrix(size);
		for (int i=0; i<size; i++){
			int num;
			cout << "[" << i << "] = ";
			cin >> num;
			if ((action == 1))
				if ((num >= 0) && (num <= 7))
					dec2bin(num, length, matrix[i]);
				else break;


			if ((action == 2))
				if ((num >= 0) && (num <= 15))
					dec2bin(num, length, matrix[i]);
				else break;
		}
		cout << endl;
		print(matrix);
		Matrix resMatrix = getMinFunc(matrix);
		cout << "Result" << endl;
		print(resMatrix);

	}
	
	 
	return 0;
}
