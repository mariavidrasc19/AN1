function A_k = task1(image, k)
    % se face descompunerea redusa a valorilor singulare
  % A_k = double(imread(image));
  % returneaza A_k =U_k * S_k * (V_K)' 
  
  A=imread(image);
  A_D=double(A);
  [m,n] = size(A_D);
  [U,S,V] = svd(A_D);
  A_k=U(1:m,1:k)*S(1:k,1:k)*V'(1:k,1:n);
  
end