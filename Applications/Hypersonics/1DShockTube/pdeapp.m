% Add Exasim to Matlab search path
cdir = pwd(); ii = strfind(cdir, "Exasim");
run(cdir(1:(ii+5)) + "/Installation/setpath.m");

% initialize pde structure and mesh structure
[pde,mesh] = initializeexasim();

pde.mutationflag = 1;
pde.mutationopts = {};
pde.mutationopts{1} = "air_5";
pde.mutationopts{2} = "ChemNonEq1T";
pde.mutationopts{3} = "RRHO";
pde.mutationpath = "/Users/rloekvh/Mutationpp";

pde.cpucompiler="/opt/homebrew/Cellar/llvm@12/12.0.1_1/bin/clang++";
% pde.cpuappflags = "-arch x86_64";
% pde.cpulibflags = "-arch x86_64";
% pde.cpuflags = "-arch x86_64";

% Define a PDE model: governing equations, initial solutions, and boundary conditions
pde.model = "ModelC";          % ModelC, ModelD, ModelW
pde.modelfile = "pdemodel_inflow";    % name of a file defining the PDE model

% Choose computing platform and set number of processors
%pde.platform = "gpu";         % choose this option if NVIDIA GPUs are available
pde.mpiprocs = 1;              % number of MPI processors

% Set discretization parameters, physical parameters, and solver parameters
pde.porder = 1;          % polynomial degree
pde.torder = 1;          % time-stepping order of accuracy
pde.nstage = 1;          % time-stepping number of stages
nt = 2e5;
pde.dt = 1e-7*ones(1,nt);   % time step sizes
pde.saveSolFreq = nt/10;
% pde.soltime = 1:pde.saveSolFreq:length(pde.dt); % steps at which solution are collected

%Solver params
pde.linearsolveriter = 40;
pde.GMRESrestart = 20;
pde.linearsolvertol = 1e-3;
pde.matvectol = 1e-5;
pde.NLiter = 5;
pde.RBdim = 5;

% rhoL = [0 0 0.000936356 0.000248905 0];
% rhouL = 4.74105;
% rhoEL = 12226.7;
% rhoR = [0 0 0.00691678 0.00183864 0];
% rhouR = 4.74544;
% rhoER = 72810.4;
rho_pre = [0 0 0 0.000911061 0.000242181 ];
rhou_pre = 4.61296;
rhoE_pre = 9128.09;

rho_post = [0 0 0 0.00672992 0.00178897 ];
rhou_post = 4.61724;
rhoE_post = 52157.2;

rho_inf = sum(rho_post);
u_inf = rhou_post/rho_inf;

% pde.physicsparam = [rho_pre(:)', rhou_pre, rhoE_pre, rho_post(:)', rhou_post, rhoE_post];
pde.physicsparam = [rho_pre(:)'/rho_inf,...
                    rhou_pre/(rho_inf * u_inf),...
                    rhoE_pre/(rho_inf * u_inf * u_inf),...
                    rho_post(:)'/rho_inf,...
                    rhou_post/(rho_inf*u_inf),...
                    rhoE_post/(rho_inf * u_inf * u_inf)];

pde.externalparam = [rho_inf, u_inf];
% pde.physicsparam = [rhoL(:)', rhouL, rhoEL,    rhoR(:)',  rhouR,  rhoER];
                %    1:ns    ns+1   ns+2   ns+3:2*ns+2  2*ns+3  2*ns+4
% pde.tau = [0.1, 0.1, 0.1, 0.1, 0.1, 10, 50000];           % DG stabilization parameter
pde.tau = 2;
pde.dae_alpha = 0;
pde.dae_beta = 1;
% create a grid of 8 by 8 on the unit square
nDiv = 2^8;

[mesh.p,mesh.t] = linemesh(nDiv-1);
a = 0; b = 2;
mesh.p = a + (b-a)*mesh.p;
mesh.p = loginc(mesh.p, 15);
% expressions for domain boundaries
mesh.boundaryexpr = {@(p) abs(p(1,:)-a)<1e-16, @(p) abs(p(1,:) - b)<1e-8}; %TODO: double check boundaries
mesh.boundarycondition = [1;2]; % Set boundary condition for each boundary

%% call exasim to generate and run C++ code to solve the PDE model
% [sol,pde,mesh,master,dmd] = exasim(pde,mesh);

% search compilers and set options
pde = setcompilers(pde);       

% generate input files and store them in datain folder
[pde,mesh,master,dmd] = preprocessing(pde,mesh);

% generate source codes and store them in app folder
gencode(pde);
cd("app");
eval('!./fixargsMPP_Mac.sh');
% eval('!./movefiles.sh');
% eval('!cp opuInituMPP.cpp opuInitu.cpp');  
eval('!cp opuInitwdgMPP.cpp opuInitwdg.cpp');
eval('!cp opuSourcewMPP.cpp opuSourcew.cpp');
% eval('!cp opuFbou_MPP.cpp opuFbou.cpp');
% eval('!cp opuFlux_MPP.cpp opuFlux.cpp');
% eval('!cp opuSource_MPP.cpp opuSource.cpp');
% eval('!./compileMutation.sh');
cd("..");
% compile source codes to build an executable file and store it in app folder
compilerstr = compilecode(pde);

% run executable file to compute solution and store it in dataout folder
runstr = runcode(pde);

%% plot solution
% sol = fetchsolution(pde,master,dmd, 'dataout');
ti = nt;
sol = getsolution(['dataout/out_t' num2str(ti)],dmd,master.npe);
dgnodes = createdgnodes(mesh.p,mesh.t,mesh.f,mesh.curvedboundary,mesh.curvedboundaryexpr,pde.porder);    
for i = 1:5    
    u = sol(:,i,:);
    subplot(1,3,1)
    hold on
    semilogx(dgnodes(:),u(:),'LineWidth',1.3)
end
u = sol(:,6,:);
subplot(1,3,2)
semilogx(dgnodes(:),u(:),'LineWidth',1.3);

u = sol(:,7,:);
subplot(1,3,3)
semilogx(dgnodes(:), u(:),'LineWidth',1.3)

% solw = getsolution(['dataout/out_wdg_t' num2str(ti)],dmd,master.npe);
% w = solw(:,6,:);
% figure(2);
% plot(dgnodes(:),w(:))


        
