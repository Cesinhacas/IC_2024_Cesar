clear all
close all
clc

cd ..\
cd Dados
Dados_NLLS_p = readmatrix('Dados_rest_NLLS');
Dados_NLLS_m = readmatrix('Dados_NLLS_m.csv');
Dados_ETS_p = readmatrix('Dados_rest_ETS.csv');
Dados_ETS_m = readmatrix('Dados_ETS_m.csv');
Dados_TW_p = readmatrix('Dados_rest_TW.csv');
Dados_TW_m = readmatrix('Dados_TW_m.csv');
Dados_teoricos = readmatrix('transpose_dados.csv')';
cd ..\
cd Matlab

Dados_ETS_p = Dados_ETS_p(:, 1+1:end);
Dados_NLLS_p = Dados_NLLS_p(:, 1+1:end);
Dados_TW_p = Dados_TW_p(:, 1+1:end);

NLLS = Dados_NLLS_m - Dados_NLLS_p;
ETS = Dados_ETS_m - Dados_ETS_p;
TW = Dados_TW_m - Dados_TW_p;

NLLS_p = Dados_teoricos - Dados_NLLS_p;
NLLS_m = Dados_teoricos - Dados_NLLS_m;

ETS_p = Dados_teoricos - Dados_ETS_p;
ETS_m = Dados_teoricos - Dados_ETS_m;

NLLS_x_m = mean(NLLS_m(1,:));
NLLS_y_m = mean(NLLS_m(2,:));
NLLS_z_m = mean(NLLS_m(3,:));

NLLS_x_p = mean(NLLS_p(1,:));
NLLS_y_p = mean(NLLS_p(2,:));
NLLS_z_p = mean(NLLS_p(3,:));

ETS_x_m = mean(ETS_m(1,:));
ETS_y_m = mean(ETS_m(2,:));
ETS_z_m = mean(ETS_m(3,:));

ETS_x_p = mean(ETS_p(1,:));
ETS_y_p = mean(ETS_p(2,:));
ETS_z_p = mean(ETS_p(3,:));