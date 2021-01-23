function y = gaussmf (x, params)

  sig = params(1);
  c = params(2);

  y_val = @(x_val) exp ((-(x_val - c)^2)/(2 * sig^2));
  y = arrayfun (y_val, x);

endfunction