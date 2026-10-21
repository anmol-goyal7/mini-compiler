#!/usr/bin/env bash
# Runs every test program through mycc.
#   tests/valid/NAME_N.c   must compile, link and exit with status N
#   tests/invalid/*.c      must be rejected with a line:column error
set -u
cd "$(dirname "$0")/.."
mkdir -p tests/out
fail=0

for src in tests/valid/*.c; do
  name=$(basename "$src" .c)
  want=${name##*_}
  [[ $want =~ ^[0-9]+$ ]] || want=$(grep -o 'return [0-9]*' "$src" | head -1 | cut -d' ' -f2)
  if ./mycc "$src" > "tests/out/$name.s" && cc "tests/out/$name.s" -o "tests/out/$name"; then
    ./"tests/out/$name"
    got=$?
    if [[ $got -eq $want ]]; then echo "ok   $src (exit $got)"; else echo "FAIL $src: exit $got, want $want"; fail=1; fi
  else
    echo "FAIL $src: did not compile"; fail=1
  fi
done

for src in tests/invalid/*.c; do
  if err=$(./mycc "$src" 2>&1 >/dev/null); then
    echo "FAIL $src: accepted"; fail=1
  elif [[ $err =~ :[0-9]+:[0-9]+: ]]; then
    echo "ok   $src ($err)"
  else
    echo "FAIL $src: error has no line:column: $err"; fail=1
  fi
done

exit $fail
