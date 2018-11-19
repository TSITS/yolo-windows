#include "cutAndSave.h"
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include<direct.h>
#include <io.h>

#define _CRT_SECURE_NO_WARNINGS

void removeDirFile(const char* dirPath){
	
	long Handle;
	struct _finddata_t FileInfo;
	char dirPathTemp[100];
	

	strcpy(dirPathTemp, dirPath);
	int size = strlen(dirPathTemp);
	if (dirPathTemp[size - 1] != '\\')
		strcat(dirPathTemp, "\\*.*");
	else
		strcat(dirPathTemp, "*.*");

	if ((Handle = _findfirst(dirPathTemp, &FileInfo)) == -1L)
		std::cout << "The Dir is empty" << std::endl;
	else
	{
		char removeFileNameFir[100] = {};
		strcpy(removeFileNameFir, dirPath);
		int size = strlen(removeFileNameFir);
		if (removeFileNameFir[size - 1] != '\\')
		{
			strcat(removeFileNameFir, "\\");
			strcat(removeFileNameFir, FileInfo.name);
		}
		else
			strcat(removeFileNameFir, FileInfo.name);
		remove(removeFileNameFir);
		while (_findnext(Handle, &FileInfo) == 0)
		{
			char removeFileNameNex[100] = {};
			strcpy(removeFileNameNex, dirPath);
			int size = strlen(removeFileNameNex);
			if (removeFileNameNex[size - 1] != '\\')
			{
				strcat(removeFileNameNex, "\\");
				strcat(removeFileNameNex, FileInfo.name);
			}
			else
				strcat(removeFileNameNex, FileInfo.name);
			remove(removeFileNameNex);
		}
			
		_findclose(Handle);
	}
}

void deleteDirAndFile(const char* dirPath){
	int hasDirFlag = -1;
	int creatDirFlag = -1;

	char dirPathTemp[100];

	strcpy(dirPathTemp, dirPath);
	int size = strlen(dirPathTemp);
	if (dirPathTemp[size - 1] != '\\')
		strcat(dirPathTemp, "\\*.*");
	else
		strcat(dirPathTemp, "*.*");

	hasDirFlag = _access(dirPath, 0);
	if (hasDirFlag == -1){
		creatDirFlag = _mkdir(dirPath);
		if (creatDirFlag == -1)
			printf("%s", "Creat failed");
	}
	else
		removeDirFile(dirPath);
		
}

void add_zero(int n_, char *Out)
{
	char n[200];
	char NUM[100];

	strcpy(NUM, "0");
	_itoa(n_, n, 10);

	int size_ = strlen(n);
	for (int i = 0; i < 4 - size_; i++){
		strcat(Out, NUM);
	}
	strcat(Out, n);
}

void cutImg(const char * ori_filename, const char * save_split_path){

	cv::Mat imgTemp;
	cv::Mat im_ori = cv::imread(ori_filename);
	if (!im_ori.data)
	{
		std::cout << "Load the image error!" << std::endl;
	}
	//cv::imshow("test", im_ori);
	//cv::waitKey(0);
	int cutWid = CUTWID;
	int cutHei = CUTHEI;
	int cutStep = CUTSTEP;
	int cutBeginX = 0;
	int cutBeginY = 0;

	if (im_ori.cols > cutWid && im_ori.rows > cutHei){

		for (int i = 0; i*cutStep < im_ori.rows; i++){
			cutBeginY = cutStep*i;

			if ((cutBeginY + CUTHEI)>im_ori.rows){
				cutHei = im_ori.rows - cutBeginY;
			}
			else cutHei = CUTHEI;

			for (int j = 0; j*cutStep < im_ori.cols; j++){
				cutBeginX = cutStep*j;
				if ((cutBeginX + CUTWID) > im_ori.cols){
					cutWid = im_ori.cols - cutBeginX;
				}
				else cutWid = CUTWID;

				cv::Rect rect(cutBeginX, cutBeginY, cutWid, cutHei);
				imgTemp = im_ori(rect);

				char imgTempName[200];
				strcpy(imgTempName, save_split_path);
				char Outi[4] = {};
				add_zero(i, Outi);
				strcat(imgTempName, Outi);
				strcat(imgTempName, "_");
				char Outj[4] = {};
				add_zero(j, Outj);
				strcat(imgTempName, Outj);
				strcat(imgTempName, ".jpg");

				if (imgTemp.cols>10 && imgTemp.rows>10)
					cv::imwrite(imgTempName, imgTemp);
			}
		}
	}
}

void cutAndSaveLargeImage(const char* dirPath, const char * ori_filename){
	deleteDirAndFile(dirPath);
	cutImg(ori_filename, dirPath);
	std::cout << "Cut the large image sucess!" << std::endl;
	std::cout << "  " << std::endl;
}