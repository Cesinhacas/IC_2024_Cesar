clear all
close all
clc

cd ..\
cd Dados
dados_x = readmatrix('fisher_Matlab.csv');
dados_xyz = readmatrix('fisher_Matlab_dist.csv');
dados_xyz2 = readmatrix('fisher_Matlab_dist2.csv');
dados_xyz3 = readmatrix('fisher_Matlab_dist3.csv');
cd ..\
cd Matlab\

disp("Conjuntos de dados padrão:")
for i = 1:1:9
    disp(mean(dados_x(i,:)))
end

disp("Conjunto de dados distribuidos nos três eixos 556")
for i = 1:1:9
    disp(mean(dados_xyz(i,:)))
end

disp("Conjunto de dados distribuidos nos três eixos 1112")
for i = 1:1:9
    disp(mean(dados_xyz2(i,:)))
end

disp("Conjunto de dados distribuidos nos três eixos 332")
for i = 1:1:9
    disp(mean(dados_xyz3(i,:)))
end