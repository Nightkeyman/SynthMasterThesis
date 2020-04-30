clear
clc
notes = zeros(1, 128);
Fs = 96e3;
notes(60) = 1;
notes(72) = 1;
N = 2048*4;
t = 0:1/Fs:1;
x = zeros(1, N);
for i=1:N
    x(i) = sin(2*pi*(1/Fs)*i*630);
end
x = x.*hanning(N)';
% x = sin(2*pi*t*600);
figure(1)
plot(x);

figure(2);
x_fft = abs(fft(x));
x_fft = zeros(1, N/2);
for i = 1:128
    if notes(i) == 1
       freq_wav = 440*1.059463^(i - 69); 
       freq_index = find_nearest_freq(freq_wav/2, Fs, N);
       x_fft(freq_index) = x_fft(freq_index) + N/2;
    end
end
% x_fft(N-L2+2) = 1024;
plot(x_fft);

figure(3);
x_ifft = real(ifft(x_fft));
plot(x_ifft);


y = zeros(1, 24*N);
for i=1:48
   y( (i-1)*N/2 + 1 : (i)*N/2 ) = x_ifft; 
end
% plot(abs(fft(y)));
%sound(y*0.05, Fs);
%pause(2)
%clear sound
