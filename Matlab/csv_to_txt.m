dados = zeros(3,1112);
dados2 = zeros(3,556);
for i = 1:1:3000
    cd Dados_com_ruido\
    strg_save = sprintf("conjunto_dados_corrompidos_%d.csv", i);
    dados = readmatrix(strg_save);
    
    dados2 = dados(:,1:7:end);
    %dados3 = dados2(:,1:2:end);
    strg_save = sprintf("run%d.txt", i);

    
    cd ..\
    cd dados_139\
    writematrix(dados2, strg_save);
    cd ..\


%     cd ..\
%     cd dados_ATmega\
%     strg_save = sprintf("run%d.txt", i);
%     writematrix(dados2, strg_save)
%     cd ..\
% 
%     cd dados_reduzidos\
%     writematrix(dados3, strg_save);
%     cd ..\


end