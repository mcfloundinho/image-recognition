#ifndef BIGIMAGE_HPP
#define BIGIMAGE_HPP

#include <string>
#include <vector>
#include "opencv2/highgui/highgui.hpp"
#include "SmallImageSet.hpp"

using namespace std;
using namespace cv;

class BigImage {
public:
    BigImage(string fileName, int numRow, int numColumn);
    ~BigImage();
    void match(SmallImageSet& smallImageSet);
    void output();

private:
    Mat mImage;
    int mNumRow, mNumColumn;
    vector<Mat*> mBlocks;
    vector<string> mMatchResults;
};

#endif