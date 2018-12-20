#include<direct.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include "parser.h"
#include "cuda.h"
#include "utils.h"
#include "blas.h"
#include "detector.h"
#include "connected_layer.h"

#ifdef OPENCV
#include "opencv2/highgui/highgui_c.h"
	//#include "opencv2/opencv.hpp"
#endif

//extern  void removeDirFile(const char* dirPath);
//extern  void deleteDirAndFile(const char* dirPath);
//extern  void add_zero(int n_, char *Out);
//extern  void cutImg(const char * ori_filename, const char * save_split_path);
//extern  void cutAndSaveBigImage(const char* dirPath, const char * ori_filename);

typedef struct {
	int left;
	int right;
	int top;
	int bot;
}rect;

void bigImgDetect(const char* datacfg, const char* cfg, const char* weights, const char* filename, 
	const char* ori_filename, const char* rect_txt, const float thresh){

	FILE *fin;
	run_detector(datacfg, cfg, weights, filename, thresh, rect_txt);

	image im_ori = load_image(ori_filename, 0, 0, 3);
	int width = im_ori.h * .003; //线宽
	//int width = 1;
	if (width < 1)
		width = 1;
	fin = fopen(rect_txt, "r");
	char *p;
	float nms = .15;
	int rows = 0;

	rect rect1[1000];
	while (!feof(fin))
	{
		char buf[100];
		fgets(buf, 100, fin); //读取文件中的一行到buf中
		rows++;
		//printf("%d\n", rows);
		if (rows % 4 == 1) rect1[(rows - 1) / 4].left = atoi(buf);
		if (rows % 4 == 2) rect1[(rows - 1) / 4].right = atoi(buf);
		if (rows % 4 == 3) rect1[(rows - 1) / 4].top = atoi(buf);
		if (rows % 4 == 0) rect1[(rows - 1) / 4].bot = atoi(buf);
	}
	for (int i = 0; i < rows / 4; i++){

		draw_box_width(im_ori, rect1[i].left, rect1[i].top, rect1[i].right, rect1[i].bot, width, 255, 0, 0);
	}
	fclose(fin);
	cvNamedWindow("ori_im", 0);
	show_image(im_ori, "ori_im");
	save_image(im_ori, "LargeImagePre");
	free_image(im_ori);
	
	cvWaitKey(0);
	cvDestroyAllWindows();
}

int main(int argc, char **argv)
{
	//Cut the large image
	char dirPath[] = "x64\\data\\testSplit\\";
	char imgSrcFilename[] = "x64\\data\\panorama.jpg";
	cutAndSaveLargeImage(dirPath, imgSrcFilename);
	
	//Detection
	char datacfg[] = "x64\\data\\voc.data";
	char cfg[] = "x64\\yolo-obj.cfg";
	char weights[] = "x64\\yolo-obj_2200.weights";
	char ori_filename[] = "x64\\data\\panorama.jpg";
	char filename[] = "x64\\data\\testSplit";
	char rect_txt[] = "detectRect.txt";
	float thresh = 0.1;

	bigImgDetect(datacfg, cfg, weights, filename, ori_filename, rect_txt, thresh);

    return 0;
}

