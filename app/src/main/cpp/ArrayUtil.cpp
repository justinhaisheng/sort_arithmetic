//
// Created by haisheng on 2020/2/13.
//

#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <string>
#include "AndroidLog.h"

using namespace std;

namespace ArrayUtil{


    int create_random_array_(int* sourceArr,int len,int start,int high){
        assert(sourceArr && len  >0);
        for (int i = 0; i < len; ++i) {
            sourceArr[i] = rand() %(high - start) + start;
        }
        return 1;
    }

    int copy_random_array_(int* sourceArr,int* targetArr,int len ){
        assert(sourceArr && targetArr && len >0);
        memcpy(targetArr,sourceArr, sizeof(int)*len);
        return 1;
    }

    double sort_array_time_(char* sortName,void(*sort)(int*,int),int* array,int len){
       size_t  start_time = clock();
       sort(array,len);
       size_t  end_time = clock();
       double  time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
       LOGE("%s的执行时间：%lf", sortName, time);

        for (int i = 0; i < len - 1; ++i) {
            assert(array[i] <= array[i+1]);
        }
        return time;
    }

    int swap_(int &tempA,int &tempB){
        tempA= tempA + tempB;
        tempB = tempA - tempB;
        tempA = tempA - tempB;
        return 1;
    }

    void print_array_(int arr[], int len) {
        string temp_string("");
        for (int i = 0; i < len; ++i) {
            // 这个方法比较复杂
           // LOGI("%d", arr[i]);
            char temp[5];
            if(i == len -1){
                sprintf(temp,"%d",arr[i]);
            }else{
                sprintf(temp,"%d-",arr[i]);
            }
            temp_string.append(temp);
        }
         LOGD("数组： %s",temp_string.c_str());
    }
}
