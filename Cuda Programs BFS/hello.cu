#include <stdio.h>
#include <cuda.h>

void CPUFunction()
{
  printf("Runs on the CPU.\n");
}

__global__
void GPUFunction()
{
  printf("Runs on the GPU.\n");
}

int main()
{
  CPUFunction();

  GPUFunction<<<1, 1>>>();

  cudaDeviceSynchronize();

  return EXIT_SUCCESS;
}