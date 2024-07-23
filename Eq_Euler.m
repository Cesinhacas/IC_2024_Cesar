function dw = Eq_Euler(I,M,w)
wx = w(1);
wy = w(2);
wz = w(3);
Ix = I(1);
Iy = I(2);
Iz = I(3);

Mx = M(1);
My = M(2);
Mz = M(3);

dwx = (Mx - wy*wz*(Iz - Iy))/Ix;
dwy = (My - wx*wz*(Ix - Iz))/Iy;
dwz = (Mz - wx*wy*(Iy - Ix))/Iz;

dw=[dwx dwy dwz]';

end