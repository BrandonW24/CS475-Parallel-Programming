#!/bin/bash
#SBATCH -J project05
#SBATCH -A cs475-575
#SBATCH -p class
#SBATCH --gres=gpu:1
#SBATCH -o project05out.out
#SBATCH -e project05.err
#SBATCH --mail-type=BEGIN,END,FAIL
#SBATCH --mail-user=withingb@oregonstate.edu
#./project05
for b in 16 32 64 128
do
printf "Changing BLOCK SIZE to : \n"
echo BLOCKSIZE=$b
for t in 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2097152 4194304 8388606 16777216
do
	/usr/local/apps/cuda/cuda-10.1/bin/nvcc -DBLOCKSIZE=$b -DNUMTRIALS=$t -o project05 kernel.cu
	./project05
done

done
