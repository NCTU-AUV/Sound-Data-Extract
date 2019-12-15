#include<bits/stdc++.h>
#define BOUND 6
#define CAPACITY 30
#define MIC_DISTANCE 2.5

using namespace std;

vector<long long> data_a, data_b;
map<int, int> possible_ans;
long long non_zero = 0, zero = 0, ans;

long long append_num(long long now, long long num, long long exp){
	if(exp > 19) return 0;
	
	return now += num*pow(10, exp);
}

long long cmp(vector<long long> a, vector<long long> b){
	// compare two data row
	// shift at most -4*N-1 ~ 4*N+1, for N = number of waves = distance(two mic)/2.5 (now distance of two mic = 2.5, N = 1)
	// return index where min sum(dif) occur
	
	long long min_dif = LLONG_MAX, ans = 0; // LLONG_MAX is defined in limits.h
	
	// sliding window on A, from  AAA AAA AAA  to  AAA AAA AAA
	//                            BBB                      BBB
	
	for(long long start_point = 0 ; start_point+b.size() < a.size() ; start_point++){
		long long diff_sum = 0;
		
		// compare difference between window A and B
		for(long long i = 0 ; i < b.size() ; i++)
			diff_sum += abs(a[start_point+i]-b[i]);
			
		if(diff_sum < min_dif){
			min_dif = diff_sum;
			ans = start_point-(CAPACITY/3);
		}
	}
	
	// marking possible shift count
	possible_ans[ans]++;
	
	return ans;
}

void init(){
	data_a.clear();
	data_b.clear();
	non_zero = 0;
	zero = 0;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	ifstream cin;
	ofstream file_cout("./fourth/data/measurements_30l_N.txt");
	cin.open("./fourth/data/dual_30l_pin0_N.txt");
	
	if(!cin){
		cout << "Unable to open file" << endl;
		exit(-1);
	}
	
	init();
	
	string s;
	
	while(cin >> s){
		//cout << s << endl;
		bool save = false, save_a = true;
		long long a = 0, b = 0, exp = 0;
		string sa = "", sb = "";
		
		
		// string parsing to number for each row in file
		for(int i = 0 ; i < s.size() ; i++){
			if(s[i] == ',') save = false, save_a = false;
			
			if(save && save_a) sa += s[i];
			if(save && !save_a) sb += s[i];
			
			if(s[i] == '.') save = true;
		}
		
		for(int i = sa.size()-1 ; i >= 0 ; i--)
			a = append_num(a, (long long)sa[i]-'0', exp++);
			
		exp = 0;
		
		for(int i = sb.size()-1 ; i >= 0 ; i--)
			b = append_num(b, (long long)sb[i]-'0', exp++);
		
		if(!a && !b) zero++;
		else zero = 0;
		
		if(zero >= 6) init();
		
		// count non_zero
		if(non_zero < BOUND) non_zero += (a || b);
		else{ // start saving data
		
			// data_b save the middle part of data_a
			// AAA AAA AAA
			// ___ BBB ___
			
			if(data_a.size() > CAPACITY/3 && data_a.size() < 2*CAPACITY/3) data_b.push_back(b);
			data_a.push_back(a);
		}
		
		if(data_a.size() == CAPACITY){
			ans = cmp(data_a, data_b);
			file_cout << ans+11 << '\n';
			init();
		}
	}
	
	pair<long long, long long> result = make_pair(0, 0);
	
	for(auto x : possible_ans){
		cout << x.first << " " << x.second << '\n';
		if(x.second > result.second) result = make_pair(x.first, x.second);
	}
		
	cout << "result: " << result.first << " " << result.second << '\n';
	
	file_cout.close();
	
	return 0;
}

