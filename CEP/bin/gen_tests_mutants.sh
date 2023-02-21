#! /bin/bash
for f in *.s
do
    name=$(basename $f .s)
    for tag in $(awk 'match($0,/^\s+([a-z]{2,6})/,a){print a[1]}' $f | sort  | uniq)
    do
        echo "# TAG = $tag" > "${name}_${tag}.s"
        sed '/TAG/d' "$f" >>  "${name}_${tag}.s"
    done
done
