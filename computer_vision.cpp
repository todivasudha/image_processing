#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <queue>
#include <vector>
using namespace cv;
using namespace std;

/*int main()
{
	Mat img;
	int i, j;
	img = imread("fruits.jpg", CV_LOAD_IMAGE_COLOR);
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			img.at<Vec3b>(i, j)[0] = 0;
			img.at<Vec3b>(i, j)[1] = 0;
		}
	}
	namedWindow("My window", WINDOW_AUTOSIZE);
	imshow("My window", img);
	waitKey(0);
	return 0;


}*/

/*int main()
{
Mat img(300,1000,CV_8UC3);
int i, j;
for (i = 0; i < 100; i++)
{
for (j = 0; j < 1000; j++)
{
img.at<Vec3b>(i, j)[0] = 0;
img.at<Vec3b>(i, j)[1] = 165;
img.at<Vec3b>(i, j)[2] = 255;
}
}
for (i = 100; i < 200; i++)
{
for (j = 0; j < 1000; j++)
{
img.at<Vec3b>(i, j)[0] = 255;
img.at<Vec3b>(i, j)[1] = 255;
img.at<Vec3b>(i, j)[2] = 255;

}
}
for (i =200; i < 300; i++)
{
for (j = 0; j < 1000; j++)
{
img.at<Vec3b>(i, j)[0] = 0;
img.at<Vec3b>(i, j)[1] = 255;
img.at<Vec3b>(i, j)[2] = 0;

}
}

namedWindow("My window", WINDOW_AUTOSIZE);
imshow("My window", img);
waitKey(0);
return(0);

}*/

Mat greyscale(Mat img)
{
	int i, j;
	Mat x(img.rows, img.cols, CV_8UC1);
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			x.at<uchar>(i, j) = (img.at<Vec3b>(i, j)[0] + img.at<Vec3b>(i, j)[1] + img.at<Vec3b>(i, j)[2]) / 3;
		}
	}
	return x;
}
/*int main()
{
	Mat img;
	img = imread("fruits.jpg", CV_LOAD_IMAGE_COLOR);
	Mat x(img.rows, img.cols, CV_8UC1);
	x = greyscale(img);
	namedWindow("My window", WINDOW_AUTOSIZE);
	imshow("My window", x);
	waitKey(0);
	return 0;
}*/
Mat binary(Mat img,int t)
{
	Mat x(img.rows, img.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (img.at<uchar>(i, j) < t)
				x.at<uchar>(i, j) = 0;
			else
				x.at<uchar>(i, j) = 255;
		}
	}
	return x;
}

/*int main()
{
	Mat image;
	image= imread("fruits.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img(image.rows, image.cols, CV_8UC1);
	img = greyscale(image);
	int thres;
	cin >> thres;
	Mat x;
	x = binary(img,thres);
	namedWindow("My window", WINDOW_AUTOSIZE);
	imshow("My window", x);
	waitKey(0);
	return 0;
}*/

/*Mat invert(Mat image)
{
	Mat x(image.rows, image.cols, CV_8UC3);
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			x.at<Vec3b>(i, j)[0] = image.at<Vec3b>(image.rows - i-1, j)[0];
			x.at<Vec3b>(i, j)[1] = image.at<Vec3b>(image.rows - i-1, j)[1];
			x.at<Vec3b>(i, j)[2] = image.at<Vec3b>(image.rows - i-1, j)[2];
		}
	}
	return x;
		
}*/

/*int main()
{
	Mat img;
	img = imread("fruits.jpg", CV_LOAD_IMAGE_COLOR);

	Mat x = invert(img);
	namedWindow("My window", WINDOW_AUTOSIZE);
	imshow("My window", x);
	waitKey(0);
	return 0;
}*/
int thres;
Mat histogram(Mat img)
{
	int a[256];
	int i, j, t,s=0;
	for (i = 0; i < 256; i++)
		a[i] = 0;
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
			a[img.at<uchar>(i, j)]++;
	}
	for (i = 0;;i++)
	{
		s += a[i];
		if (s>img.rows*img.cols / 2)
		{
			thres = i;
			break;
		}

	}
	for (i = 0; i < 256; i++)
		a[i] = a[i] / 20;
	t = a[0];
	for (i = 1; i < 256; i++)
	{
		if (a[i]>t)
			t = a[i];
	}
	Mat x(t , 256, CV_8UC1);
	for (j = 0; j < 256; j++)
	{
		for (i = 0; i < t; i++)
		{
			if (i < (t - a[j]))
				x.at<uchar>(i, j) = 255;
			else
				x.at<uchar>(i, j) = 0;
		}
	}
	return x;
}

/*int main()
{
	Mat image,x,y;
	image = imread("fruits.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img(image.rows, image.cols, CV_8UC1);
	img = greyscale(image);
	x = histogram(img);
	namedWindow("My window", WINDOW_AUTOSIZE);
	imshow("My window", x);
	waitKey(0);
	y = binary(img, thres);
	namedWindow("My window", WINDOW_AUTOSIZE);
	imshow("My window", y);
	waitKey(0);
	return 0;
} */





Mat binary1(Mat img, int  p,int q,int r)
{
	Mat x(img.rows, img.cols, CV_8UC3);
	int i, j;
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (img.at<Vec3b>(i, j)[0] < r)
				x.at<Vec3b>(i, j)[0] = 0;
			else
				x.at<Vec3b>(i, j)[0] = 255;
			if (img.at<Vec3b>(i, j)[1] < q)
				x.at<Vec3b>(i, j)[1] = 0;
			else
				x.at<Vec3b>(i, j)[1] = 255;
			if (img.at<Vec3b>(i, j)[2] < p)
				x.at<Vec3b>(i, j)[2] = 0;
			else
				x.at<Vec3b>(i, j)[2] = 255;
		}
	}
	return x;
}

/*int main()
{
	int p = 0, q = 0, r = 0;
	Mat img, y;
	img = imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("My window", CV_WINDOW_FULLSCREEN);
	createTrackbar("Red", "My window", &p, 255);
	createTrackbar("Green", "My window", &q, 255);
	createTrackbar("Blue", "My window", &r, 255);
	while (1)
	{
		y = binary1(img, p,q,r);
		imshow("My window", y);
		char a = waitKey(33);
		if (a == 27) break;
	}

}*/

Mat edgeDetection(Mat img,int p)
{
	Mat x(img.rows,img.cols,CV_8UC1);
	int i, j, k,l,max,min;
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (i == 0 || j == 0 || i == img.rows - 1 || j == img.cols - 1)
				x.at<uchar>(i, j) = 0;
			else
			{
				 max = img.at<uchar>(i, j);
				 min = img.at<uchar>(i, j);
				for (k = i - 1; k <= i + 1; k++)
				{
					for (l = j - 1; l <= j + 1; l++)
					{
						if (max<img.at<uchar>(k, l))
							max = img.at<uchar>(k, l);
						if (min>img.at<uchar>(k, l))
							min = img.at<uchar>(k, l);
					}
				}
				if (max - min > p)
					x.at<uchar>(i, j) = 255;
				else
					x.at<uchar>(i, j) = 0;
			}
		}
	}
   return x;
	}

/*int main()
{
	
	Mat img;
	int p;
	img =imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image = greyscale(img);
	Mat x;
	namedWindow("My window", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "My window", &p, 255);
	while (1)
	{
		 x = edgeDetection(image,p);
		imshow("My window", x);
		char a = waitKey(33);
		if (a == 27) break;
	}
	return 0;
}*/

Mat edgeDetection1(Mat img)
{
	Mat z(img.rows, img.cols, CV_8UC1,Scalar(0));
	int i, j, k, l, x, y;
	for (i = 1; i < img.rows-1; i++)
	{
		for (j = 1; j < img.cols-1; j++)
		{
				x = 0;
				y = 0;
				for (k = i - 1; k <= i + 1; k++)
				{
					for (l = j - 1; l <= j + 1; l++)
					{
						y += (k - i)*img.at<uchar>(k, l);
						x += (l - j)*img.at<uchar>(k, l);
					}
				}
				z.at<uchar>(i, j) =(uchar)sqrt((x*x) + (y*y));
				if (z.at<uchar>(i, j) > 255)
					z.at<uchar>(i, j) = 255;
		}
	}
	return z;
}

/*int main()
{
	Mat img;
	img = imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image = greyscale(img);
	Mat x;
	namedWindow("My window", WINDOW_AUTOSIZE);
		x = edge1detection1(image);
		imshow("My window", x);
		waitKey(0);
	return 0;
}*/

Mat dilation(Mat img)
{
	Mat x(img.rows, img.cols, CV_8UC1,Scalar(0));
	int i, j, k, l, b=0,w=0;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			b = 0; w = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					if (img.at<uchar>(k, l) == 0)
						b++;
					else w++;
				}
			}
			if (b > w)x.at<uchar>(i, j) = 0;
			else x.at<uchar>(i, j) = 255;
		}
	}
	return x;
}
Mat erosion(Mat img)
{

	Mat x(img.rows, img.cols, CV_8UC1, Scalar(0));
	int i, j, k, l, b = 0, w = 0;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			b = 0; w = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					if (img.at<uchar>(k, l) == 0)
						b++;
					else w++;
				}
			}
			if ((b < w||w==0)&&b!=0)x.at<uchar>(i, j) = 0;
			else x.at<uchar>(i, j) = 255;
		}
	}
	return x;
}

/*int main()
{
	Mat img;
	img = imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image = greyscale(img);
	namedWindow("My window", WINDOW_AUTOSIZE);
	namedWindow("My window1", WINDOW_AUTOSIZE);
	namedWindow("My window2", WINDOW_AUTOSIZE);
	image = edgeDetection(image,25);
	imshow("My window2", image);
	image = dilation(image);
	imshow("My window1", image);
	image = erosion(image);
	imshow("My window", image);
	waitKey(0);
	return 0;
}*/

Mat meanFilter(Mat img)
{
	Mat x(img.rows, img.cols, CV_8UC1, Scalar(0));
	int i, j, k, l,s;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			s = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					s += img.at<uchar>(k, l);
				}
			}
			x.at<uchar>(i, j) = s/9;
		}
	}
	return x;
}

Mat medianFilter(Mat img)
{
	Mat x(img.rows, img.cols, CV_8UC1, Scalar(0));
	int i, j, k, l,a[9],c,temp;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			c = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					a[c]= img.at<uchar>(k, l);
					c++;
				}
			}
			for (k = 8; k >=0; k--)
			{
				for (l = 0; l < 9 - k-1; l++)
				{
					if (a[l]>a[l + 1])
					{
						temp = a[l];
						a[l] = a[l + 1];
						a[l + 1] = temp;
					}
				}
			}
			x.at<uchar>(i, j) = a[4];
		}
	}
	return x;
}

Mat guassianFilter(Mat img)
{
	Mat x(img.rows, img.cols, CV_8UC1, Scalar(0));
	int i, j, k, l;
	double temp[3][3] = { 0.06, 0.098, 0.06, 0.098, 0.162, 0.098, 0.06, 0.098, 0.06 };
	double s=0.0;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			s = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					s += temp[k - i + 1][l - j + 1] * img.at<uchar>(k, l);
				}
			}
			x.at<uchar>(i, j) = s;
		}
	}
	return x;
}

/*int main()
{
	Mat img;
	img = imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image = greyscale(img);
	Mat x,y,z;
	namedWindow("My window", WINDOW_AUTOSIZE);
	namedWindow("My window1", WINDOW_AUTOSIZE);
	namedWindow("My window2", WINDOW_AUTOSIZE);
	x = mean(image);
	imshow("My window", x);
	y = median(image);
	imshow("My window1", y);
	z = guassian(image);
	imshow("My window2", z);
	waitKey(0);
	return 0;
}*/
/*
int main()      //canny
{
	int p, q;
	namedWindow("My window", WINDOW_AUTOSIZE);
	createTrackbar("Threshold 1", "My window", &p, 255);
	createTrackbar("Threshold 2", "My window", &q, 255);
	Mat img = imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image = greyscale(img);
	Mat x;
	while (1)
	{
		Canny(image, x, p, q);
		imshow("My window", x);
		char a = waitKey(33);
		if (a == 27) break;
	}
	
	
}
*/
/*int main()  //video
{
	Mat frame;
	VideoCapture V("video.mp4");
	int p = 0, q = 0;
	namedWindow("My window", WINDOW_AUTOSIZE);
	createTrackbar("Threshold 1", "My window", &p, 255);
	createTrackbar("Threshold 2", "My window", &q, 255);
	while (1)
	{
		V >> frame;
		Mat img;
		img = greyscale(frame);
		Canny(img, img, q, p);
		imshow("My window", img);
		char a=waitKey(1);
		if (a == 27)break;
	}
	return 0;
}*/
Mat colorDetection(Mat img, int tol,int h,int s,int l,int tol1,int tol2)
{
	int i, j;
	Mat x(img.rows, img.cols, CV_8UC3);
	cvtColor(img, x, CV_BGR2HLS_FULL);
	Mat y(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (x.at<Vec3b>(i, j)[0]<h + tol&&x.at<Vec3b>(i, j)[0] > h - tol&&x.at<Vec3b>(i, j)[2]<s + tol1&&x.at<Vec3b>(i, j)[2] > s - tol1&&x.at<Vec3b>(i, j)[1]<l + tol2&&x.at<Vec3b>(i, j)[1] > l - tol2)
				y.at<uchar>(i, j) = 255;
		}
	}
	return y;
}

/*int main()
{
	int p = 0, q = 0, r = 0, s = 0, t = 0, u = 0;
	Mat img, x, y;
	img = imread("b.png", CV_LOAD_IMAGE_COLOR);
	namedWindow("My window", CV_WINDOW_AUTOSIZE);
	createTrackbar("Hue Threshold", "My window", &p, 240);
	createTrackbar("Hue", "My window", &q, 240);
	createTrackbar("Saturation Threshold", "My window", &t, 240);
	createTrackbar("Saturation", "My window", &r, 240);
	createTrackbar("Light Threshold", "My window", &u, 240);
	createTrackbar("Light", "My window", &s, 240);
	while (1)
	{
		x = colorDetection(img, p, q, r, s, t, u);
		imshow("My window1", x);
		char a = waitKey(33);
		if (a == 27) break;
	}
}*/




Mat shade(Mat x)
{
	int i, j;
	Mat y(x.rows, x.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < x.rows; i++)
	{
		for (j = 0; j < x.cols; j++)
		{
			if (x.at<char>(i, j) != -1)
				y.at<uchar>(i, j) =255/ x.at<char>(i, j);
		}
	}
	return y;

}

Mat blobDetection(Mat img)
{
	queue<Point> q;
	int i, j, c = 1, m, n;
	Mat x(img.rows, img.cols, CV_8SC1, Scalar(-1));
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			m = i; n = j;
			if (img.at<uchar>(i, j) == 255 && x.at<char>(i, j) == -1)
			{
				Point temp(m, n);
				q.push(temp);
				x.at<char>(i, j) = c;
				while (!q.empty())
				{
					for (int k = m - 1; k <= m + 1; k++)
					{
						for (int l = n - 1; l <= n + 1; l++)
						{
							if (img.at<uchar>(k, l) == 255 && x.at<char>(k, l) == -1)
							{
								Point temp3(k, l);
								q.push(temp3);
								x.at<char>(k, l) = c;
							}
						}
					}
					q.pop();
					if (!q.empty())
					{
						Point temp2;
						temp2 = q.front();
						m = temp2.x;
						n = temp2.y;
					}
				}
				c++;
			}
		}
	}
	return x;
}

/*int main()
{
	Mat img, x;
	img = imread("abc.png", CV_LOAD_IMAGE_GRAYSCALE);
	namedWindow("My window", CV_WINDOW_FULLSCREEN);
	x = blobDetection(img);
	x = shade(x);
	imshow("My window", x);
	waitKey(0);
	return 0;
}*/

Mat linesDetection(Mat img)
{
	int i, j, k,r;
	Mat x(10000, 181, CV_16UC1, Scalar(0));
	
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (img.at<uchar>(i, j) > 200)
			{
				for (k = 0; k < 180; k++)
				{
					r = abs(j*cos((k*CV_PI) / 180) + i*sin((k*CV_PI) / 180));
					x.at<unsigned short>(r,k)++;
				}
			}
		}
	}
	int max = 0;
	i = 0; j = 0;
	{
		max = 0;
		for (r = 0; r < 10000; r++)
		{
			for (k = 0; k <= 180; k++)
			{
				int c = 0;
				for (int a = r - 5; a <= r + 5; a++)
				{
					for (int b = k - 2; b <= k + 2; b++)
					{
						if (a>=0&&b>=0&&a<10000&&b<180)
						c += x.at<unsigned short>(a, b);
					}
				}

				       if (c>max)
				    {
						   max = c;
					  i = r; j = k;
				   }
			}
		}
	}
	Mat z(1500, 181, CV_8UC1, Scalar(0));
	for (k = 0; k < 1500; k++)
	{
		for (r = 0; r <= 180; r++)
		{
			z.at<uchar>(k, r) = x.at<unsigned short>(k, r) * 255 / x.at<unsigned short >(i,j);
		}
	}
	namedWindow("My window1", WINDOW_AUTOSIZE);
	imshow("My window1", z);
	Mat y(img.rows, img.cols, CV_8UC1,Scalar(0));

	for (int f = 0; f < img.cols; f++)
	{
		k = (i - f*cos(j*3.14159 / 180)) / sin(j*3.14159 / 180);
		if (k<img.rows && k>-1)
		y.at<uchar>(k,f) = 255;
	}
	return y;
}
/*int main()
{
	Mat img, x;
	img = imread("abc3.png", CV_LOAD_IMAGE_GRAYSCALE);
	x = linesDetection(img);
	namedWindow("My window", WINDOW_AUTOSIZE);
	imshow("My window", x);
	waitKey(0);
	return 0;
}*/

Point shapeDetection(Mat img,int p)
{
	vector<vector<Point> > c;
	findContours(img, c, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	vector<Point> app;
	Point a;
	float d;
	for (int j = 0; j < c.size();j++)
	cout << c[j].size()<<endl;
	for (int i = 0; i < c.size(); i++)
	{
		double epsilon = 0.04*arcLength(c[i], true);
		approxPolyDP(c[i], app, epsilon, true);
		cout << app.size() << endl;
		if (app.size() == p)
		{
			a.x = 0;
			a.y = 0;
			for (int j = 0; j < p; j++)
			{
				a.x += (int)app[j].x;
				a.y += (int)app[j].y;
			}
			d = (app[1].x - app[0].x)*(app[1].x - app[0].x) + (app[1].y - app[0].y)*(app[1].y - app[0].y);
			if (d>1000)
			{
				a.x /= p;
				a.y /= p;
				cout << "(" << a.x << "," << a.y << ")\n";
				return a;
			}
		}	
		else if ((app.size()>4 && p == 0))
		{
			float m1 = (float)(app[1].y - app[0].y) / (float)(app[1].x - app[0].x);
			float m2 = (float)(app[2].y - app[1].y) /(float) (app[2].x - app[1].x);
			a.x =(int) (m1*m2*(app[2].y - app[0].y) + m1*(app[1].x + app[2].x) - m2*(app[1].x + app[0].x)) / (2 * (m1 - m2));
			a.y = (int)((app[0].x + app[1].x) / 2 - a.x) / m1 + (app[0].y + app[1].y) / 2;
			d = (a.x - app[0].x)*(a.x - app[0].x) + (a.y - app[0].y)*(a.y - app[0].y);
			if (d > 1000)
			{
				cout << "(" << a.x << "," << a.y << ")\n";
				return a;
			}
		}
	}
	a.x = a.y = -1;
	return a;

}
/*int main()
{
	int k=75;
	int p;
	Mat image;
	image = imread("b1.png", CV_LOAD_IMAGE_COLOR);
	Mat y = colorDetection(image,50,171,240 ,116,50, 50);
	Mat x(y.rows,y.cols,CV_8UC1,Scalar(0));
	x = dilation(y);
	namedWindow("My window", WINDOW_AUTOSIZE);
	imshow("My window", x);
	waitKey(0);
	Point a = shapeDetection(x,0);
	if (a.y < image.rows-k&&a.y>=0)
	{
	cout << "(" << a.x << "," << a.y << ")\n";
	
	}
	y= colorDetection(image, 50, 254, 240, 110, 75, 50);
	x = dilation(y);
	imshow("My window", x);
	waitKey(0);
	 a = shapeDetection(x, 4);
	 if (a.y < image.rows-k&&a.y>=0)
	 {
		 cout << "(" << a.x << "," << a.y << ")\n";
		
	 }
    y = colorDetection(image, 50, 254, 240, 111, 50, 50);
	x = dilation(y);
	imshow("My window", x);
	waitKey(0);
    a = shapeDetection(x, 3);
	if (a.y < image.rows-k&&a.y>=0)
	{
		cout << "(" << a.x << "," << a.y << ")\n";
	
	}
	y = colorDetection(image, 30, 42, 240, 125, 50, 50);
	x = dilation(y);
	imshow("My window", x);
	waitKey(0);
	a = shapeDetection(x, 4);
	if (a.y < image.rows-k&&a.y >= 0)
	{
		cout << "(" << a.x << "," << a.y << ")\n";
	
	}
	y = colorDetection(image, 50, 84, 222, 73, 75, 50);
	x = dilation(y);
	imshow("My window", x);
	waitKey(0);
	a = shapeDetection(x, 5);
	if (a.y < image.rows-k&&a.y >= 0)
	{
		cout << "(" << a.x << "," << a.y << ")\n";
		
	}
	getchar();
	return 0;
}*/

int main()
{
	int k = 75;
		int p,i,j;
		Mat image;
		VideoCapture V("PS.mp4");
		namedWindow("My window", WINDOW_AUTOSIZE);
		while (1)
		{
			V >> image;
			Mat y;
			Mat q(image.rows, image.cols, CV_8UC3, Scalar(255));
			Mat x(image.rows, image.cols, CV_8UC1, Scalar(0));
			Point a;
			while (1)
			{
				V >> image;
				y = colorDetection(image, 50, 171, 240, 116, 50, 50);
				x = dilation(y);
				a = shapeDetection(x, 0);
				if (a.y < image.rows-k&&a.y >= 0)
				{
					for (i = 0; i<image.rows; i++)
					{
						for (j = 0; j < image.cols; j++)
						{
							if (i>image.rows - 20 && j > a.x - 80 && j < a.x + 80)
								q.at<Vec3b>(i, j)[0] = q.at<Vec3b>(i, j)[1] = q.at<Vec3b>(i, j)[2]= 0;
							else {
								q.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, j)[0];
								q.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[1];
								q.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[2];
							}
						}
					}
					imshow("My window", q);
					waitKey(1);
				}
				if (a.y >image.rows - k || a.y == -1)
					break;
			}
			while (1)
			{
				V >> image;
				y = colorDetection(image, 50, 254, 240, 111, 50, 50);
				x = dilation(y);
				a = shapeDetection(x, 4);
				if (a.y < image.rows - k&&a.y >= 0)
				{
					for (i = 0; i<image.rows; i++)
					{
						for (j = 0; j < image.cols; j++)
						{
							if (i>image.rows - 20 && j > a.x - 80 && j < a.x + 80)
								q.at<Vec3b>(i, j)[0] = q.at<Vec3b>(i, j)[1] = q.at<Vec3b>(i, j)[2] = 0;
							else{
								q.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, j)[0];
								q.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[1];
								q.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[2];
							}
						}
					}
					imshow("My window", q);
					waitKey(1);
				}
				if (a.y >image.rows - k || a.y == -1)
					break;
			}
			while (1)
			{
				V >> image;
				y = colorDetection(image, 50, 254, 240, 111, 50, 50);
				x = dilation(y);
				a = shapeDetection(x, 3);
				if (a.y < image.rows - k&&a.y >= 0)
				{
					for (i = 0; i<image.rows; i++)
					{
						for (j = 0; j < image.cols; j++)
						{
							if (i>image.rows - 20 && j > a.x - 80 && j < a.x + 80)
								q.at<Vec3b>(i, j)[0] = q.at<Vec3b>(i, j)[1] = q.at<Vec3b>(i, j)[2] = 0;
							else {
								q.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, j)[0];
								q.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[1];
								q.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[2];
							}
						}
					}
					imshow("My window", q);
					waitKey(1);
				}
				if (a.y >image.rows - k || a.y == -1)
					break;
			}
			while (1)
			{
				V >> image;
				y = colorDetection(image, 30, 42, 240, 125, 50, 50);
				x = dilation(y);
				a = shapeDetection(x, 4);
				if (a.y < image.rows - k&&a.y >= 0)
				{
					for (i = 0; i<image.rows; i++)
					{
						for (j = 0; j < image.cols; j++)
						{
							if (i>image.rows - 20 && j > a.x - 80 && j < a.x + 80)
								q.at<Vec3b>(i, j)[0] = q.at<Vec3b>(i, j)[1] = q.at<Vec3b>(i, j)[2] = 0;
							else
							{
								q.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, j)[0];
								q.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[1];
								q.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[2];
							}
					    }
					}
					imshow("My window", q);
					waitKey(1);
				}
				if (a.y >image.rows - k || a.y == -1)
					break;
			}
			while (1)
			{
				V >> image;
				y = colorDetection(image, 50, 84, 222, 73, 75, 50);
				x = dilation(y);
				a = shapeDetection(x, 5);
				if (a.y < image.rows - k&&a.y >= 0)
				{
					for (i = 0; i<image.rows; i++)
					{
						for (j = 0; j < image.cols; j++)
						{
							if (i>image.rows - 20 && j > a.x - 80 && j < a.x + 80)
								q.at<Vec3b>(i, j)[0] = q.at<Vec3b>(i, j)[1] = q.at<Vec3b>(i, j)[2] = 0;
							else {
								q.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, j)[0];
								q.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[1];
								q.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[2];
							}
						}
					}
					imshow("My window", q);
					waitKey(1);
				}
				if (a.y >image.rows - k || a.y == -1)
					break;
			}
			char w=waitKey(1);
			if (w == 27) break;

		}
		return 0;
}
