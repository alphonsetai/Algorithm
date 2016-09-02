//
//  bucket_sort.hpp
//  Algorithm
//
//  Created by dtysky on 16/8/31.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#include <iostream>
#include "bucket_sort.h"
#include "utils.hpp"


namespace algorithm {
    using std::cout;
    using std::endl;
    using std::vector;
    
    void testBucketSort(){
        auto v1 = vector<int>({10, 9, 8, 0});
        bucketSort(v1, 10);
        printVector<int>(v1);
        bucketSort(v1, 10, true);
        printVector<int>(v1);
    }
}