#include <iostream>
#include <fstream>
using namespace std;

int numRows;
int numCols;
int minVal;
int maxVal;
int** imgAry;

class image
{
public:
	image(int row, int col, int min, int max)
	{
		numRows = row;
		numCols = col;
		minVal = min;
		maxVal = max;
		imgAry = new int*[numRows + 2];
		for(int i = 0; i < numRows + 2; i++)
		{
			imgAry[i] = new int[numCols + 2];
		}
	}

	~image()
	{
		for(int i = 0; i < numRows+2; ++i)
		{
			delete[] imgAry[i];
		}
		delete[]imgAry;
	}

	void zeroFramed()
	{
		for(int col = 0; col < numCols + 2; col++)
		{
			imgAry[0][col] = 0;
		}

		for(int row = 0; row < numRows + 2; row++)
		{
			imgAry[row][0] = 0;
		}
	}
};

class chainCode
{
public:
	class point
	{
	public:
		int row;
		int col;
	};

	point neighborCoord[8];
	point startP;
	point currentP;
	point nextP;
	int nextQ;
	int lastQ;
	int nextDirTable[8] = {6, 0, 0, 2, 2, 4, 4, 6};  // range from 0 to 7, direction of last zero
	int nextDir;
	int PchainDir; // chain code direction from currentP to nextP

	chainCode(ofstream &outFile1, ofstream &outFile2)
	{
		getChainCode(outFile1, outFile2);
	}

	void getChainCode(ofstream &outFile1, ofstream &outFile2)
	{
		int count = 0;
		for(int i = 1; i < numRows + 1; i++)
		{
			for(int j = 1; j < numCols + 1; j++)
			{
				if(imgAry[i][j] > 0)
				{
					outFile1 << i << " " << j << " " << imgAry[i][j] << " ";
					outFile2 << i << " " << j << " " << imgAry[i][j] << " " << endl;
					startP.row = i;
					startP.col = j;
					currentP.row = i;
					currentP.col = j;
					lastQ = 4;
					do
					{
						nextQ = (lastQ + 7) % 8;
						PchainDir = findNextP(currentP, nextQ, nextP);
						outFile1 << PchainDir<< " ";
						outFile2 << PchainDir<< " ";
						lastQ = nextDirTable[PchainDir - 1];
						currentP = nextP;
						count++;
						if(count == 15)
						{
							outFile2 << endl;
							count = 0;
						}
					}
					while(!((currentP.row == startP.row) && (currentP.col == startP.col)));
					return;
				}
			}
		}
	}

	void loadNeighborsCoord(point currentP)
	{
		int r = currentP.row;
		int c = currentP.col;
		neighborCoord[0].row = r;
		neighborCoord[0].col= c + 1;
		neighborCoord[1].row = r - 1;
		neighborCoord[1].col= c + 1;
		neighborCoord[2].row = r - 1;
		neighborCoord[2].col= c;
		neighborCoord[3].row = r - 1;
		neighborCoord[3].col= c - 1;
		neighborCoord[4].row = r;
		neighborCoord[4].col= c - 1;
		neighborCoord[5].row = r + 1;
		neighborCoord[5].col= c - 1;
		neighborCoord[6].row = r + 1;
		neighborCoord[6].col= c;
		neighborCoord[7].row = r + 1;
		neighborCoord[7].col= c + 1;
	}

	 int findNextP(point currentP, int nextQ, point nextP1)
	 {
		 loadNeighborsCoord(currentP);
		 int chainDir = getChainDir(currentP, nextQ);
		 nextP = neighborCoord[chainDir];
		 return chainDir;
	 }

	 int getChainDir(point currentP, int nextQ)
	 {
		 int chainDir = nextQ;
		 for(int i = 0; i < 8; i++)
		 {
			 int x = neighborCoord[chainDir].row;
			 int y = neighborCoord[chainDir].col;

			 if(imgAry[x][y] != 0)
			 {
				 return chainDir;
			 }
			 else
			 {
				 chainDir = (chainDir + 1) % 8;
			 }
		 }
	 }
};

int main(int argc, char **argv)
{
	ifstream inFile;
	ofstream outFile1;
	ofstream outFile2;

	if (!inFile)
	{
		cout << "ERROR to open file";
		exit(1);
	}
	inFile.open(argv[1]);
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);

	int row, col, min, max;
	inFile >> row >> col >> min >> max;
	image img(row, col, min, max);
	img.zeroFramed();
	int value;
	while(!inFile.eof())
	{
		for(int i = 1; i < numRows + 1; i++)
		{
			for(int j = 1; j < numCols + 1; j++)
			{
				inFile >> value;
				imgAry[i][j] = value;
			}
		}
	}
	outFile1 << row << " " << col << " " << min << " " << max << endl;
	outFile2 << row << " " << col << " " << min << " " << max << endl;
	chainCode chain(outFile1, outFile2);

	inFile.close();
	outFile1.close();
	outFile2.close();
	return 0;
}
