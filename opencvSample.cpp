#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

int morph_alpha = 3;
int isDilation = 0;

Mat out_img;
Mat image;
Mat st_elem;
void on_choice_slider(int, void *)
{
    st_elem = getStructuringElement(MORPH_RECT, Size(morph_alpha, morph_alpha));
    if(isDilation)
    {
        cv::dilate(image,out_img,st_elem);
    }
    else
    { cv::erode(image,out_img,st_elem);}
       
    imshow("processed", out_img);

}
void on_choice_dilation(int, void *)
{
   on_choice_slider(0,0);

}

int main(int argv, char **argc)
{
    if (argv == 1)
    {
        return -1;
    }
    image = imread(std::string(argc[1]));
    
    // Blur image with a Gaussian kernel to remove edge noise
    Mat st_elem = getStructuringElement(MORPH_RECT, Size(morph_alpha, morph_alpha));
    cv::erode(image,out_img,st_elem);    
    namedWindow("Original image");
    namedWindow("processed");
    createTrackbar("morph_alpha","processed",&morph_alpha,30,on_choice_slider);
    createTrackbar("isDilation","processed",&isDilation,1,on_choice_slider);
    imshow("Original image", image);
    imshow("processed", out_img);
    while (char(waitKey(1)) != 'q')
    {
    }
    return 0;
}