f1 = 160;
f2 = 400;
Fs = 22e3;
T = 1.8;
t = 0:1/Fs:T;
n = length(t);
% z = (T-t)/T;
% z = (-abs(t-t(fix(n/2))) + 2.75)/2.75;


z = hann(n)'.*((T-t)/T);
z = z/max(z);
g = 2.^(-t*0.5*T/0.1 + T/4);
 g = g/max(g);
for i=150:100:1000
    disp(['f1 = ' num2str(i) ' ##################################']);
    for j=10:15:1000
        disp(['f2 = ' num2str(j)]);
        f1 = i;
        f2 = j;
        y = 2*sin(2*pi*f2*t).*z;
        x = sin(2*pi*f1*t.*g + y).*g;
        sound(x, Fs);
        pause(2);
    end
end
plot(t,z);
% axis([0 0.05 -2 2]);
% sound(x, Fs);
