function [b,D]= theta_to_b_D(theta)
% Converts a value of theta to usable physical values
[c,E]=theta_to_c_E(theta);
[U,S]=eig(E);
W=-eye(3)+(eye(3)+S).^(0.5);
D=U*W*U';
% Calculate b using the inversr of (I+D)
b=(eye(3)+D)\c;
end