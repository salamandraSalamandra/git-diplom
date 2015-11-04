// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <fstream>
#include <math.h>
#include <algorithm>
#include "Rectangle.h"


typedef std::pair<double, double> MyPair;

bool input(std::vector<Rectangle> &vecRect)///функция чтения файла и записи данных
{
	std::fstream input;
	input.open("in.txt", std::fstream::in);
	//std::fstream input("D:\C#\ConsoleApplication2\input.txt");

	if (input.is_open())
	{
		MyPair tempDouble, tempDoubleNext;
		input >> tempDouble.first;
		input >> tempDouble.second;
		Rectangle::setNorma(tempDouble);
		int number = 0;
		input >> number;
		for (int i = 0; i < number; i++)
		{
			input >> tempDouble.first;
			input >> tempDouble.second;
			input >> tempDoubleNext.first;
			input >> tempDoubleNext.second;
			Rectangle tempRectFirst(tempDouble, tempDoubleNext);
			vecRect.push_back(tempRectFirst);
			//std::cout << tempRectFirst; 

		}

		input.close();///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
		return true;
	}
	else return false;

	//,std::fstream s
	//checkValues(MyPair);
	return true;
}

/*struct myclassCompareLessX :public std::binary_function<MyPair,MyPair, bool>///check;
{

	bool operator() (const MyPair & first, const MyPair &  second)
	{
		return (first.first < second.first);
		//сортировка
		//нужно придумать
		//if (first.second < second.second)
		//	return true;
		//else(
	}
}myFunctorCompareLessX;//не работает */
//перегрузка потока:

std::ostream &operator<<(std::ostream &output, const MyPair &pair)
{
	output << "MyPair x=" << pair.first << " y=" << pair.second ;
	return output;
}

using std::cout;
using std::endl;
using std::cin;
using std::vector;
template <class T>
void display(const T& rect)
{
	
	cout << rect <<endl;
}
int main()
{
	
	std::vector<Rectangle> vec;
	if (input(vec))
	{
		cout << "input finish" << endl;
	}
	//Rectangle aklja, akljasflk;
	//MyPair hold = Rectangle::getNorma();
	//cout << hold.first << "   " << hold.second << endl;
	//cout <<"countObject="<<Rectangle::getCount()<<endl;

	
	std::for_each(vec.begin(), vec.end(), display<Rectangle>);

	Rectangle::set_Angle_and_deltaStep(80,0.1);
	cout << Rectangle::get_Angle_and_deltaStep() << endl;

	std::vector<double> vec1;
	vec1=vec.begin()->integral(Rectangle::leftDown);

	//std::for_each(vec1.begin(), vec1.end(), display<double>);
	cout << *(vec1.end() - 1) << endl;
	cout << endl <<vec.begin()->getRangNewVector() << endl;
	cout << vec1.size()<<endl;
	system("pause");
    return 0;
}

