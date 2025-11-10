function [x_prop, PT_prop, i_out] = propagador_FK(u_gyro, Dt, PT_est, x_est, Q, i_in)
%#codegen

i_out = i_in + 1;

% ================== Propagação ==================
% ------ Propagação do Estado
% São medidos os Girômetros e sua saída subtraida
% do bias é integrada no período de propagação

q_est = x_est(1:4,1);
b_est = x_est(5:7,1);


% Matriz de atualização do quaternion
Th = u_gyro * Dt;

Omega4 = [ 0     Th(3) -Th(2)  Th(1);
	  -Th(3)  0     Th(1)  Th(2); 
      Th(2) -Th(1)  0     Th(3);
     -Th(1) -Th(2) -Th(3)  0   ];

M = eye(4) * cos(norm(Th)/2) + Omega4 * sin(norm(Th)/2) / norm(Th);
q_prop = M * q_est; 

b_prop = b_est;

x_prop = [q_prop ; b_prop];

% Matriz Constante // A ser executado fora dessa função
GT = [ -1/2*eye(3) zeros(3,3); zeros(3,3) eye(3)];
QT = GT * Q * GT';

% ---------------------

Omega3_prop = [ 0     q_prop(3) -q_prop(2);
	  -q_prop(3)  0     q_prop(1); 
      q_prop(2) -q_prop(1)  0   ];

A_prop = (q_prop(4)^2 - norm(q_prop(1:3,1))^2)*eye(3) + 2*q_prop(1:3,1)*q_prop(1:3,1)' ... 
      + 2*q_prop(4)*Omega3_prop;
  
Omega3_est = [ 0     q_est(3) -q_est(2);
	  -q_est(3)  0     q_est(1); 
      q_est(2) -q_est(1)  0   ];  
  
A_est = (q_est(4)^2 - norm(q_est(1:3,1))^2)*eye(3) + 2*q_est(1:3,1)*q_est(1:3,1)' ... 
      + 2*q_est(4)*Omega3_est;
  
% ------ Propagação da Matriz de Covariância
L = A_prop * A_est';
KK = -1/2 * (L + eye(3)) * Dt/2;  % Integral Trapézio
PhiT = [L KK; zeros(3,3) eye(3)];
SiG = (PhiT * QT * PhiT' + QT) * Dt/2; % Integral Trapézio
PT_prop = PhiT * PT_est * PhiT' + SiG;