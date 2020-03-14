function task5()
  A = imread('in/images/image1.gif');
  A_D = double(A);
  [m n] = size(A_D);
  [U,S,V] = svd(A_D);
  % reprezentare gra?ca a tuturor valorilor singulare ale matricei A in ordine descrescatoare
  subplot(2, 2, 1);
  plot(diag(S));
  grid on
  % reprezentare gra?ca k (pe axa OX) si informatia data de primele k valori singulare (pe axa OY)
  MM = zeros(1, 19);
  for k = 1:19
    A_k = cerinta1('in/images/image1.gif',k);
    S1(1:k) = diag(S(1:k, 1:k));
    S2 = diag(S);
    M(k) = sum(S1) / sum(S2);
  % reprezentare gra?ca k (pe axa OX) si eroarea aproximarii pentru matricea A (pe axa OY)
    for i = 1:m
      for j = 1:n
        MM(k)+= (A_D(i,j) - A_k(i,j))^2;
      endfor
    endfor
     MM(k) /= m*n;  
  % reprezentare gra?ca k (pe axa OX) si rata de compresie a datelor (pe axa OY)
    MMM(k) = (2*k + 1) / n;
  endfor
  subplot(2, 2, 2);
  plot([1:19], M);
  grid on
  xlabel('k');
  ylabel('Informatia celor k valori singulare'); 
  subplot(2, 2, 3);
  plot([1:19], MM);
  grid on
  xlabel('k');
  ylabel('Eroarea aproximarii pentru matricea A'); 
  subplot(2, 2, 4);
  plot([1:19],MMM);
  grid on
  xlabel('k');
  ylabel('Rata de compresie a datelor'); 
end