# 25 50 75 100 125 150 175 200 225 240 241 242 243 244 245 246 247 248 249 250
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
echo "k=249"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 249 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t249/' > k249.txt
echo "##############################################"
echo "k=250"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 250 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t250/' > k250.txt

cat k*.txt > kResults.tsv


echo "##############################################"
echo "h=1"
echo "##############################################"
./aaTest -j 48 -q 1 -l 1000000049 -g 1000 -t 100000 -m 3 -a 5 -h 1 -k 50 ./ | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t1/' > h1.txt

echo "##############################################"
echo "h=3"
echo "##############################################"
./aaTest -j 48 -q 1 -l 1000000049 -g 1000 -t 100000 -m 3 -a 5 -h 3 -k 50 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t3/' > h3.txt

echo "##############################################"
echo "h=5"
echo "##############################################"
./aaTest -j 48 -q 1 -l 1000000049 -g 1000 -t 100000 -m 3 -a 5 -h 5 -k 50 -i reads.fa | grep -A1 aaHash |  awk -f transpose.awk | sed 's/$/\t5/' > h5.txt

cat h1.txt h3.txt h5.txt > hResults.tsv


echo "##############################################"
echo "uniformity simulated"
echo "##############################################"
./aaTest -j 48 -q 4000000 -l 250 -g 5000000 -t 100 -m 3 -a 5 -h 5 -u ./
echo "##############################################"
echo "uniformity real"
echo "##############################################"
./aaTest -j 48 -q 4000000 -l 250 -g 5000000 -t 100 -m 3 -a 5 -h 5 -u -i genes.fa uniprot-reviewed_yes+AND+proteome_up000005640.singleLine.fasta


echo "##############################################"
echo "hashlvl1"
echo "##############################################"
./aaTest -j 48 -q 1 -l 1000099 -g 5000000 -t 100 -m 3 -a 5 -h 5 -z -k 100 -y1 ./ > hashlvl1.txt 
echo "##############################################"
echo "hashlvl2"
echo "##############################################"
./aaTest -j 48 -q 1 -l 1000099 -g 5000000 -t 100 -m 3 -a 5 -h 5 -z -k 100 -y2 -i reads.fa > hashlvl2.txt 
echo "##############################################"
echo "hashlvl3"
echo "##############################################"
./aaTest -j 48 -q 1 -l 1000099 -g 5000000 -t 100 -m 3 -a 5 -h 5 -z -k 100 -y3 -i reads.fa > hashlvl3.txt 



echo "##############################################"
echo "RAM test k=50"
echo "##############################################"
/usr/bin/time -pv -o ramTestCityk50h1.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 1 -h 1 -k 50 -r ./ > /dev/null
echo "##############################################"
echo "RAM test k=150"
echo "##############################################"
/usr/bin/time -pv -o ramTestCityk150h1.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 1 -h 1 -k 150 -i -r reads.fa > /dev/null
echo "##############################################"
echo "RAM test k=250"
echo "##############################################"
/usr/bin/time -pv -o ramTestCityk250h1.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 1 -h 1 -k 250 -i -r reads.fa > /dev/null


echo "##############################################"
echo "RAM test k=50"
echo "##############################################"
/usr/bin/time -pv -o ramTestMurmurk50h1.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 2 -h 1 -k 50 -i -r reads.fa > /dev/null
echo "##############################################"
echo "RAM test k=150"
echo "##############################################"
/usr/bin/time -pv -o ramTestMurmurk150h1.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 2 -h 1 -k 150 -i -r reads.fa > /dev/null
echo "##############################################"
echo "RAM test k=250"
echo "##############################################"
/usr/bin/time -pv -o ramTestMurmurk250h1.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 2 -h 1 -k 250 -i -r reads.fa > /dev/null

echo "##############################################"
echo "RAM test k=50"
echo "##############################################"
/usr/bin/time -pv -o ramTestxxHashk50h1.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 3 -h 1 -k 50 -i -r reads.fa > /dev/null
echo "##############################################"
echo "RAM test k=150"
echo "##############################################"
/usr/bin/time -pv -o ramTestxxHashk150h1.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 3 -h 1 -k 150 -i -r reads.fa > /dev/null
echo "##############################################"
echo "RAM test k=250"
echo "##############################################"
/usr/bin/time -pv -o ramTestxxHashk250h1.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 3 -h 1 -k 250 -i -r reads.fa > /dev/null


echo "##############################################"
echo "RAM test k=50"
echo "##############################################"
/usr/bin/time -pv -o ramTestAAHashk50h1.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 0 -h 1 -k 50 -i -r reads.fa > /dev/null
echo "##############################################"
echo "RAM test k=150"
echo "##############################################"
/usr/bin/time -pv -o ramTestAAHashk150h1.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 0 -h 1 -k 150 -i -r reads.fa > /dev/null
echo "##############################################"
echo "RAM test k=250"
echo "##############################################"
/usr/bin/time -pv -o ramTestAAHashk250h1.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 0 -h 1 -k 250 -i -r reads.fa > /dev/null


echo "##############################################"
echo "City RAM test k=25 h=3"
echo "##############################################"
/usr/bin/time -pv -o ramTestCityk50h3.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 1 -h 3 -k 50 -i -r reads.fa > /dev/null
echo "##############################################"
echo "City RAM test k=25 h=5"
echo "##############################################"
/usr/bin/time -pv -o ramTestCityk50h5.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 1 -h 5 -k 50 -i -r reads.fa > /dev/null


echo "##############################################"
echo "Murmur RAM test k=25 h=3"
echo "##############################################"
/usr/bin/time -pv -o ramTestMurmurk50h3.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 2 -h 3 -k 50 -i -r reads.fa > /dev/null
echo "##############################################"
echo "Murmur RAM test k=25 h=5"
echo "##############################################"
/usr/bin/time -pv -o ramTestMurmurk50h5.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 2 -h 5 -k 50 -i -r reads.fa > /dev/null

echo "##############################################"
echo "xxHash RAM test k=25 h=3"
echo "##############################################"
/usr/bin/time -pv -o ramTestxxHashk50h3.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 3 -h 3 -k 50 -i -r reads.fa > /dev/null
echo "##############################################"
echo "xxHash RAM test k=25 h=5"
echo "##############################################"
/usr/bin/time -pv -o ramTestxxHashk50h5.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 3 -h 5 -k 50 -i -r reads.fa > /dev/null

echo "##############################################"
echo "AAHash RAM test k=50 h=3"
echo "##############################################"
/usr/bin/time -pv -o ramTestAAHashk50h3.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 0 -h 3 -k 50 -i -r reads.fa > /dev/null
echo "##############################################"
echo "AAHash RAM test k=50 h=5"
echo "##############################################"
/usr/bin/time -pv -o ramTestAAHashk50h5.log ./aaTest -j 48 -q 1000000 -l 250 -g 1000 -t 100000 -m 3 -a 0 -h 5 -k 50 -i -r reads.fa > /dev/null
