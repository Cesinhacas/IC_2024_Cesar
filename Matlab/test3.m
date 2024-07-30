function [D, h] = test3(Dados_Corrompido)
mx = Dados_Corrompido(1,:);
my = Dados_Corrompido(2,:);
mz = Dados_Corrompido(3,:);

l = [0 0 0 0 0 0 0 0 0];
z = 0;

for i=1:1:length(mx)
    i_vec = [mx(i) my(i) mz(i)];
    sigma(i) = 1/var(i_vec);
    MU(i) = (i_vec(1) + i_vec(2) + i_vec(3))/(3*sigma(i));
    Z(i) = norm(i_vec)^2 - 1;
    L(i,:) = [2*i_vec -mx(i)^2 -my(i)^2 -mz(i)^2 -2*mx(i)*my(i) -2*mx(i)*mz(i) -2*my(i)*mz(i)];
    l = l + L(i,:)./sigma(i);
    z = z + Z(i)/sigma(i);
end

SIGMA = 1/sum(sigma);
L_ = SIGMA*l;
Z_ = SIGMA*z;
MU_ = SIGMA*sum(MU);
covariance = 0;
estim = [0; 0; 0; 0; 0; 0; 0; 0; 0];
for i=1:1:length(mx)
    L(i,:) = L(i,:) - L_;
    Z(i) = Z(i)-Z_;
    MU(i) = MU(i) - MU_;
    covariance = covariance + sigma(i)*(L(i,:)'*L(i,:));
    estim = estim + sigma(i)*(Z(i)-MU(i))*L(i,:)';
end
estim = estim\covariance;

c = [estim(1); estim(2); estim(3)];
E = [estim(4) estim(7) estim(8);
        estim(7) estim(5) estim(9);
        estim(8) estim(9) estim(6)];
    
loop = 1;
n = 1;
theta = estim;
 while loop ==1
     v = inv(eye(3) + E)*c;
     phi = [2*v' -v(1)^2 -v(2)^2 -v(3)^2 -2*v(1)*v(2) -2*v(1)*v(3) -2*v(2)*v(3)];
     g = covariance*(theta - estim) - (1/SIGMA)*(Z_-L_*theta' + c'*v - MU_)*(L_-phi);
     theta = theta - inv(covariance+ SIGMA*(L_ - phi)'*(L_ - phi))*g;
     n_i = (theta - estim)'*(covariance + (1/SIGMA) * (L_ - phi)'*(L_-phi)) * (theta - estim);
     if n_i < n
         loop = 0;
     end
 end
 
c = [estim(1); estim(2); estim(3)];
E = [estim(4) estim(7) estim(8);
        estim(7) estim(5) estim(9);
        estim(8) estim(9) estim(6)];
    
 D = E;
 h = c;


end