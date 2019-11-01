#include"file_tool.h"
#include <iostream>
#include <cv.hpp>
using namespace cv;
using namespace utils_file;
using namespace std;
int get_distance(int x,int y,Mat img);
int main()
{
	string dir="/media/yang/软件与文件/transfer_detetion/green_label/";
	list<pair<string, string>>files;
	ListDir(dir,files);
    list<pair<string, string>>::iterator file;
    for(file=files.begin();file!=files.end();file++) {
       string pic_dir=file.operator->()->second;
       string file_name=file.operator->()->first;
       vector<Mat>s_img;
       Mat img=imread(pic_dir,IMREAD_UNCHANGED);
       split(img,s_img);
       namedWindow("label",0);
       Mat write_img(img.rows,img.cols,CV_8UC4,Scalar(0,0,0,0));
       for (int i=0;i<img.rows;i++)
       {
           for (int j=0;j<img.cols;j++)
           {    int b=255,g=255,r=255;

                int alpha_value=s_img[3].at<uchar>(i,j);
                if (alpha_value>1)
                {
                  int min_d =get_distance(i,j,s_img[3]);
//                  if (min_d<30){
                      int bin=rand()%45+180;
                      int br=bin-(rand()%20+10);
                      float s_mind=float(min_d-20)/15;
                      int ran=rand()%15+5;
                      float y=1 / (1 + exp((0 - s_mind)) * 1);
                      float yb=1/(1+exp((0-s_mind)*1));
                      g=int(bin*y+30);
                      b=int(br*yb+20);
                      r=b-ran;
//                  }
//                  else{
//                      int bin=225;
//                      int br=190;
//                      float s_mind=float(min_d-20)/5;
//                      int ran=rand()%15+5;
//                      float y=1 / (1 + exp((0 - s_mind)) * 1.2);
//                      float yb=1/(1+exp((0-s_mind)*1));
//                      g=int(bin*y+30);
//                      b=int(br*yb+20);
//                      r=b-ran;
//
//                  }


                }
               write_img.at<Vec4b>(i,j)=Vec4b(b,g,r,s_img[3].at<uchar>(i,j));
           }
       }
       imwrite("../label/"+file_name,write_img);
//       imshow("label",write_img);
//       imshow("wim",img);
//       waitKey(0);



    }

}

/* 计算距离背景最近点的距离*/
int get_distance(int x,int y,Mat img){
    int t=30;
    int min_d=t*t;
    int x1=max(0,x-t);
    int x2=min(img.rows-t,x+t);
    int y1=max(0,y-t);
    int y2=min(img.cols-t,y+t);
    for (int i=x1;i<x2;i++){
        for (int j=y1;j<y2;j++)
        {
            if (img.at<uchar>(i,j)==0) {
                int d = (i - x) * (i - x) + (j - y) * (j - y);
                if (d <= min_d) { min_d = d; }
            }

        }
    }
    return min_d;

}

//#include <unistd.h>
//#include "find_file.h"
//
//int main(void)
//{
//    DIR *dir;
//    char basePath[100]="/media/yang/软件与文件/transfer_detetion/pic_pross/label";
//
//    ///get the current absoulte path


//    cout<<endl<<endl;
//    vector<string> files=getFiles(basePath);
//    for (int i=0; i<files.size(); i++)
//    {
//        cout<<files[i]<<endl;
//    }
//
//
//    cout<<"end..."<<endl<<endl;
//    return 0;
//}
