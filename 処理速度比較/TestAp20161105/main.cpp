#include <iostream>
#include<math.h>
#include <windows.h>
#include <time.h>     // for clock()
int main()
{
	//���[�v��
	const int TotalLoop = 5;
	//�ꎞ�I�ɏ���
	double TotalAve1 = 0;
	double TotalAve2 = 0;
	//�ꎞ�I�ɏ���

	for (int s = 0; s < TotalLoop; s++)
	{
		std::cout << "\n**********" << s+1 <<"��ڃ��[�v**********\n\n";

		//���ώ���
		double timeAve = 0;

		//�����
		const int Count = 10;

		//�������������邩
		const int InCount = 1000 * 100;

		//----------------------------------//

		std::cout << "----------1��----------\n";
		clock_t start = clock();    // �X�^�[�g����

		//Count�񕪌v�Z
		for (int i = 0; i < Count; i++)
		{
			clock_t startTime = clock();

			for (int j = 0; j < InCount; j++)
			{
				//�����ɏ���----------------------------------
				float x = 5;
				float y = 5;
				float x2 = 0;
				float y2 = 0;

				float tx = 3;
				float ty = 3;
				//�����傫��
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

				//�P�̂ق����������Ȃ�
				if ((x < tx && tx < x2) && (y < ty && ty < y2))
				{
					bool flg = false;

					float dx = (x2 - x) * (x2 - x);
					float dy = (y2 - y) * (y2 - y);

					if (dx + dy <= 10*10)
					{

					}
				}

				//�����ɏ���----------------------------------

			}

			clock_t endTime = clock();

			timeAve += (double)endTime - startTime;
		}

		timeAve /= Count;


		clock_t end = clock();     // �I������

		std::cout << "Average = " << timeAve / CLOCKS_PER_SEC << "sec\n";

		std::cout << "TotalTime = " << (double)(end - start) / CLOCKS_PER_SEC << "sec\n";

		//�ꎞ�I�ɏ���
		TotalAve1 += (double)(end - start);
		//�ꎞ�I�ɏ���
		
		//----------------------------------//

		//2��
		std::cout << "----------2��----------\n";

		timeAve = 0;

		start = clock();

		//Count�񕪌v�Z
		for (int i = 0; i < Count; i++)
		{
			clock_t startTime = clock();

			for (int j = 0; j < InCount; j++)
			{
				//�����ɏ���----------------------------------
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

				//�����ɏ���----------------------------------
			}

			clock_t endTime = clock();

			timeAve += (double)endTime - startTime;
		}

		timeAve /= Count;


		end = clock();     // �I������

		std::cout << "Average = " << timeAve / CLOCKS_PER_SEC << "sec\n";

		std::cout << "TotalTime = " << (double)(end - start) / CLOCKS_PER_SEC << "sec\n";

		//�ꎞ�I�ɏ���
		TotalAve2 += (double)(end - start);
		//�ꎞ�I�ɏ���

		//----------------------------------//

	}

	//�ꎞ�I�ɏ���
	//���[�v���̕��ώ��Ԃ�\��
	std::cout << "\n***************************************\n";
	std::cout << "\n" << TotalLoop << "�񕪂̕��ώ��Ԃ�\�����܂�\n";
	std::cout << "TotalAve1 = " << (TotalAve1 / TotalLoop) / CLOCKS_PER_SEC << "sec\n";
	std::cout << "TotalAve2 = " << (TotalAve2 / TotalLoop) / CLOCKS_PER_SEC << "sec\n";

	std::cout << "Ave2/Ave1 = " << (TotalAve2 / TotalLoop) / (TotalAve1 / TotalLoop) << "\n";
	std::wcout << "\n-----�R�[�h����I��-----\n\n";
	//�ꎞ�I�ɏ���


	return 0;
}