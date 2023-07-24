template <typename T>  __device__  void devicegpuUbou1(T *f, T *xdg, T *udg, T *odg, T *wdg, T *uhg, T *nlg, T *tau, T *uinf, T *param, T time, int modelnumber, int ng, int nc, int ncu, int nd, int ncx, int nco, int ncw)
{
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	while (i<ng) {
		T param2 = param[1];
		f[0*ng+i] = param2;
		i += blockDim.x * gridDim.x;
	}
}

template <typename T>  __global__  void kernelgpuUbou1(T *f, T *xdg, T *udg, T *odg, T *wdg, T *uhg, T *nlg, T *tau, T *uinf, T *param, T time, int modelnumber, int ng, int nc, int ncu, int nd, int ncx, int nco, int ncw)
{
	devicegpuUbou1(f, xdg, udg, odg, wdg, uhg, nlg, tau, uinf, param, time, modelnumber, ng, nc, ncu, nd, ncx, nco, ncw);
}

template <typename T> void gpuUbou(T *f, T *xdg, T *udg, T *odg, T *wdg, T *uhg, T *nlg, T *tau, T *uinf, T *param, T time, int modelnumber, int ib, int ng, int nc, int ncu, int nd, int ncx, int nco, int ncw)
{
	int blockDim = 256;
	int gridDim = (ng + blockDim - 1) / blockDim;
	gridDim = (gridDim>1024)? 1024 : gridDim;
	if (ib == 1)
		kernelgpuUbou1<<<gridDim, blockDim>>>(f, xdg, udg, odg, wdg, uhg, nlg, tau, uinf, param, time, modelnumber, ng, nc, ncu, nd, ncx, nco, ncw);
}

template void gpuUbou(double *, double *, double *, double *, double *, double *, double *, double *, double *, double *, double, int, int, int, int, int, int, int, int, int);
template void gpuUbou(float *, float *, float *, float *, float *, float *, float *, float *, float *, float *, float, int, int, int, int, int, int, int, int, int);
#ifdef _ENZYME
template <typename T> __global__ void kernelGradgpuUbou1Enzyme(T *f, T *df, T *xg, T *udg, T *dudg, T *odg, T *wdg, T *dwdg, T *uhg, T *nlg, T *tau, T *uinf, T *param, T time, int modelnumber, int ib, int ng, int nc, int ncu, int nd, int ncx, int nco, int ncw)
{
	__enzyme_fwddiffgpuUbou((void*)devicegpuUbou1<T>,
			  enzyme_dup, f, df,
			 enzyme_const, xg,
			 enzyme_dup, udg, dudg,
			 enzyme_const, odg,
			 enzyme_dup, wdg, dwdg,
			 enzyme_const, uhg,
			 enzyme_const, nlg,
			 enzyme_const, tau,
			 enzyme_const, uinf,
			 enzyme_const, param,
			 enzyme_const, time,
			 enzyme_const, modelnumber,
			 enzyme_const, ng,
			 enzyme_const, nc,
			 enzyme_const, ncu,
			 enzyme_const, nd,
			 enzyme_const, ncx,
			 enzyme_const, nco,
			 enzyme_const, ncw);
}

template <typename T> void gpuUbouEnzyme(T *f, T *df, T *xg, T *udg, T *dudg, T *odg, T *wdg, T *dwdg, T *uhg, T *nlg, T *tau, T *uinf, T *param, T time, int modelnumber, int ib, int ng, int nc, int ncu, int nd, int ncx, int nco, int ncw)
{
	int blockDim = 256;
	int gridDim = (ng + blockDim - 1) / blockDim;
	gridDim = (gridDim>1024)? 1024 : gridDim;
	if (ib == 1)
		kernelGradgpuUbou1Enzyme<<<gridDim, blockDim>>>(f, df, xg, udg, dudg, odg, wdg, dwdg, uhg, nlg, tau, uinf, param, time, modelnumber, ib, ng, nc, ncu, nd, ncx, nco, ncw);
}

template void gpuUbouEnzyme(double *, double *, double *, double *, double *, double *, double *, double *, double *, double *, double *, double *, double *, double, int, int, int, int, int, int, int, int, int);
#endif