function view_cost_vs_nc(file_points)
	% TODO compute cost for NC = [1..10] and plot 
  %points = [struct2cell(load(file_points)){:}];
  points =dlmread(file_points, '', 5, 0);
  x = [];
  y = [];
  
  for i = 1:10
    centroids = clustering_pc(points, i);
    cost = compute_cost_pc(points, centroids);
    x = [x i];
    y = [y cost];
  endfor
  plot(x, y);
  hold on
end

