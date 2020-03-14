function [landa, y] = mpi(A, max, landa, miu, tol)
  
  z = [];
  y = [1 2];
  y = y';
  
  for k = 1:max
    z = ((A - miu*eye(2))^-1) * y;
    yold = y;
    y = z/norm(z);
    landa = y' * A * y;
    
    if norm(y - yold) < tol 
      break;
    endif
  endfor
   miu = landa;
endfunction
