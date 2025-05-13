for i = 1:1:3000
    cd Dados_com_ruido\
    strg_save = sprintf("conjunto_dados_corrompidos_%d.csv", i);
    dados = readmatrix(strg_save);
    cd ..\
    cd dados_f7\
    strg_save = sprintf("run%d.txt", i);
    writematrix(dados, strg_save)
    cd ..\
end