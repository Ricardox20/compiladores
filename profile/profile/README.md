1. Compilar o arquivo .c com o comando abaixo:
```
gcc -Wall -pg test.c -o test.exe
```

2. Rodar o executavel gerado com o comando abaixo:
```
.\test.exe
```

3. Após rodar o comando acima, um arquivo "gmon.out" será criado. Executar o profiler com este arquivo gerado para criar o relatório. O comando abaixo põe este relatório no arquivo de texto de nome "relatorio.txt". OBS: podem aparecer vários warnings, basta ignorá-los.
```
gprof test.exe gmon.out > relatorio.txt
```

4. Estudar o arquivo "relatorio.txt", para saber interpretá-lo e chuva.