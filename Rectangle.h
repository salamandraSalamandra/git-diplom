#pragma once
#include <vector>
class Rectangle

{ //не производитс€ проверка наложени€ !!! все фигуры отдельно считаютс€.

private:
	typedef std::pair<double, double> MyPair;
	
	
public:
	enum MyEnum
	{//по часовой
		leftDown = 0, leftUp = 1//, rightUp = 2, rightDown = 3
	};
	Rectangle(const MyPair & pair_1, const  MyPair & pair_2);//Rectangle(const MyPair &, const MyPair &, const MyPair &, const MyPair &);
	Rectangle(const int = 0);
	~Rectangle();
	friend std::ostream &operator<<(std::ostream &output, const Rectangle &Rect);
	



	static int    getCount();
	static bool   setNorma(const MyPair &);
	static MyPair getNorma();

	size_t getRangNewVector()const;
	
	
	static bool set_Angle_and_deltaStep(const double &angle_, const double &deltaStep_);// дублирование имен??? //0  90 
	static MyPair get_Angle_and_deltaStep();
	std::vector<double> integral(MyEnum);//step можно убрать , по умолчанию с начала фигуры начинать , т е задать начальные услови€.
private:
	
	bool checkValues(const MyPair &pair)const;
	bool mySortClock(std::vector<MyPair> &vec);
private:
	static double angle;
	static double deltaStep;
	static MyPair norma;									//Ќќ–ћ»–ќ¬ ј я„≈… »					
	static int count;
	
	std::vector<MyPair> coorDiag;



};
