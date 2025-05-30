dados = zeros(3,1112);
dados2 = zeros(3,556);
for i = 1:1:3000
    cd Dados_com_ruido\
    strg_save = sprintf("conjunto_dados_corrompidos_%d.csv", i);
    dados = readmatrix(strg_save);
    
    dados2 = dados(:,1:2:end);

    cd ..\
    cd dados_ATmega\
    strg_save = sprintf("run%d.txt", i);
    writematrix(dados2, strg_save)
    cd ..\
end