#include <jni.h>
#include <string>
#include <iostream>
#include "AndroidLog.h"
#include <assert.h>
#include "ArrayUtil.cpp"
using namespace std;

//冒泡排序
void bubbleSort(int arr[], int len) {
    assert(arr&& len >1);
    for (int i = 0; i < len -1 ; ++i) { //  n-1 步
        // j < len - i - 1
        for (int j = 0; j < len - i - 1; ++j) { // n-1, n-2 ,n - 3, 1
            if (arr[j] > arr[j + 1]) {
                // 交换 一次交换是三次赋值
                ArrayUtil::swap_(arr[j], arr[j + 1]);
            }
        }
       // LOGD("执行第%d趟，数据为",i);
      //  ArrayUtil::print_array_(arr,len);
    }
}

//优化后的冒泡排序算法
void bubbleSortOptimize(int arr[], int len){
    assert(arr && len >1);

    int pos = 0;
    int k = len - 1;
    for (int i = 0; i < len -1 ; ++i) { //  n-1 步
        //LOGD("交换次数%d:",k);
        bool flag = false;
        for (int j = 0; j < k; ++j) { // k次交换
            if (arr[j] > arr[j + 1]) {
              //  LOGE("执行交换");
                // 交换 一次交换是三次赋值
                ArrayUtil::swap_(arr[j], arr[j + 1]);
                flag = true;//发生了交换
                pos = j;//记录此时的交换位置
            }
        }
        //LOGD("执行第%d趟，数据为:",i);
        //ArrayUtil::print_array_(arr,len);
        if (!flag){
         //   LOGI("执行第%d趟后，数据不再进行交换则退出",i);
            break;
        }
        k = pos;
    }
}

// 选择：思想 遍历找出最小的位置，最后与第一个位置进行交换 O(1)
//最小值排序

void selectSort(int arr[], int len) {
    for (int i = 0; i < len - 1; ++i) {
        int min_pos = i;//假设每一趟的第一个为最小值
        for (int j = i+1; j < len; ++j) {
             if (arr[min_pos] > arr[j]){
                 min_pos = j;//记录改变后的位置
             }
        }
        if (min_pos!=i){//如果位置发生了改变则交换
            ArrayUtil::swap_(arr[i], arr[min_pos]);
        }
    }
}

//插入排序 ，倒叙排序
void simpleInsertSort(int arr[], int len){
    for (int i = 1; i < len; ++i) {//从第一个数开始
        for (int j = i; j >0; j--) {//从后往前比较
            if (arr[j] < arr [j-1]){
                ArrayUtil::swap_(arr[j], arr[j-1]);
            }else{
                break;//则跳出循环9
            }
        }
    }
}

void insertSort(int arr[], int len){
    int j;
    for (int i = 1; i < len; ++i) {
        int temp = arr[i];//保存i 这个值
        for (j = i; j > 0  ; j--) {
            if (arr[j - 1] > temp){
                arr[j] = arr[j-1];
            }else{
                break;
            }
        }
        arr[j] = temp;
    }
}
//希尔排序（分治的插入排序）
void chille_insert_sort(int* arr,int len){
    int step = len /2;
    while (step > 0){
        for (int i = 0; i < step; ++i) {
            for (int j = i+step; j < len ; j+=step) {
                 int k;
                 int temp = arr[j];
                 for (k = j; k>i; k-=step) {
                      if (arr[k-1] > arr[k]){
                          arr[k] = arr[k-1];
                      }else{
                          break;
                      }
                 }
                 arr[k] = temp;
            }
        }
        step/=2;
    }
}




extern "C" JNIEXPORT jstring JNICALL
Java_com_aispeech_sort_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    int len = 10;
    int* arr1 = new int[len];
    int* arr2 = new int[len];
    int* arr3 = new int[len];
    int* arr4 = new int[len];
    int* arr5 = new int[len];
    ArrayUtil::create_random_array_(arr1,len,1,20);
    ArrayUtil::copy_random_array_(arr1,arr2,len);
    ArrayUtil::copy_random_array_(arr1,arr3,len);
    ArrayUtil::copy_random_array_(arr1,arr4,len);
    ArrayUtil::copy_random_array_(arr1,arr5,len);

    LOGE("insertSort");
    ArrayUtil::sort_array_time_("insertSort",insertSort,arr5,len);

    LOGE("simpleInsertSort");
    ArrayUtil::sort_array_time_("simpleInsertSort",simpleInsertSort,arr4,len);

   // LOGE("原始数组");
   // ArrayUtil::print_array_(arr1,len);
    LOGE("bubbleSort");
    ArrayUtil::sort_array_time_("bubbleSort",bubbleSort,arr1,len);
   // ArrayUtil::print_array_(arr1,len);
    //LOGE("bubbleSortOptimize");
   // ArrayUtil::sort_array_time_("bubbleSortOptimize",bubbleSortOptimize,arr2,len);
   // ArrayUtil::print_array_(arr2,len);
    //LOGE("selectSort");
   // ArrayUtil::sort_array_time_("selectSort",selectSort,arr3,len);





    //bubbleSortOptimize(arr, );
    //print_array(arr,7);
    delete (arr1);
    delete (arr2);
    delete (arr3);
    delete (arr4);
    delete (arr5);
    return env->NewStringUTF(hello.c_str());
}
