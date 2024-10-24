H = ones(1,1112);
noise = 0.006^2*ones(3,1112);

cd ..
cd dados\
load('Dados_Corrompidos.mat')
cd ..
cd Matlab
clc