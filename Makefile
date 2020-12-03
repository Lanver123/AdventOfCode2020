day1:
	g++ solution1_1.cpp -o solution1_1
	g++ solution1_2.cpp -o solution1_2
day2:
	g++ -g solution2_1.cpp -o solution2_1
	g++ solution2_2.cpp -o solution2_2

day3:
	g++ -g solution3_1.cpp -o solution3_1
	g++ -g solution3_2.cpp -o solution3_2

clean:
	rm -rf solution?_?
