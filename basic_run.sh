#!/usr/bin/env bash
set -euo pipefail

cd -- "$(dirname -- "${BASH_SOURCE[0]}")"

if [[ ! -x ./basic.out ]]; then
  echo "Error: basic.out is missing or not executable." >&2
  exit 1
fi

shopt -s nullglob
inputs=(materials/Datapoints/*.txt)
if (( ${#inputs[@]} == 0 )); then
  echo "Error: no input files found in materials/Datapoints." >&2
  exit 1
fi

mkdir -p results/basic
status=0
for input in "${inputs[@]}"; do
  name=${input##*/}
  echo "Running $name"
  if ! ./basic.out "$input" "results/basic/$name" 2> "results/basic/${name%.txt}.err"; then
    echo "Failed: $name (see results/basic/${name%.txt}.err)" >&2
    status=1
  fi
done

exit "$status"
