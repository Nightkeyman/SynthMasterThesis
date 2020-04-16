clear
clc
Fs = 96e3;
T = 2;
t = 0:1/Fs:T-1/Fs;

D = 40;
x = sin(2*pi*t*20);
N = Fs/D;
sintable = sin(2*pi*(1:N)/N);
sound(x*0.05, Fs);
plot(sintable)
notes = zeros(1 , 128);
% notes(66) = 1;
notes(70) = 1;
y = zeros(1, T*D*N);

fid=fopen('code.txt','w');
fprintf(fid, 'sound = 0;\n');
for i=1:128
    fprintf(fid, 'if (notes[%d] == 1) {\n', i-1);
    freq_wav = round(440*1.059463^(i - 69)/D);
    fprintf(fid, '	sound += notes[(int)round(generator_iterator*%d)%%N_LUT];\n',  freq_wav);
    fprintf(fid, '}\n');
    if notes(i) == 1
        freq_wav2 = 440*1.059463^(i - 69)/D;
        
        freq_wav2
        for j=1:length(y)
           
            y(j) = y(j) + sintable(mod(round((j-1)*freq_wav2), N)+1);
        end
        
    end
    
end
y2 = sin(2*pi*t*freq_wav2*D);


figure(1)
plot(t,y);
axis([0 0.3 -2 2]);
y_fft = abs(fft(y));
figure(2)
plot(y_fft);
% sound(y2*0.05, Fs)
% pause(T)
% sound(y*0.05, Fs)
fid=fopen('sinustable.txt','w');
fprintf(fid, '#define N_LUT %d\n', N);
fprintf(fid, 'const float sinustable[N_LUT] = {');
for i = 1:N
    fprintf(fid, '%.15f', sintable(i));
    if i < N
         fprintf(fid, ', ');
    end
end
fprintf(fid, '};');
fclose(fid)