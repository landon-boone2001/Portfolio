#!/bin/bash                                                                                                                                                          #!/bin/sh

dir=~/cs102/projects/cs202/labs/lab5/
ge="$dir/Gradescript-Examples"

if [ $# -ne 0 ]; then
  echo 'usage: gradeall' >&2
  exit 1
fi

enum=1
n=0
while [ $enum -le 100 ]; do
  out=`$dir/gradescript $enum  | head -n 1`
  echo $out
  n=`echo $n $out | awk '{ print $1 + ($NF == "correct.") }'`

  rm -rf tmp-???-test-copy.txt tmp-???-test.txt tmp-???-correct.txt tmp-???-correct-stdout.txt \
         tmp-???-correct-stderr.txt tmp-???-test-stdout.txt tmp-???-test-stderr.txt

  enum=`echo $enum | awk '{ print $1+1 }'`
done
              