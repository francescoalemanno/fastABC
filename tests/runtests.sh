echo "Running Tests for particle type"
g++ --std=c++17 test_particle.cpp -o test_particle
./test_particle
echo "Running Tests for distributions"
g++ --std=c++17 ./test_statistics.cpp -o test_statistics
./test_statistics
echo "Running Tests for fastabc"
g++ --std=c++17 ./test_fastabc.cpp -o test_fastabc
./test_fastabc
echo "Complex Inference Test"
g++ -Ofast -march=native -std=c++17 application.cpp -o application; 
time ./application
