function [D, h] = test3(Dados_Corrompido)
mx = Dados_Corrompido(1,:);
my = Dados_Corrompido(2,:);
mz = Dados_Corrompido(3,:);

for i=1:1:length(mx)
    i_vec = [mx(i) my(i) mz(i)];
    sigma(i) = 1/var(i_vec);
    Z(i) = norm(i_vec) - 1;
    S(i,:) = [mx(i)^2 my(i)^2 mz(i)^2 2*mx(i)*my(i) 2*mx(i)*mz(i) 2*my(i)*mz(i)];
    L(:,i) = [2*i_vec -S(i,:)];
    l(i) = sum(L(:,i))/sigma(i);
    z(i) = Z(i)/sigma(i);
end

SIGMA = 1/sum(sigma);
L_ = SIGMA*sum(l);
Z_ = SIGMA*sum(z);

for i=1:1:length(mx)
    L(:,i) = L(:,i) - L_;
    Z(i) = Z(i)-Z_;
end


end