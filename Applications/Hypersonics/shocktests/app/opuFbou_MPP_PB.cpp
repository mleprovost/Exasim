template <typename T> void opuFbou1(T *f, T *xdg, T *udg, T *odg, T *wdg, T *uhg, T *nlg, T *tau, T *uinf, T *param, T time, int modelnumber, int ng, int nc, int ncu, int nd, int ncx, int nco, int ncw, Mutation::Mixture *mix)
{
    double Uwork[5];
    double dTdU[6];
    int nspecies = 5;
    int ndim = 1;
    double rho_scale = uinf[0];
    double u_scale = uinf[1];
    double rhoe_scale = uinf[2];

	for (int i = 0; i <ng; i++) {
		T param1 = param[0];
		T param18 = param[18];
		T param19 = param[19];
		T uinf1 = uinf[0];
		T uinf2 = uinf[1];
		T uinf3 = uinf[2];
		T uinf4 = uinf[3];
		T uinf5 = uinf[4];
		T uinf6 = uinf[5];
		T uinf7 = uinf[6];
		T uinf8 = uinf[7];
		T uinf9 = uinf[8];
		T uinf10 = uinf[9];
		T uinf11 = uinf[10];
		T uinf12 = uinf[11];
		T uinf13 = uinf[12];
		T uinf14 = uinf[13];
		T uinf15 = uinf[14];
		T uinf16 = uinf[15];
		T uinf17 = uinf[16];
		T uinf18 = uinf[17];
		T uinf19 = uinf[18];
		T tau1 = tau[0];
		T tau2 = tau[1];
		T tau3 = tau[2];
		T tau4 = tau[3];
		T tau5 = tau[4];
		T tau6 = tau[5];
		T tau7 = tau[6];
		T udg1 = udg[0*ng+i];
		T udg2 = udg[1*ng+i];
		T udg3 = udg[2*ng+i];
		T udg4 = udg[3*ng+i];
		T udg5 = udg[4*ng+i];
		T udg6 = udg[5*ng+i];
		T udg7 = udg[6*ng+i];
		T udg8 = udg[7*ng+i];
		T udg9 = udg[8*ng+i];
		T udg10 = udg[9*ng+i];
		T udg11 = udg[10*ng+i];
		T udg12 = udg[11*ng+i];
		T udg13 = udg[12*ng+i];
		T udg14 = udg[13*ng+i];
		T uhg1 = uhg[0*ng+i];
		T uhg2 = uhg[1*ng+i];
		T uhg3 = uhg[2*ng+i];
		T uhg4 = uhg[3*ng+i];
		T uhg5 = uhg[4*ng+i];
		T uhg6 = uhg[5*ng+i];
		T uhg7 = uhg[6*ng+i];
		T odg1 = odg[0*ng+i];
		T odg2 = odg[1*ng+i];
		T odg3 = odg[2*ng+i];
		T odg4 = odg[3*ng+i];
		T odg5 = odg[4*ng+i];
		T odg6 = odg[5*ng+i];
		T odg7 = odg[6*ng+i];
		T odg8 = odg[7*ng+i];
		T nlg1 = nlg[0*ng+i];

        T t1pi = 1.0/3.141592653589793;
		udg1 = udg1*(t1pi*atan(udg1*1.0E+12)+1.0/2.0)+3.182454300088011e-13;
		udg2 = udg2*(t1pi*atan(udg2*1.0E+12)+1.0/2.0)+3.182454300088011e-13;
		udg3 = udg3*(t1pi*atan(udg3*1.0E+12)+1.0/2.0)+3.182454300088011e-13;
		udg4 = udg4*(t1pi*atan(udg4*1.0E+12)+1.0/2.0)+3.182454300088011e-13;
		udg5 = udg5*(t1pi*atan(udg5*1.0E+12)+1.0/2.0)+3.182454300088011e-13;

		double Ucons[7] = {udg1, udg2, udg3, udg4, udg5, udg6, udg7};
		double Ustate[6];
		dimensionalizeConsVars(Ucons, (double*)uinf, nspecies, 1);
		conservativeToState(Ucons, Ustate, (double*)uinf, nspecies, 1);
		double rhovec[5] = {Ustate[0],Ustate[1],Ustate[2],Ustate[3],Ustate[4]};
		double rhoe = Ustate[nspecies];

		mix->setState(rhovec, &rhoe, 0);

        dT_dUstate(dTdU, Ustate, Uwork, nspecies, ndim, mix);
        nondimensionalize_dT_dUstate(dTdU, (double*)uinf, nspecies, nd);

		uinf1 = mix->P()/rhoe_scale;
		uinf2 = 0.0; // D_1
		uinf3 = 0.0; // D_2
		uinf4 = 0.0; // D_3 
		uinf5 = 0.0; // D_4
		uinf6 = 0.0; // D_5
		uinf7 = 0.0; // h_1
		uinf8 = 0.0; // h_2
		uinf9 = 0.0; // h_3
		uinf10 = 0.0; // h_4
		uinf11 = 0.0; // h_5 
		uinf12 = 0.0; // mu
		uinf13 = 0.0; // kappa
		uinf14 = dTdU[0];
		uinf15 = dTdU[1];
		uinf16 = dTdU[2];
		uinf17 = dTdU[3];
		uinf18 = dTdU[4];
		uinf19 = dTdU[5];

		T t2 = odg4+uinf2;
		T t3 = odg5+uinf3;
		T t4 = odg6+uinf4;
		T t5 = odg7+uinf5;
		T t6 = odg2+uinf12;
		T t7 = odg8+uinf6;
		T t8 = udg1*udg1;
		T t9 = udg2*udg2;
		T t10 = udg3*udg3;
		T t11 = udg4*udg4;
		T t12 = udg5*udg5;
		T t13 = udg6*udg6;
		T t14 = 1.0/3.141592653589793;
		T t15 = 1.0/param19;
		T t16 = udg1*1.0E+9;
		T t17 = udg2*1.0E+9;
		T t18 = udg3*1.0E+9;
		T t19 = udg4*1.0E+9;
		T t20 = udg5*1.0E+9;
		T t26 = udg1*1.0E+12;
		T t27 = udg2*1.0E+12;
		T t28 = udg3*1.0E+12;
		T t29 = udg4*1.0E+12;
		T t30 = udg5*1.0E+12;
		T t21 = atan(t16);
		T t22 = atan(t17);
		T t23 = atan(t18);
		T t24 = atan(t19);
		T t25 = atan(t20);
		T t31 = atan(t26);
		T t32 = atan(t27);
		T t33 = atan(t28);
		T t34 = atan(t29);
		T t35 = atan(t30);
		T t51 = t8*1.0E+18;
		T t52 = t9*1.0E+18;
		T t53 = t10*1.0E+18;
		T t54 = t11*1.0E+18;
		T t55 = t12*1.0E+18;
		T t36 = t14*t21;
		T t37 = t14*t22;
		T t38 = t14*t23;
		T t39 = t14*t24;
		T t40 = t14*t25;
		T t41 = t14*t31;
		T t42 = t14*t32;
		T t43 = t14*t33;
		T t44 = t14*t34;
		T t45 = t14*t35;
		T t61 = t51+1.0;
		T t62 = t52+1.0;
		T t63 = t53+1.0;
		T t64 = t54+1.0;
		T t65 = t55+1.0;
		T t46 = t36+1.0/2.0;
		T t47 = t37+1.0/2.0;
		T t48 = t38+1.0/2.0;
		T t49 = t39+1.0/2.0;
		T t50 = t40+1.0/2.0;
		T t66 = t41+1.0/2.0;
		T t67 = t42+1.0/2.0;
		T t68 = t43+1.0/2.0;
		T t69 = t44+1.0/2.0;
		T t70 = t45+1.0/2.0;
		T t76 = 1.0/t61;
		T t77 = 1.0/t62;
		T t78 = 1.0/t63;
		T t79 = 1.0/t64;
		T t80 = 1.0/t65;
		T t56 = t46*udg1;
		T t57 = t47*udg2;
		T t58 = t48*udg3;
		T t59 = t49*udg4;
		T t60 = t50*udg5;
		T t71 = t66*udg1;
		T t72 = t67*udg2;
		T t73 = t68*udg3;
		T t74 = t69*udg4;
		T t75 = t70*udg5;
		T t81 = t14*t16*t76;
		T t82 = t14*t17*t77;
		T t83 = t14*t18*t78;
		T t84 = t14*t19*t79;
		T t85 = t14*t20*t80;
		T t86 = t56+3.183098229442294E-10;
		T t87 = t57+3.183098229442294E-10;
		T t88 = t58+3.183098229442294E-10;
		T t89 = t59+3.183098229442294E-10;
		T t90 = t60+3.183098229442294E-10;
		T t91 = t46+t81;
		T t92 = t47+t82;
		T t93 = t48+t83;
		T t94 = t49+t84;
		T t95 = t50+t85;
		T t101 = t56+t57+t58+t59+t60+1.591549114721147E-9;
		T t104 = t71+t72+t73+t74+t75+1.591227150044006E-12;
		T t96 = t91*udg8;
		T t97 = t92*udg9;
		T t98 = t93*udg10;
		T t99 = t94*udg11;
		T t100 = t95*udg12;
		T t102 = 1.0/t101;
		T t105 = 1.0/t104;
		T t103 = t102*t102;
		T t106 = t96*t101;
		T t107 = t97*t101;
		T t108 = t98*t101;
		T t109 = t99*t101;
		T t110 = t100*t101;
		T t116 = t96+t97+t98+t99+t100;
		T t111 = -t106;
		T t112 = -t107;
		T t113 = -t108;
		T t114 = -t109;
		T t115 = -t110;
		T t117 = t86*t116;
		T t118 = t87*t116;
		T t119 = t88*t116;
		T t120 = t89*t116;
		T t121 = t90*t116;
		T t122 = t102*t116*udg6;
		T t123 = -t122;
		T t125 = t111+t117;
		T t126 = t112+t118;
		T t127 = t113+t119;
		T t128 = t114+t120;
		T t129 = t115+t121;
		T t130 = -odg1*t102*(t122-udg13);
		T t131 = t6*t15*t102*(t122-udg13)*(-4.0/3.0);
		T t132 = -t2*t103*(t106-t117);
		T t133 = -t3*t103*(t107-t118);
		T t134 = -t4*t103*(t108-t119);
		T t135 = -t5*t103*(t109-t120);
		T t136 = -t7*t103*(t110-t121);
		T t124 = t123+udg13;
		T t137 = t132+t133+t134+t135+t136;
		f[0*ng+i] = tau1*(udg1-uhg1)+nlg1*t105*udg6*(t71+3.182454300088011E-13);
		f[1*ng+i] = tau2*(udg2-uhg2)+nlg1*t105*udg6*(t72+3.182454300088011E-13);
		f[2*ng+i] = tau3*(udg3-uhg3)+nlg1*t105*udg6*(t73+3.182454300088011E-13);
		f[3*ng+i] = tau4*(udg4-uhg4)+nlg1*t105*udg6*(t74+3.182454300088011E-13);
		f[4*ng+i] = tau5*(udg5-uhg5)+nlg1*t105*udg6*(t75+3.182454300088011E-13);
		f[5*ng+i] = tau6*(udg6-uhg6)+nlg1*(t130+t131+uinf1+t13*t105);
		f[6*ng+i] = -nlg1*(-udg6*(t105*udg7+t105*uinf1)+uinf7*(t86*(t2*t103*(t106-t117)+t3*t103*(t107-t118)+t4*t103*(t108-t119)+t5*t103*(t109-t120)+t7*t103*(t110-t121))-t2*t102*(t106-t117))+uinf8*(t87*(t2*t103*(t106-t117)+t3*t103*(t107-t118)+t4*t103*(t108-t119)+t5*t103*(t109-t120)+t7*t103*(t110-t121))-t3*t102*(t107-t118))+uinf9*(t88*(t2*t103*(t106-t117)+t3*t103*(t107-t118)+t4*t103*(t108-t119)+t5*t103*(t109-t120)+t7*t103*(t110-t121))-t4*t102*(t108-t119))+uinf10*(t89*(t2*t103*(t106-t117)+t3*t103*(t107-t118)+t4*t103*(t108-t119)+t5*t103*(t109-t120)+t7*t103*(t110-t121))-t5*t102*(t109-t120))+uinf11*(t90*(t2*t103*(t106-t117)+t3*t103*(t107-t118)+t4*t103*(t108-t119)+t5*t103*(t109-t120)+t7*t103*(t110-t121))-t7*t102*(t110-t121))+t102*udg6*(odg1*t102*(t122-udg13)+t6*t15*t102*(t122-udg13)*(4.0/3.0))-(t15*(odg3+uinf13)*(t96*uinf14+t97*uinf15+t98*uinf16+t99*uinf17+t100*uinf18+uinf19*(udg6+udg14-(t13*t103*t116)/2.0)))/param18)+tau7*(udg7-uhg7);
	}
}

template <typename T> void opuFbou2(T *f, T *xdg, T *udg, T *odg, T *wdg, T *uhg, T *nlg, T *tau, T *uinf, T *param, T time, int modelnumber, int ng, int nc, int ncu, int nd, int ncx, int nco, int ncw, Mutation::Mixture *mix)
{
    double Uwork[5];
    double dTdU[6];
    int nspecies = 5;
    int ndim = 1;
    double rho_scale = uinf[0];
    double u_scale = uinf[1];
    double rhoe_scale = uinf[2];

	for (int i = 0; i <ng; i++) {
		T param1 = param[0];
		T param18 = param[18];
		T param19 = param[19];
		T uinf1 = uinf[0];
		T uinf2 = uinf[1];
		T uinf3 = uinf[2];
		T uinf4 = uinf[3];
		T uinf5 = uinf[4];
		T uinf6 = uinf[5];
		T uinf7 = uinf[6];
		T uinf8 = uinf[7];
		T uinf9 = uinf[8];
		T uinf10 = uinf[9];
		T uinf11 = uinf[10];
		T uinf12 = uinf[11];
		T uinf13 = uinf[12];
		T uinf14 = uinf[13];
		T uinf15 = uinf[14];
		T uinf16 = uinf[15];
		T uinf17 = uinf[16];
		T uinf18 = uinf[17];
		T uinf19 = uinf[18];
		T tau1 = tau[0];
		T tau2 = tau[1];
		T tau3 = tau[2];
		T tau4 = tau[3];
		T tau5 = tau[4];
		T tau6 = tau[5];
		T tau7 = tau[6];
		T udg1 = udg[0*ng+i];
		T udg2 = udg[1*ng+i];
		T udg3 = udg[2*ng+i];
		T udg4 = udg[3*ng+i];
		T udg5 = udg[4*ng+i];
		T udg6 = udg[5*ng+i];
		T udg7 = udg[6*ng+i];
		T udg8 = udg[7*ng+i];
		T udg9 = udg[8*ng+i];
		T udg10 = udg[9*ng+i];
		T udg11 = udg[10*ng+i];
		T udg12 = udg[11*ng+i];
		T udg13 = udg[12*ng+i];
		T udg14 = udg[13*ng+i];
		T uhg1 = uhg[0*ng+i];
		T uhg2 = uhg[1*ng+i];
		T uhg3 = uhg[2*ng+i];
		T uhg4 = uhg[3*ng+i];
		T uhg5 = uhg[4*ng+i];
		T uhg6 = uhg[5*ng+i];
		T uhg7 = uhg[6*ng+i];
		T odg1 = odg[0*ng+i];
		T odg2 = odg[1*ng+i];
		T odg3 = odg[2*ng+i];
		T odg4 = odg[3*ng+i];
		T odg5 = odg[4*ng+i];
		T odg6 = odg[5*ng+i];
		T odg7 = odg[6*ng+i];
		T odg8 = odg[7*ng+i];
		T nlg1 = nlg[0*ng+i];

        T t1pi = 1.0/3.141592653589793;
		udg1 = udg1*(t1pi*atan(udg1*1.0E+12)+1.0/2.0)+3.182454300088011e-13;
		udg2 = udg2*(t1pi*atan(udg2*1.0E+12)+1.0/2.0)+3.182454300088011e-13;
		udg3 = udg3*(t1pi*atan(udg3*1.0E+12)+1.0/2.0)+3.182454300088011e-13;
		udg4 = udg4*(t1pi*atan(udg4*1.0E+12)+1.0/2.0)+3.182454300088011e-13;
		udg5 = udg5*(t1pi*atan(udg5*1.0E+12)+1.0/2.0)+3.182454300088011e-13;

		double Ucons[7] = {udg1, udg2, udg3, udg4, udg5, udg6, udg7};
		double Ustate[6];
		dimensionalizeConsVars(Ucons, (double*)uinf, nspecies, 1);
		conservativeToState(Ucons, Ustate, (double*)uinf, nspecies, 1);
		double rhovec[5] = {Ustate[0],Ustate[1],Ustate[2],Ustate[3],Ustate[4]};
		double rhoe = Ustate[nspecies];

		mix->setState(rhovec, &rhoe, 0);

        dT_dUstate(dTdU, Ustate, Uwork, nspecies, ndim, mix);
        nondimensionalize_dT_dUstate(dTdU, (double*)uinf, nspecies, nd);

		uinf1 = mix->P()/rhoe_scale;
		uinf2 = 0.0; // D_1
		uinf3 = 0.0; // D_2
		uinf4 = 0.0; // D_3 
		uinf5 = 0.0; // D_4
		uinf6 = 0.0; // D_5
		uinf7 = 0.0; // h_1
		uinf8 = 0.0; // h_2
		uinf9 = 0.0; // h_3
		uinf10 = 0.0; // h_4
		uinf11 = 0.0; // h_5 
		uinf12 = 0.0; // mu
		uinf13 = 0.0; // kappa
		uinf14 = dTdU[0];
		uinf15 = dTdU[1];
		uinf16 = dTdU[2];
		uinf17 = dTdU[3];
		uinf18 = dTdU[4];
		uinf19 = dTdU[5];


		T t2 = odg4+uinf2;
		T t3 = odg5+uinf3;
		T t4 = odg6+uinf4;
		T t5 = odg7+uinf5;
		T t6 = odg2+uinf12;
		T t7 = odg8+uinf6;
		T t8 = udg1*udg1;
		T t9 = udg2*udg2;
		T t10 = udg3*udg3;
		T t11 = udg4*udg4;
		T t12 = udg5*udg5;
		T t13 = udg6*udg6;
		T t14 = 1.0/3.141592653589793;
		T t15 = 1.0/param19;
		T t16 = udg1*1.0E+9;
		T t17 = udg2*1.0E+9;
		T t18 = udg3*1.0E+9;
		T t19 = udg4*1.0E+9;
		T t20 = udg5*1.0E+9;
		T t26 = udg1*1.0E+12;
		T t27 = udg2*1.0E+12;
		T t28 = udg3*1.0E+12;
		T t29 = udg4*1.0E+12;
		T t30 = udg5*1.0E+12;
		T t21 = atan(t16);
		T t22 = atan(t17);
		T t23 = atan(t18);
		T t24 = atan(t19);
		T t25 = atan(t20);
		T t31 = atan(t26);
		T t32 = atan(t27);
		T t33 = atan(t28);
		T t34 = atan(t29);
		T t35 = atan(t30);
		T t51 = t8*1.0E+18;
		T t52 = t9*1.0E+18;
		T t53 = t10*1.0E+18;
		T t54 = t11*1.0E+18;
		T t55 = t12*1.0E+18;
		T t36 = t14*t21;
		T t37 = t14*t22;
		T t38 = t14*t23;
		T t39 = t14*t24;
		T t40 = t14*t25;
		T t41 = t14*t31;
		T t42 = t14*t32;
		T t43 = t14*t33;
		T t44 = t14*t34;
		T t45 = t14*t35;
		T t61 = t51+1.0;
		T t62 = t52+1.0;
		T t63 = t53+1.0;
		T t64 = t54+1.0;
		T t65 = t55+1.0;
		T t46 = t36+1.0/2.0;
		T t47 = t37+1.0/2.0;
		T t48 = t38+1.0/2.0;
		T t49 = t39+1.0/2.0;
		T t50 = t40+1.0/2.0;
		T t66 = t41+1.0/2.0;
		T t67 = t42+1.0/2.0;
		T t68 = t43+1.0/2.0;
		T t69 = t44+1.0/2.0;
		T t70 = t45+1.0/2.0;
		T t76 = 1.0/t61;
		T t77 = 1.0/t62;
		T t78 = 1.0/t63;
		T t79 = 1.0/t64;
		T t80 = 1.0/t65;
		T t56 = t46*udg1;
		T t57 = t47*udg2;
		T t58 = t48*udg3;
		T t59 = t49*udg4;
		T t60 = t50*udg5;
		T t71 = t66*udg1;
		T t72 = t67*udg2;
		T t73 = t68*udg3;
		T t74 = t69*udg4;
		T t75 = t70*udg5;
		T t81 = t14*t16*t76;
		T t82 = t14*t17*t77;
		T t83 = t14*t18*t78;
		T t84 = t14*t19*t79;
		T t85 = t14*t20*t80;
		T t86 = t56+3.183098229442294E-10;
		T t87 = t57+3.183098229442294E-10;
		T t88 = t58+3.183098229442294E-10;
		T t89 = t59+3.183098229442294E-10;
		T t90 = t60+3.183098229442294E-10;
		T t91 = t46+t81;
		T t92 = t47+t82;
		T t93 = t48+t83;
		T t94 = t49+t84;
		T t95 = t50+t85;
		T t101 = t56+t57+t58+t59+t60+1.591549114721147E-9;
		T t104 = t71+t72+t73+t74+t75+1.591227150044006E-12;
		T t96 = t91*udg8;
		T t97 = t92*udg9;
		T t98 = t93*udg10;
		T t99 = t94*udg11;
		T t100 = t95*udg12;
		T t102 = 1.0/t101;
		T t105 = 1.0/t104;
		T t103 = t102*t102;
		T t106 = t96*t101;
		T t107 = t97*t101;
		T t108 = t98*t101;
		T t109 = t99*t101;
		T t110 = t100*t101;
		T t116 = t96+t97+t98+t99+t100;
		T t111 = -t106;
		T t112 = -t107;
		T t113 = -t108;
		T t114 = -t109;
		T t115 = -t110;
		T t117 = t86*t116;
		T t118 = t87*t116;
		T t119 = t88*t116;
		T t120 = t89*t116;
		T t121 = t90*t116;
		T t122 = t102*t116*udg6;
		T t123 = -t122;
		T t125 = t111+t117;
		T t126 = t112+t118;
		T t127 = t113+t119;
		T t128 = t114+t120;
		T t129 = t115+t121;
		T t130 = -odg1*t102*(t122-udg13);
		T t131 = t6*t15*t102*(t122-udg13)*(-4.0/3.0);
		T t132 = -t2*t103*(t106-t117);
		T t133 = -t3*t103*(t107-t118);
		T t134 = -t4*t103*(t108-t119);
		T t135 = -t5*t103*(t109-t120);
		T t136 = -t7*t103*(t110-t121);
		T t124 = t123+udg13;
		T t137 = t132+t133+t134+t135+t136;
		f[0*ng+i] = tau1*(udg1-uhg1)+nlg1*t105*udg6*(t71+3.182454300088011E-13);
		f[1*ng+i] = tau2*(udg2-uhg2)+nlg1*t105*udg6*(t72+3.182454300088011E-13);
		f[2*ng+i] = tau3*(udg3-uhg3)+nlg1*t105*udg6*(t73+3.182454300088011E-13);
		f[3*ng+i] = tau4*(udg4-uhg4)+nlg1*t105*udg6*(t74+3.182454300088011E-13);
		f[4*ng+i] = tau5*(udg5-uhg5)+nlg1*t105*udg6*(t75+3.182454300088011E-13);
		f[5*ng+i] = tau6*(udg6-uhg6)+nlg1*(t130+t131+uinf1+t13*t105);
		f[6*ng+i] = -nlg1*(-udg6*(t105*udg7+t105*uinf1)+uinf7*(t86*(t2*t103*(t106-t117)+t3*t103*(t107-t118)+t4*t103*(t108-t119)+t5*t103*(t109-t120)+t7*t103*(t110-t121))-t2*t102*(t106-t117))+uinf8*(t87*(t2*t103*(t106-t117)+t3*t103*(t107-t118)+t4*t103*(t108-t119)+t5*t103*(t109-t120)+t7*t103*(t110-t121))-t3*t102*(t107-t118))+uinf9*(t88*(t2*t103*(t106-t117)+t3*t103*(t107-t118)+t4*t103*(t108-t119)+t5*t103*(t109-t120)+t7*t103*(t110-t121))-t4*t102*(t108-t119))+uinf10*(t89*(t2*t103*(t106-t117)+t3*t103*(t107-t118)+t4*t103*(t108-t119)+t5*t103*(t109-t120)+t7*t103*(t110-t121))-t5*t102*(t109-t120))+uinf11*(t90*(t2*t103*(t106-t117)+t3*t103*(t107-t118)+t4*t103*(t108-t119)+t5*t103*(t109-t120)+t7*t103*(t110-t121))-t7*t102*(t110-t121))+t102*udg6*(odg1*t102*(t122-udg13)+t6*t15*t102*(t122-udg13)*(4.0/3.0))-(t15*(odg3+uinf13)*(t96*uinf14+t97*uinf15+t98*uinf16+t99*uinf17+t100*uinf18+uinf19*(udg6+udg14-(t13*t103*t116)/2.0)))/param18)+tau7*(udg7-uhg7);
	}
}

template <typename T> void opuFbou(T *f, T *xdg, T *udg, T *odg, T *wdg, T *uhg, T *nlg, T *tau, T *uinf, T *param, T time, int modelnumber, int ib, int ng, int nc, int ncu, int nd, int ncx, int nco, int ncw, Mutation::Mixture *mix)
{
	if (ib == 1)
		opuFbou1(f, xdg, udg, odg, wdg, uhg, nlg, tau, uinf, param, time, modelnumber, ng, nc, ncu, nd, ncx, nco, ncw, mix);
	else if (ib == 2)
		opuFbou2(f, xdg, udg, odg, wdg, uhg, nlg, tau, uinf, param, time, modelnumber, ng, nc, ncu, nd, ncx, nco, ncw, mix);
}

template void opuFbou(double *, double *, double *, double *, double *, double *, double *, double *, double *, double *, double, int, int, int, int, int, int, int, int, int, Mutation::Mixture *);
template void opuFbou(float *, float *, float *, float *, float *, float *, float *, float *, float *, float *, float, int, int, int, int, int, int, int, int, int, Mutation::Mixture *);
