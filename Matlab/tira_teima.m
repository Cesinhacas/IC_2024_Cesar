%% Tira teima

%clear all
cd 'Dados'
load Dados_Corrompidos.mat
cd ../

ParT.x0 = 0;
ParT.y0 = 0;
ParT.z0 = 0;
ParT.a = 1;
ParT.b = 1;
ParT.c = 1;
ParT.rho = 0;
ParT.phi = 0;
ParT.lambda = 0;
ParP = ParT;


[DataNLLS, ParC, Time, Est, Erros] = NLLS_9Dcalib(ParT, ParP, Dados_Corrompido, 1, 0, 0)