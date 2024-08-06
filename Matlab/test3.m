function [D, h] = test3(B)
mx = B(1,:);
my = B(2,:);
mz = B(3,:);

L = [2*B; -(B.^2); -2*B(1,:).*B(2,:); -2*B(1,:).*B(3,:); -2*B(2,:).*B(3,:)];


for i=1:1:length(mx)
    i_vec = [mx(i) my(i) mz(i)]';
    cov_M = [0.006^2 0 0;0 0.006^2 0;0 0 0.006^2];
    MU(i) = -trace(cov_M);
    sigma(i) = (4*0.006^2*(i_vec')*i_vec + 6*(0.006^4));
    Z(i) = norm(i_vec)^2 - 1;
    L(i,:) = [2*i_vec' -mx(i)^2 -my(i)^2 -mz(i)^2 -2*mx(i)*my(i) -2*mx(i)*mz(i) -2*my(i)*mz(i)];
end

SIGMA = 0;
for i=1:1:length(mx)
    SIGMA = SIGMA + 1/sigma(i);
end
SIGMA = 1/SIGMA;

Z_ =0;
L_ = [0 0 0 0 0 0 0 0 0];
MU_ =0;

for i=1:1:length(mx)
    Z_ = Z_ + SIGMA*Z(i)/sigma(i);
    L_ = L_ + SIGMA*L(i,:)/sigma(i);
    MU_ = MU_ + SIGMA*(MU(i)/sigma(i));
end

for i=1:1:length(mx)
    MU(i) = MU(i) - MU_;
    Z(i) = Z(i) - Z_;
    L(i,:) = L(i,:) - L_;
end

covariance = zeros(9);
estim = zeros(9,1);
for i=1:1:length(mx)
    estim = estim + (1/sigma(i))*(Z(i) - MU(i))*L(i,:)';
    covariance = covariance + L(i,:)'*L(i,:)./sigma(i);
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

    c = [estim(1); estim(2); estim(3)];
    E = [estim(4) estim(7) estim(8);
    estim(7) estim(5) estim(9);
    estim(8) estim(9) estim(6)];
    
    if passo > 200
        loop = 0;
    end
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