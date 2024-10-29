%% TWOSTEP - calibração
%B deve ser uma matriz 3xN, contendo as medidas do sensor
%H deve ser uma matriz 1xN, contendo o módulo do campo magnético da medida
%Sigma_noise deve ser uma matriz 3xN, sendo cada linha a diagonal da matriz
%de covariância de cada medida

function [Time,passo,D,h] = TWOSTEP(B,H,Sigma_noise)
% Determinando parâmetros
stop = 1e-24;
tam = length(B(1,:));
passo_max = 200;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

tic
% Iniciando variáveis (não necessário em matlab, mas uma boa prática)
z_k = zeros(1,tam);
mu_k = zeros(1,tam);
sigma_k = zeros(1,tam);
L_k = zeros(9,tam);
sigma_bar = 0;

% Iniciando o 'estatistiquês', cálculo do erro das medidas, variância e
% média dos erros
for i=1:1:tam
    i_vec = [B(1,i);B(2,i);B(3,i)];
    z_k(i) = norm(i_vec)^2 - H(i)^2;
    mu_k(i) = -(Sigma_noise(1,i) + Sigma_noise(2,i) + Sigma_noise(3,i));
    sigma_k(i) = 4*i_vec' * diag(Sigma_noise(:,i)) * i_vec + 2*(Sigma_noise(1,i)^2 + Sigma_noise(2,i)^2 + Sigma_noise(3,i)^2);
    sigma_bar = sigma_bar + 1/sigma_k(i);
    L_k(:,i) = [2*i_vec' -B(1,i)^2 -B(2,i)^2 -B(3,i)^2 -2*B(1,i)*B(2,i) -2*B(1,i)*B(3,i) -2*B(2,i)*B(3,i)];
end
sigma_bar = 1/sigma_bar;

% Centralizando os parâmetros
z_bar = 0;
mu_bar = 0;
L_bar = zeros(9,1);

for i=1:1:tam
    z_bar = z_bar + sigma_bar*(z_k(i)/sigma_k(i));
    mu_bar = mu_bar + sigma_bar*(mu_k(i)/sigma_k(i));
    L_bar = L_bar + sigma_bar*L_k(:,i)./sigma_k(i);
end

z_tilde = zeros(1,tam);
mu_tilde = zeros(1,tam);
L_tilde = zeros(9,tam);
for i=1:1:tam
    z_tilde(i) = z_k(i) - z_bar;
    mu_tilde(i) = mu_k(i) - mu_bar;
    L_tilde(:,i) = L_k(:,i) - L_bar;
end

F_tt = zeros(9);
for i=1:1:tam
    F_tt = F_tt + L_tilde(:,i)*(L_tilde(:,i)')./sigma_k(i);
end
P_tt = F_tt\eye(9);

theta = zeros(9,1);
for i=1:1:tam
    theta = theta + ((z_tilde(i)-mu_tilde(i))/sigma_k(i))*L_tilde(:,i);
end
theta = P_tt*theta;

ABC = -(((z_tilde-mu_tilde)./sigma_k)*L_tilde')';
passo = 0;
loop = 1;

while(loop ==1)
    if(passo ~= 0)
        theta = theta_np1;
    end
    c = [theta(1); theta(2); theta(3)];
    
    E = [theta(4) theta(7) theta(8);
            theta(7) theta(5) theta(9);
            theta(8) theta(9) theta(6)];
    E_inv = (eye(3)+E)\eye(3);

    tmp = (E_inv*c)*(E_inv*c)';

    dJdThetap_tilde = ABC + F_tt*theta;

    dbsqdtheta_p=[2*(E_inv*c); -diag(tmp);-2*tmp(1,2); -2*tmp(1,3); -2*tmp(2,3)]';

    dJdThetap_bar = (-(1/sigma_bar)*(L_bar' - dbsqdtheta_p)*(z_bar - L_bar'*theta + c'*(E_inv*c) - mu_bar))';

    dJdTheta = dJdThetap_tilde + dJdThetap_bar;
    
    
    F_tt_bar = ((L_bar'-dbsqdtheta_p)'*(L_bar'-dbsqdtheta_p))/sigma_bar;
    
    theta_np1 = theta - (F_tt + F_tt_bar)\dJdTheta;
    
    TS_erro = (theta_np1 - theta)'*(F_tt + F_tt_bar)*(theta_np1 - theta);
        
    if(passo>passo_max)
        loop = 0;
    end
    if(TS_erro < stop)
        loop = 0;
    end
    passo = passo + 1;
end
[U,S] = eig(E);
W = -eye(3)+(eye(3)+S).^0.5;

D = U*W*U';
h = (eye(3)+D)\c;
Time = toc;
end