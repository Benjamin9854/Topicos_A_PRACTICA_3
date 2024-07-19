Es problable que se tenga que modificar el PATH de MPI en el archivo c_cpp_properties.json



Para compilar:   mpicc -o sum_vector sum_vector.c



Para hacer las pruebas y obtener grafico:  ./run_test.sh



Para solo hacer una pruba sin grafico:    mpirun -np 4 ./sum_vector