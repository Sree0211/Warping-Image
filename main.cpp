// File to bend image on to a cylindrical projection

#include<iostream>
#include<opencv2/opencv.hpp>
#include<cmath>


using namespace std;

class WarpImage
{
    private:
    cv::Mat out_img;

    public:
    WarpImage(){}

    cv::Point2f projection_point(cv::Point2f& pt, int width, int height)
    {
        cv::Point2f pcenter(pt.x-width/2, pt.y-height/2);

        // Working happens in the z-x plane

        // Focal length and radius for the cylinder
        float f = 10*width; // these can be modified based on your preference
        float r = width;

        float omega = width/2; // This is the x value for the imaginary cylinder
        float z0 = f + sqrt(r*r - omega*omega);

        float zc = (2*z0+sqrt(4*z0*z0-4*(pcenter.x*pcenter.x/(f*f)+1)*(z0*z0-r*r)))/(2* (pcenter.x*pcenter.x/(f*f)+1)); // Point of the image on the cylinder 

        cv::Point2f fpoint(pcenter.x*zc/f, pcenter.y*zc/f);
        fpoint.x += width/2;
        fpoint.y += height/2;
        return fpoint;
    }
    
    cv::Mat projection(const cv::Mat& img)
    {
        int width = img.cols;
        int height = img.rows;

        out_img.create(img.size(), img.type());

        for(int c=0; c<img.channels(); ++c)
        {
            for(int y=0; y<height; y++)
            {
                for(int x=0; x<width; x++)
                {
                    cv::Point2f imgPoint(x,y);
                    imgPoint = projection_point(imgPoint,width,height);

                    cv::Point2i topLeft(static_cast<int>(imgPoint.x),static_cast<int>(imgPoint.y));

                    // Check if the points are inside the image
                    if(topLeft.x < 0 ||
                    topLeft.x > width-2 ||
                    topLeft.y < 0 ||
                    topLeft.y > height-2)
                    {
                        continue;
                    }

                    // Perform interpolation

                    float dx = imgPoint.x - static_cast<float>(topLeft.x);
                    float dy = imgPoint.y - static_cast<float>(topLeft.y);

                    float weight_tl = (1.0 - dx) * (1.0 - dy);
                    float weight_tr = (dx)       * (1.0 - dy);
                    float weight_bl = (1.0 - dx) * (dy);
                    float weight_br = (dx)       * (dy);

                    // Apply the warping process to each channel
                    uchar value = weight_tl * img.at<cv::Vec3b>(topLeft.y, topLeft.x)[c] +
                                  weight_tr * img.at<cv::Vec3b>(topLeft.y, topLeft.x + 1)[c] +
                                  weight_bl * img.at<cv::Vec3b>(topLeft.y + 1, topLeft.x)[c] +
                                  weight_br * img.at<cv::Vec3b>(topLeft.y + 1, topLeft.x + 1)[c];

                    out_img.at<cv::Vec3b>(y,x)[c] = value;
                }
            }
        }
        return out_img;
    }

};

int main()
{
    WarpImage wimg;

    // Load the image
    cv::Mat img = cv::imread("images/n02085936_10307.jpg");

    // Check the image

    if(img.empty())
    {
        cout<<"Could not load the image"<<endl;
        cin.get();
        return -1;
    }
    
    cv::Mat input_img = img.clone();
    // cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY); //  Grayscale image conversion if required

    cv::Mat output_img;
    
    
    output_img = wimg.projection(input_img);
    cout<<" Dimension of the output image is "<<output_img.size()<<endl;

    string windowName = "Warp Image";
    cv::namedWindow(windowName, cv::WINDOW_FREERATIO); // Create a window
    // cv::resizeWindow(windowName,500,500);
    cv::imshow(windowName, output_img); 

    string output_imagePath = "/output/wolves2.jpg";
    cv::imwrite(output_imagePath,output_img);
    cv::waitKey(0);
    cv::destroyWindow(windowName); //destroy the created window

    return 0;

}
