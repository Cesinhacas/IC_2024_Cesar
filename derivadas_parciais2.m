syms mx my mz sx sy sz bx by bz rho phi lambida;

f = (mx-bx).^2/(sx)^2 + (sx*(my-by) - sy*sin(rho)*(mx-bx)).^2/(sx*sy*cos(rho))^2 + (sx*sy*cos(rho)*(mz-bz) - sx*sz*sin(lambida)*(my-by) + sy*sz*(sin(lambida)*sin(rho) - cos(rho)*sin(phi)*cos(lambida))*(mx-bx)).^2/(sx*sy*sz*cos(rho)*cos(phi)*cos(lambida))^2;

h1 = diff(f, sx);
h2 = diff(f, sy);
h3 = diff(f, sz);
h4 = diff(f, bx);
h5 = diff(f, by);
h6 = diff(f, bz);
h7 = diff(f, rho);
h8 = diff(f, phi);
h9 = diff(f, lambida);

r1 = simplify(h1)
r2 = simplify(h2)
r3 = simplify(h3)
r4 = simplify(h4)
r5 = simplify(h5)
r6 = simplify(h6)
r7 = simplify(h7)
r8 = simplify(h8)
r9 = simplify(h9)