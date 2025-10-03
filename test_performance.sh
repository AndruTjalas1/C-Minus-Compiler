#!/bin/bash

echo "=== Compiler Performance Benchmark ==="
echo "Platform: $(uname -s)"
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "CPU: $(sysctl -n machdep.cpu.brand_string)"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "CPU: $(lscpu | grep 'Model name' | cut -d: -f2 | xargs)"
fi
echo ""

# Create test files of increasing complexity

# Small test file
cat > test_small.c << 'EOF'
int x;
int y;
x = 10;
y = 20;
write(x + y);
EOF

# Medium test file
cat > test_medium.c << 'EOF'
int a; int b; int c; int d; int e;
int f; int g; int h; int i; int j;
a = 1; b = 2; c = 3; d = 4; e = 5;
f = 6; g = 7; h = 8; i = 9; j = 10;
int result;
result = a + b + c + d + e + f + g + h + i + j;
write(result);
int x; int y; int z;
x = result + 10;
y = result + 20;
z = x + y;
write(z);
EOF

# Large test file with conditionals
cat > test_large.c << 'EOF'
int i;
int result;
result = 0;

i = 0;
if (i < 100) {
    result = result + 1;
}

i = 1;
if (i < 100) {
    result = result + 2;
}

i = 2;
if (i < 100) {
    result = result + 3;
}

i = 3;
if (i < 100) {
    result = result + 4;
}

i = 4;
if (i < 100) {
    result = result + 5;
}

write(result);
EOF

# Very large test file
echo "Generating very large test file..."
echo "" > test_xlarge.c
for i in {1..200}; do
    echo "int var$i;" >> test_xlarge.c
done
for i in {1..200}; do
    echo "var$i = $i;" >> test_xlarge.c
done
echo "int sum;" >> test_xlarge.c
echo "sum = var1 + var100 + var200;" >> test_xlarge.c
echo "write(sum);" >> test_xlarge.c

echo "=== Running Benchmarks ==="
echo ""

# Small file
echo "Small file (5 statements):"
time ./Compiler test_small.c test_small.s 2>&1 | grep -E "Performance|Statistics|instructions"
echo ""

# Medium file
echo "Medium file (20+ statements):"
time ./Compiler test_medium.c test_medium.s 2>&1 | grep -E "Performance|Statistics|instructions"
echo ""

# Large file
echo "Large file (with conditionals):"
time ./Compiler test_large.c test_large.s 2>&1 | grep -E "Performance|Statistics|instructions"
echo ""

# Very large file
echo "Very large file (400+ statements):"
time ./Compiler test_xlarge.c test_xlarge.s 2>&1 | grep -E "Performance|Statistics|instructions"
echo ""

# Compare TAC files
if [ -f tac_unoptimized.txt ] && [ -f tac.txt ]; then
    UNOPT_LINES=$(wc -l < tac_unoptimized.txt)
    OPT_LINES=$(wc -l < tac.txt)
    SAVED=$((UNOPT_LINES - OPT_LINES))
    PERCENT=$(awk "BEGIN {printf \"%.1f\", ($SAVED / $UNOPT_LINES) * 100}")
    echo "=== TAC Optimization Results ==="
    echo "Unoptimized TAC: $UNOPT_LINES lines"
    echo "Optimized TAC: $OPT_LINES lines"
    echo "Lines saved: $SAVED ($PERCENT%)"
fi

echo ""
echo "=== Benchmark Complete ==="
echo "Test files created: test_small.c, test_medium.c, test_large.c, test_xlarge.c"
echo "Compare tac_unoptimized.txt with tac.txt to see optimization effects"
