echo "##############################################"
echo "k=25"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 25 ./ | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t25/' > k25.txt
echo "##############################################"
echo "k=50"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 50 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t50/' > k50.txt
echo "##############################################"
echo "k=75"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 75 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t75/' > k75.txt
echo "##############################################"
echo "k=100"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 100 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t100/' > k100.txt
echo "##############################################"
echo "k=125"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 125 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t125/' > k125.txt
echo "##############################################"
echo "k=150"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 150 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t150/' > k150.txt
echo "##############################################"
echo "k=175"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 175 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t175/' > k175.txt
echo "##############################################"
echo "k=200"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 200 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t200/' > k200.txt
echo "##############################################"
echo "k=225"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 225 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t225/' > k225.txt
echo "##############################################"
echo "k=240"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 240 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t240/' > k240.txt
echo "##############################################"
echo "k=241"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 241 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t241/' > k241.txt
echo "##############################################"
echo "k=242"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 242 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t242/' > k242.txt
echo "##############################################"
echo "k=243"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 243 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t243/' > k243.txt
echo "##############################################"
echo "k=244"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 244 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t244/' > k244.txt
echo "##############################################"
echo "k=245"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 245 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t245/' > k245.txt
echo "##############################################"
echo "k=246"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 246 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t246/' > k246.txt
echo "##############################################"
echo "k=247"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 247 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t247/' > k247.txt
echo "##############################################"
echo "k=248"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 248 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t248/' > k248.txt
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 249 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t249/' > k249.txt
echo "##############################################"
echo "k=250"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 250 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t250/' > k250.txt

cat k*.txt > kResults.tsv
