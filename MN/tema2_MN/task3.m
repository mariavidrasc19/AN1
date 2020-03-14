function [A_k S] = task3(image, k)
  % transforma date de tipul A = [a1,a2...,an] dintr-un spatiu R_m intr-un spatiu R_k
  % citim imaginea si aplicam formulele indicate in cerinta 
 
  A_D = double(imread(image));
  [m,n] = size(A_D);
  niu = sum (A_D,2)/n;
  for i = 1:m
    for j = 1:n
      A_D(i,j) = A_D(i,j)-niu(i,1);
      endfor
  endfor
  Z = (A_D')/sqrt(n-1);
  [U,S,V] = svd(Z);
  W = V(1:m,1:k);
  Y = (W')*A_D;
  A_k = W*Y + niu; 
endfunction