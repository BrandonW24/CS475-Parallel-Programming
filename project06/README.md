# OpenCL Array Multiply, Multiply-Add, and Multiply-Reduce

## Introduction
There are many problems in scientific computing where you want to do arithmetic on multiple arrays of numbers (matrix manipulation, Fourier transformation, convolution, etc.). This project is in three parts:

Multiply two arrays together using OpenCL:
```
D[gid] = A[gid] * B[gid];
```

Benchmark it against both input array size (i.e., the global work size) and the local work size (i.e., number of work-items per work-group).

Multiply two arrays together and add a third using OpenCL:
```
D[gid] = ( A[gid] * B[gid] ) + C[gid];
```
Benchmark it against both input array size (i.e., the global work size) and the local work size (i.e., number of work-items per work-group).
Perform the same array multiply as in #1, but this time with a reduction:
```
Sum = summation{ A[:]*B[:] };
```
Benchmark that against input array size (i.e., the global work size). You can pick a local work size and hold that constant.
