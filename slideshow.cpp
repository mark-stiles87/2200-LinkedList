#define WIN32
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
#include "ListLinked.h"
void wait(int secs)
{
	int start = clock();
	while (clock() < start + secs * CLOCKS_PER_SEC);
}
class Slide
{
public:
	static const int HEIGHT = 11,
		WIDTH = 36;
	void display() const;
private:
	char image[HEIGHT][WIDTH];
	int pause;
	friend istream& operator>> (istream& in, Slide& slide);
	friend ostream& operator<< (ostream& out, const Slide& slide);
};
int main()
{
	List<Slide> slideShow;
	Slide currSlide;
	char filename[81];
	cout << endl << "Enter the name of the slide show file: ";
	cin >> filename;
	ifstream slideFile(filename);
	if (!slideFile)
	{
		cout << "Error opening file " << filename << endl;
	}
	else
	{
		// Read in the slides one-by-one.
		while (slideFile >> currSlide)
		{
			slideShow.insert(currSlide);
		}
		slideShow.insert(currSlide);

		// Close file
		slideFile.close();
		// Display the slide show slide-by-slide.
		slideShow.gotoBeginning();
		do
		{
			currSlide = slideShow.getCursor();
			cout << currSlide;
		} while (slideShow.gotoNext());
	}
	return 0;
}
istream& operator>> (istream& inFile, Slide& slide)
{
	char character;
	for (int j = 0; j < slide.HEIGHT; j++)
	{
		for (int i = 0; i < slide.WIDTH; i++)
		{
			inFile.get(character);
			if (character != '\n')
				slide.image[j][i] = character;
			else
			{
				for (int a = i; a < slide.WIDTH; a++)
					slide.image[j][a] = ' ';
				i = slide.WIDTH;
				inFile.clear();
			}
		}
	}
	return inFile;
}
ostream& operator<< (ostream& out, const Slide& slide)
{
	slide.display();
	return out;
}
void Slide::display() const
{
	//This should compile and run on both Windows and Unix
	//Feel free to change this if you want to do something nicer.
#ifdef WIN32
	system("cls");
#else
	system("clear");
#endif
	// Missing 'display' part
	char character;
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			character = image[j][i];
			cout << character;
		}
		cout << '\n';
	}
	wait(1);
	return;
}
