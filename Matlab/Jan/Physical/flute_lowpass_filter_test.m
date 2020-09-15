filt_b = -0.1; %-0.3
filt_a = -0.7; %0.7

f_sin = 220;
T = 2;
Fs = 44100;
dt = 1/Fs;
L = 10000;
asum3 = zeros(length(0:dt:T-dt) + 1, 1);
avalue = zeros(length(0:dt:T-dt) + 1, 1);

% create square
for i = 1:length(0:dt:T-dt)
  if(sin(2*pi*i*f_sin/Fs) >= 0)
    asum3(i) = 1;
  else
    asum3(i) = -1;
  end
end

% filter
for i = 1:length(0:dt:T-dt)
  avalue(i+1) = filt_b*asum3(i+1) - filt_a*avalue(i);
end

x = 500;
subplot(2,1,1)
plot(1:x, asum3(1:x))
subplot(2,1,2)
plot(1:x, avalue(1:x))