%% Código 01a - Gera vetor de 572 (passo = 10) 1112 (passo = 5) pontos similar ao do teste da bobina:
clear all
close all
clc

save_data = 1;

phi(1) = 0;
theta(1) = 0;
it(1) = 1;
k = 2;
passo = 5;

for i=0:passo:180
    for j=6:12:354
        phi(k) = j;
        theta(k) = i; 
        it(k) = k;
        k = k + 1;
    end
end
phi(k) = 180;
theta(k) = 0;
it(k) = k;

phi_Rad = pi/180*phi; 
theta_Rad = pi/180*theta;

r = 1;

x = r.*cos(theta_Rad).*sin(phi_Rad);
y = r.*sin(theta_Rad).*sin(phi_Rad);
z = r.*cos(phi_Rad);

Dados = [x; y; z];

if save_data==1
    Dados_Teoricos = Dados;
    clearvars -except Dados_Teoricos 
    cd ../
    cd 'Dados'
    save Dados_Teoricos.mat
    cd ../
    cd 'Matlab'
end

%% Gera dados corrompidos
% OFFSET => -0.2 ~ 0.2
% Fs => 0.8 ~ 1.2
% Ang => -3 ~ 3 ** transformar de grau para radiano.

Data_Simul = Dados_Teoricos;
t_NLLS = 0;
t_ETS = 0;
for i=1:1000
    offset = (rand(3,1)*0.4)-0.2;
    Escala = (rand(3,1)*0.4)+0.8;
    Ang = (rand(3,1)*6 - 3) * (pi/180);

    rho = Ang(1);
    phi = Ang(2);
    lambda = Ang(3);
    
    e = [Escala; offset; Ang];

    scale = diag(Escala);

    T = [1 0 0; sin(rho) cos(rho) 0; sin(phi)*cos(lambda) sin(lambda) cos(phi)*cos(lambda)];

    for j=1:length(Data_Simul(1,:))
        Ruido(:,j) = 0.006*(rand(3,1));
        Dados_Corrompido(:,j) = scale*T*Data_Simul(:,j) + offset + Ruido(:,j); 
    end
    t_NLLS_start = tic;
    p0 = [1; 1; 1; 0; 0; 0; 0; 0; 0];
    [p] = test2(Dados_Corrompido, p0);
    t_NLLS = t_NLLS + toc(t_NLLS_start);

    t_ETS_start = tic;
    [p1] = test1(Dados_Corrompido);
    t_ETS = t_ETS + toc(t_ETS_start);
end
t_ETS = (t_ETS/1000)*10^3;
t_NLLS = t_NLLS/1000*10^3;

ratio = t_NLLS/t_ETS;

disp("O tempo de execução do ETS foi:")
disp(t_ETS)

disp("O tempo de execução do NLLS foi:")
disp(t_NLLS)

disp("A relação entre os tempos de execução foi (tempo NLLS/tempo ETS):")
disp(ratio)