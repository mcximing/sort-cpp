
### Introduction

This is a C++ implementation of SORT, a simple online and realtime tracking algorithm for 2D multiple object tracking in video sequences.
Original Python code and publication infomation found at https://github.com/abewley/sort , By Alex Bewley

This code has been tested on Windows with Visual Studio Community 2013 + OpenCV 2.4.8. It depends on OpenCV without any other libs, so theoretically it can be compiled on Linux with OpenCV support.

Detection data in The ./data folder come from the original directory of SORT. They are the *Faster* RCNN detections for the MOT benchmark sequences in the benchmark format, created by Alex Bewley.

The Hungarian algorithm implementation comes from https://github.com/mcximing/hungarian-algorithm-cpp, which is derived from [Markus Buehren's code](http://www.mathworks.com/matlabcentral/fileexchange/6543-functions-for-the-rectangular-assignment-problem).

The license is also kept to the GPLv3 License.

### Results

The overall results of code are close to those of original SORT implmentation.

Using the [MOT challenge devkit](https://motchallenge.net/devkit/) this code produces the following results.

 Sequence       | Rcll  Prcn   FAR| GT  MT  PT  ML|   FP    FN  IDs   FM|  MOTA  MOTP MOTAL
--------------- |:---------------:|:-------------:|:-------------------:|:------------------:
 TUD-Campus     | 67.4  91.0  0.34|  8   5   3   0|   24   117    8   12|  58.5  74.8  60.5
 ETH-Sunnyday   | 77.8  81.7  0.92| 30  12  15   3|  324   412   22   57|  59.2  74.6  60.3
 ETH-Pedcross2  | 51.5  89.8  0.44|133  16  61  56|  366  3037   83  118|  44.3  74.6  45.6
 ADL-Rundle-8   | 44.3  75.3  1.50| 28   6  15   7|  984  3779  109  214|  28.2  70.9  29.8
 Venice-2       | 42.6  64.7  2.77| 26   8  11   7| 1661  4098   63  112|  18.5  72.8  19.3
 KITTI-17       | 67.9  92.6  0.26|  9   1   8   0|   37   219   13   16|  60.6  72.6  62.4
 **Overall**    | 49.5  77.1  1.28|234  48 113  73| 3396 11662  298  529|  33.5  73.1  34.8

A bit worse than original SORT but not significantly. This may due to my keeping the default parameters of Kalman filters.
The speed of this implementation is at about 1800 FPS, or ~3 seconds over 5500 frames on my machine, with the Debug configuration. 

