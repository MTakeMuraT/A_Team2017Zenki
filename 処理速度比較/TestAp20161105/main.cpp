#include <iostream>
#include<math.h>
#include <windows.h>
#include <time.h>     // for clock()
int main()
{
	//ループ回数
	const int TotalLoop = 5;
	//一時的に書く
	double TotalAve1 = 0;
	double TotalAve2 = 0;
	//一時的に書く

	for (int s = 0; s < TotalLoop; s++)
	{
		std::cout << "\n**********" << s+1 <<"回目ループ**********\n\n";

		//平均時間
		double timeAve = 0;

		//測定回数
		const int Count = 10;

		//内部処理何回やるか
		const int InCount = 1000 * 100;

		//----------------------------------//

		std::cout << "----------1個目----------\n";
		clock_t start = clock();    // スタート時間

		//Count回分計算
		for (int i = 0; i < Count; i++)
		{
			clock_t startTime = clock();

			for (int j = 0; j < InCount; j++)
			{
				//ここに書く----------------------------------
				float x = 5;
				float y = 5;
				float x2 = 0;
				float y2 = 0;

				float tx = 3;
				float ty = 3;
				//左が大きい
				if (x > x2)
				{
					float wo = x2;
					x2 = x;
					x = wo;
				}
				if (y > y2)
				{
					float wo = y2;
					y2 = y;
					y = wo;
				}

				//１のほうが小さくなる
				if ((x < tx && tx < x2) && (y < ty && ty < y2))
				{
					bool flg = false;

					float dx = (x2 - x) * (x2 - x);
					float dy = (y2 - y) * (y2 - y);

					if (dx + dy <= 10*10)
					{

					}
				}

				//ここに書く----------------------------------

			}

			clock_t endTime = clock();

			timeAve += (double)endTime - startTime;
		}

		timeAve /= Count;


		clock_t end = clock();     // 終了時間

		std::cout << "Average = " << timeAve / CLOCKS_PER_SEC << "sec\n";

		std::cout << "TotalTime = " << (double)(end - start) / CLOCKS_PER_SEC << "sec\n";

		//一時的に書く
		TotalAve1 += (double)(end - start);
		//一時的に書く
		
		//----------------------------------//

		//2個目
		std::cout << "----------2個目----------\n";

		timeAve = 0;

		start = clock();

		//Count回分計算
		for (int i = 0; i < Count; i++)
		{
			clock_t startTime = clock();

			for (int j = 0; j < InCount; j++)
			{
				//ここに書く----------------------------------
				float x = 5;
				float y = 5;
				float x2 = 0;
				float y2 = 0;
				
				float tx = 3;
				float ty = 3;

				if (((x < tx && tx < x2) || (x2 < tx && tx < x)) && ((y < ty && ty < y2) || (y2 < ty && ty < y)))
				{
					bool flg = false;

					float dx = abs(x - x2);
					float dy = abs(y - y2);

					dx *= dx;
					dy *= dy;
					if (dx + dy <= 10*10)
					{

					}
				}

				//ここに書く----------------------------------
			}

			clock_t endTime = clock();

			timeAve += (double)endTime - startTime;
		}

		timeAve /= Count;


		end = clock();     // 終了時間

		std::cout << "Average = " << timeAve / CLOCKS_PER_SEC << "sec\n";

		std::cout << "TotalTime = " << (double)(end - start) / CLOCKS_PER_SEC << "sec\n";

		//一時的に書く
		TotalAve2 += (double)(end - start);
		//一時的に書く

		//----------------------------------//

	}

	//一時的に書く
	//ループ分の平均時間を表示
	std::cout << "\n***************************************\n";
	std::cout << "\n" << TotalLoop << "回分の平均時間を表示します\n";
	std::cout << "TotalAve1 = " << (TotalAve1 / TotalLoop) / CLOCKS_PER_SEC << "sec\n";
	std::cout << "TotalAve2 = " << (TotalAve2 / TotalLoop) / CLOCKS_PER_SEC << "sec\n";

	std::cout << "Ave2/Ave1 = " << (TotalAve2 / TotalLoop) / (TotalAve1 / TotalLoop) << "\n";
	std::wcout << "\n-----コード正常終了-----\n\n";
	//一時的に書く


	return 0;
}