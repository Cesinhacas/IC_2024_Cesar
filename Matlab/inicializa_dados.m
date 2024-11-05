H = 0.5*ones(1,572);
noise = 0.006^2*ones(3,1112);

cd ..
cd dados\
load('Dados_Corrompidos.mat')
cd ..
cd Matlab
clc