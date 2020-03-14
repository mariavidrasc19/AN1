function [A_k S] = task4(image, k)
   % calculam componentele principale folosind matricea de covarianta
  
  A_D = double(imread(image));
  [m,n] = size(A_D);
  niu = sum (A_D,2)/n;
  for i = 1:m
    for j = 1:n
      A_D(i,j) = A_D(i,j)-niu(i,1);
      endfor
  endfor
  Z = (1/(1-n)*(A_D*(A_D')));
  [V S] = eig(Z);
  W = V(1:m,1:k);
  Y = (W')*A_D;
  A_k = W*Y + niu;   
endfunction