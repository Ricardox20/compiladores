$optimizationFlags = @("O0", "O1", "O2", "O3", "Os", "Ofast")

foreach ($flag in $optimizationFlags) {
    $command = "gcc -${flag} .\main.c -o .\main.exe; .\main.exe > ExecutionTime-${flag}.txt"
    Write-Host "Executando flag -${flag}"
    Invoke-Expression $command
}