#include<iostream>
#include <cstdlib>
#include<ctime>
#include <unordered_set>
#include <queue>



using namespace std;


int FIFO(int pages[], int n, int capacity) {//pages第幾筆測資,n是16,capacity計算總容量

	unordered_set<int> s;

	queue<int> indexes;


	int page_faults = 0;
	for (int i = 0; i < n; i++) {

		if (s.size() < capacity) {

			if (s.find(pages[i]) == s.end()) {
				s.insert(pages[i]);
				page_faults++;
				indexes.push(pages[i]);
			}
		}

		else {

			if (s.find(pages[i]) == s.end())
			{

				int val = indexes.front();
				indexes.pop();

				s.erase(val);

				s.insert(pages[i]);

				indexes.push(pages[i]);

				page_faults++;
			}
		}
	}
	return page_faults;
}
int LRU(int pages[], int n, int capacity) {

	vector<int> lrubuffer;

	vector<int> timebuffer;
	int page_faults = 0;
	int time_record = 0;

	for (int i = 0; i < n; i++) {

		if (lrubuffer.size() < capacity) {
			int index = -1;

			for (int j = 0; j < lrubuffer.size(); j++)
				if (lrubuffer[j] == pages[i]) {
					index = j;
					break;
				}

			if (index == -1) {
				lrubuffer.push_back(pages[i]);
				timebuffer.push_back(time_record);
				page_faults++;
			}

			else
				timebuffer[index] = time_record;
		}

		else {
			int index = -1;

			for (int j = 0; j < lrubuffer.size(); j++) {
				if (lrubuffer[j] == pages[i]) {
					index = j;
					break;
				}
			}

			if (index == -1) {
				int lruindex;
				int min = INT_MAX;
				for (int j = 0; j < lrubuffer.size(); j++)
					if (timebuffer[j] < min) {
						lruindex = j;
						min = timebuffer[j];
					}
				lrubuffer[lruindex] = pages[i];
				timebuffer[lruindex] = time_record;
				page_faults++;
			}

			else {
				timebuffer[index] = time_record;
			}
		}
		time_record++;
	}
	return page_faults;
}

int main()
{
	int iter = 10;
	int page_num = 16;
	int pages[10][16];
	srand(time(NULL));

	for (int i = 0; i < iter; i++) {
		for (int j = 0; j < page_num; j++) {
			pages[i][j] = rand() % 8;

		}

	}

	int capacity = 4;
	int FIFOpagefault = 0;
	int LRUpagefault = 0;
	for (int i = 0; i < iter; i++) {
		int f = FIFO(pages[i], page_num, capacity);
		int l = LRU(pages[i], page_num, capacity);
		cout << "Iteration :" << i + 1 << " FIFO pagefault time=" << f << "/" << page_num << ", LRU pagefault time=" << l << "/" << page_num << "\n";
		FIFOpagefault += f;
		LRUpagefault += l;
	}
	cout << "FIFO total pagefault time = " << FIFOpagefault << endl;
	cout << "LRU total pagefault time = " << LRUpagefault << endl;
	system("pause");
	return 0;
}

