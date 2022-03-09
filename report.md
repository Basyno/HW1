# EE6470 HW1 Guassian Blur

### 110061546 邱博昇
## How Execution
```
$ cmake .. 
$ make
$ make run // execution, output file will be Gaussian.bmp
```
## Github Link
```
https://github.com/Basyno/HW1.git
```
## Introduction
In homework1, I implemented the Gaussian blur through C++ and systemC.

Guassian blur is an image processing technique, which blurring an image by a Guassian function ,we can reduce image noise and details by this method.
## Implementation
* Part I

  The source code is mainly from the introduction website and lab2 sobel_fifo example.

  In the introduction website , we can get the Guassian blur formula , but also we can get the parameters with 3*3 kernal Gaussian filter, I change the original sobel mask by new parameters, and the testbench will read each pixel's RGB value from the picture and transfer them to grayscale. Finally, we determined the pixel whether it is black or white by setting threshold. So, the result should be black and white.
* Gaussian blur
```
   Approximation to 3x3 kernel:
   double filter[filterHeight][filterWidth] =
{
  1, 2, 1,
  2, 4, 2,
  1, 2, 1,
};

double factor = 1.0 / 16.0;
double bias = 0.0;
```
* Part II
  
  In this part, we need to create a row buffer to store the pixel read from testbench row by row.

  I create my row buffer in tread and its size is 3*256 . In the beginnig , because every pixel needs to do convoution , we need  at least two row pixels to complete our calculation. after the first row has been finished, the new row pixel will shift to third row . when the row buffer is fulled , the second row pixel will shift to fisrt row and replace the old pixel data , and third row pixel will shift to second row ,and so on . We will get the result .bmp file when every computation of row pixel has been finished. 
## Results
### Before
![Image](https://raw.githubusercontent.com/Basyno/HW1/main/part1/lena_std_short.bmp)
### After
![Image](https://raw.githubusercontent.com/Basyno/HW1/main/part1/build/Gaussian.bmp)
## Discussion and Conclution
In this homework, I think the most difficult part is to recognize how the row buffer operate and we need to know how systemC work and get familiar with the systemC language.

I think the advatage of row buffer is we dont need to read the repeat pixel in order to caculate the convolution value, and it can avoid loading too much useless data in our memory. 
