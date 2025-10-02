% Dados_Corrompido é a variável que simula as medidas dos sensores.
% p0 é o "chute inicial" do algoritmo, usualmente, o valor desse chute não
% é de extrema relevância. Sugestão: p0 = [1; 1; 1; 0; 0; 0; 0; 0; 0], onde
% os três primeiros valores são o fator de escala, do 4 ao 6 bias(offset) e
% os três últimos são os ângulos: Rho, Phi e Lambda.
% Be é o vetor com o módulo do campo de cada medida.
% Retona-se o parâmetro p, um vetor semelhante a p0.


function [Time, passo, p, fisher] = test2(Dados_Corrompido, p0, Be)
passo = 1;
loop = 1;
mx = Dados_Corrompido(1,:)';
my = Dados_Corrompido(2,:)';
mz = Dados_Corrompido(3,:)';

tic;
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

    sin_rho = sin(rho);
    cos_rho = cos(rho);
    sin_phi = sin(phi);
    cos_phi = cos(phi);
    sin_lambida = sin(lambida);
    cos_lambida = cos(lambida);
    
    f = (mx-bx).^2/(sx)^2 + (sx*(my-by) - sy*sin_rho*(mx-bx)).^2/(sx*sy*cos_rho)^2 + (sx*sy*cos_rho*(mz-bz) - sx*sz*sin_lambida*(my-by) + sy*sz*(sin_lambida*sin_rho - cos_rho*sin_phi*cos_lambida)*(mx-bx)).^2/(sx*sy*sz*cos_rho*cos_phi*cos_lambida)^2;

    e = Be.^2 - f;
    
    J = (1/2)*(e')*e;
    
     e_std = sqrt((1/(length(e)))*(e'*e));
    
    if passo < 3
        error_ant = J;
    else
        delta_J = 100*abs(J-error_ant)/J;
        if delta_J < 0.1
            loop = 0;
        end
        error_ant = J;
    end

    h1 = (2*(sx*(by - my) - sy*sin_rho*(bx - mx)).*(by - my))./(sx^2*sy^2*cos_rho^2) - (2*(sx*(by - my) - sy*sin_rho*(bx - mx)).^2)./(sx^3*sy^2*cos_rho^2) - (2*(bx - mx).^2)./sx^3 - (2*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi).*(bx - mx) + sx*sy*cos_rho.*(bz - mz) - sx*sz*sin_lambida*(by - my)).^2)./(sx^3*sy^2*sz^2*cos_lambida^2*cos_phi^2*cos_rho^2) + (2*(sy*cos_rho.*(bz - mz) - sz*sin_lambida*(by - my)).*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi).*(bx - mx) + sx*sy*cos_rho.*(bz - mz) - sx*sz*sin_lambida.*(by - my)))./(sx^2*sy^2*sz^2*cos_lambida^2*cos_phi^2*cos_rho^2);
    h2 = -(2*(by - my).*(by*sx*sz*sin_lambida^2 - my*sx*sz*sin_lambida^2 + by*sx*sz*cos_lambida^2*cos_phi^2 - my*sx*sz*cos_lambida^2*cos_phi^2 - bz*sx*sy*cos_rho*sin_lambida + mz*sx*sy*cos_rho*sin_lambida - bx*sy*sz*sin_lambida^2*sin_rho + mx*sy*sz*sin_lambida^2*sin_rho - bx*sy*sz*cos_lambida^2*cos_phi^2*sin_rho + mx*sy*sz*cos_lambida^2*cos_phi^2*sin_rho + bx*sy*sz*cos_lambida*cos_rho*sin_lambida*sin_phi - mx*sy*sz*cos_lambida*cos_rho*sin_lambida*sin_phi))/(sx*sy^3*sz*cos_lambida^2*cos_phi^2*cos_rho^2);
    h3 = -(2*(bz - mz).*(bz*sx*sy*cos_rho - by*sx*sz*sin_lambida - mz*sx*sy*cos_rho + my*sx*sz*sin_lambida + bx*sy*sz*sin_lambida*sin_rho - mx*sy*sz*sin_lambida*sin_rho - bx*sy*sz*cos_lambida*cos_rho*sin_phi + mx*sy*sz*cos_lambida*cos_rho*sin_phi))./(sx*sy*sz^3*cos_lambida^2*cos_phi^2*cos_rho);
    h4 = (2*bx - 2*mx)/sx^2 - (2*sin_rho*(sx*(by - my) - sy*sin_rho*(bx - mx)))./(sx^2*sy*cos_rho^2) + (2*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi).*(bx - mx) + sx*sy*cos_rho.*(bz - mz) - sx*sz*sin_lambida*(by - my)))./(sx^2*sy*sz*cos_lambida^2*cos_phi^2*cos_rho^2);
    h5 = (2.*(sx*(by - my) - sy*sin_rho*(bx - mx)))./(sx*sy^2*cos_rho^2) - (2*sin_lambida*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi).*(bx - mx) + sx*sy*cos_rho.*(bz - mz) - sx*sz*sin_lambida.*(by - my)))./(sx*sy^2*sz*cos_lambida^2*cos_phi^2*cos_rho^2);
    h6 = (2*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi).*(bx - mx) + sx*sy*cos_rho.*(bz - mz) - sx*sz*sin_lambida.*(by - my)))./(sx*sy*sz^2*cos_lambida^2*cos_phi^2*cos_rho); 
    h7 = -(2.*(bx*sy - mx*sy - by*sx*sin_rho + my*sx*sin_rho).*(by*sx*sz*sin_lambida^2 - my*sx*sz*sin_lambida^2 + by*sx*sz*cos_lambida^2*cos_phi^2 - my*sx*sz*cos_lambida^2*cos_phi^2 - bz*sx*sy*cos_rho*sin_lambida + mz*sx*sy*cos_rho*sin_lambida - bx*sy*sz*sin_lambida^2*sin_rho + mx*sy*sz*sin_lambida^2*sin_rho - bx*sy*sz*cos_lambida^2*cos_phi^2*sin_rho + mx*sy*sz*cos_lambida^2*cos_phi^2*sin_rho + bx*sy*sz*cos_lambida*cos_rho*sin_lambida*sin_phi - mx*sy*sz*cos_lambida*cos_rho*sin_lambida*sin_phi))./(sx^2*sy^2*sz*cos_lambida^2*cos_phi^2*cos_rho^3);
    h8 = (2*sin_phi.*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi).*(bx - mx) + sx*sy*cos_rho.*(bz - mz) - sx*sz*sin_lambida.*(by - my)).^2)./(sx^2*sy^2*sz^2*cos_lambida^2*cos_phi^3*cos_rho^2) - (2.*(bx - mx).*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi).*(bx - mx) + sx*sy*cos_rho.*(bz - mz) - sx*sz*sin_lambida.*(by - my)))./(sx^2*sy*sz*cos_lambida*cos_phi*cos_rho);
    h9 = (2*sin_lambida*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi).*(bx - mx) + sx*sy*cos_rho.*(bz - mz) - sx*sz*sin_lambida.*(by - my)).^2)./(sx^2*sy^2*sz^2*cos_lambida^3*cos_phi^2*cos_rho^2) + (2*(sy*sz*(cos_lambida*sin_rho + cos_rho*sin_lambida*sin_phi).*(bx - mx) - sx*sz*cos_lambida.*(by - my)).*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi).*(bx - mx) + sx*sy*cos_rho.*(bz - mz) - sx*sz*sin_lambida.*(by - my)))./(sx^2*sy^2*sz^2*cos_lambida^2*cos_phi^2*cos_rho^2);
    H = [h1 h2 h3 h4 h5 h6 h7 h8 h9];
    deltap = ((H'*H)\eye(9))*H'*e;

    p0 = p0 + deltap;

    passo = passo +1;
end
p = p0;
Time = toc;
passo = passo -1;

P = e_std*inv(H'*H);
fisher = diag(P).^(1/2);
% disp(P)
end