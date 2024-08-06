function [B_total]=total_field(B_in)
% Calculates total field of B in (3xn matrix).
B_total=sum(B_in.^2,1).^0.5;
end