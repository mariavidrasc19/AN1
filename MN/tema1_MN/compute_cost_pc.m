% computes a clustering solution total cost
function cost = compute_cost_pc(points, centroids)
	cost = 0;
  
  NC = size(centroids, 1);
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
  
  for i = 1:NC
    
    for j = 1:size(points, 1)
      if p_cluster(j) == i
        cost = cost + norm(points(j, :) - centroids(i, :));
      endif
    endfor
    endfor
	% TODO compute clustering solution cost
end

