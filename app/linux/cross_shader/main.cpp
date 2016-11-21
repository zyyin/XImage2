#include <opencv_all.h>

void CrossShader(Mat& img, Mat& dst)
{
	//CFunctionLog fl(__FUNCTION__);
	double value;
	double r, g;
	int dim(256);  
	Mat lut(1,&dim,CV_8UC3);  
	uchar *pData = lut.ptr(0);
	for(int i = 0; i < 256; i++)  
	{  
		value=i<128?i:256-i;
		*(pData) = saturate_cast<uchar>(i/2 + 0x25);
		g = pow(value, 2)/128.0;
		*(pData+1) =  (i<128?g:256-g);
		r = pow(value, 3)/64.0/256.0;
		*(pData+2) = (i<128?r:256-r);
		pData+=3;
	}  

	LUT(img, lut, dst);
	return ;
}
static void help()
{
    printf("\nThis is a crossshader sample \n"
           "Call:\n"
           "    /.main [image_name]\n\n");
}

const char* keys =
{
    "{1| |lena.jpg|input image name}"
};

int main( int argc, const char** argv )
{
    help();

    CommandLineParser parser(argc, argv, keys);
    string filename = parser.get<string>("1");

    Mat image = imread(filename, 1);
    if(image.empty())
    {
        printf("Cannot read image file: %s\n", filename.c_str());
        help();
        return -1;
    }
    Mat dst;
    CrossShader(image, dst);
    imshow("dst", dst);
    waitKey(0);

    return 0;
}
