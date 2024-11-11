function [c,E]=theta_to_c_E(theta)
% Extracts c and E elements from theta as per Alonso paper.
c=theta(1:3);
E=[theta(4), theta(7), theta(8);...
    theta(7), theta(5), theta(9);...
    theta(8), theta(9), theta(6)];
end