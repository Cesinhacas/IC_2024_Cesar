clear all
close all
clc

ETS_param = zeros(11,3000);
NLLS_param = zeros(11,3000);

cd RES_F7_FPU\

for i = 1:1:3000
    strg_save = sprintf("run%d.TXT", i);
    dados = readmatrix(strg_save);
    
    ETS_param(:,i) = dados(:,1);
    NLLS_param(:,i) = dados(:,2);
    
end

cd ..\
cd Dados_com_ruido\

for i = 1:1:3000
    strg_save = sprintf("param_%d.csv", i);
    dados = readmatrix(strg_save);
    for j = 1:1:9
        ETS_param(j,i) = dados(j) - ETS_param(j,i);
        NLLS_param(j,i) = dados(j) - NLLS_param(j,i);
    end
end

cd ..\

cd ..\
cd Dados\
writematrix(ETS_param, 'MTS_ETS_f7_FPU.csv')
writematrix(NLLS_param, 'MTS_NLLS_f7_FPU.csv')
cd ..\
cd Matlab\
