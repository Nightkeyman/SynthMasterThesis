
fm = 55;
Fs = 44e3;
T = 0.2;
t = 0:1/Fs:T;

f = 220;
tw_amp = [8 8 8 0 0 0 0 0 0]; % values 0 - 8
y = tw_amp(1)*sin(2*pi*f*t) + tw_amp(2)*sin(2*pi*3*f*t) + tw_amp(3)*sin(2*pi*2*f*t) ...
  + tw_amp(4)*sin(2*pi*4*f*t) + tw_amp(5)*sin(2*6*pi*f*t) + tw_amp(6)*sin(2*8*pi*f*t) ... 
  + tw_amp(7)*sin(2*10*pi*f*t) + tw_amp(8)*sin(2*12*pi*f*t) + tw_amp(9)*sin(2*16*pi*f*t);
y = y/max(y);

f = 196;
tw_amp = [8 8 8 0 0 0 0 0 0]; % values 0 - 8
x = tw_amp(1)*sin(2*pi*f*t) + tw_amp(2)*sin(2*pi*3*f*t) + tw_amp(3)*sin(2*pi*2*f*t) ...
  + tw_amp(4)*sin(2*pi*4*f*t) + tw_amp(5)*sin(2*6*pi*f*t) + tw_amp(6)*sin(2*8*pi*f*t) ... 
  + tw_amp(7)*sin(2*10*pi*f*t) + tw_amp(8)*sin(2*12*pi*f*t) + tw_amp(9)*sin(2*16*pi*f*t);
x = x/max(x);

T = 2;
t = 0:1/Fs:T;
f = 220;
tw_amp = [8 8 8 0 0 0 0 0 0]; % values 0 - 8
z = tw_amp(1)*sin(2*pi*f*t) + tw_amp(2)*sin(2*pi*3*f*t) + tw_amp(3)*sin(2*pi*2*f*t) ...
  + tw_amp(4)*sin(2*pi*4*f*t) + tw_amp(5)*sin(2*6*pi*f*t) + tw_amp(6)*sin(2*8*pi*f*t) ... 
  + tw_amp(7)*sin(2*10*pi*f*t) + tw_amp(8)*sin(2*12*pi*f*t) + tw_amp(9)*sin(2*16*pi*f*t);
z = z/max(z);

q = [y x z];
%sound(q, Fs); % play 3 notes A, G, A

tw_amp = [8 8 8 8 8 8 8 8 8]; % values 0 - 8
m = tw_amp(1)*sin(2*pi*f*t) + tw_amp(2)*sin(2*pi*3*f*t) + tw_amp(3)*sin(2*pi*2*f*t) ...
  + tw_amp(4)*sin(2*pi*4*f*t) + tw_amp(5)*sin(2*6*pi*f*t) + tw_amp(6)*sin(2*8*pi*f*t) ... 
  + tw_amp(7)*sin(2*10*pi*f*t) + tw_amp(8)*sin(2*12*pi*f*t) + tw_amp(9)*sin(2*16*pi*f*t);
m = m/max(m);

tw_amp = [8 8 8 8 8 8 0 0 0]; % values 0 - 8
n = tw_amp(1)*sin(2*pi*f*t) + tw_amp(2)*sin(2*pi*3*f*t) + tw_amp(3)*sin(2*pi*2*f*t) ...
  + tw_amp(4)*sin(2*pi*4*f*t) + tw_amp(5)*sin(2*6*pi*f*t) + tw_amp(6)*sin(2*8*pi*f*t) ... 
  + tw_amp(7)*sin(2*10*pi*f*t) + tw_amp(8)*sin(2*12*pi*f*t) + tw_amp(9)*sin(2*16*pi*f*t);
n = n/max(n);

subplot(3, 1, 1)
plot(1:800, y(1:800))
axis([1 800 -1 1])
title('Sygna³ organów z³o¿ony z trzech sk³adowych harmonicznych')
subplot(3, 1, 2)
plot(1:800, n(1:800))
axis([1 800 -1 1])
title('Sygna³ organów z³o¿ony z szeœciu sk³adowych harmonicznych')
subplot(3, 1, 3)
plot(1:800, m(1:800))
axis([1 800 -1 1])
title('Sygna³ organów z³o¿ony z dziewiêciu sk³adowych harmonicznych')

