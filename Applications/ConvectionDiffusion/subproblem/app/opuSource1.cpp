template <typename T> void opuSource1(T *f, T *xdg, T *udg, T *odg, T *wdg, T *uinf, T *param, T time, int modelnumber, int ng, int nc, int ncu, int nd, int ncx, int nco, int ncw)
{
	for (int i = 0; i <ng; i++) {
		f[0*ng+i] = 1.0;
	}
}

template void opuSource1(double *, double *, double *, double *, double *, double *, double *, double, int, int, int, int, int, int, int, int);
template void opuSource1(float *, float *, float *, float *, float *, float *, float *, float, int, int, int, int, int, int, int, int);
