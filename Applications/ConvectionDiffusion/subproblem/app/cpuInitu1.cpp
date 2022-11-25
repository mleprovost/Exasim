template <typename T> void cpuInitu1(T *f, T *xdg, T *uinf, T *param, int modelnumber, int ng, int ncx, int nce, int npe, int ne)
{
	#pragma omp parallel for
	for (int i = 0; i <ng; i++) {
		int j = i%npe;
		int k = (i-j)/npe;
		T xdg1 = xdg[j+npe*0+npe*ncx*k];
		T xdg2 = xdg[j+npe*1+npe*ncx*k];
		f[j+npe*0+npe*nce*k] = 0.0;
	}
}

template void cpuInitu1(double *, double *, double *, double *, int, int, int, int, int, int);
template void cpuInitu1(float *, float *, float *, float *, int, int, int, int, int, int);
