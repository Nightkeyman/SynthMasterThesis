clear;
%{
Fs = 8000;
Ts = 1/Fs;
N = 24000;
t = (1:1:N)*Ts;

 Square wave
x = square(t,Fs);

plot(t,x); 
%}
t = linspace(0,5*pi)';

x_sq = square(t);
x_sin = sin(t);

plot(t,x_sq,t,x_sin);

sq_fft = fft(x_sq);
sin_fft = fft(x_sin);

figure(2)
plot(sq_fft);