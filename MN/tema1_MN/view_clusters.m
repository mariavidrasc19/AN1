% outputs a graphical representation of the clustering solution
function view_clusters(points, centroids)
	% TODO graphical representation coded here 
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
  
  %figure
  a = 0;
  b = 0.5;
  c = 0.5;
  for i = 1:NC
    t = [a b c];
    for j = 1:size(points, 1)
      if p_cluster(j) == i
        %comanda de culoare a punctului dintr un claster
        scatter3(points(j, 1),points(j, 2),points(j, 3), [], hsv2rgb(t))
        hold on
      endif
    endfor
    a = a + 0.75/NC;
    b = b+0.35/NC;
    c = c + 0.3/NC;
    %schimbam astfel incat culoarea sa se schimbe cand se trece la urm claster
  endfor
end

