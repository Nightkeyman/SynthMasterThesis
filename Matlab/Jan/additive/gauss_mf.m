x = 0:0.1:10;
y = gaussmf(x, [2 5]);

x = 0:(48000/1024):48000 - (48000/1024);
y = gaussmf(x, [10 440]) + gaussmf(x, [10 1720]) + gaussmf(x, [10 5280]);
figure(1)
plot(x,y)

sig = real(ifft(y));
figure(2)
plot(sig)