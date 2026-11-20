# just an automation for parsing and testing parse_file.cpp

g++ input_generator.cpp -o input_generator.out

if [[ $# -eq 0 ]]; then
  ./input_generator.out "materials/SampleTestCases/input1.txt"
else
  ./input_generator.out "$1"
fi
