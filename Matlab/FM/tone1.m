function tone1( f2 )
    f1 = 0;
    Fs = 22e3;
    T = 1.9;
    t = 0:1/Fs:T;
    n = length(t);

    z = hann(n)'.*((T-t)/T);
    z = z/max(z);
    g = 2.^(-t*0.5*T/0.1 + T/4);
    g = g/max(g);
    y = 2*sin(2*pi*f2*t).*z;
    x = sin(2*pi*f1*t.*g + y).*g;
    sound(x, Fs);
    plot(t,z,t,y,t,x);
end

