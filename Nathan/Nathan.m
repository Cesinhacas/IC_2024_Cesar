%% Leitura do arquivo q.txt (separado por vírgula)
q_txt = readmatrix('q.txt', 'Delimiter', ',');

q_txt_col1 = q_txt(:,1);   % primeira coluna (q0)


%% Leitura do arquivo quaternion_c.csv (separado por tab ou espaço)
q_csv = readmatrix('quaternion_c.csv');

q_csv_col1 = q_csv(:,1);   % primeira coluna (q0)


%% Ajuste de tamanho (caso tenham comprimentos diferentes)
N = min(length(q_txt_col1), length(q_csv_col1));

q_txt_col1 = q_txt_col1(1:N);
q_csv_col1 = q_csv_col1(1:N);


%% Comparação
erro = q_txt_col1 - q_csv_col1;
erro_abs = abs(erro);


%% Resultados numéricos
fprintf('Erro máximo absoluto: %.3e\n', max(erro_abs));
fprintf('Erro médio absoluto : %.3e\n', mean(erro_abs));


%% Plot para inspeção visual
figure
plot(q_txt_col1, 'b', 'LineWidth', 1.5); hold on
plot(q_csv_col1, 'r--', 'LineWidth', 1.5);
grid on
xlabel('Índice da amostra')
ylabel('q_0')
legend('q.txt', 'quaternion\_c.csv')
title('Comparação da primeira componente do quaternion')


%% Plot do erro
figure
plot(erro, 'k', 'LineWidth', 1.2)
grid on
xlabel('Índice da amostra')
ylabel('Erro (q.txt - quaternion\_c.csv)')
title('Erro da primeira componente do quaternion')
