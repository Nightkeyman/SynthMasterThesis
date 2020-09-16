L = 1000;
x1 = zeros(1, L);
x2 = zeros(1, L);
x3 = zeros(1, L);
dt = 0:1/L:1 - 1/L;
f = 5;

N = 2;
for k = 1:N
  x1 = x1 + ((-1)^k)*sin(2*pi*f*k*dt)/k;
endfor

N = 10;
for k = 1:N
  x2 = x2 + ((-1)^k)*sin(2*pi*f*k*dt)/k;
endfor

N = 50;
for k = 1:N
  x3 = x3 + ((-1)^k)*sin(2*pi*f*k*dt)/k;
endfor

subplot(3,1,1)
plot(dt, x1)
title("N = 2")
subplot(3,1,2)
plot(dt, x2)
title("N = 10")
subplot(3,1,3)
plot(dt, x3)
title("N = 50")