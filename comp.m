function [p, p2] = comp(Dados_Corrompido, p0, p1)
passo = 0;
mx = Dados_Corrompido(1,:);
my = Dados_Corrompido(2,:);
mz = Dados_Corrompido(3,:);
Be = ones(1,length(mx));

vx = Dados_Corrompido(1,:);
vy = Dados_Corrompido(2,:);
vz = Dados_Corrompido(3,:);
sf = Be;
while passo<4
    
    xo = p1(1);
    yo = p1(2);
    zo = p1(3);
    a  = p1(4);
    b  = p1(5);
    c  = p1(6);
    ro = p1(7);
    fi = p1(8);
    la = p1(9);
    
    r = ((vx-xo).^2/a^2+(-b*sin(ro).*(vx-xo)+a.*(vy-yo)).^2/a^2/b^2/cos(ro)^2+(b*c*(sin(ro)*sin(la)-cos(ro)*sin(fi)*cos(la)).*(vx-xo)-a*c*sin(la).*(vy-yo)+a*b*cos(ro).*(vz-zo)).^2/a^2/b^2/c^2/cos(ro)^2/cos(fi)^2/cos(la)^2);
    r = r';
    e1  = (sf.^2)' - r;
    
    B1 = (2*sin(ro)*(a*(vy - yo) - b*sin(ro)*(vx - xo)))/(a^2*b*cos(ro)^2) - (2*vx - 2*xo)/a^2 - (2*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi))*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi))*(vx - xo) + a*b*cos(ro)*(vz - zo) - a*c*sin(la)*(vy - yo)))/(a^2*b*c*cos(fi)^2*cos(la)^2*cos(ro)^2);
    B2 = (2*sin(la)*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi))*(vx - xo) + a*b*cos(ro)*(vz - zo) - a*c*sin(la)*(vy - yo)))/(a*b^2*c*cos(fi)^2*cos(la)^2*cos(ro)^2) - (2*(a*(vy - yo) - b*sin(ro)*(vx - xo)))/(a*b^2*cos(ro)^2);
    B3 = -(2*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi))*(vx - xo) + a*b*cos(ro)*(vz - zo) - a*c*sin(la)*(vy - yo)))/(a*b*c^2*cos(fi)^2*cos(la)^2*cos(ro));
    B4 = (2*(a*(vy - yo) - b*sin(ro)*(vx - xo)).*(vy - yo))./(a^2*b^2*cos(ro)^2) - (2*(a*(vy - yo) - b*sin(ro)*(vx - xo)).^2)./(a^3*b^2*cos(ro)^2) - (2*(vx - xo).^2)./a^3 - (2*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi)).*(vx - xo) + a*b*cos(ro).*(vz - zo) - a*c*sin(la)*(vy - yo)).^2)./(a^3*b^2*c^2*cos(fi)^2*cos(la)^2*cos(ro)^2) + (2*(b*cos(ro).*(vz - zo) - c*sin(la)*(vy - yo)).*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi)).*(vx - xo) + a*b*cos(ro).*(vz - zo) - a*c*sin(la).*(vy - yo)))./(a^2*b^2*c^2*cos(fi)^2*cos(la)^2*cos(ro)^2);
    B5 = -(2*(vy - yo).*(a*c*vy*sin(la)^2 - a*c*yo*sin(la)^2 - a*b*vz*cos(ro)*sin(la) + a*b*zo*cos(ro)*sin(la) - b*c*vx*sin(la)^2*sin(ro) + b*c*xo*sin(la)^2*sin(ro) + a*c*vy*cos(fi)^2*cos(la)^2 - a*c*yo*cos(fi)^2*cos(la)^2 - b*c*vx*cos(fi)^2*cos(la)^2*sin(ro) + b*c*xo*cos(fi)^2*cos(la)^2*sin(ro) + b*c*vx*cos(la)*cos(ro)*sin(fi)*sin(la) - b*c*xo*cos(la)*cos(ro)*sin(fi)*sin(la)))/(a*b^3*c*cos(fi)^2*cos(la)^2*cos(ro)^2);
    B6 = -(2*(vz - zo).*(a*b*vz*cos(ro) - a*b*zo*cos(ro) - a*c*vy*sin(la) + a*c*yo*sin(la) + b*c*vx*sin(la)*sin(ro) - b*c*xo*sin(la)*sin(ro) - b*c*vx*cos(la)*cos(ro)*sin(fi) + b*c*xo*cos(la)*cos(ro)*sin(fi)))./(a*b*c^3*cos(fi)^2*cos(la)^2*cos(ro));
    B7 = -(2*(b*vx - b*xo - a*vy*sin(ro) + a*yo*sin(ro)).*(a*c*vy*sin(la)^2 - a*c*yo*sin(la)^2 - a*b*vz*cos(ro)*sin(la) + a*b*zo*cos(ro)*sin(la) - b*c*vx*sin(la)^2*sin(ro) + b*c*xo*sin(la)^2*sin(ro) + a*c*vy*cos(fi)^2*cos(la)^2 - a*c*yo*cos(fi)^2*cos(la)^2 - b*c*vx*cos(fi)^2*cos(la)^2*sin(ro) + b*c*xo*cos(fi)^2*cos(la)^2*sin(ro) + b*c*vx*cos(la)*cos(ro)*sin(fi)*sin(la) - b*c*xo*cos(la)*cos(ro)*sin(fi)*sin(la)))/(a^2*b^2*c*cos(fi)^2*cos(la)^2*cos(ro)^3);
    B8 = (2*sin(fi)*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi)).*(vx - xo) + a*b*cos(ro).*(vz - zo) - a*c*sin(la).*(vy - yo)).^2)./(a^2*b^2*c^2*cos(fi)^3*cos(la)^2*cos(ro)^2) - (2.*(vx - xo).*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi)).*(vx - xo) + a*b*cos(ro).*(vz - zo) - a*c*sin(la).*(vy - yo)))./(a^2*b*c*cos(fi)*cos(la)*cos(ro));
    B9 = (2*(b*c*(cos(la)*sin(ro) + cos(ro)*sin(fi)*sin(la)).*(vx - xo) - a*c*cos(la).*(vy - yo)).*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi)).*(vx - xo) + a*b*cos(ro).*(vz - zo) - a*c*sin(la).*(vy - yo)))./(a^2*b^2*c^2*cos(fi)^2*cos(la)^2*cos(ro)^2) + (2*sin(la)*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi)).*(vx - xo) + a*b*cos(ro).*(vz - zo) - a*c*sin(la).*(vy - yo)).^2)./(a^2*b^2*c^2*cos(fi)^2*cos(la)^3*cos(ro)^2);                                                                                                                                                                                                                           
    B = [B1' B2' B3' B4' B5' B6' B7' B8' B9']';
    
    q = inv(B*B')*B*e1;
    
    p1 = p1 + q;
    
    bx = p0(1);
    by = p0(2);
    bz = p0(3);
    sx = p0(4);
    sy = p0(5);
    sz = p0(6);
    rho = p0(7);
    phi = p0(8);
    lambida = p0(9);
    
    f = (mx-bx).^2/(sx)^2 + (sx*(my-by) - sy*sin(rho)*(mx-bx)).^2/(sx*sy*cos(rho))^2 + (sx*sy*cos(rho)*(mz-bz) - sx*sz*sin(lambida)*(my-by) + sy*sz*(sin(lambida)*sin(rho) - cos(rho)*sin(phi)*cos(lambida))*(mx-bx)).^2/(sx*sy*sz*cos(rho)*cos(phi)*cos(lambida))^2;
    f = f';
    
    e = (Be.^2)' - f;
    
    h1 = (2*sin(rho)*(sx*(my - by) - sy*sin(rho)*(mx - bx)))/(sx^2*sy*cos(rho)^2) - (2*mx - 2*bx)/sx^2 - (2*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(mx - bx) + sx*sy*cos(rho)*(mz - bz) - sx*sz*sin(lambida)*(my - by)))/(sx^2*sy*sz*cos(phi)^2*cos(lambida)^2*cos(rho)^2);
    h2 = (2*sin(lambida)*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(mx - bx) + sx*sy*cos(rho)*(mz - bz) - sx*sz*sin(lambida)*(my - by)))/(sx*sy^2*sz*cos(phi)^2*cos(lambida)^2*cos(rho)^2) - (2*(sx*(my - by) - sy*sin(rho)*(mx - bx)))/(sx*sy^2*cos(rho)^2);
    h3 = -(2*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi))*(mx - bx) + sx*sy*cos(rho)*(mz - bz) - sx*sz*sin(lambida)*(my - by)))/(sx*sy*sz^2*cos(phi)^2*cos(lambida)^2*cos(rho));
    h4 = (2*(sx*(my - by) - sy*sin(rho)*(mx - bx)).*(my - by))./(sx^2*sy^2*cos(rho)^2) - (2*(sx*(my - by) - sy*sin(rho)*(mx - bx)).^2)./(sx^3*sy^2*cos(rho)^2) - (2*(mx - bx).^2)./sx^3 - (2*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(mx - bx) + sx*sy*cos(rho).*(mz - bz) - sx*sz*sin(lambida)*(my - by)).^2)./(sx^3*sy^2*sz^2*cos(phi)^2*cos(lambida)^2*cos(rho)^2) + (2*(sy*cos(rho).*(mz - bz) - sz*sin(lambida)*(my - by)).*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(mx - bx) + sx*sy*cos(rho).*(mz - bz) - sx*sz*sin(lambida).*(my - by)))./(sx^2*sy^2*sz^2*cos(phi)^2*cos(lambida)^2*cos(rho)^2);
    h5 = (2*(sx*(my - by) - sy*sin(rho)*(mx - bx)).*(my - by))./(sx^2*sy^2*cos(rho)^2) - (2*(sx*(my - by) - sy*sin(rho)*(mx - bx)).^2)./(sx^3*sy^2*cos(rho)^2) - (2*(mx - bx).^2)./sx^3 - (2*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(mx - bx) + sx*sy*cos(rho).*(mz - bz) - sx*sz*sin(lambida)*(my - by)).^2)./(sx^3*sy^2*sz^2*cos(phi)^2*cos(lambida)^2*cos(rho)^2) + (2*(sy*cos(rho).*(mz - bz) - sz*sin(lambida)*(my - by)).*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(mx - bx) + sx*sy*cos(rho).*(mz - bz) - sx*sz*sin(lambida).*(my - by)))./(sx^2*sy^2*sz^2*cos(phi)^2*cos(lambida)^2*cos(rho)^2);
    h6 = -(2*(mz - bz).*(sx*sy*mz*cos(rho) - sx*sy*bz*cos(rho) - sx*sz*my*sin(lambida) + sx*sz*by*sin(lambida) + sy*sz*mx*sin(lambida)*sin(rho) - sy*sz*bx*sin(lambida)*sin(rho) - sy*sz*mx*cos(lambida)*cos(rho)*sin(phi) + sy*sz*bx*cos(lambida)*cos(rho)*sin(phi)))./(sx*sy*sz^3*cos(phi)^2*cos(lambida)^2*cos(rho));
    h7 = -(2*(sy*mx - sy*bx - sx*my*sin(rho) + sx*by*sin(rho)).*(sx*sz*my*sin(lambida)^2 - sx*sz*by*sin(lambida)^2 - sx*sy*mz*cos(rho)*sin(lambida) + sx*sy*bz*cos(rho)*sin(lambida) - sy*sz*mx*sin(lambida)^2*sin(rho) + sy*sz*bx*sin(lambida)^2*sin(rho) + sx*sz*my*cos(phi)^2*cos(lambida)^2 - sx*sz*by*cos(phi)^2*cos(lambida)^2 - sy*sz*mx*cos(phi)^2*cos(lambida)^2*sin(rho) + sy*sz*bx*cos(phi)^2*cos(lambida)^2*sin(rho) + sy*sz*mx*cos(lambida)*cos(rho)*sin(phi)*sin(lambida) - sy*sz*bx*cos(lambida)*cos(rho)*sin(phi)*sin(lambida)))/(sx^2*sy^2*sz*cos(phi)^2*cos(lambida)^2*cos(rho)^3);
    h8 = (2*sin(phi)*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(mx - bx) + sx*sy*cos(rho).*(mz - bz) - sx*sz*sin(lambida).*(my - by)).^2)./(sx^2*sy^2*sz^2*cos(phi)^3*cos(lambida)^2*cos(rho)^2) - (2.*(mx - bx).*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(mx - bx) + sx*sy*cos(rho).*(mz - bz) - sx*sz*sin(lambida).*(my - by)))./(sx^2*sy*sz*cos(phi)*cos(lambida)*cos(rho));
    h9 = (2*(sy*sz*(cos(lambida)*sin(rho) + cos(rho)*sin(phi)*sin(lambida)).*(mx - bx) - sx*sz*cos(lambida).*(my - by)).*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(mx - bx) + sx*sy*cos(rho).*(mz - bz) - sx*sz*sin(lambida).*(my - by)))./(sx^2*sy^2*sz^2*cos(phi)^2*cos(lambida)^2*cos(rho)^2) + (2*sin(lambida)*(sy*sz*(sin(lambida)*sin(rho) - cos(lambida)*cos(rho)*sin(phi)).*(mx - bx) + sx*sy*cos(rho).*(mz - bz) - sx*sz*sin(lambida).*(my - by)).^2)./(sx^2*sy^2*sz^2*cos(phi)^2*cos(lambida)^3*cos(rho)^2);                                                                                                                                                                                                                           
     
    H = [h1' h2' h3' h4' h5' h6' h7' h8' h9']';
    deltap = inv(H*H')*H*e;

    p0 = p0 + deltap;

    passo = passo +1;
end

p = p0;
p2 = p1;
end