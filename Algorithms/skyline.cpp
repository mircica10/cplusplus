#include "stdafx.h"
#include <vector>
#include <utility>
#include <queue>

class Skyline
{
private:
	struct InterestPoint
	{
		bool isLeft;
		int x;
		int y;
	public:
		InterestPoint(bool _isleft, int _x, int _y)
		{
			isLeft = _isleft;
			x = _x;
			y = _y;
		}

	};
	struct InterestPointCompare
	{
		bool operator()(InterestPoint const &p1, InterestPoint const &p2)
		{
			if (p1.y == p2.y)
				return p1.y < p2.y;
			else
				return p1.x > p2.x;
		}
	};



public:
	std::vector<std::pair<int, int>> getSkyline(std::vector<std::vector<int>> &buildings)
	{
		std::priority_queue<InterestPoint, std::vector<InterestPoint>, InterestPointCompare> coadaPuncteInteres;
		std::vector<InterestPoint> vectorPuncteInteres;


		for (std::vector<int> building : buildings)
		{
			vectorPuncteInteres.push_back(InterestPoint(true, building.at(0), building.at(2)));
			vectorPuncteInteres.push_back(InterestPoint(false, building.at(1), building.at(2)));
		}

		//sortam in ordinea x-urilor
		std::sort(vectorPuncteInteres.begin(), vectorPuncteInteres.end(), [](const InterestPoint &p1, const InterestPoint &p2) {
			return p1.x < p2.x;
		});

		std::vector<std::pair<int, int>> raspuns;

		//pentru fiecare punct
		for (InterestPoint ipCurrent : vectorPuncteInteres)
		{
			if (ipCurrent.isLeft)
			{
				if (coadaPuncteInteres.size() == 0 || ipCurrent.y > coadaPuncteInteres.top().y)
				{
					raspuns.push_back(std::make_pair(ipCurrent.x, ipCurrent.y));
				}
				//introducem in coada prioritara punctul de interes
				coadaPuncteInteres.emplace(ipCurrent);
			}
			else
			{
				if (!coadaPuncteInteres.empty())
				{
					//daca e cea mai mare valoare
					if (ipCurrent.y == coadaPuncteInteres.top().y)
					{
						//o scoatem din heap
						coadaPuncteInteres.pop();
						if ((!coadaPuncteInteres.empty()) && ipCurrent.y > coadaPuncteInteres.top().y)
						{
							raspuns.push_back(std::make_pair(ipCurrent.x, coadaPuncteInteres.top().y));
						}
					}
					else
					{
						coadaPuncteInteres.pop();
					}
				}
			}
		}
		return raspuns;
	}

	void testSkyline()
	{
		std::vector<int> v1 = { 2, 9, 10 };
		std::vector<int> v2 = { 3, 7, 15 };
		std::vector<int> v3 = { 5, 12, 12 };
		std::vector<int> v4 = { 15, 20, 10 };
		std::vector<int> v5 = { 19, 24, 8 };
		std::vector<std::vector<int>> test1 = { v1, v2, v3, v4, v5 };

		std::vector<std::pair<int, int>> raspuns1 = { std::make_pair(2,10), std::make_pair(3,15), std::make_pair(7,12), std::make_pair(12,0),
			std::make_pair(15, 10), std::make_pair(20, 8), std::make_pair(24 ,0) };

		std::vector<std::pair<int, int>> test = getSkyline(test1);



	}

	


};