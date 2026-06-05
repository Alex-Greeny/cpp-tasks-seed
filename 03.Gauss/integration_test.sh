#!/bin/bash

status=true

# Создание входног офайла
cat << 'EOF' > itest_in.csv
X1,X2,X3,B
2.0,1.0,-1.0,2.0
-3.0,-1.0,2.0,-7.0
-2.0,1.0,2.0,-21.0
EOF

# Создание выходного файла
cat << 'EOF' > itest_ref.csv
A,B
8.000000
-11.000000
3.000000
EOF

./gauss itest_in.csv > itest_out.csv

if cmp -s itest_ref.csv itest_out.csv; then
  echo "Integration test ok!"
else
  echo "Integration test failed!" >&2
  diff -u itest_ref.csv itest_out.csv >&2
  status=false
fi

$status