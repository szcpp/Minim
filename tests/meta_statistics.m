clear;

function S = entropy(input)
	norm = sum(input,2);
	normalized = input./norm;
	normalized_safe = (normalized == 0) + normalized;
	S = sum(-normalized.*log(normalized_safe),2);
endfunction

load status_pm.out
load status_pc.out

populationSize = size(status_pm(1,2:end))(2);

figure(1);
hist(status_pc(1,2:end),1024);
axis([0 1024 0 100]);
axis 'autoy';
title(['poczatkowy rozklad pc N=' num2str(populationSize)]);
xlabel('kod chromosomu');
ylabel('ilosc osobnikow');
print('tmp/beginning_pc_hist.png','-S1024,768');
close(1);

figure(3);
hist(status_pm(1,2:end),1024);
axis([0 1024 0 100]);
axis 'autoy';
title(['poczatkowy rozklad pm N=' num2str(populationSize)]);
xlabel('kod chromosomu');
ylabel('ilosc osobnikow');
print('tmp/beginning_pm_hist.png','-S1024,768');
close(3);

figure(4);
hist(status_pc(end,2:end),1024);
axis([0 1024 0 100]);
axis 'autoy';
title(['koncowy rozklad pc N=' num2str(populationSize)]);
xlabel('kod chromosomu');
ylabel('ilosc osobnikow');
print('tmp/end_pc_hist.png','-S1024,768');
close(4);

figure(5);
hist(status_pm(end,2:end),1024);
axis([0 1024 0 100]);
axis 'autoy';
title(['koncowy rozklad pm N=' num2str(populationSize)]);
xlabel('kod chromosomu');
ylabel('ilosc osobnikow');
print('tmp/end_pm_hist.png','-S1024,768');
close(5);
