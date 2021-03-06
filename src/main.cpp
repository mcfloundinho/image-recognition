#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <exception>
#include "BigImage.hpp"
#include "SmallImageSet.hpp"

using namespace std;

char* getCmdOption(char** begin, char** end, const string& option);
bool cmdOptionExists(char** begin, char** end, const string& option);
void printHelp(char* name);

int main(int argc, char* argv[])
{
    if (cmdOptionExists(argv, argv + argc, "-h")) {
        printHelp(argv[0]);
        return 0;
    }
    if (!cmdOptionExists(argv, argv + argc, "-b") || !cmdOptionExists(argv, argv + argc, "-s")
        || !cmdOptionExists(argv, argv + argc, "-r") || !cmdOptionExists(argv, argv + argc, "-c")) {
        printHelp(argv[0]);
        return 0;
    }
    if (!getCmdOption(argv, argv + argc, "-b") || !getCmdOption(argv, argv + argc, "-s")
        || !getCmdOption(argv, argv + argc, "-r") || !getCmdOption(argv, argv + argc, "-c")) {
        printHelp(argv[0]);
        return 0;
    }
    string bigImageList = getCmdOption(argv, argv + argc, "-b");
    string smallImageList = getCmdOption(argv, argv + argc, "-s");
    int numRow = -1, numColumn = -1;
    stringstream ss;
    ss << getCmdOption(argv, argv + argc, "-r");
    ss >> numRow;
    ss.clear();
    ss << getCmdOption(argv, argv + argc, "-c");
    ss >> numColumn;
    if (numRow <= 0 || numColumn <= 0) {
        printHelp(argv[0]);
        return 0;
    }
    try {
        SmallImageSet smallImageSet(smallImageList);
        ifstream bigImageListStream(bigImageList.c_str());
        string bigImageFileName;
        BigImage* bigImage;
        while (getline(bigImageListStream, bigImageFileName)) {
            bigImage = new BigImage(bigImageFileName, numRow, numColumn);
            bigImage->match(smallImageSet);
            cout << bigImageFileName << ":" << endl;
            bigImage->output();
            cout << endl;
            delete bigImage;
        }
    }
    catch (exception& e) {
        cout << e.what() << endl;
    }
    return 0;
}

char* getCmdOption(char** begin, char** end, const string& option)
{
    char** itr = find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const string& option)
{
    return find(begin, end, option) != end;
}

void printHelp(char* name)
{
    cout << "Usage: " << name << " "
         << "-b BIG_IMAGE_LIST "
         << "-s SMALL_IMAGE_LIST "
         << "-r NUM_ROW "
         << "-c NUM_COLUMN"
         << endl;
}
