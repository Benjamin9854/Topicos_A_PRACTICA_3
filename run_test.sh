#!/bin/bash
unset LC_ALL
export LC_NUMERIC=C

# Archivo para almacenar los datos de tiempo de ejecución
echo "" > tiempo.dat

# Ejecutar sum_vector para cada número de procesos de 1, 2, 4 y 8
for i in 1 2 4 8
do
    sum=0
    for j in {1..10}
    do
        # Medir el tiempo de ejecución usando el comando time y almacenar el tiempo real
        # Usar /usr/bin/time para capturar el tiempo real
        time=$(/usr/bin/time -f "%e" mpirun -np "$i" ./sum_vector 2>&1 1>/dev/null)
        sum=$(echo "$sum + $time" | bc -l)
    done
    avg=$(echo "scale=6; $sum / 10" | bc -l)
    printf "%d %.6f\n" "$i" "$avg" >> tiempo.dat
    echo "$i processes test finished"
done

# Generar el gráfico usando gnuplot
gnuplot -persist <<-EOFMarker
    set title "Tiempo de ejecución vs Número de procesos"
    set xlabel "Número de procesos"
    set ylabel "Tiempo de ejecución (s)"
    set grid
    set term png
    set output "tiempo.png"
    plot "tiempo.dat" using 1:2 with linespoints title "Tiempo de ejecución"
EOFMarker
