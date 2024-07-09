clc
clear all
Ymed = [1.03 1.95 2.4 4.03];
dp = [(0.05)^2 (0.06)^2 (0.7)^2 (0.08)^2]; %desvio padrao de cada 

Med = [1 2 3 4];

H = [1 1; 
        2 1;
        3 1;
        4 1;] ; %Vetores compostos pelo numero da medida e o numero 1 (matriz H)
P = (H'*H)^-1;
 
Yest1 = P*H'*Ymed';
disp('a estimação para os parâmetros é:')
disp(Yest1)
 
W = [1/dp(1) 0 0 0;
         0  1/dp(2) 0 0;
        0 0 1/dp(3) 0;
        0 0 0 1/dp(4)];
P2 = (H'*W*H)^-1;
Yest2 = P2*H'*W*Ymed';
disp('a estimação para os parâmetros é:')
disp(Yest2)