function [X_bar,X_tilde]=center_data(X,sigma_sq_k,sigma_sq_bar)
% Calculates the centered and center components of X
% Center component
X_bar = sigma_sq_bar*(X*(1./sigma_sq_k)');
% Centered component
X_tilde = X - X_bar*ones(1,size(X,2));
end