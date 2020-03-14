function vp = grd(A,tol)
 
  n = length(A);
  n0 = n;
  vp = [];
  for i = 1:n0-1
    while(1)
    R = [];
    Q = [];
      landa = A(n,n);
      I = eye(n);
      [Q, R] = qr(A - landa*I);
      A = R*Q +landa*I;
      if abs(A(n,n-1)) < tol
        vp = [vp, A(n, n)];
        A = A(1:n-1, 1:n-1);
        n = n-1;
        break;
      endif
    endwhile
  endfor
  vp = [vp, A(1,1)];
endfunction
