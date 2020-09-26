#!/bin/bash
#SBATCH -J project06
#SBATCH -A cs475-575
#SBATCH -p class
#SBATCH --gres=gpu:1
#SBATCH -o project06MUarrAdd.out
#SBATCH -e project06MUarrAdderr.err
#SBATCH --mail-type=BEGIN,END,FAIL
#SBATCH --mail-user=withingb@oregonstate.edu
#./project06MUAA

for numB in  1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192
do
for localwg in 8 16 32 64 128 256 512 
do
	printf "MultiArray no addition results : \n "
	printf " _________________________________ \n"
	g++ -DNMB=$numB -DLOCAL_SIZE=$localwg -o multiArrAdd multiArrayAdd.cpp /usr/local/apps/cuda/cuda-10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp
	./multiArrAdd

done
done
#done
