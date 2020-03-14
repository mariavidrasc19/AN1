% computes the NC centroids corresponding to the given points using K-Means
function centroids = clustering_pc(points, NC)
	centroids = [];
  indexes = 1:1:size(points, 1);
   % [ 1 2 3 4 .. ]
  for i=1:NC
    
    a = randi(size(indexes, 2));
    b = indexes(a);
    centroids(end + 1, :) =  points(b, :);
    indexes(a) = [];
    
  endfor
  
  p_cluster = zeros(size(points, 1), 1);
  e_ok = 1;
  
  while e_ok == 1
    
    indexes = 1:1:size(points, 1);
    while(size(indexes) > 0)
      p_i = indexes(1);
      punctulet = points(p_i, :);
      indexes(1) = [];
      
      min =  norm(punctulet - centroids(1, :));
      min_i = 1;
      for i = 2:NC
        dist = norm(punctulet - centroids(i, :));
        if dist < min
          min = dist;
          min_i = i;
        endif
      endfor
      
      p_cluster(p_i) = min_i;
    endwhile
    centroids_vechi = centroids;
    
    for k = 1:size(points, 2)
      for i= 1:NC
        x_med = 0;
        x = 0;
        for j = 1:size(p_cluster)
          
          if p_cluster(j) == i
            x_med = x_med + points(j, k);
            x = x+1;
          endif
          
        endfor
        x_med = x_med/x;
        centroids(i, k) = x_med;
      endfor
    endfor
       %d=de facut norm
    if norm(centroids - centroids_vechi) < 10^-16
      e_ok = 0;
    endif
    
  endwhile
  %p_cluster
end
