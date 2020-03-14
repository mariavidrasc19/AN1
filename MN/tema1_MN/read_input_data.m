function [NC points] = read_input_data(file_params, file_points)
  format long;
  output_precision(16);
  file1 = fopen(file_params,  'r');
  file2 = fopen(file_points,  'r');
  
  NC = dlmread(file_params);
  points =dlmread(file_points, '', 5, 0);
  
    %NC = load(file_params);
    %points = [struct2cell(load(file_points)){:}];
    
end

