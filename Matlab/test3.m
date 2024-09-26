function [D, h] = test3(B, H, SIGMA_noise)
mx = B(1,:);
my = B(2,:);
mz = B(3,:);

L = [2*B; -(B.^2); -2*B(1,:).*B(2,:); -2*B(1,:).*B(3,:); -2*B(2,:).*B(3,:)];
sigma = 4*sum(B.*(SIGMA_noise.*B),1)+5*(sum(SIGMA_noise.^2,1))-(sum(SIGMA_noise,1).^2);
 
for i=1:1:length(mx)
    i_vec = [mx(i) my(i) mz(i)]';
    Z(i) = norm(i_vec)^2 - H(1)^2;
    cov_M = diag(SIGMA_noise(:,i));
    MU(i) = -trace(cov_M);
end

SIGMA = 0;
for i=1:1:length(mx)
    SIGMA = SIGMA + 1/sigma(i);
end
SIGMA = 1/SIGMA;

Z_ = SIGMA*(Z*(1./sigma)');
L_ = SIGMA*(L*(1./sigma)');
MU_ = SIGMA*(MU*(1./sigma)');

MU_tilde = MU - MU_*ones(1,size(length(mx),2));
L = L - L_.*ones(1,size(L,2));
Z = Z - Z_*ones(1,size(Z,2));

F_tt = zeros(9);
for i=1:1:length(mx)
    F_tt = F_tt + L(:,i)*(L(:,i)')./sigma(i);
end
P_tt_inv = F_tt\eye(9);

estim = P_tt_inv*(L*((Z-MU_tilde)'./sigma'));
    
loop = 1;
n = 1e-24;
passo = 0;

ABC = -(((Z-MU)./sigma)*L')';
 while loop ==1
     
    c = [estim(1); estim(2); estim(3)];
    E = [estim(4) estim(7) estim(8);
        estim(7) estim(5) estim(9);
        estim(8) estim(9) estim(6)];
    
    tmp = ((eye(3) +E)\c)*((eye(3) + E)\c)';
    dbsqdtheta_p = [2*((eye(3) + E)\c); -diag(tmp);...
        -2*tmp(1,2); -2*tmp(1,3); -2*tmp(2,3)]';
    
    djdTheta_tilde = ABC + F_tt*estim;
    dJdTheta_bar = (-(1/SIGMA)*(L_' - dbsqdtheta_p)*...
        (Z_ - L_'*estim + c'*((eye(3) + E)\c) - MU_))';
    djdtheta = djdTheta_tilde + dJdTheta_bar;
    
    P_tt_ = ((L_'-dbsqdtheta_p)'*(L_'-dbsqdtheta_p))/MU_;
    
    theta_estim = estim - (F_tt+P_tt_)\djdtheta;
    
    n_i = (theta_estim-estim)'*(F_tt+P_tt_)*(theta_estim-estim);
    
    estim = theta_estim;
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