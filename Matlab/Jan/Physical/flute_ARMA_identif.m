close all
clear

N = 100;
Fs = 44100;
fft_size = 8192*2;
y = audioread('Woodwind/Woodwind/flute/flute_A4_1_mezzo-piano_normal.mp3');
%y = y(fft_size:2*fft_size, 1);
L = length(y);
y_id = [zeros(1, N+1) zeros(1, L)];
v = randn(1, 2*L+N+1);

sys_flute = armax(y, [N N/2]);
display(sys_flute.A);
display(sys_flute.C);

Y = filter(sys_flute.C, sys_flute.A, v);
Y = Y/max(Y);
sound(Y, Fs);

%% SPECTRUM
spectrum = abs(fft(y));
spect_dens = 20*log10(abs(spectrum));
figure(1);
plot(spect_dens);
axis([1 L/2 -60 60]);
grid on;
hold on;

spectrum = abs(fft(Y));
spect_dens = 20*log10(abs(spectrum));
plot(spect_dens);
legend('Original signal', 'Synthesized signal');
