lines=0
for f in *; do
    wc=$(cat "$f" | wc -l)
    lines=$((lines + wc))
done;
echo $lines
