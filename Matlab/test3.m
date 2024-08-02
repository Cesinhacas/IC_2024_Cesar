function [D, h] = test3(Dados_Corrompido)
mx = Dados_Corrompido(1,:);
my = Dados_Corrompido(2,:);
mz = Dados_Corrompido(3,:);

for i=1:1:length(mx)
    i_vec = [mx(i) my(i) mz(i)]';
    MU(i) = sum(var([mx(i) 0 0; 0 my(i) 0; 0 0 mz(i)]));
    sigma_m(i,:) = var([mx(i) 0 0; 0 my(i) 0; 0 0 mz(i)]);
    sigma(i) =  1/(4*i_vec'*diag(sigma_m(i,:))*i_vec + 2*trace(diag(sigma_m(i,:).^2)));
    Z(i) = norm(i_vec)^2 - 1;
    L(i,:) = [2*i_vec' -mx(i)^2 -my(i)^2 -mz(i)^2 -2*mx(i)*my(i) -2*mx(i)*mz(i) -2*my(i)*mz(i)];
end

Z_ =0;
L_ = [0 0 0 0 0 0 0 0 0];
MU_ =0;
SIGMA = 1/sum(sigma);

for i=1:1:length(mx)
    Z_ = Z_ + SIGMA*sum(Z(i)/sigma(i));
    L_ = L_ + SIGMA*sum(L(i,:)/sigma(i));
    MU_ = MU_ + SIGMA*(MU(i)/sigma(i));
end



for i=1:1:length(mx)
    MU(i) = MU(i)-MU_;
    Z(i) = Z(i) - Z_;
    L(i,:) = L(i,:) - L_;
end
covariance = zeros(9);
estim = zeros(9,1);
for i=1:1:length(mx)
    estim = estim + sigma(i)*(Z(i) - MU(i))*L(i,:)';
    covariance = covariance + L(i,:)'*L(i,:).*sigma(i);
end

estim = covariance\estim;

c = [estim(1); estim(2); estim(3)];
E = [estim(4) estim(7) estim(8);
        estim(7) estim(5) estim(9);
        estim(8) estim(9) estim(6)];
    
loop = 1;
n = 1e-24;
theta = estim;
passo = 0;


 while loop ==1
     v = (eye(3) + E)\c;
     phi = [2*v' -v(1)^2 -v(2)^2 -v(3)^2 -2*v(1)*v(2) -2*v(1)*v(3) -2*v(2)*v(3)];
     g = covariance*(theta - estim) - (1/SIGMA)*(Z_-L_*theta + c'*v - MU_)*(L_'-phi');
     theta = theta - (inv(covariance)+ 1/SIGMA*(L_ - phi)'*(L_ - phi))\g;
     n_i = (theta - estim)'*(covariance + (1/SIGMA) * (L_ - phi)'*(L_-phi)) * (theta - estim);
     estim = theta;
     if n_i < n
         loop = 0;
     end
     passo = passo + 1;
 end
 
c = [estim(1); estim(2); estim(3)];
E = [estim(4) estim(7) estim(8);
        estim(7) estim(5) estim(9);
        estim(8) estim(9) estim(6)];
    
[U,S,V] = svd(E);
W = diag([-1+sqrt(1+S(1,1)) -1+sqrt(1+S(2,2)) -1+sqrt(1+S(3,3))]);
D = U*W*V';
h = (eye(3)+D)\c;


end