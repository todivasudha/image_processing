#include <stdio.h>
#include "iostream"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <queue>
//#include "tserial.h"
//#include "bot_control.h"
//#include "targetver.h"
using namespace std;
using namespace cv;
const int lmargin = 10;
const int rmargin = 790;
const int umargin = 10;
const int dmargin = 590;
const int r = 16;
const int t = 16;
const int R = 50;
const int lcols = 460;
const int thresh = 5;
Point pos;
Point bcentre;
VideoCapture v("augh1.avi");
VideoCapture v1(2);

Mat rgb_to_hsl(Mat img1)
{
	Mat img2;
	cvtColor(img1, img2, CV_BGR2HLS);
	//imshow("2", img2);
	return (img2);
}
Mat blob(Mat img)
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
//int main()
//{
//	Mat img;
//	//img = imread("Capture.png", CV_LOAD_IMAGE_COLOR);
//	v1 >> img;
//	Mat img3(img.rows, img.cols, CV_8UC1, Scalar(0));
//	imshow("abc", img);
//	img = rgb_to_hsl(img);
//	int p = 0, q = 0, r = 0,s=0,t=0,u=0;
//		namedWindow("My window", CV_WINDOW_FULLSCREEN);
//		createTrackbar("Hue Threshold", "My window", &p, 240);
//			createTrackbar("Hue", "My window", &q, 240);
//			createTrackbar("Saturation Threshold", "My window", &t, 240);
//			createTrackbar("Saturation", "My window", &r, 240);
//			createTrackbar("Light Threshold", "My window", &u, 240);
//			createTrackbar("Light", "My window", &s, 240);
//		while (1)
//		{   
//			for (int i = 0; i < img.rows; i++)
//			{
//				for (int j = 0; j < img.cols; j++)
//				{  
//					if (((img.at<Vec3b>(i, j)[0]<q+ p) && (img.at<Vec3b>(i, j)[0]>q - p)) && ((img.at<Vec3b>(i, j)[1]<u + s) && (img.at<Vec3b>(i, j)[1]>s - u)) && ((img.at<Vec3b>(i, j)[2]<r + t) && (img.at<Vec3b>(i, j)[2]>r- t)))
//						img3.at<uchar>(i, j) = 255;
//					else img3.at<uchar>(i, j) = 0;
//				}
//			}
//			imshow("My window", img3);
//			char a = waitKey(33);
//			if (a == 27) break;
//		}
//	waitKey(0);
//
//}
int cam(Mat frame)
{
	int i, j;
	Mat img = rgb_to_hsl(frame);
	Mat img3(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (((img.at<Vec3b>(i, j)[0]<193 + 67) && (img.at<Vec3b>(i, j)[0]>193 - 67)) && ((img.at<Vec3b>(i, j)[1]<19 + 100) && (img.at<Vec3b>(i, j)[1]>19 - 100)) && ((img.at<Vec3b>(i, j)[2]<37 + 138) && (img.at<Vec3b>(i, j)[2]>37 - 138)) )img3.at<uchar>(i, j) = 255;
		}
	}
	/*namedWindow("pop", CV_WINDOW_AUTOSIZE);
	imshow("pop", img3);*/
	Mat img4(img.rows, img.cols, CV_8SC1, Scalar(-1));
	img4 = blob(img3);
	int max_val=0, val=1, max_no = 0, no=0;
	while (1)
	{
		no = 0;
		for (i=0; i < img.rows; i++)
		{
			for (j=0; j < img.cols; j++)
			{
				if (img4.at<char>(i, j) == val)
				{
					cout << no << endl;
					no++;
				}
			}
		}
		if (no == 0) break;
	    if (no>max_no)
		{
					max_no = no;
					max_val = val;
		}
		val++;
	}
	cout << max_no;
	cout << val;

	cout << endl << "c";
	Point center;
	center.x = 0;
	center.y = 0;
	for (i = 10; i < img4.rows-10; i++)
	{
		for (j = 10; j < img4.cols-10; j++)
		{
			if (img4.at<char>(i, j) == max_val)
			{
				center.x += j;
				center.y += i;
			}
		}

	}
	return center.x/max_no;
}



Point centreball(Mat img1)
{
	Mat img2;
	//imshow("pop2", img1);
	cvtColor(img1, img2, CV_BGR2HLS);
	//imshow("pop1", img2);
	Mat img3(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((img2.at<Vec3b>(i, j)[0]<60 + 5) && (img2.at<Vec3b>(i, j)[0]>60 - 5)) img3.at<uchar>(i, j) = 255;
		}
	}
	/*namedWindow("pop", CV_WINDOW_AUTOSIZE);
	imshow("pop", img3);*/
	Mat img4(img3.rows, img3.cols, CV_8SC1, Scalar(-1));
	img4 = blob(img3);
	int max_val, val, max_no = 0, no;
	for (int i =20; i < img4.rows-70; i++)
	{
		for (int j = 16; j < img4.cols-16; j++)
		{
			if (img4.at<char>(i, j) != -1)
			{
				no = 0;
				val = img4.at<char>(i, j);
				for (int k = 0; k < img4.rows; k++)
				{
					for (int l = 0; l < img4.cols; l++)
					{
						if (img4.at<char>(k, l) == val)
						{
							no++;
						}
					}
				}
				if (no>max_no)
				{
					max_no = no;
					max_val = val;
				}
			}
		}
	}
	Point center;
	center.x = 0;
	center.y = 0;
	for (int i = 0; i < img4.rows; i++)
	{
		for (int j = 0; j < img4.cols; j++)
		{
			if (img4.at<char>(i, j) == max_val)
			{
				center.x += j;
				center.y += i;
			}
		}
	}
	center.x = center.x / max_no;
	center.y /= max_no;
	return center;
}
float slope()
{
	float s=0.0;
	int n = 0;
	int i, j;
	
	Mat frame;
	Point initpos;
	v >> frame;
	bcentre = centreball(frame);
	initpos.x = bcentre.x;
	initpos.y = bcentre.y;
	cout << "(" << initpos.x << "," << initpos.y << ")" << endl;
startslope:
	for (i = 0; i<5; i++)
	{   
		v >> frame;
		//imshow("a", frame);
		bcentre = centreball(frame);
		cout << i <<endl;
		if ((bcentre.x + r >= rmargin - t) || (bcentre.x - r <= lmargin + t))
		{
			cout << "in";
			initpos.x = bcentre.x;
			initpos.y = bcentre.y;
			goto startslope;
		}
		if ((bcentre.x - initpos.x) != 0)
		{
			cout << "(" << bcentre.x << "," << bcentre.y << ")" << endl;
			cout << "(" << initpos.x << "," << initpos.y << ")" << endl;
			s =s+ (float)(bcentre.y - initpos.y) / (float)(bcentre.x - initpos.x);
			cout << s << endl;
			n++;
		}
	}
	s /= n;
	return s;
}
float ncollisions(float s)
{
	Mat frame;
	int a, b, c, d;
	v >> frame;
	pos.y = lcols;
	pos.x = bcentre.x;
	int x;
  if(s==0)
  return s;
	bcentre = centreball(frame);
	if (s>0)
	{
		d = lcols - (bcentre.y + (rmargin - bcentre.x) *s);
		if (d > 0)
		{
			c = s*(rmargin - lmargin);
			b = d / c;
			a = d%c;
			x = a / s;
			cout << "d" << d << " c" << c << " b" << b << " a" << a << " x" << x;
			if (b % 2 == 0)
			{
				s = -s;
				pos.x = rmargin - x;
				cout << pos.x<<"pos.x"<<endl;
			}
			else
				pos.x = x;
		}
		if (d < 0)
		{
			x = (lcols - bcentre.y) / s;
			pos.x = bcentre.x + x;
		}
	}
	else if (s<0)
	{
		d = lcols - (bcentre.y + bcentre.x *(-s));
		if (d>0)
		{
			c = (-s)*(rmargin - lmargin);
			b = d / c;
			a = d%c;
			x = a /(-s);
			cout << "d" << d << " c" << c << " b" << b << " a" << a << " x" << x;
			if (b % 2 == 0)
			{
				s = -s;
				pos.x = x;
			}
			else
				pos.x = rmargin - x;

		}
		else
		{
			x = (lcols - bcentre.y) /s;
			pos.x = bcentre.x + x;
		}
	}
	return s;
}
Point brick(float s)
{
	Mat frame;
	frame = imread("v5.png", CV_LOAD_IMAGE_COLOR);
	v >> frame;
	//imshow("pop2", frame);
	int val;
	Mat img2;
	//namedWindow("pop2", CV_WINDOW_AUTOSIZE);
	
	cvtColor(frame, img2, CV_BGR2HLS);
	//imshow("pop1", img2);
	Mat img3(frame.rows, frame.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < frame.rows; i++)
	{
		for (int j = 0; j < frame.cols; j++)
		{
			if ((img2.at<Vec3b>(i, j)[0]<120 + 5) && (img2.at<Vec3b>(i, j)[0]>120 - 5)) img3.at<uchar>(i, j) = 255;
		}
	}
	//imshow("pop5", img3);
	Mat img = blob(img3);
	Point hit, rect;
	hit.x = 0;
	hit.y = 0;
	for (int i = umargin; i < (dmargin + umargin) / 2; i++)
	{
		for (int j = lmargin; j < rmargin; j++)
		{
			int n = 0;
			if (img.at<char>(i, j) != -1)
			{
				val = img.at<char>(i, j);
				for (int k = umargin; k < (dmargin + umargin) / 2; k++)
				{
					for (int l = lmargin; l < rmargin; l++)
					{
						if (img.at<char>(k, l) == val)
							n++;
					}
				}
			}
			rect.x = 0;
			rect.y = 0;
			if (n>1500)
			{
				for (int k = umargin; k < (dmargin + umargin) / 2; k++)
				{
					for (int l = lmargin; l < rmargin; l++)
					{
						if (img.at<char>(k, l) == val)
						{
							rect.x += l;
							rect.y += k;
						}
					}
				}
				rect.x /= n;
				rect.y /= n;
			}
			if (s<0)
			{
				if (rect.y > hit.y - 10)
				{
					if (rect.x > hit.x)
						hit = rect;
				}
			}
			if (s>0)
			{
				if (rect.y > hit.y - 10)
				{
					if (rect.x < hit.x)
						hit = rect;
				}
			}
		}
	}
	return hit;
}
int paddlept(float slope, Point br)
{
	float theta = atan(slope);
	int i, c;
	float beta;
	Point hit[3];
	float delta[3];
	float alpha[3] = { 0.78, 1.047, 1.57 };
	float min = 0.0;
	int posi;
	for (i = 0; i < 3; i++)
	{
		if (slope < 0)
			alpha[i] = (-1)*alpha[i];
	}
	for (i = 0; i < 3; i++)
	{
		hit[i].y = lcols + R - R*fabs(sin(alpha[i]));
		hit[i].x = (hit[i].y - pos.y) / slope + pos.x;
		beta = atan((br.y - hit[i].y) / (br.x - hit[i].x));
		delta[i] = 2 * alpha[i] - atan(slope) - beta;
		delta[i] = fabs(delta[i]);
	}
	min = delta[0];
	posi = 0;
	for (i = 1; i < 3; i++)
	{
		if (min > delta[i])
		{
			min = delta[i];
			posi = i;
		}
	}
	if (slope > 0)
		c = hit[posi].x + R*cos(alpha[posi]);
	else
		c = hit[posi].x - R*cos(alpha[posi]);
	if (c > 730) c = 730;
	if (c < 70) c = 70;
	return c;
}
//int main()
//{
//	Mat img;
//	while (1)
//	{
//		float s;
//		v >> img;
//		Point bcentre = centreball(img);
//		Point b1;
//		Point br;
//		int final;
//
//		v >> img;
//		b1 = centreball(img);
//		//cout << "b1(" << b1.x << "," << b1.y << endl;
//
//		//cout << "bcenter(" << bcentre.x << "," << bcentre.y<<endl;
//
//		if ((bcentre.y > 180) && (b1.y > bcentre.y) && (bcentre.y < 260))
//		{
//			//cout << "bcenter(" << bcentre.x << "," << bcentre.y << endl;
//			//cout << "b1(" << b1.x << "," << b1.y << endl;
//
//			s = slope();
//			cout << s;
//			s = ncollisions(s);
//			cout << s << endl;
//			cout << "(" << pos.x << "," << pos.y << ")";
//			br = brick(s);
//			final = paddlept(s, br);
//			cout << "final" << final;
//			break;
//		}
//	}
//		 waitKey(0);
//		 getchar();
//}
int main()
{
	Mat img;
	while (1)
	{
		float s;
		v >> img;
		Point bcentre = centreball(img);
		Point b1;
		Point br;
		int final;

		v >> img;
		b1 = centreball(img);
	//	cout << "b1(" << b1.x << "," << b1.y << endl;

	//	cout << "bcenter(" << bcentre.x << "," << bcentre.y<<endl;
	//	cout << b1.x << " " << b1.y;
			if ((bcentre.y > 170) && (b1.y > bcentre.y) && (bcentre.y < 260))
			{
				cout << "bcenter(" << bcentre.x << "," << bcentre.y << endl;
				cout << "b1(" << b1.x << "," << b1.y << endl;

		s = slope();
		cout << s;
		s = ncollisions(s);
		cout << s << endl;
		cout << "(" << pos.x << "," << pos.y << ")";
		br = brick(s);
		final = paddlept(s, br);
		cout << "final" << final;
		break;
	  }
	}
	getchar();
}
//	int final = 100;
//	Mat frame;
//	frame=imread("v1.png", CV_LOAD_IMAGE_COLOR);
//	/*namedWindow("abc", CV_WINDOW_AUTOSIZE);
//	imshow("abc", frame);*/
//	int x;
//	while (1)
//	{
//		v1 >> frame;
//		x = cam(frame);
//		cout << x;
//		if ((x > final - thresh) && (x < final + thresh))
//		{
//			cout << "stop";
//			break;
//		}
//		else if(x <= final - thresh)
//			cout << "right";
//		else cout << "left";
//	}
//	/*Mat image;
//	int a = cam(image);
//	int s,c,k;
//	char str[100];
//	if (final > x)
//	{
//		c = (final - x)*s;
//		for (k = 0; k < c; k++)
//			str[k] = 'w';
//		str[k] = '\0';
//	}
//	if (final < x)
//	{
//		c = -(final - x)*s;
//		for (k = 0; k < c; k++)
//			str[k] = 's';
//		str[k] = '\0';
//	}
//	cout << str;*/
//
//	waitKey(0);
//	//getchar();
//	return 0;
//}
	 //serial comm; //serial is a class type defined in these files, used for referring to the communication device
	 //int final;
	 //void main() {
		// char data; //To store the character to send
		// comm.startDevice("\\\\.\\COM13", 9600);
		// /* “COM 2” refers to the com port in which the USB to SERIAL port is attached. It is shown by right clicking on my computer, then going to properties and then device manager
		// 9600 is the baud-rate in bits per second */
		// Mat img;
		// 
		// while (1)
		// {
		//	 float s;
		//	 v >> img;
		//	 Point bcentre = centreball(img);
		//	 Point b1;
		//	 Point br;

		//	 v >> img;
		//	 b1 = centreball(img);
		//	 //cout << "b1(" << b1.x << "," << b1.y << endl;

		//	 //cout << "bcenter(" << bcentre.x << "," << bcentre.y<<endl;

		//	 if ((bcentre.y > 150) && (b1.y > bcentre.y) && (bcentre.y < 250))
		//	 {
		//		 //cout << "bcenter(" << bcentre.x << "," << bcentre.y << endl;
		//		 //cout << "b1(" << b1.x << "," << b1.y << endl;

		//		 s = slope();
		//		 cout << s;
		//		 s = ncollisions(s);
		//		 cout << s << endl;
		//		 cout << "(" << pos.x << "," << pos.y << ")";
		//		 br = brick(s);
		//		 final = paddlept(s, br);
		//		 cout << "final" << final;
		//		 break;
		//	 }
		//	 Mat frame;
		//	 //frame = imread("v1.png", CV_LOAD_IMAGE_COLOR);
		//	 // namedWindow("abc", CV_WINDOW_AUTOSIZE);
		//	 //imshow("abc", frame);
		//	 int x;
		//	 while (1)
		//	 {
		//		 v1 >> frame;
		//		 x = cam(frame);
		//		 x = (x*img.cols) / frame.cols;
		//		 cout << "pos"<<x << endl;
		//		 if ((x > (final - thresh)) && (x < (final + thresh)))
		//		 {
		//			 cout << "stop";
		//			 comm.stopDevice();
		//			 break;
		//		 }
		//		 else if (x <= (final - thresh))
		//		 {
		//			 cout << "right";
		//			 comm.send_data('w');
		//		 }

		//		 else {
		//			 cout << "left";
		//			 comm.send_data('s');
		//		 }
		//	 }

		// }
	 //}