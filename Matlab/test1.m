% Dados_Corrompido é a variável que simula as medidas dos sensores.
% 
% Retona-se o parâmetro p, um vetor semelhante a p0, onde os três parâmetros são as estimativas dos fatores de escala, do 4 ao 6 são as estimativas para os offsets (bias) e os três últimos valores são os ângulos Rho, Phi e Lambda.



function [p1] = test1(Dados_Corrompido)

mx = Dados_Corrompido(1,:)';
my = Dados_Corrompido(2,:)';
mz = Dados_Corrompido(3,:)';
vet = ones(1,length(mx))';
Y = - my.^2;

H = [mx.^2 mx.*my mx.*mz my.*mz mz.^2 mx my mz vet];
X = (H'*H)\H'*Y;

psi7 = 2*(X(5)*X(2)^2 - X(2)*X(3)*X(4) + X(3)^2 + X(1)*X(4)^2 - 4*X(1)*X(5));

bx = -(X(4)^2*X(6) + 2*X(3)*X(8) - 4*X(5)*X(6) - X(2)*X(4)*X(8) + 2*X(2)*X(5)*X(7) - X(3)*X(4)*X(7))/psi7;
by = -(X(3)^2*X(7) + 2*X(1)*X(4)*X(8) - 4*X(1)*X(5)*X(7) - X(2)*X(3)*X(8) + 2*X(2)*X(5)*X(6) - X(3)*X(4)*X(6))/psi7;
bz = -(X(2)^2*X(8) - 4*X(1)*X(8) + 2*X(3)*X(6) + 2*X(1)*X(4)*X(7) - X(2)*X(3)*X(7) - X(2)*X(4)*X(6))/psi7;

%m = 1; % magnitude local do campo magnético da terra

psi8 = -(X(2)^2)*(X(8)^2) + 4*X(5)*X(9)*(X(2)^2) - 4*X(9)*X(2)*X(3)*X(4) + 2*X(2)*X(3)*X(7)*X(8) + 2*X(2)*X(4)*X(6)*X(8) - 4*X(5)*X(2)*X(6)*X(7) - (X(3)^2)*(X(7)^2) + 4*X(9)*(X(3)^2) + 2*X(3)*X(4)*X(6)*X(7) - 4*X(3)*X(6)*X(8) - (X(4)^2)*(X(6)^2) + 4*X(1)*X(9)*(X(4)^2) + 4*X(5)*(X(6)^2) + 4*X(1)*X(5)*(X(7)^2) + 4*X(1)*(X(8)^2) - 16*X(1)*X(5)*X(9) - 4*X(1)*X(4)*X(7)*X(8);

divs = 2 * abs(X(5))^3 * (X(5)*(X(2)^2) - X(2)*X(3)*X(4) + (X(3)^2) + X(1)*(X(4)^2) - 4*X(1)*X(5));

sx = -(X(5)^3) *sqrt( psi8*(-X(4)^2 + 4*X(5) ))/(divs);
sy = -(X(5)^3) *sqrt(psi8*(-X(3)^2 + 4*X(1)*X(5)))/(divs);
sz = -(X(5)^3) *sqrt(psi8*(-X(2)^2 + 4*X(1)))/(divs);

rho = -atan( (2*X(2)*X(5) - X(3)*X(4))/(2*X(5)^2*sqrt(-(X(5)*X(2)^2 - X(2)*X(3)*X(4) + X(3)^2 + X(1)*X(4)^2 - 4*X(1)*X(5))/(X(5)^3))));
lambida = -atan((X(4)/X(5))*sqrt(-(X(5)^2*(X(5)*X(2)^2 - X(2)*X(3)*X(4) + X(3)^2 - 4*X(1)*X(5))/(2*X(2)^2*X(4)^2*X(5) - 4*X(2)^2*X(5)^2 - 4*X(2)^2*X(5)^2 - X(2)*X(3)*X(4)^3 + X(1)*X(4)^4 - 8*X(1)*X(4)^2*X(5) + 16*X(1)*X(5)^2))));

n1 = -X(2)^2*X(8)^2 + 4*X(2)^2*X(5)*X(9) - 4*X(2)*X(3)*X(4)*X(9) + 2*X(2)*X(3)*X(7)*X(8) + 2*X(2)*X(4)*X(6)*X(8) - 4*X(2)*X(5)*X(6)*X(7) - X(3)^2*X(7)^2 + 2*X(3)*X(4)*X(6)*X(7) + 4*X(3)^2*X(9) - 4*X(3)*X(6)*X(8) - X(4)^2*X(6)^2 + 4*X(2)*X(4)^2*X(9) - 4*X(1)*X(4)*X(7)*X(8) + 4*X(5)*X(6)^2 + 4*X(1)*X(5)*X(7)^2 + 4*X(1)*X(8)^2 - 16*X(1)*X(5)*X(9);
n2 = X(2)^2*X(5) - X(2)*X(3)*X(4) + X(3)^2 + X(1)*X(4)^2 - 4*X(1)*X(5);
n3 = 2*X(2)^2*X(4)^2*X(5) - 4*X(2)^2*X(5)^2 - X(2)*X(3)*X(4)^3 + X(3)^2*X(4)^2 + X(1)*X(4)^2 - 8*X(1)*X(4)^2*X(5) + 16*X(1)*X(5)^2;
n4 = 4*X(5) - X(4)^2;
n5 = 4*X(1)*X(5) - X(3)^2;
n6 = 4*X(1) - X(2)^2;

phi = -atan((abs(X(5))*sqrt(n1*n5)*(2*X(3) - X(2)*X(4))*sqrt((X(5)*n4*n6)/n3))/(X(5)^2 * sqrt(-n2/X(5)) * sqrt(n1*n6) * sqrt(-(n2*n4)/n3)*sqrt(-(n4*n5)/(X(5)*n2))));
p1 = [sx; sy; sz; bx; by; bz; rho; phi; lambida];
end
