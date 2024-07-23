function dq = cinematica(w,q)
%#eml
wx = w(1);
wy = w(2);
wz = w(3);

q = q/norm(q);
qteta = q(1);
qx = q(2);
qy = q(3);
qz = q(4);

W = [0 -wx -wy -wz; wx 0 wz -wy; wy -wz 0 wx; wz wy -wx 0];
dq=0.5*W*[qteta qx qy qz]';