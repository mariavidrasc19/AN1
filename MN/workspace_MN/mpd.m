function [landa, y] = mpd(A, max, landa, tol)
  
  z = [];
  y = [1 2];
  y = y';
  
  for k = 1:max
    z = A * y;
    yold = y;
    y = z/norm(z);
    landa = y' * A * y;
    
    if norm(y - yold) < tol 
      break;
    endif
  endfor
   
endfunction
