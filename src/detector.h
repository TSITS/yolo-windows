#ifndef DETECTOR_H
#define DETECTOR_H


#include "network.h"
#include "region_layer.h"
#include "cost_layer.h"
#include "utils.h"
#include "parser.h"
#include "box.h"
#include "demo.h"
#include "option_list.h"
#include <io.h>
#include <stdlib.h>


#ifdef OPENCV
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/core/core_c.h"
//#include "opencv2/core/core.hpp"
#include "opencv2/core/version.hpp"
#include "opencv2/imgproc/imgproc_c.h"
//#include "opencv2/opencv.hpp"

#ifndef CV_VERSION_EPOCH
#include "opencv2/videoio/videoio_c.h"
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_MAJOR)"" CVAUX_STR(CV_VERSION_MINOR)"" CVAUX_STR(CV_VERSION_REVISION)
#pragma comment(lib, "opencv_world" OPENCV_VERSION ".lib")
#else
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_EPOCH)"" CVAUX_STR(CV_VERSION_MAJOR)"" CVAUX_STR(CV_VERSION_MINOR)
#pragma comment(lib, "opencv_core" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_imgproc" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_highgui" OPENCV_VERSION ".lib")
#endif
#define IMGNUM 20000 //测试图片所在文件夹中图片的最大数量

IplImage* draw_train_chart(float max_img_loss, int max_batches, int number_of_lines, int img_size);
void draw_train_loss(IplImage* img, int img_size, float avg_loss, float max_img_loss, int current_batch, int max_batches);
#endif    // OPENCV


int getFiles(char *path);
void train_detector(char *datacfg, char *cfgfile, char *weightfile, int *gpus, int ngpus, int clear, int dont_show);
static int get_coco_image_id(char *filename);
static void print_cocos(FILE *fp, char *image_path, detection *dets, int num_boxes, int classes, int w, int h);
void print_detector_detections(FILE **fps, char *id, detection *dets, int total, int classes, int w, int h);
void print_imagenet_detections(FILE *fp, int id, detection *dets, int total, int classes, int w, int h);
void validate_detector(char *datacfg, char *cfgfile, char *weightfile, char *outfile);
void validate_detector_recall(char *datacfg, char *cfgfile, char *weightfile);

int detections_comparator(const void *pa, const void *pb);
void validate_detector_map(char *datacfg, char *cfgfile, char *weightfile, float thresh_calc_avg_iou);


int anchors_comparator(const void *pa, const void *pb);
void calc_anchors(char *datacfg, int num_of_clusters, int width, int height, int show);
void test_detector(char *datacfg, char *cfgfile, char *weightfile, char *filename, float thresh,
	float hier_thresh, int dont_show, int ext_output, int save_labels, char *rect_txt);
void run_detector(char * datacfg, char *cfg, char *weights, char *filename, float thresh, char *rect_txt);


#endif
