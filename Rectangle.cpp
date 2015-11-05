#include "stdafx.h"
#include "Rectangle.h"
#include <iostream>
#include <algorithm>
#include <math.h>


#ifndef  PI
#define PI 3.14159265
#endif

typedef std::pair<double, double> MyPair;

double Rectangle::angle(0);
double Rectangle::deltaStep(0);
int Rectangle::count(0);
MyPair Rectangle::norma = std::make_pair(10.0, 10.0);


//передача вектора в функцию с изменением
bool Rectangle::mySortClock(std::vector<MyPair> &vec)
{
	bool firsPairsIsReserveDiag = false;
	if ((vec[0].first > vec[1].first && vec[0].second > vec[1].second) || (vec[0].first < vec[1].first && vec[0].second < vec[1].second))
		firsPairsIsReserveDiag = true;
	else firsPairsIsReserveDiag = false;
	//std::cout << vec[0].first << " " << vec[0].second << "   ";
	if (firsPairsIsReserveDiag == false)
	{
		//std::cout << vec[0].first << " " << vec[0].second << "   ";
		//std::iter_swap(vec.begin(), vec.begin() + 2);
		//std::iter_swap(vec.begin()+1, vec.begin() + 3);

		std::swap(vec[0], vec[2]);
		std::swap(vec[1], vec[3]);

	}
	//std::cout << vec[0].first << " " << vec[0].second << "   " << std::endl;
	// не сортирует 
	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& функтор??? указатели??
	// std::sort(vec.begin(),vec.begin()+1, myclassCompareLessX());

	 //std::sort(vec.begin()+2,vec.begin()+3, myFunctorCompareLessX);
	
	for (int i = 0; i <= 2; i += 2)
	{
		if (vec[i].first > vec[i + 1].first)
		{
			std::swap(vec[i], vec[i + 1]);
		}
	}
	return true;

}
bool Rectangle::setNorma(const MyPair &pair)
{
	if (pair.first>0 && pair.second>0)
	{
		norma.first = pair.first;
		norma.second = pair.second;
		return true;
	}
	else return false;
}
MyPair Rectangle::getNorma()
{

	return norma;
}

bool Rectangle::set_Angle_and_deltaStep(const double & angle_, const double & deltaStep_)
{
	if (angle_ > 0 && angle_ < 90 && deltaStep_>0)
	{
		angle = angle_;
		deltaStep = deltaStep_;
		return true;
	}
	return false;
}

MyPair Rectangle::get_Angle_and_deltaStep()
{

	return std::make_pair(angle,deltaStep);
}





int Rectangle::getCount()
{
	return count;
}//не использовать констуктор по умолчанию;
 //не использовать констуктор по умолчанию;
Rectangle::Rectangle(const int) 
{
	coorDiag[0] = std::make_pair(0.0, 0.0);
	coorDiag[1] = std::make_pair(0.0, 0.0);
	//currentAngle = leftDown;
	count++;
}
size_t Rectangle::getRangNewVector() const
{
	size_t normaDiag = pow((norma.first*norma.first + norma.second*norma.second), 0.5);
	return ((size_t)normaDiag/deltaStep + 1);

}
//не использовать констуктор по умолчанию;//не использовать констуктор по умолчанию;
bool Rectangle::checkValues(const MyPair &pair)const
{
	if ((pair.first >= 0) && (pair.second >= 0) && (pair.first <= norma.first) && (pair.second <= norma.second))
	{
		return true;
	}
	else return false;
}
Rectangle::Rectangle(const MyPair & pair_1, const  MyPair & pair_2) ///&&&&&&&&&&& currentAngle(leftDown);
{ ///нет проверки наложения одного прямоугольника на другной
	if ((checkValues(pair_1)) && (checkValues(pair_2)))
	{
		if ((pair_1.first != pair_2.first) && (pair_1.second != pair_2.second))
		{
			coorDiag.push_back(pair_1);
			coorDiag.push_back(pair_2);
			coorDiag.push_back(std::make_pair(pair_1.first, pair_2.second));
			coorDiag.push_back(std::make_pair(pair_2.first, pair_1.second));
			//не нужна первые 2 пары - диагональ , среди всех найти минимум и от него отталкиваться
			mySortClock(coorDiag);
		}
		else
		{
			coorDiag.push_back(std::make_pair(0.0, 0.0));
			coorDiag.push_back(std::make_pair(0.0, 0.0));
			coorDiag.push_back(std::make_pair(0.0, 0.0));
			coorDiag.push_back(std::make_pair(0.0, 0.0));
		}
	}
	else
	{
		coorDiag.push_back(std::make_pair(0.0, 0.0));
		coorDiag.push_back(std::make_pair(0.0, 0.0));
		coorDiag.push_back(std::make_pair(0.0, 0.0));
		coorDiag.push_back(std::make_pair(0.0, 0.0));
	}
	//currentAngle = leftDown;
	count++;

}
Rectangle::~Rectangle()
{
	count--; //?????????????????????????????????????????????? не правильно считает
}

std::ostream &operator<<(std::ostream &output, const Rectangle &Rect)
{
	for (int i = 0; i < 4; i++)
	{
		output << "rect  x=" << Rect.coorDiag[i].first << "  y=" << Rect.coorDiag[i].second << "  ";
	}
	output << std::endl;
	return output;
}

//алгоритм
const double EPS = 1E-9;

struct pt {
	double x, y;

	bool operator< (const pt & p) const {
		return x < p.x - EPS || abs(x - p.x) < EPS && y < p.y - EPS;
	}
	void deltaX(double delta)
	{
		x += delta;
	}
	friend std::ostream &  operator<<(std::ostream &output, const pt &p)
	{
		
		
		output << "x=" << p.x << "  y=" << p.y;
		return output;
	}

	
};
pt make_pt(const double &first,const double & second)
{
	pt hold;
	hold.x = first;
	hold.y = second;
	return hold;
}
pt make_pt(const MyPair &pair)
{
	pt hold;
	hold.x = pair.first;
	hold.y = pair.second;
	return hold;
}

struct line {
	double a, b, c;

	line() {}
	line(pt p, pt q) {
		a = p.y - q.y;
		b = q.x - p.x;
		c = -a * p.x - b * p.y;
		norm();
	}

	void norm() {
		double z = sqrt(a*a + b*b);
		if (abs(z) > EPS)
			a /= z, b /= z, c /= z;
	}

	double dist(pt p) const {
		return a * p.x + b * p.y + c;
	}
};

#define det(a,b,c,d)  (a*d-b*c)

inline bool betw(double l, double r, double x) {
	return std::min(l, r) <= x + EPS && x <=std:: max(l, r) + EPS;
}

inline bool intersect_1d(double a, double b, double c, double d) {
	if (a > b)  std::swap(a, b);
	if (c > d)  std::swap(c, d);
	return std::max(a, c) <= std::min(b, d) + EPS;
}
inline double distanse(const pt& first, const pt& second)
{
	return sqrt((first.x - second.x)*(first.x - second.x) + (first.y - second.y)*(first.y - second.y));
}

bool intersect(pt a, pt b, pt c, pt d, pt & left, pt & right) {
	if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
		return false;
	line m(a, b);
	line n(c, d);
	double zn = det(m.a, m.b, n.a, n.b);
	if (abs(zn) < EPS) {
		if (abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS)
			return false;
		if (b < a)  std::swap(a, b);
		if (d < c) std:: swap(c, d);
		left =std:: max(a, c);
		right = std::min(b, d);
		return true;
	}
	else {
		left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn;
		left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;
		return betw(a.x, b.x, left.x)
			&& betw(a.y, b.y, left.y)
			&& betw(c.x, d.x, left.x)
			&& betw(c.y, d.y, left.y);
	}
}

void double_2x(double &x)
{
	x *= 2;
	return;
}
std::vector<double> Rectangle::integral(const MyEnum teckAngle)
{
	
	std::vector<double> S;
	S.reserve(getRangNewVector());
	//    result = cos(param * PI / 180.0);

	//double dX, dY;
	pt crossDiagLeft,crosDiagRight;
	pt diagFirstPoint_Left, trash_DiagSecondPoint_Right;
	pt begin, end, iterator_ActualDown,iterator_actualUp;//begin end y=0 y=0
	
	//const double dX =deltaStep*cos(angle* PI / 180.0);
	double dX;
	//const double dY_div2= deltaStep*sin(angle* PI / 180.0)/2;

	pt outline_Down[2];
	pt outline_Up[2];

	double hold;
	switch (teckAngle)
	{
	case leftDown:
		dX = deltaStep / sin(angle* PI / 180.0);
		hold = norma.second / (tan((angle)* PI / 180.0));
		iterator_ActualDown = begin = make_pt(-hold, 0.0);
		end = make_pt(norma.first, 0.0);

		iterator_actualUp = make_pt(0.0, norma.second);

		diagFirstPoint_Left = make_pt(coorDiag[2]);
		trash_DiagSecondPoint_Right = make_pt(coorDiag[3]);

		
		outline_Down[0] = make_pt(coorDiag[0]);
		outline_Down[1] = make_pt(coorDiag[2]);
		outline_Up[0] = make_pt(coorDiag[2]);
		outline_Up[1] = make_pt(coorDiag[1]);
		break;
	

		
		
	case leftUp:

		dX = deltaStep / sin((90.0-angle)* PI / 180.0);
		iterator_ActualDown=begin = make_pt(0.0, 0.0);
		hold = norma.second / (tan((90.0-angle)* PI / 180.0));
		end = make_pt(hold+norma.first, 0.0);
		
		iterator_actualUp = make_pt(-hold, norma.second);

		diagFirstPoint_Left = make_pt(coorDiag[0]);
		trash_DiagSecondPoint_Right = make_pt(coorDiag[1]);


		
		break;
	}
	{

		std::cout << "begin " << begin << std::endl;
		std::cout << "dX=" << dX << std::endl;
		std::cout << "end " << end << std::endl;
		std::cout << "diagFirstPoint_Left " << diagFirstPoint_Left << std::endl;
		std::cout << "trash_DiagSecondPoint_Right " << trash_DiagSecondPoint_Right << std::endl;
		std::cout << "iterator_actualUp  " << iterator_actualUp << std::endl;
		std::cout << "iterator_ActualDown" << iterator_ActualDown << std::endl;
		std::cin.get();
	}
	//new version
	pt downCross;
	pt upCross;
	//
	
	pt trash;
	hold = 0;
	double predDy=0, tecDy=0;
	bool iter_left_down_angle = true;
	bool iter_right_up_angle = true;
	bool firstIter = true;
	bool lastIter = true;
	bool display = false;
	bool finish_calculation = false;
	int i = -1;
	//std::cin.get();
	//для правильной работы шаг долдены быть меньше минамальной стороны фигуры
	for (iterator_ActualDown=begin; iterator_ActualDown.x < end.x; iterator_ActualDown.deltaX(dX), iterator_actualUp.deltaX(dX))
	{
		i++;
		if (display)
		{
			std::cout << i << " ";
			std::cout << "iterator_actualUp                                  " << iterator_actualUp << std::endl;
			std::cout << "iterator_ActualDown            " << iterator_ActualDown << std::endl;
			//std::cin.get();
		}
		
		
		if (intersect(iterator_ActualDown, iterator_actualUp, diagFirstPoint_Left, trash_DiagSecondPoint_Right, crossDiagLeft, crosDiagRight))
		{
			

			if (teckAngle == leftDown)
			{
				//intersect(iterator_ActualDown, iterator_actualUp, make_pt(coorDiag[0]), make_pt(coorDiag[2]), downCross, trash);
				//intersect(iterator_ActualDown, iterator_actualUp, make_pt(coorDiag[1]), make_pt(coorDiag[2]), upCross, trash);
				intersect(iterator_ActualDown, iterator_actualUp,outline_Down[0],outline_Down[1], downCross, trash);
				intersect(iterator_ActualDown, iterator_actualUp,outline_Up[0],outline_Up[1], upCross, trash);
				predDy = tecDy;
				tecDy = distanse(downCross, upCross);
				if (firstIter)
				{
					firstIter = false;

					double first_katet_Dx = distanse(make_pt(coorDiag[2]), upCross);
					double second_katet_dy = distanse(make_pt(coorDiag[2]), downCross);

					//hold += 0.5*first_katet_Dx*second_katet_dy;
					
				}
				else if (iter_left_down_angle&&(downCross.y )<coorDiag[0].second )
				{
					iter_left_down_angle = false;
					outline_Down[0] = make_pt(coorDiag[0]);
					outline_Down[1] = make_pt(coorDiag[3]);
					intersect(iterator_ActualDown, iterator_actualUp, outline_Down[0], outline_Down[1], downCross, trash);
					tecDy = distanse(downCross, upCross);
					//левый нижний угол
					//hold
					//
					
					pt tempLeftDown;
					intersect(make_pt(iterator_ActualDown.x-dX,iterator_ActualDown.y), make_pt(iterator_actualUp.x - dX, iterator_actualUp.y), make_pt(0.0,coorDiag[0].second), make_pt(norma.first,coorDiag[0].second),tempLeftDown, trash);
					double firstKatet = distanse(tempLeftDown, make_pt(coorDiag[0]));
					double secondKatet=firstKatet*tan(angle* PI / 180.0);
					//hold -= 0.5*firstKatet*secondKatet;
					//hold += deltaStep*(tecDy);
				}
				else if ( iter_right_up_angle&&(upCross.x )> coorDiag[1].first )
				{	
					iter_right_up_angle = false;
					
					outline_Up[0] = make_pt(coorDiag[1]);
					outline_Up[1] = make_pt(coorDiag[3]);
					intersect(iterator_ActualDown, iterator_actualUp, outline_Up[0], outline_Up[1], upCross, trash);
					tecDy = distanse(downCross, upCross);
					

					//правый верхний угол
					//hold
					pt tempLeftDown;
					intersect(iterator_ActualDown,iterator_actualUp, make_pt(0.0, coorDiag[1].second), make_pt(norma.first, coorDiag[1].second), tempLeftDown, trash);
					double firstKatet = distanse(tempLeftDown, make_pt(coorDiag[1]));
					double secondKatet = firstKatet*tan(angle* PI / 180.0);
					//hold += deltaStep*(predDy);
					//hold -= 0.5*firstKatet*secondKatet;

				}
				else if ( lastIter&&(downCross.x+ dX) > coorDiag[3].first)//последний треугольник
				{
					//последний треугольник
					lastIter = false;
					finish_calculation = true;
					double first_katet_Dy = distanse(make_pt(coorDiag[3]), upCross);
					double second_katet_dx = distanse(make_pt(coorDiag[3]), downCross);

					//hold += 0.5*first_katet_Dy*second_katet_dx;
					
				}
				else if (finish_calculation)
				{
					//ничего с холдом не делаем
				}
				else if (true)
					 {
						
						
						 hold += 0.5*deltaStep*(tecDy + predDy);
						 //std::cout << i << " ";
						// std::cout << "true=" << hold << std::endl << std::endl;
						 if (display)
						 {
							 
							 std::cout <<std:: endl <<std:: endl;
							 std::cout <<"downCross     " <<downCross << std::endl;
							 std:: cout << "upCross                           " << upCross <<std:: endl;
							 std::cout <<std:: endl;
							 std::cin.get();
						 }
						 
					}
				
			}
			else 
			{
				//leftUp
			}
			
				
				
		}
		if (display)
		{
			std::cout << i << " ";
			std::cout << "Hold=" << hold << std::endl;
		}
		
		S.push_back(hold);
		
	}
	std::cout << *(S.end()-1) << std::endl;
	return S;
	
}
