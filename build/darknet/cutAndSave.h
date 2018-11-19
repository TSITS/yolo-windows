#ifndef CUTANDSAVE_H_
#define CUTANDSAVE_H_

#define CUTWID 512
#define CUTHEI 512
#define CUTSTEP 512

extern "C" void removeDirFile(const char* dirPath);
extern "C" void deleteDirAndFile(const char* dirPath);
extern "C" void add_zero(int n_, char *Out);
extern "C" void cutImg(const char * ori_filename, const char * save_split_path);
extern "C" void cutAndSaveLargeImage(const char* dirPath, const char * ori_filename);

#endif 