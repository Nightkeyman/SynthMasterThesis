clear;

Fs = 44100;
Ts = 1/Fs;
N = 100000;
t = (1:1:N)*Ts;

freq=240;
offset=2;
amp=8;
duty=30;
x1=offset+amp*square(2*pi*freq.*t,duty);

for i=1:N
   x1(i) = 0.6*x1(i) + 0.9*x1(i)*sin(2*pi*t(i)*5); 
end
figure(1)
plot(t,x1);
% soundsc(x1, Fs);

freq=360;
offset=0;
amp=8;
duty=30;
x2=offset+amp*square(2*pi*freq.*t,duty);

for i=1:N
   x2(i) = 0.6*x2(i) + 0.9*x2(i)*sin(2*pi*t(i)*2); 
end
figure(4)
plot(t,x2);
% soundsc(x2, Fs);

x = x1 + x2;

adsr = zeros(1,N);

for i=2:round(N/3)
    adsr(i) = adsr(i-1) + (1-(i/(N/3)))*0.001;
end
j = 0;
for i=round(N/3):1*round(N)
    j = j + 1;
    adsr(i) = adsr(i-1) - (1-(j/(N)))*0.0004;
end
% j = 0;
% for i=round(N/2):N
%     j = j + 1;
%     adsr(i) = 1 - (j/round(N/2))^2;
% end
x = x.*adsr;
figure(2)
plot(adsr);

spread = [zeros(1, 2000) x zeros(1, 2000)];
filtered = zeros(1, N + 4000);
filterorder = 66;
for i = 2000:length(filtered)-2000
    filtered(i) = sum(spread(i-filterorder+1:i))/filterorder;
end
filtered = filtered(2000:end-2001);
plot(t,filtered);
soundsc(filtered, Fs);
% axis([0 0.5 -10 10]);

figure(3);
plot(filtered)