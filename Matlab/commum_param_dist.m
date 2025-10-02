clear all
close all
clc

param = zeros(9,3000);
cd  Dados_com_ruido\

for i = 1:1:3000
    strg_save = sprintf("param_%d.csv", i);
    param(:,i) = readmatrix(strg_save);
end
cd ..\

cd Dados_dist3\
Dados_Teoricos = readmatrix('dados_distribuidos_3.csv');

for i=1:1:3000
    offset = param(4:6,i);
    Escala = param(1:3,i);
    Ang = param(7:9, i);
    
    e = [Escala; offset; Ang];

    rho = Ang(1);
    phi = Ang(2);
    lambda = Ang(3);
    
    scale = diag(Escala);
    
    T = [1 0 0; sin(rho) cos(rho) 0; sin(phi)*cos(lambda) sin(lambda) cos(phi)*cos(lambda)];
    mean = [0 0 0];
    sigma = [0.006^2 0 0;0 0.006^2 0;0 0 0.006^2];
    
    Dados_Corrompido = zeros(3,996);
    Ruido = zeros(3,996);
    for j=1:length(Dados_Teoricos(1,:))
        Ruido(:,j) = mvnrnd(mean,sigma,1)';
        Dados_Corrompido(:,j) = scale*T*Dados_Teoricos(:,j) + offset + Ruido(:,j); 
    end
    
    strg_save = sprintf("conjunto_dados_corrompidos_%d.csv", i);
    writematrix(Dados_Corrompido, strg_save);
end

cd ../