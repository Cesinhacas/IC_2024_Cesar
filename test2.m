% Dados_Corrompido é a variável que simula as medidas dos sensores.
% p0 é o "chute inicial" do algoritmo, usualmente, o valor desse chute não
% é de extrema relevância. Sugestão: p0 = [1; 1; 1; 0; 0; 0; 0; 0; 0], onde
% os três primeiros valores são o fator de escala, do 4 ao 6 bias(offset) e
% os três últimos são os ângulos: Rho, Phi e Lambda.
% Retona-se o parâmetro p, um vetor semelhante a p0.


function [p] = test2(Dados_Corrompido, p0)
passo = 1;
loop = 1;
mx = Dados_Corrompido(1,:)';
my = Dados_Corrompido(2,:)';
mz = Dados_Corrompido(3,:)';
Be = ones(1,length(mx))';
while loop == 1
    sx = p0(1);
    sy = p0(2);
    sz = p0(3);
    bx = p0(4);
    by = p0(5);
    bz = p0(6);
    rho = p0(7);
    phi = p0(8);
    lambida = p0(9);
    
    f =(mx-bx).^2/(sx)^2 + (sx*(my-by) - sy*sin(rho)*(mx-bx)).^2/(sx*sy*cos(rho))^2 + (sx*sy*cos(rho)*(mz-bz) - sx*sz*sin(lambida)*(my-by) + sy*sz*(sin(lambida)*sin(rho) - cos(rho)*sin(phi)*cos(lambida))*(mx-bx)).^2/(sx*sy*sz*cos(rho)*cos(phi)*cos(lambida))^2;

    e = Be.^2 - f;
    
    J = (1/2)*(e')*e;
    
     e_std = sqrt((1/(length(e)))*(e'*e));
    
    if passo < 3
        error_vet(passo) = J;
    else
        error_vet(passo) = J;
        delta_J = 100*abs(error_vet(passo)-error_vet(passo-1))/error_vet(passo);
        if delta_J < 0.05
            loop = 0;
        end
    end
    
    
    h1 = (2*(sx*(by - my) - sy*sin(rho)*(bx - mx)).*(by - my))./(sx^2*sy^2*cos(rho)^2) - (2*(sx*(by - my) - sy*sin(rho)*(bx - mx)).^2)./(sx^3*sy^2*cos(rho)^2) - (2*(bx - mx).^2)./sx^3 - (2*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(bx - mx) + sx*sy*cos(rho).*(bz - mz) - sx*sz*sin(lambida)*(by - my)).^2)./(sx^3*sy^2*sz^2*cos(lambida)^2*cos(phi)^2*cos(rho)^2) + (2*(sy*cos(rho).*(bz - mz) - sz*sin(lambida)*(by - my)).*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(bx - mx) + sx*sy*cos(rho).*(bz - mz) - sx*sz*sin(lambida).*(by - my)))./(sx^2*sy^2*sz^2*cos(lambida)^2*cos(phi)^2*cos(rho)^2);
    h2 = -(2*(by - my).*(by*sx*sz*sin(lambida)^2 - my*sx*sz*sin(lambida)^2 + by*sx*sz*cos(lambida)^2*cos(phi)^2 - my*sx*sz*cos(lambida)^2*cos(phi)^2 - bz*sx*sy*cos(rho)*sin(lambida) + mz*sx*sy*cos(rho)*sin(lambida) - bx*sy*sz*sin(lambida)^2*sin(rho) + mx*sy*sz*sin(lambida)^2*sin(rho) - bx*sy*sz*cos(lambida)^2*cos(phi)^2*sin(rho) + mx*sy*sz*cos(lambida)^2*cos(phi)^2*sin(rho) + bx*sy*sz*cos(lambida)*cos(rho)*sin(lambida)*sin(phi) - mx*sy*sz*cos(lambida)*cos(rho)*sin(lambida)*sin(phi)))/(sx*sy^3*sz*cos(lambida)^2*cos(phi)^2*cos(rho)^2);
    h3 = -(2*(bz - mz).*(bz*sx*sy*cos(rho) - by*sx*sz*sin(lambida) - mz*sx*sy*cos(rho) + my*sx*sz*sin(lambida) + bx*sy*sz*sin(lambida)*sin(rho) - mx*sy*sz*sin(lambida)*sin(rho) - bx*sy*sz*cos(lambida)*cos(rho)*sin(phi) + mx*sy*sz*cos(lambida)*cos(rho)*sin(phi)))./(sx*sy*sz^3*cos(lambida)^2*cos(phi)^2*cos(rho));
    h4 = (2*bx - 2*mx)/sx^2 - (2*sin(rho)*(sx*(by - my) - sy*sin(rho)*(bx - mx)))./(sx^2*sy*cos(rho)^2) + (2*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(bx - mx) + sx*sy*cos(rho).*(bz - mz) - sx*sz*sin(lambida)*(by - my)))./(sx^2*sy*sz*cos(lambida)^2*cos(phi)^2*cos(rho)^2);
    h5 = (2.*(sx*(by - my) - sy*sin(rho)*(bx - mx)))./(sx*sy^2*cos(rho)^2) - (2*sin(lambida)*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(bx - mx) + sx*sy*cos(rho).*(bz - mz) - sx*sz*sin(lambida).*(by - my)))./(sx*sy^2*sz*cos(lambida)^2*cos(phi)^2*cos(rho)^2);
    h6 = (2*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(bx - mx) + sx*sy*cos(rho).*(bz - mz) - sx*sz*sin(lambida).*(by - my)))./(sx*sy*sz^2*cos(lambida)^2*cos(phi)^2*cos(rho)); 
    h7 = -(2.*(bx*sy - mx*sy - by*sx*sin(rho) + my*sx*sin(rho)).*(by*sx*sz*sin(lambida)^2 - my*sx*sz*sin(lambida)^2 + by*sx*sz*cos(lambida)^2*cos(phi)^2 - my*sx*sz*cos(lambida)^2*cos(phi)^2 - bz*sx*sy*cos(rho)*sin(lambida) + mz*sx*sy*cos(rho)*sin(lambida) - bx*sy*sz*sin(lambida)^2*sin(rho) + mx*sy*sz*sin(lambida)^2*sin(rho) - bx*sy*sz*cos(lambida)^2*cos(phi)^2*sin(rho) + mx*sy*sz*cos(lambida)^2*cos(phi)^2*sin(rho) + bx*sy*sz*cos(lambida)*cos(rho)*sin(lambida)*sin(phi) - mx*sy*sz*cos(lambida)*cos(rho)*sin(lambida)*sin(phi)))./(sx^2*sy^2*sz*cos(lambida)^2*cos(phi)^2*cos(rho)^3);
    h8 = (2*sin(phi).*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(bx - mx) + sx*sy*cos(rho).*(bz - mz) - sx*sz*sin(lambida).*(by - my)).^2)./(sx^2*sy^2*sz^2*cos(lambida)^2*cos(phi)^3*cos(rho)^2) - (2.*(bx - mx).*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(bx - mx) + sx*sy*cos(rho).*(bz - mz) - sx*sz*sin(lambida).*(by - my)))./(sx^2*sy*sz*cos(lambida)*cos(phi)*cos(rho));
    h9 = (2*sin(lambida)*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(bx - mx) + sx*sy*cos(rho).*(bz - mz) - sx*sz*sin(lambida).*(by - my)).^2)./(sx^2*sy^2*sz^2*cos(lambida)^3*cos(phi)^2*cos(rho)^2) + (2*(sy*sz*(cos(lambida)*sin(rho) + cos(rho)*sin(lambida)*sin(phi)).*(bx - mx) - sx*sz*cos(lambida).*(by - my)).*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(bx - mx) + sx*sy*cos(rho).*(bz - mz) - sx*sz*sin(lambida).*(by - my)))./(sx^2*sy^2*sz^2*cos(lambida)^2*cos(phi)^2*cos(rho)^2);
    H = [h1 h2 h3 h4 h5 h6 h7 h8 h9];
    deltap = inv(H'*H)*H'*e;

    p0 = p0 + deltap;

    passo = passo +1;
end

P = e_std*inv(H'*H);
%disp(P)

p = p0;
end




