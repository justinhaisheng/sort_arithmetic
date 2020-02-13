#include <jni.h>
#include <string>
#include <iostream>
#include "AndroidLog.h"
#include <assert.h>
#include "ArrayUtil.cpp"
using namespace std;


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



extern "C" JNIEXPORT jstring JNICALL
Java_com_aispeech_sort_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    int len = 10000;
    int* arr1 = new int[len];
    int* arr2 = new int[len];

    ArrayUtil::create_random_array_(arr1,len,20,1000);
    ArrayUtil::copy_random_array_(arr1,arr2,len);
   // LOGE("原始数组");
   // ArrayUtil::print_array_(arr1,len);
    LOGE("bubbleSort");
    ArrayUtil::sort_array_time_("bubbleSort",bubbleSort,arr1,len);
   // ArrayUtil::print_array_(arr1,len);
    LOGE("bubbleSortOptimize");
    ArrayUtil::sort_array_time_("bubbleSortOptimize",bubbleSortOptimize,arr2,len);
   // ArrayUtil::print_array_(arr2,len);



    //bubbleSortOptimize(arr, );
    //print_array(arr,7);
    delete(arr1);
    delete(arr2);
    return env->NewStringUTF(hello.c_str());
}
