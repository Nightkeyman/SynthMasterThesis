fs = 44100;
f = 1:2048;
length = 2048;
y = audioread("flute_A_440.wav");

signal = y(1:length, 1);
hann_coef = hanning(length);
signal = signal.*hann_coef;
%figure(1);
%plot(signal);

spectrum = fft(signal);
%figure(2);
%plot(f,spectrum);
axis([0 100 0 15])
title("Signal 1");

%%% Signal 2 for comparison %%%
signal2 = y(length:2*length - 1, 1);
signal2 = signal2.*hann_coef;
%figure(3);
%plot(signal2);

spectrum2 = fft(signal2);
%figure(4);
%plot(f,spectrum2);
axis([0 100 0 15])
title("Signal 2");

%%% IFFT of spectrum2 %%%
signal2_ifft = ifft2(spectrum2);
figure(5);
plot(f,signal2_ifft);
title("Signal 2 again");

%%% unhann
unhann = (1./hann_coef);
unhann(~isfinite(unhann))=424557.26892*8

signal2_unhann = signal2_ifft.*unhann;
figure(6);
plot(f,signal2_unhann);

%%% create 1 sec of waveform
waveform = zeros(length*66, 1);
for i=0:65
  waveform((i*length+1:(i+1)*length), 1) = signal2_unhann;
endfor
figure(7)
plot(f,waveform(1:length, 1));

%%% play waveform
player = audioplayer(waveform, fs)
