value = 0;
while value ~= 27
    k = waitforbuttonpress;
    value = double(get(gcf,'CurrentCharacter'));
    switch value
        case 122
            fx = 261.6;
        case 120
            fx = 293.7;
        case 99
            fx = 329.6;
        case 118
            fx = 349.2;
        case 98
            fx = 392.0;
        case 110
            fx = 440;
        case 109
            fx = 466.2;
        case 44
            fx = 493.9;
        otherwise
            fx = 0;
    end
    tone1(fx);
end

