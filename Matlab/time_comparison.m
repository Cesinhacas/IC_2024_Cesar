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

% cd ..
% cd Dados\
% load Dados_Corrompidos.mat

Data_Simul = Dados_Teoricos;
t_NLLS = 0;
t_NLLSD = 0;
t_ETS = 0;
t_TWOSTEP = 0;
t_TWOSTEP2 = 0;
passos = 0;
steps = 0;
passitos = 0;
exe = 2000;

for i=1:exe
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

    p0 = [1; 1; 1; 0; 0; 0; 0; 0; 0];
   
    [tempo,step,p] = test2(Dados_Corrompido, p0);
    t_NLLS = t_NLLS + tempo;
    steps = steps + step;
    
    ParT.x0 = 0;
    ParT.y0 = 0;
    ParT.z0 = 0;
    ParT.a = 0;
    ParT.b = 0;
    ParT.c = 0;
    ParT.rho = 0;
    ParT.phi = 0;
    ParT.lambda = 0;
    
    ParP.x0 = 0;
    ParP.y0 = 0;
    ParP.z0 = 0;
    ParP.a = 1;
    ParP.b = 1;
    ParP.c = 1;
    ParP.rho = 0;
    ParP.phi = 0;
    ParP.lambda = 0;


    [DataNLLS, ParC, Time, Est, Erros] = NLLS_9Dcalib(ParT, ParP, Dados_Corrompido, 1, 0, 0);
    t_NLLSD = t_NLLSD + Time;
    passitos = passitos + Est.Num_It;

    [tempo1,p1] = test1(Dados_Corrompido);
    t_ETS = t_ETS + tempo1;
    
    noise = 0.006^2*ones(3,1112);
    H = ones(1,1112);

    [tempo,passo,D,h] = TWOSTEP(Dados_Corrompido,H,noise);
    t_TWOSTEP = t_TWOSTEP + tempo;
    passos = passos + passo;
end

t_ETS = (t_ETS/exe)*10^3;
t_NLLS = (t_NLLS/exe)*10^3;
t_TWOSTEP = (t_TWOSTEP/exe)*10^3;
t_NLLSD = (t_NLLSD/exe)*10^3;
passos = passos/exe;
steps = steps/exe;
passitos = passitos/exe;

ratio = t_NLLS/t_ETS;
ratio1 = t_TWOSTEP/t_ETS;

disp("O número de passos do TWOSTEP foi:")
disp(passos)

disp("O número de passos do NLLS foi:")
disp(steps)

disp("O número de passos do NLLSD foi:")
disp(passitos)

disp("O tempo de execução do TWOSTEP em milissegundos foi:")
disp(t_TWOSTEP)

disp("O tempo de execução do ETS em milissegundos foi:")
disp(t_ETS)

disp("O tempo de execução do NLLS em milissegundos foi:")
disp(t_NLLS)

disp("O tempo de execução do NLLSD em milissegundos foi:")
disp(t_NLLSD)

disp("A relação entre os tempos de execução foi (tempo NLLS/tempo ETS):")
disp(ratio)

disp("A relação entre os tempos de execução foi (tempo TWOSTEP/tempo ETS):")
disp(ratio1)