L = 2048;
win = hanning(L);
txt = [];
txt = [txt 'float hann[] = {'];
for i=1:L
  
    txt = [txt num2str(win(i))];
      if i < L
        txt = [txt ',' ];
    end
end
txt = [txt '};'];
disp(txt);

fid = fopen ("hann_win.txt", "w");
fdisp (fid, txt);
fclose (fid);