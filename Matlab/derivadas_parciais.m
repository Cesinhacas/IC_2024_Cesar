

syms sx sy sz bx y0 z0 rho lambida phi mx my mz

f = ((mx-bx)^2/(sx)^2 + (sx*(my-y0) - sy*sin(rho)*(mx-bx))^2/(sx*sy*cos(rho))^2+(sx*sy*cos(rho)*(mz-z0) - sx*sz*sin(lambida)*(my-y0) + sy*sz*(sin(lambida)*sin(rho) - cos(rho)*sin(phi)*cos(lambida))*(mx-bx))^2/(sx*sy*sz*cos(rho)*cos(phi)*cos(lambida))^2);
t1 = diff(f, sx)
h2 = diff(f, sy)
h3 = diff(f, sz)
h4 = diff(f, bx)
h5 = diff(f, y0)
h6 = diff(f, z0)
h7 = diff(f, rho)
h8 = diff(f, lambida)
h9 = diff(f, phi)

%%
syms vx vy vz a b c bx y0 z0 ro fi la
 r = ((vx-bx).^2/a^2+(-b*sin(ro).*(vx-bx)+a.*(vy-y0)).^2/a^2/b^2/cos(ro)^2+(b*c*(sin(ro)*sin(la)-cos(ro)*sin(fi)*cos(la)).*(vx-bx)-a*c*sin(la).*(vy-y0)+a*b*cos(ro).*(vz-z0)).^2/a^2/b^2/c^2/cos(ro)^2/cos(fi)^2/cos(la)^2);
 r1 = diff(r, a)
 
 
 syms a b c xo yo zo ro la fi vx vy vz;

f = (vx-xo)^2/(a)^2 + (a*(vy-yo) - b*sin(ro)*(vx-xo))^2/(a*b*cos(ro))^2 +(a*b*cos(ro)*(vz-zo) - a*c*sin(la)*(vy-yo) + b*c*(sin(la)*sin(ro) - cos(ro)*sin(fi)*cos(la))*(vx-xo))^2/(a*b*c*cos(ro)*cos(fi)*cos(la))^2;

h1 = diff(f, a)
h2 = diff(f, b)
h3 = diff(f, c)
h4 = diff(f, xo)
h5 = diff(f, yo)
h6 = diff(f, zo)
h7 = diff(f, ro)
h8 = diff(f, la)
h9 = diff(f, fi)
