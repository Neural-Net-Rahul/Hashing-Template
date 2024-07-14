#include <bits/stdc++.h>
using namespace std;
#define ll long long int
using namespace chrono;

class HashedString {
private:
    static const ll M = 1e9+7;
    static const ll B;

    // pow[i] contains B^i % M
    static vector<ll> pow;

    // p_hash[i] is the hash of the first i characters of the given string
    vector<ll> p_hash;

    ll mod(ll a){
    	return (a%M + M)%M;
    }

    ll mod_mul(ll a, ll b) {
        // ll a_high = a >> 31, a_low = a & ((1LL << 31) - 1);
        // ll b_high = b >> 31, b_low = b & ((1LL << 31) - 1);
        // ll high = a_high * b_high;
        // ll mid1 = a_high * b_low;
        // ll mid2 = a_low * b_high;
        // ll low = a_low * b_low;

        // ll result = (high << 62) + (mid1 << 31) + (mid2 << 31) + low;
        // result = (result + M) % M;  // Ensure the result is positive

        // return result;
        return mod(mod(a)*mod(b));
    }

public:
    // O(N)
    HashedString(const string &s) : p_hash(s.size() + 1) {
        while (pow.size() <= s.size()) { 
            pow.push_back(mod_mul(pow.back(), B)); 
        }
        p_hash[0] = 0;
        for (int i = 0; i < s.size(); i++) {
            p_hash[i + 1] = (mod_mul(p_hash[i], B) + s[i]) % M;
        }
    }

    // O(1)
    ll getHash(int start, int end) {
        ll raw_val = p_hash[end + 1] - mod_mul(p_hash[start], pow[end - start + 1]);
        return (raw_val + M) % M;
    }
};

vector<ll> HashedString::pow = {1};
const ll HashedString::B = 1999; // change the value of B from here

int main() {
    int idx1,idx2;
    string a,b;
    cin>>a>>b;
    if(a.size()<b.size()){
	    HashedString s1(a);
	    HashedString s2(b);
	    ll val1 = s1.getHash(0,a.size()-1);
	    bool first = true;
	    for(int i = 0;i<=b.size()-a.size();i++){
	    	ll val2 = s2.getHash(i,i+a.size()-1);
	    	if(val1==val2){
	    		if(first){
	    			idx1 = i;
	    			idx2 = i+a.size()-1;
	    			first = false;
	    		}
	    		else{
	    			idx2 = i+a.size()-1;
	    		}
	    		i = i+a.size()-1;
	    	}
	    }
	    ll ans = 0;
	    if(idx1>0){
	    	ans++;
	    }
	    if(idx2<b.size()-1){
	    	ans++;
	    }
	    ans += (idx2-idx1+1)/(a.size());
	    cout<<ans<<endl;
	}
	else if(a.size()>=b.size()){
		HashedString s1(b);
		HashedString s2(a);
		bool got = false;
		for(int i = 0;i<=a.size()-b.size();i++){
			if(s1.getHash(0,b.size()-1)==s2.getHash(i,i+b.size()-1)){
				got = true;
				break;
			}
		}
		if(got){
			cout<<1<<endl;
		}
		else{
			cout<<2<<endl;
		}
	}
}
