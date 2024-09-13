function [D, h] = test3(B, H, SIGMA_noise)
mx = B(1,:);
my = B(2,:);
mz = B(3,:);

SF = H.*ones(size(mx));

L = [2*B; -(B.^2); -2*B(1,:).*B(2,:); -2*B(1,:).*B(3,:); -2*B(2,:).*B(3,:)]';
sigma = 4*sum(B.*(SIGMA_noise.*B),1)+5*(sum(SIGMA_noise.^2,1))-(sum(SIGMA_noise,1).^2);
Z = sum(B.^2,1).^0.5 - H.^2;
 
for i=1:1:length(mx)
    i_vec = [mx(i) my(i) mz(i)]';
    cov_M = diag(SIGMA_noise(:,i));
    MU(i) = -trace(cov_M);
end

SIGMA = 0;
for i=1:1:length(mx)
    SIGMA = SIGMA + 1/sigma(i);
end
SIGMA = 1/SIGMA;

Z_ = SIGMA*(Z*(1./sigma)');
L_ = SIGMA*(L.*(1./sigma)');
MU_ = SIGMA*(MU*(1./sigma)');

MU_tilde = MU - MU_*ones(1,size(length(mx),2));
L = L - L_.*ones(1,size(L,2));
Z = Z - Z_*ones(1,size(Z,2));

P_tt = zeros(9);
estim = zeros(9,1);

for i=1:length(mx)
    P_tt = P_tt + L(i,:)'*L(i,:)*1/sigma(i);
end
estim = P_tt\(L'*((Z-MU_tilde)'./sigma'));

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
    g = P_tt*(theta - estim) - (1/SIGMA)*(Z_- L_*theta + c'*v - MU_)*(L_'-phi');
    theta = theta - (inv(P_tt)+ 1/SIGMA*(L_ - phi)'*(L_ - phi))\g;
    n_i = (theta - estim)'*(P_tt + (1/SIGMA) * (L_ - phi)'*(L_-phi)) * (theta - estim);
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