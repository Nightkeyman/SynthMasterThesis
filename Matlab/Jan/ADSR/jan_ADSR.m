clear;
cutoff_freq = 0;
fs = 44100;   %probkowanie
t_sig = 2;    %czas trwania sygnalu
pitch = 150;  %wysokosc sygnalu (Hz)

%% SQUARE
figure(1)
t = 0:1/fs:t_sig-1/fs;                     
x_sq = (1.3)*square(2*pi*pitch*t);      

y_sq = fft(x_sq);

n = length(x_sq);          % number of samples
f = (0:n-1)*(fs/n);     % frequency range
power_sq = abs(y_sq).^2/n;    % power of the DFT

subplot(3,1,1);
plot(t,x_sq)
xlabel('Time')
ylabel('Amplitude')
title('BEFORE FFT')
axis([0 0.2 -2 2])

subplot(3,1,2);
plot(f(1:floor(n/2)),power_sq(1:floor(n/2)))
xlabel('Frequency')
ylabel('Power')
title('Frequency domain');

for i = 1:length(y_sq),
    if(i > cutoff_freq && i < (fs - cutoff_freq))
       y_sq(i) = 0; 
    end
end
x_sq_af = real(ifft(y_sq));

subplot(3,1,3);
plot(t,x_sq_af)
xlabel('Time')
ylabel('Amplitude')
title('AFTER FFT')
axis([0 0.2 -2 2])

%% ADSR

% Attack



%% ODTWARZANKO
soundsc(x_sq,fs)
pause(3)
soundsc(x_sq_af,fs)

