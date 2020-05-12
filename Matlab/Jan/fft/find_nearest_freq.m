function [ y ] = find_nearest_freq( freq, Fs, N )
  minind = 0;
  currmin = 9999;
  for i = 1:N/2
      if abs(i*Fs/N - freq) < currmin
         currmin =  abs(i*Fs/N - freq);
         minind = i;
      end
  end
  y = minind;
end

