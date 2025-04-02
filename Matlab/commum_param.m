cd ../
cd 'Dados'
load Dados_Teoricos.mat
writematrix(Dados_Teoricos', 'transpose_dados.csv');
cd ../
cd 'Matlab'

cd Dados_com_ruido\

for i=1:1:3000
    offset = (rand(3,1)*0.4)-0.2;
    Escala = (rand(3,1)*0.4)+0.8;
    Ang = (rand(3,1)*6 - 3) * (pi/180);
    
    e = [Escala; offset; Ang];

    rho = Ang(1);
    phi = Ang(2);
    lambda = Ang(3);
    
    scale = diag(Escala);
    
    T = [1 0 0; sin(rho) cos(rho) 0; sin(phi)*cos(lambda) sin(lambda) cos(phi)*cos(lambda)];
    mean = [0 0 0];
    sigma = [0.006^2 0 0;0 0.006^2 0;0 0 0.006^2];
    
    Dados_Corrompido = zeros(3,1112);
    Ruido = zeros(3,1112);
    for j=1:length(Dados_Teoricos(1,:))
        Ruido(:,j) = mvnrnd(mean,sigma,1)';
        Dados_Corrompido(:,j) = scale*T*Dados_Teoricos(:,j) + offset + Ruido(:,j); 
    end
    
    strg_save = sprintf("conjunto_dados_corrompidos_%d.csv", i);
    writematrix(Dados_Corrompido, strg_save);

    strg_save = sprintf("param_%d.csv", i);
    writematrix(e, strg_save);
end

cd ../