clear;

function S = entropy(input)
	norm = sum(input,2);
	normalized = input./norm;
	normalized_safe = (normalized == 0) + normalized;
	S = sum(-normalized.*log(normalized_safe),2);
endfunction

load status.out

populationSize = size(status(1,2:end))(2);

figure(1);
hist(status(1,2:end),1024);
axis([0 100 0 100]);
axis 'autoy';
title(['poczatkowy rozklad populacji N=' num2str(populationSize)]);
xlabel('kod chromosomu');
ylabel('ilosc osobnikow');
print('tmp/beginning_hist.png','-S1024,768');
close(1);

figure(3);
% hist(status(5,2:end),1024);
% axis([0 100 0 100]);
% axis 'autoy';
% titl[e('rozklad populacji w 5 generacji N=' num2str(populationSize)]);
% xlabel('kod chromosomu');
% ylabel('ilosc osobnikow');
% print('tmp/5_hist.png','-S1024,768');
close(3);

figure(4);
hist(status(end,2:end),1024);
axis([0 100 0 100]);
axis 'autoy';
title(['rozklad populacji w 100 generacji N=' num2str(populationSize)]);
xlabel('kod chromosomu');
ylabel('ilosc osobnikow');
print('tmp/end_hist.png','-S1024,768');
close(4);

figure(5);
plot(status(:,1));
xlabel('numer generacji');
ylabel('srednie przystosowanie');
title(['srednie przystosowanie N=' num2str(populationSize)]);
print('tmp/mean_fittness.png','-S1024,768');
close(5);

figure(6);
plot(entropy(status(:,2:end)));
xlabel('numer generacji');
ylabel('entropia');
title(['entropia populacji N=' num2str(populationSize)]);
print('tmp/entropy.png','-S1024,768');
close(6);

figure(7);
plot(std(status(:,2:end),0,2));
xlabel('numer generacji');
ylabel('odchylenie standardowe');
title(['odchylenie standardowe N=' num2str(populationSize)]);
print('tmp/std.png','-S1024,768');
close(7);

figure(7);
plot(kurtosis(status(:,2:end),2));
xlabel('numer generacji');
ylabel('kurtoza');
title(['kurtoza N=' num2str(populationSize)]);
print('tmp/kurtosis.png','-S1024,768');
close(7);